# snafu-opensource

Source delivery and acknowledgements for the open-source components of Snafu, an
image editor. Snafu ships several LGPL-licensed libraries as separate dynamic
libraries inside the app bundle's `Frameworks` folder, and this repository makes
their corresponding source available, as the LGPL requires. Each release of Snafu
republishes this repository, so its contents correspond to the libraries that
release ships.

## Contents

- `lame/`: the complete corresponding source of the modified LAME 3.100 that Snafu
  ships as `libmp3lame`. This is the upstream LAME 3.100 source with the changes
  recorded in `lame/SNAFU_PATCHES.md`; LAME's `COPYING` and `LICENSE` texts ship
  alongside it.
- `heif/`: the upstream source archives for the unmodified libheif and libde265
  builds Snafu ships as `libheif` and `libde265`, pinned by URL and SHA-256 in
  `heif/SOURCES.md`, with their license texts under `heif/licences/`.
- `notices/`: copies of `THIRD_PARTY_NOTICES.md` and `THIRD_PARTY_RUST_NOTICES.md`
  as they ship in the app bundle's `Resources` folder.

## Contact

Written source offers and questions about these components: snafu@stuible.com.
