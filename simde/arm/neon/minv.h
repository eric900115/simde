/* SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Copyright:
 *   2020      Evan Nemerson <evan@nemerson.com>
 *   2023      Yung-Cheng Su <eric20607@gapp.nthu.edu.tw>
 *   2023      Yi-Yen Chung <eric681@andestech.com> (Copyright owned by Andes Technology)
 */

#if !defined(SIMDE_ARM_NEON_MINV_H)
#define SIMDE_ARM_NEON_MINV_H

#include "types.h"
#include <float.h>

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde_float16_t
simde_vminv_f16(simde_float16x4_t a) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    return vminv_f16(a);
  #else
    simde_float32_t r;
    simde_float16x4_private a_ = simde_float16x4_to_private(a);

    r = simde_float16_to_float32(SIMDE_INFINITYHF);
    #if defined(SIMDE_FAST_NANS)
      SIMDE_VECTORIZE_REDUCTION(min:r)
    #else
      SIMDE_VECTORIZE
    #endif
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      simde_float32_t a32 = simde_float16_to_float32(a_.values[i]);
      #if defined(SIMDE_FAST_NANS)
        r = a32 < r ? a32 : r;
      #else
        r = a32 < r ? a32 : (a32 >= r ? r : ((a32 == a32) ? r : a32));
      #endif
    }

    return simde_float16_from_float32(r);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminv_f16
  #define vminv_f16(v) simde_vminv_f16(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float32_t
simde_vminv_f32(simde_float32x2_t a) {
  simde_float32_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminv_f32(a);
  #else
    simde_float32x2_private a_ = simde_float32x2_to_private(a);

    r = SIMDE_MATH_INFINITYF;
    #if defined(SIMDE_FAST_NANS)
      SIMDE_VECTORIZE_REDUCTION(min:r)
    #else
      SIMDE_VECTORIZE
    #endif
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      #if defined(SIMDE_FAST_NANS)
        r = a_.values[i] < r ? a_.values[i] : r;
      #else
        r = (a_.values[i] < r) ? a_.values[i] : ((a_.values[i] >= r) ? r : ((a_.values[i] == a_.values[i]) ? r : a_.values[i]));
      #endif
    }
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminv_f32
  #define vminv_f32(v) simde_vminv_f32(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int8_t
