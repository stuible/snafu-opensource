# libheif and libde265 source pins

Snafu builds libheif and libde265 unmodified from the upstream source archives
pinned below and ships them as dynamic libraries in the app bundle's `Frameworks`
folder. Each release of Snafu republishes this repository, so these pins describe
the archives behind the release you have; the same table appears in
`notices/THIRD_PARTY_NOTICES.md`.

| Library | Version | License | Upstream source |
| --- | --- | --- | --- |
| libheif | 1.21.2 | LGPL-3.0 | https://github.com/strukturag/libheif/tree/v1.21.2 (archive SHA-256 `79996de959d28ca82ef070c382304683f5cdaf04cbe2953a74587160a3710a36`) |
| libde265 | 1.0.16 | LGPL-3.0 | https://github.com/strukturag/libde265/tree/v1.0.16 (archive SHA-256 `ed12c931759c1575848832f70db5071a001ac813db4e4f568ee08aef6e234d4e`) |

`licences/` holds the license texts extracted from those archives. Source is also
offered on request to snafu@stuible.com.
