/*
 * Build configuration for the vendored LAME on macOS and Linux. Upstream's configure
 * script writes this file; it's checked in so the build needs no configure step.
 * Windows uses config/windows/config.h, upstream's configMS.h.
 */
#ifndef SNAFU_LAME_CONFIG_H
#define SNAFU_LAME_CONFIG_H

#define SIZEOF_DOUBLE 8
#define SIZEOF_FLOAT 4
#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define SIZEOF_LONG_DOUBLE 16
#define SIZEOF_SHORT 2
#define SIZEOF_UNSIGNED_INT 4
#define SIZEOF_UNSIGNED_LONG 8
#define SIZEOF_UNSIGNED_SHORT 2

#define STDC_HEADERS 1
#define HAVE_ERRNO_H 1
#define HAVE_FCNTL_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIMITS_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_STRCHR 1
#define HAVE_MEMCPY 1
#define PACKAGE "lame"
#define PROTOTYPES 1
#define USE_FAST_LOG 1
#define LAME_LIBRARY_BUILD 1

typedef long double ieee854_float80_t;
typedef double ieee754_float64_t;
typedef float ieee754_float32_t;

#ifdef HAVE_MPGLIB
# define DECODE_ON_THE_FLY 1
#endif

#endif