simde_vminv_s8(simde_int8x8_t a) {
  int8_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminv_s8(a);
  #else
    simde_int8x8_private a_ = simde_int8x8_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = INT8_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminv_s8
  #define vminv_s8(v) simde_vminv_s8(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int16_t
simde_vminv_s16(simde_int16x4_t a) {
  int16_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminv_s16(a);
  #else
    simde_int16x4_private a_ = simde_int16x4_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = INT16_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminv_s16
  #define vminv_s16(v) simde_vminv_s16(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int32_t
simde_vminv_s32(simde_int32x2_t a) {
  int32_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminv_s32(a);
  #else
    simde_int32x2_private a_ = simde_int32x2_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = INT32_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminv_s32
  #define vminv_s32(v) simde_vminv_s32(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
uint8_t
simde_vminv_u8(simde_uint8x8_t a) {
  uint8_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminv_u8(a);
  #else
    simde_uint8x8_private a_ = simde_uint8x8_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = UINT8_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminv_u8
  #define vminv_u8(v) simde_vminv_u8(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
uint16_t
simde_vminv_u16(simde_uint16x4_t a) {
  uint16_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminv_u16(a);
  #else
    simde_uint16x4_private a_ = simde_uint16x4_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = UINT16_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminv_u16
  #define vminv_u16(v) simde_vminv_u16(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
uint32_t
simde_vminv_u32(simde_uint32x2_t a) {
  uint32_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminv_u32(a);
  #else
    simde_uint32x2_private a_ = simde_uint32x2_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = UINT32_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminv_u32
  #define vminv_u32(v) simde_vminv_u32(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float16_t
simde_vminvq_f16(simde_float16x8_t a) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    return vminvq_f16(a);
  #else
    simde_float32_t r;
    simde_float16x8_private a_ = simde_float16x8_to_private(a);

    r = simde_float16_to_float32(SIMDE_INFINITYHF);
    #if defined(SIMDE_FAST_NANS)
      SIMDE_VECTORIZE_REDUCTION(min:r)
    #else
      SIMDE_VECTORIZE
    #endif
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      simde_float32_t a32 = simde_float16_to_float32(a_.values[i]);
      #if defined(SIMDE_FAST_NANS)
        r = a32 < r ? a32 : r;
      #else
        r = a32 < r ? a32 : (a32 >= r ? r : ((a32 == a32) ? r : a32));
      #endif
    }

    return simde_float16_from_float32(r);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_f16
  #define vminvq_f16(v) simde_vminvq_f16(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float32_t
simde_vminvq_f32(simde_float32x4_t a) {
  simde_float32_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminvq_f32(a);
  #else
    simde_float32x4_private a_ = simde_float32x4_to_private(a);

    r = SIMDE_MATH_INFINITYF;
    #if defined(SIMDE_FAST_NANS)
      SIMDE_VECTORIZE_REDUCTION(min:r)
    #else
      SIMDE_VECTORIZE
    #endif
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      #if defined(SIMDE_FAST_NANS)
        r = a_.values[i] < r ? a_.values[i] : r;
      #else
        r = (a_.values[i] < r) ? a_.values[i] : ((a_.values[i] >= r) ? r : ((a_.values[i] == a_.values[i]) ? r : a_.values[i]));
      #endif
    }
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_f32
  #define vminvq_f32(v) simde_vminvq_f32(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_float64_t
simde_vminvq_f64(simde_float64x2_t a) {
  simde_float64_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminvq_f64(a);
  #else
    simde_float64x2_private a_ = simde_float64x2_to_private(a);

    r = SIMDE_MATH_INFINITY;
    #if defined(SIMDE_FAST_NANS)
      SIMDE_VECTORIZE_REDUCTION(min:r)
    #else
      SIMDE_VECTORIZE
    #endif
    for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
      #if defined(SIMDE_FAST_NANS)
        r = a_.values[i] < r ? a_.values[i] : r;
      #else
        r = (a_.values[i] < r) ? a_.values[i] : ((a_.values[i] >= r) ? r : ((a_.values[i] == a_.values[i]) ? r : a_.values[i]));
      #endif
    }
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_f64
  #define vminvq_f64(v) simde_vminvq_f64(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int8_t
simde_vminvq_s8(simde_int8x16_t a) {
  int8_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminvq_s8(a);
  #else
    simde_int8x16_private a_ = simde_int8x16_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = INT8_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_s8
  #define vminvq_s8(v) simde_vminvq_s8(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int16_t
simde_vminvq_s16(simde_int16x8_t a) {
  int16_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminvq_s16(a);
  #else
    simde_int16x8_private a_ = simde_int16x8_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = INT16_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_s16
  #define vminvq_s16(v) simde_vminvq_s16(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
int32_t
simde_vminvq_s32(simde_int32x4_t a) {
  int32_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminvq_s32(a);
  #else
    simde_int32x4_private a_ = simde_int32x4_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = INT32_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_s32
  #define vminvq_s32(v) simde_vminvq_s32(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
uint8_t
simde_vminvq_u8(simde_uint8x16_t a) {
  uint8_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminvq_u8(a);
  #else
    simde_uint8x16_private a_ = simde_uint8x16_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = UINT8_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_u8
  #define vminvq_u8(v) simde_vminvq_u8(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
uint16_t
simde_vminvq_u16(simde_uint16x8_t a) {
  uint16_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminvq_u16(a);
  #else
    simde_uint16x8_private a_ = simde_uint16x8_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = UINT16_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_u16
  #define vminvq_u16(v) simde_vminvq_u16(v)
#endif

SIMDE_FUNCTION_ATTRIBUTES
uint32_t
simde_vminvq_u32(simde_uint32x4_t a) {
  uint32_t r;

  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    r = vminvq_u32(a);
  #else
    simde_uint32x4_private a_ = simde_uint32x4_to_private(a);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_SCALAR) && HEDLEY_HAS_BUILTIN(__builtin_reduce_min)
      r = __builtin_reduce_min(a_.values);
    #else
      r = UINT32_MAX;
      SIMDE_VECTORIZE_REDUCTION(min:r)
      for (size_t i = 0 ; i < (sizeof(a_.values) / sizeof(a_.values[0])) ; i++) {
        r = a_.values[i] < r ? a_.values[i] : r;
      }
    #endif
  #endif

  return r;
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vminvq_u32
  #define vminvq_u32(v) simde_vminvq_u32(v)
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif /* !defined(SIMDE_ARM_NEON_MINV_H) */
