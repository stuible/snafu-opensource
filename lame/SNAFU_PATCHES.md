# Snafu's changes to LAME 3.100

Snafu vendors upstream LAME 3.100 (tarball sha256
`ddfe36cab873794038ae2c1210557ad34857a4b6bdc515785d1da9e175b1da1e`) for the MP3 effect.
Everything here is upstream unless listed below. LAME is licensed under the LGPL 2
(`COPYING` and `LICENSE` in this folder).

## What is vendored

- `libmp3lame/`: the encoder sources and headers, plus `vector/lame_intrin.h`, which
  `fft.c` and `quantize.c` include. The x86 assembly (`i386/`), the SSE and AltiVec
  vector routines (`vector/*.c`), the autotools files and `lame.rc` are not built.
- `mpglib/`: LAME's own decoder, used to decode the round trip.
- `include/`: `lame.h`, the export list `libmp3lame.sym` and `lame.def` (the Windows
  export file, with the two new entry points).
- `config/unix/config.h` (macOS and Linux) and `config/windows/config.h` (upstream's
  `configMS.h`). Both are checked in; nothing runs `configure`.

## Build

`build.rs` compiles every `libmp3lame/*.c` and `mpglib/*.c` with `HAVE_CONFIG_H` and
`HAVE_MPGLIB` defined, at `-O2`, and links them into a dynamic library. The library is
never linked statically: the app loads it from its bundle or next to the executable.

## Changes

1. **Bit-target scale (Turbo).** `lame_set_bitrate_squish_bends(gfp, squish)` stores the
   scale in `lame_internal_flags::bend_squish`. `outer_loop` in `quantize.c` multiplies its
   bit target by it before anything else, so each granule gets fewer bits and the frame size
   stays the same. Snafu passes `(1 - turbo)^3`.
2. **Masking tilt.** `lame_set_threshold_bias_bends(gfp, tilt)` stores the tilt in
   `bend_tilt`. `apply_tilt_bend` in `encoder.c` runs on the chosen masking table, before
   the iteration loops use it. For each long-block scalefactor band `i` (0 to 21) it
   multiplies `thm.l[i]` by `10^(-tilt*(i-11))`, and for a negative tilt also by
   `10^(6*(-tilt))`. A result that isn't finite is written as zero. Short blocks are not
   changed.
3. **Defaults.** `lame_init_internal_flags` sets `bend_squish` to 1 and `bend_tilt` to 0, so
   every encoder starts with both bends off, and the setters are called after `lame_init`.
4. **Thread safety.** `hip_decode1` (and the other `hip_decode*` and `lame_decode*` entry
   points) wrote through `static char out[...]` buffers in `libmp3lame/mpglib_interface.c`,
   so concurrent decodes shared one buffer and their output depended on timing. The buffers
   are now per-call locals. Upstream's `lame_decode_init` path (the `static MPSTR mp`) is
   not used by Snafu. Encoders rewrite LAME's shared quantiser tables with the same values
   on every `iteration_init`; that's benign, and it's upstream's design.
   `bitstream.c` writes a debug counter (`hogege`) that nothing reads; it can't change output.
5. **Exports.** The two setters are declared in `include/lame.h`, and listed in
   `include/libmp3lame.sym` and `include/lame.def`.

## Verified

- All 28 library and decoder sources compile with clang at `-O2`. Upstream's warnings
  remain; `build.rs` suppresses warnings for the vendored code.
- Rendering through the library gives the spike's cut-offs and error statistics (see
  `docs/plans/archive/MP3_EFFECT_PLAN.md`, Results).
- `config/windows/config.h` drops upstream's forced `HAVE_XMMINTRIN_H` on x64. That
  setting calls the SSE quantizer in `vector/xmm_quantize_sub.c`, which isn't vendored, so
  the link failed. Windows now uses the same scalar path as macOS.
- A cross build from macOS (`cargo xwin check --target x86_64-pc-windows-msvc`) compiles
  and links the library. A native MSVC build and running it on Windows aren't verified here.
