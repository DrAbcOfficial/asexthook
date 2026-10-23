"""Verify and package a complete installed x86 plugin payload."""
import argparse
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tarfile
import tempfile
import zipfile

from upstream import git


def pe_exports(data, offset):
    optional = offset + 24
    sections = optional + struct.unpack_from("<H", data, offset + 20)[0]
    count = struct.unpack_from("<H", data, offset + 6)[0]

    def file_offset(rva):
        for index in range(count):
            size, address, raw_size, raw_offset = struct.unpack_from("<IIII", data, sections + index * 40 + 8)
            if address <= rva < address + max(size, raw_size):
                return raw_offset + rva - address
        raise ValueError("Invalid PE export address")

    directory = file_offset(struct.unpack_from("<I", data, optional + 96)[0])
    name_count = struct.unpack_from("<I", data, directory + 24)[0]
    names = file_offset(struct.unpack_from("<I", data, directory + 32)[0])
    exports = set()
    for index in range(name_count):
        name = file_offset(struct.unpack_from("<I", data, names + index * 4)[0])
        exports.add(data[name:data.index(b"\0", name)].decode("ascii"))
    return exports


def verify(prefix, platform):
    suffix = ".dll" if platform == "windows" else ".so"
    dlls = prefix / "addons/metamod/dlls"
    for component in ("metamod", "asext", "asexthook"):
        library = dlls / (component + suffix)
        data = library.read_bytes()
        if platform == "windows":
            offset = struct.unpack_from("<I", data, 0x3C)[0]
            if data[:2] != b"MZ" or data[offset:offset + 4] != b"PE\0\0" or struct.unpack_from("<H", data, offset + 4)[0] != 0x14C:
                raise ValueError(f"Not an x86 PE library: {library}")
            pdb = dlls / (component + ".pdb")
            if not pdb.is_file() or not pdb.stat().st_size:
                raise ValueError(f"Missing PDB: {pdb}")
            exports = pe_exports(data, offset)
        elif data[:5] != b"\x7fELF\x01" or struct.unpack_from("<H", data, 18)[0] != 3:
            raise ValueError(f"Not an i386 ELF library: {library}")
        else:
            output = subprocess.run(["nm", "-D", "--defined-only", str(library)],
                                    check=True, capture_output=True, text=True).stdout
            exports = {line.split()[-1] for line in output.splitlines() if line.strip()}
        required = {"GetEntityAPI2"} if component == "metamod" else {"Meta_Query", "Meta_Attach", "Meta_Detach"}
        if not required <= exports or not {"GiveFnptrsToDll", "_GiveFnptrsToDll@8"} & exports:
            raise ValueError(f"Missing engine/Metamod entrypoints: {library}")
        if component == "asext" and not {"ASEXT_CallHook", "ASEXT_CallCASBaseCallable",
                                        "ASEXT_RegisterDocInitCallback", "ASEXT_RegisterHook",
                                        "ASEXT_RegisterObjectMethod", "ASEXT_RegisterObjectMethodEx",
                                        "ASEXT_RegisterObjectBehaviourEx", "ASEXT_RegisterObjectType",
                                        "ASEXT_RegisterObjectProperty", "ASEXT_RegisterEnum",
                                        "ASEXT_RegisterEnumValue", "ASEXT_RegisterFuncDef",
                                        "ASEXT_GetCurrentContext", "ASEXT_GetServerManager",
                                        "ASEXT_CreateCASFunction", "ASEXT_CStringAssign",
                                        "ASEXT_CASBaseManager_GetTypeInfoByName"} <= exports:
            raise ValueError("ASExt is missing required ASExtHook API exports")
    root = Path(__file__).resolve().parents[1]
    for component in ("asext", "asexthook"):
        gamedata = prefix / "addons/metamod/gamedata" / component
        manifest = root / (
            "asext/scripts/manifests/asext.json" if component == "asext"
            else "scripts/manifests/asexthook.json")
        subprocess.run([sys.executable, "-B", str(root / "metamod/scripts/sync-gamedata.py"),
                        "--manifest", str(manifest), "--target-dir", str(gamedata), "--validate-only"], check=True)
    for file in ("addons/metamod/plugins.ini.example", "examples/CSQLite.as", "docs/index.html",
                 "assets/logo.png", "README.md", "LICENSE", "THIRD_PARTY.md", "licenses/astemplate-LICENSE"):
        if not (prefix / file).is_file():
            raise ValueError(f"Missing installed file: {file}")


