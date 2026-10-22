# Third-party notices

ASExtHook retains its GPL version 3 license and the notices in individual source
files. Dependency licenses do not replace this repository's license.

- [Metamod](https://github.com/metamod-svencoop/metamod): see `metamod/LICENSE`
  and individual source/header notices. Legacy Metamod files credit Will Day and
  contain GPL version 2-or-later notices with a Half-Life engine linking exception.
  HLSDK files contain Valve/Id notices.
- [ASExt](https://github.com/metamod-svencoop/asext): see `asext/LICENSE` and
  individual source/header notices.
- Transitive dependencies include the customized AngelScript SDK, Capstone,
  procmap, RapidJSON, Chocobo1Hash and FormatValidation. Their notices remain in
  their source trees fetched by Git or CMake.
- SQLite is dynamically loaded from the Sven Co-op installation; this repository
  does not bundle or link an additional SQLite library.

The CMake, packaging, release and upstream-update workflows are adapted from
[astemplate](https://github.com/metamod-svencoop/astemplate), under its MIT license.
The original notice is preserved in `licenses/astemplate-LICENSE`.

Binary packages include dependency license/notice files under `build/licenses/`
and exact component commits in `build/dependencies.json`.
