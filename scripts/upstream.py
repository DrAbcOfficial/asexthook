"""Detect and publish validated ASExt release updates; no third-party packages."""
import argparse
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import urllib.error
import urllib.request


def git(root, *args, check=True):
    return subprocess.run(["git", "-C", str(root), *args], check=check,
                          capture_output=True, text=True)


def sha(value):
    if not isinstance(value, str) or not re.fullmatch(r"[0-9a-f]{40}", value):
        raise ValueError("Expected a full Git commit SHA")
    return value


def api(path, missing_ok=False):
    token = os.environ.get("GH_TOKEN", "")
    request = urllib.request.Request(
        "https://api.github.com/" + path,
        headers={"Accept": "application/vnd.github+json",
                 "Authorization": "Bearer " + token,
                 "X-GitHub-Api-Version": "2022-11-28"})
    try:
        with urllib.request.urlopen(request, timeout=30) as response:
            return json.load(response)
    except urllib.error.HTTPError as error:
        if missing_ok and error.code == 404:
            return None
        raise RuntimeError(f"GitHub API request failed: HTTP {error.code}") from error


def release_candidate(repository, branch, base, release, existing_tag, resolve):
    """Keep release identity independent from changing branch tips."""
    if release is None or release.get("draft") or release.get("prerelease"):
        return None
    release_id = release["id"]
    if not isinstance(release_id, int) or release_id <= 0:
        raise ValueError("Invalid release ID")
    tag = f"asext-release-{release_id}"
    if existing_tag(tag):
        return None
    asext_sha, metamod_sha = resolve(release["tag_name"])
    return {"repository": repository, "branch": branch, "base_sha": sha(base),
            "release_id": release_id, "release_tag": release["tag_name"],
            "release_url": release["html_url"], "template_tag": tag,
            "asext_sha": sha(asext_sha), "metamod_sha": sha(metamod_sha)}


def detect(root, repository, branch):
    release = api("repos/metamod-svencoop/asext/releases/latest", missing_ok=True)

    def existing(tag):
        return api(f"repos/{repository}/git/ref/tags/{tag}", missing_ok=True) is not None

    def resolve(tag):
        # Fetch the tag itself, not target_commitish (which can name a moving branch).
        tag_ref = "refs/tags/" + tag
        git(root, "check-ref-format", tag_ref)
        git(root / "asext", "fetch", "origin", tag_ref)
        asext = git(root / "asext", "rev-parse", "FETCH_HEAD^{commit}").stdout.strip()
        metamod = api("repos/metamod-svencoop/metamod/commits/main")["sha"]
        return asext, metamod

    return release_candidate(repository, branch,
                             git(root, "rev-parse", "HEAD").stdout.strip(),
                             release, existing, resolve)


def checkout_dependencies(root, asext_sha, metamod_sha):
    for name, commit in (("asext", sha(asext_sha)), ("metamod", sha(metamod_sha))):
        git(root / name, "fetch", "origin", commit)
        git(root / name, "checkout", "--detach", commit)
        git(root / name, "submodule", "sync", "--recursive")
        git(root / name, "submodule", "update", "--init", "--recursive")


def publish(root, candidate, repository, branch, validated=False):
    if not validated:
        raise ValueError("Both platform builds must succeed before publishing")
    if candidate["repository"] != repository or candidate["branch"] != branch:
        raise ValueError("Candidate belongs to another repository or branch")
    tag = candidate["template_tag"]
    if tag != f"asext-release-{candidate['release_id']}" or not re.fullmatch(r"asext-release-[1-9][0-9]*", tag):
        raise ValueError("Invalid update tag")
    git(root, "check-ref-format", "refs/heads/" + branch)
    git(root, "fetch", "origin", "refs/heads/" + branch)
    if git(root, "rev-parse", "FETCH_HEAD").stdout.strip() != sha(candidate["base_sha"]):
        return "stale"
    if git(root, "ls-remote", "--tags", "origin", "refs/tags/" + tag).stdout.strip():
        return "already-published"
    if git(root, "status", "--porcelain").stdout.strip():
        raise ValueError("Publishing requires a clean checkout")
    git(root, "checkout", "--detach", candidate["base_sha"])
    checkout_dependencies(root, candidate["asext_sha"], candidate["metamod_sha"])
    git(root, "add", "asext", "metamod")
    difference = git(root, "diff", "--cached", "--quiet", check=False)
    if difference.returncode not in (0, 1):
        raise subprocess.CalledProcessError(difference.returncode, difference.args, stderr=difference.stderr)
    if difference.returncode == 1:
        message = (f"chore(deps): update for asext release {candidate['release_id']}\n\n"
                   f"ASExt release: {candidate['release_url']}\n"
                   f"ASExt: {candidate['asext_sha']}\nMetamod: {candidate['metamod_sha']}\n\n"
                   "Co-Authored-By: Codex <codex@openai.com>")
        git(root, "-c", "user.name=github-actions[bot]", "-c",
            "user.email=41898282+github-actions[bot]@users.noreply.github.com",
            "commit", "-m", message)
    git(root, "tag", tag)
    # No force: a competing branch update rejects the entire atomic push.
    git(root, "push", "--atomic", "origin", "HEAD:refs/heads/" + branch, "refs/tags/" + tag)
    return "published"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=["detect", "publish", "checkout"])
    parser.add_argument("--candidate", type=Path, default=Path("build/upstream-candidate.json"))
    parser.add_argument("--validated", action="store_true")
    parser.add_argument("--asext-sha")
    parser.add_argument("--metamod-sha")
    args = parser.parse_args()
    root = Path.cwd()
    if args.command == "checkout":
        checkout_dependencies(root, args.asext_sha, args.metamod_sha)
        return
    repository = os.environ["GITHUB_REPOSITORY"]
    branch = os.environ["DEFAULT_BRANCH"]
    if args.command == "publish":
        result = publish(root, json.loads(args.candidate.read_text()), repository, branch, args.validated)
        print("Update result:", result)
        return
    candidate = detect(root, repository, branch)
    outputs = {"changed": "true" if candidate else "false"}
    if candidate:
        args.candidate.parent.mkdir(parents=True, exist_ok=True)
        args.candidate.write_text(json.dumps(candidate, indent=2) + "\n", encoding="utf-8")
        outputs.update({key: candidate[key] for key in ("base_sha", "asext_sha", "metamod_sha")})
    output = os.environ.get("GITHUB_OUTPUT")
    if output:
        with open(output, "a", encoding="utf-8") as stream:
            for key, value in outputs.items():
                stream.write(f"{key}={value}\n")
    print("New ASExt release detected." if candidate else "No unprocessed stable ASExt release.")


if __name__ == "__main__":
    try:
        main()
    except subprocess.CalledProcessError as error:
        print(error.stderr or str(error), file=sys.stderr)
        sys.exit(error.returncode)