def copy_notices(root, build_tree, destination):
    sources = [("metamod", root / "metamod"), ("asext", root / "asext")]
    sources += [(path.name, path) for path in (build_tree / "_deps").glob("*-src")]
    for name, source in sources:
        for directory, folders, files in os.walk(source):
            folders[:] = [folder for folder in folders if folder not in (".git", "build", "__pycache__")]
            for file in files:
                if file.upper().startswith(("LICENSE", "COPYING", "COPYRIGHT", "NOTICE")):
                    path = Path(directory) / file
                    target = destination / name / path.relative_to(source)
                    target.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copy2(path, target)
    # Retain the legacy SDK's per-file license and engine exception verbatim.
    for relative in ("include/meta_api.h", "include/HLSDK/dlls/extdll.h"):
        target = destination / "metamod" / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(root / "metamod" / relative, target)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", choices=["Debug", "Release"], required=True)
    parser.add_argument("--platform", choices=["windows", "linux"], required=True)
    parser.add_argument("--prefix", type=Path, help="Installed payload (default: install/x86/<config>)")
    parser.add_argument("--build-dir", type=Path, help="Native build tree (default: build/x86/<config>)")
    args = parser.parse_args()
    root = Path.cwd()
    prefix = args.prefix or root / "install/x86" / args.config
    build_tree = args.build_dir or root / "build/x86" / args.config
    verify(prefix, args.platform)
    output = root / "build/packages"
    output.mkdir(parents=True, exist_ok=True)
    source = git(root, "rev-parse", "HEAD", check=False)
    metadata = {"repository": os.environ.get("GITHUB_REPOSITORY", "hzqst/asexthook"),
                "source_sha": source.stdout.strip() if source.returncode == 0 else None,
                "uncommitted": bool(git(root, "status", "--porcelain").stdout.strip()),
                "platform": args.platform, "configuration": args.config,
                "components": {name: {"sha": git(root / name, "rev-parse", "HEAD").stdout.strip(),
                                      "url": git(root / name, "remote", "get-url", "origin").stdout.strip()}
                               for name in ("metamod", "asext")}}
    with tempfile.TemporaryDirectory(prefix="asexthook-package-") as temporary:
        stage = Path(temporary)
        shutil.copytree(prefix, stage / "build")
        copy_notices(root, build_tree, stage / "build/licenses")
        (stage / "build/dependencies.json").write_text(json.dumps(metadata, indent=2) + "\n", encoding="utf-8")
        name = f"asexthook-{args.platform}-x86-{args.config}"
        if args.platform == "windows":
            archive = output / (name + ".zip")
            with zipfile.ZipFile(archive, "w", zipfile.ZIP_DEFLATED) as stream:
                for file in sorted((stage / "build").rglob("*")):
                    if file.is_file():
                        stream.write(file, file.relative_to(stage))
            with zipfile.ZipFile(archive) as stream:
                if stream.testzip() is not None:
                    raise ValueError("ZIP integrity check failed")
        else:
            archive = output / (name + ".tar.gz")
            with tarfile.open(archive, "w:gz") as stream:
                stream.add(stage / "build", arcname="build")
            with tarfile.open(archive) as stream:
                if not stream.getmember("build/addons/metamod/dlls/asexthook.so").isfile():
                    raise ValueError("Plugin missing from archive")
    print(f"Verified package: {archive}")


if __name__ == "__main__":
    main()
