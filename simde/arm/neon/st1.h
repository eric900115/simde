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
 *   2023      Yi-Yen Chung <eric681@andestech.com> (Copyright owned by Andes Technology)
 *   2023      Chi-Wei Chu <wewe5215@gapp.nthu.edu.tw> (Copyright owned by NTHU pllab)
 */

#if !defined(SIMDE_ARM_NEON_ST1_H)
#define SIMDE_ARM_NEON_ST1_H

#include "types.h"

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_f16(simde_float16_t ptr[HEDLEY_ARRAY_PARAM(4)], simde_float16x4_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    vst1_f16(ptr, val);
  #else
    simde_float16x4_private val_ = simde_float16x4_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE) && SIMDE_ARCH_RISCV_ZVFH
      __riscv_vse16_v_f16m1((_Float16 *)ptr , val_.sv64 , 4);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_f16
  #define vst1_f16(a, b) simde_vst1_f16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_f32(simde_float32_t ptr[HEDLEY_ARRAY_PARAM(2)], simde_float32x2_t val) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    vst1_f32(ptr, val);
  #else
    simde_float32x2_private val_ = simde_float32x2_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse32_v_f32m1(ptr , val_.sv64 , 2);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_f32
  #define vst1_f32(a, b) simde_vst1_f32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_f64(simde_float64_t ptr[HEDLEY_ARRAY_PARAM(1)], simde_float64x1_t val) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    vst1_f64(ptr, val);
  #else
    simde_float64x1_private val_ = simde_float64x1_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse64_v_f64m1(ptr , val_.sv64 , 1);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vst1_f64
  #define vst1_f64(a, b) simde_vst1_f64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_s8(int8_t ptr[HEDLEY_ARRAY_PARAM(8)], simde_int8x8_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_s8(ptr, val);
  #else
    simde_int8x8_private val_ = simde_int8x8_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse8_v_i8m1(ptr , val_.sv64 , 8);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_s8
  #define vst1_s8(a, b) simde_vst1_s8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_s16(int16_t ptr[HEDLEY_ARRAY_PARAM(4)], simde_int16x4_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_s16(ptr, val);
  #else
    simde_int16x4_private val_ = simde_int16x4_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse16_v_i16m1(ptr , val_.sv64 , 4);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_s16
  #define vst1_s16(a, b) simde_vst1_s16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_s32(int32_t ptr[HEDLEY_ARRAY_PARAM(2)], simde_int32x2_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_s32(ptr, val);
  #else
    simde_int32x2_private val_ = simde_int32x2_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse32_v_i32m1(ptr , val_.sv64 , 2);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_s32
  #define vst1_s32(a, b) simde_vst1_s32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_s64(int64_t ptr[HEDLEY_ARRAY_PARAM(1)], simde_int64x1_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_s64(ptr, val);
  #else
    simde_int64x1_private val_ = simde_int64x1_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse64_v_i64m1(ptr , val_.sv64 , 1);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_s64
  #define vst1_s64(a, b) simde_vst1_s64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_u8(uint8_t ptr[HEDLEY_ARRAY_PARAM(8)], simde_uint8x8_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_u8(ptr, val);
  #else
    simde_uint8x8_private val_ = simde_uint8x8_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse8_v_u8m1(ptr , val_.sv64 , 8);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_u8
  #define vst1_u8(a, b) simde_vst1_u8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_u16(uint16_t ptr[HEDLEY_ARRAY_PARAM(4)], simde_uint16x4_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_u16(ptr, val);
  #else
    simde_uint16x4_private val_ = simde_uint16x4_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse16_v_u16m1(ptr , val_.sv64 , 4);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_u16
  #define vst1_u16(a, b) simde_vst1_u16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_u32(uint32_t ptr[HEDLEY_ARRAY_PARAM(2)], simde_uint32x2_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_u32(ptr, val);
  #else
    simde_uint32x2_private val_ = simde_uint32x2_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse32_v_u32m1(ptr , val_.sv64 , 2);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_u32
  #define vst1_u32(a, b) simde_vst1_u32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_u64(uint64_t ptr[HEDLEY_ARRAY_PARAM(1)], simde_uint64x1_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_u64(ptr, val);
  #else
    simde_uint64x1_private val_ = simde_uint64x1_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse64_v_u64m1(ptr , val_.sv64 , 1);
    #else
      simde_memcpy(ptr, &val_, 8);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_u64
  #define vst1_u64(a, b) simde_vst1_u64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_f16(simde_float16_t ptr[HEDLEY_ARRAY_PARAM(8)], simde_float16x8_t val) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    vst1q_f16(ptr, val);
  #else
    simde_float16x8_private val_ = simde_float16x8_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE) && SIMDE_ARCH_RISCV_ZVFH
      __riscv_vse16_v_f16m1((_Float16 *)ptr , val_.sv128 , 8);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vst1q_f16
  #define vst1q_f16(a, b) simde_vst1q_f16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_f32(simde_float32_t ptr[HEDLEY_ARRAY_PARAM(4)], simde_float32x4_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_f32(ptr, val);
  #else
    simde_float32x4_private val_ = simde_float32x4_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse32_v_f32m1(ptr , val_.sv128 , 4);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_f32
  #define vst1q_f32(a, b) simde_vst1q_f32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_f64(simde_float64_t ptr[HEDLEY_ARRAY_PARAM(2)], simde_float64x2_t val) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    vst1q_f64(ptr, val);
  #else
    simde_float64x2_private val_ = simde_float64x2_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse64_v_f64m1(ptr , val_.sv128 , 2);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vst1q_f64
  #define vst1q_f64(a, b) simde_vst1q_f64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_s8(int8_t ptr[HEDLEY_ARRAY_PARAM(16)], simde_int8x16_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_s8(ptr, val);
  #else
    simde_int8x16_private val_ = simde_int8x16_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse8_v_i8m1(ptr , val_.sv128 , 16);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_s8
  #define vst1q_s8(a, b) simde_vst1q_s8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_s16(int16_t ptr[HEDLEY_ARRAY_PARAM(8)], simde_int16x8_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_s16(ptr, val);
  #else
    simde_int16x8_private val_ = simde_int16x8_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse16_v_i16m1(ptr , val_.sv128 , 8);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_s16
  #define vst1q_s16(a, b) simde_vst1q_s16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_s32(int32_t ptr[HEDLEY_ARRAY_PARAM(4)], simde_int32x4_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_s32(ptr, val);
  #else
    simde_int32x4_private val_ = simde_int32x4_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse32_v_i32m1(ptr , val_.sv128 , 4);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_s32
  #define vst1q_s32(a, b) simde_vst1q_s32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_s64(int64_t ptr[HEDLEY_ARRAY_PARAM(2)], simde_int64x2_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_s64(ptr, val);
  #else
    simde_int64x2_private val_ = simde_int64x2_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse64_v_i64m1(ptr , val_.sv128 , 2);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_s64
  #define vst1q_s64(a, b) simde_vst1q_s64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_u8(uint8_t ptr[HEDLEY_ARRAY_PARAM(16)], simde_uint8x16_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_u8(ptr, val);
  #else
    simde_uint8x16_private val_ = simde_uint8x16_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse8_v_u8m1(ptr , val_.sv128 , 16);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_u8
  #define vst1q_u8(a, b) simde_vst1q_u8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_u16(uint16_t ptr[HEDLEY_ARRAY_PARAM(8)], simde_uint16x8_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_u16(ptr, val);
  #else
    simde_uint16x8_private val_ = simde_uint16x8_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse16_v_u16m1(ptr , val_.sv128 , 8);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_u16
  #define vst1q_u16(a, b) simde_vst1q_u16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_u32(uint32_t ptr[HEDLEY_ARRAY_PARAM(4)], simde_uint32x4_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_u32(ptr, val);
  #else
    simde_uint32x4_private val_ = simde_uint32x4_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse32_v_u32m1(ptr , val_.sv128 , 4);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_u32
  #define vst1q_u32(a, b) simde_vst1q_u32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_u64(uint64_t ptr[HEDLEY_ARRAY_PARAM(2)], simde_uint64x2_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_u64(ptr, val);
  #else
    simde_uint64x2_private val_ = simde_uint64x2_to_private(val);

    #if defined(SIMDE_WASM_SIMD128_NATIVE)
      wasm_v128_store(ptr, val_.v128);
    #elif defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse64_v_u64m1(ptr , val_.sv128 , 2);
    #else
      simde_memcpy(ptr, &val_, 16);
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_u64
  #define vst1q_u64(a, b) simde_vst1q_u64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_p8(simde_poly8_t ptr[HEDLEY_ARRAY_PARAM(8)], simde_poly8x8_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_p8(ptr, val);
  #else
    simde_poly8x8_private val_ = simde_poly8x8_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse8_v_u8m1(ptr , val_.sv64 , 8);
    #else
      simde_memcpy(ptr, &val_, sizeof(val_));
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_p8
  #define vst1_p8(a, b) simde_vst1_p8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_p16(simde_poly16_t ptr[HEDLEY_ARRAY_PARAM(4)], simde_poly16x4_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1_p16(ptr, val);
  #else
    simde_poly16x4_private val_ = simde_poly16x4_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse16_v_u16m1(ptr , val_.sv64 , 4);
    #else
      simde_memcpy(ptr, &val_, sizeof(val_));
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1_p16
  #define vst1_p16(a, b) simde_vst1_p16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_p64(simde_poly64_t ptr[HEDLEY_ARRAY_PARAM(1)], simde_poly64x1_t val) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE)
    vst1_p64(ptr, val);
  #else
    simde_poly64x1_private val_ = simde_poly64x1_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse64_v_u64m1(ptr , val_.sv64 , 1);
    #else
      simde_memcpy(ptr, &val_, sizeof(val_));
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES)
  #undef vst1_p64
  #define vst1_p64(a, b) simde_vst1_p64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_p8(simde_poly8_t ptr[HEDLEY_ARRAY_PARAM(16)], simde_poly8x16_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_p8(ptr, val);
  #else
    simde_poly8x16_private val_ = simde_poly8x16_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse8_v_u8m1(ptr , val_.sv128 , 16);
    #else
      simde_memcpy(ptr, &val_, sizeof(val_));
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_p8
  #define vst1q_p8(a, b) simde_vst1q_p8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_p16(simde_poly16_t ptr[HEDLEY_ARRAY_PARAM(8)], simde_poly16x8_t val) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    vst1q_p16(ptr, val);
  #else
    simde_poly16x8_private val_ = simde_poly16x8_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse16_v_u16m1(ptr , val_.sv128 , 8);
    #else
      simde_memcpy(ptr, &val_, sizeof(val_));
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vst1q_p16
  #define vst1q_p16(a, b) simde_vst1q_p16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_p64(simde_poly64_t ptr[HEDLEY_ARRAY_PARAM(2)], simde_poly64x2_t val) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE)
    vst1q_p64(ptr, val);
  #else
    simde_poly64x2_private val_ = simde_poly64x2_to_private(val);
    #if defined(SIMDE_RISCV_V_NATIVE)
      __riscv_vse64_v_u64m1(ptr , val_.sv128 , 2);
    #else
      simde_memcpy(ptr, &val_, sizeof(val_));
    #endif
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES)
  #undef vst1q_p64
  #define vst1q_p64(a, b) simde_vst1q_p64((a), (b))
#endif

#if !defined(SIMDE_TARGET_NOT_SUPPORT_INT128_TYPE)
SIMDE_FUNCTION_ATTRIBUTES
void
simde_vstrq_p128(simde_poly128_t ptr[HEDLEY_ARRAY_PARAM(1)], simde_poly128_t val) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE) && defined(SIMDE_ARCH_ARM_CRYPTO)
    vstrq_p128(ptr, val);
  #else
    simde_memcpy(ptr, &val, sizeof(val));
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES)
  #undef vstrq_p128
  #define vstrq_p128(a, b) simde_vstrq_p128((a), (b))
#endif
#endif /* !defined(SIMDE_TARGET_NOT_SUPPORT_INT128_TYPE) */

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1_bf16(simde_bfloat16_t ptr[HEDLEY_ARRAY_PARAM(4)], simde_bfloat16x4_t val) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE) && defined(SIMDE_ARM_NEON_BF16)
    vst1_bf16(ptr, val);
  #else
    simde_bfloat16x4_private val_ = simde_bfloat16x4_to_private(val);
    simde_memcpy(ptr, &val_, sizeof(val_));
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES)
  #undef vst1_bf16
  #define vst1_bf16(a, b) simde_vst1_bf16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
void
simde_vst1q_bf16(simde_bfloat16_t ptr[HEDLEY_ARRAY_PARAM(8)], simde_bfloat16x8_t val) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE) && defined(SIMDE_ARM_NEON_BF16)
    vst1q_bf16(ptr, val);
  #else
    simde_bfloat16x8_private val_ = simde_bfloat16x8_to_private(val);
    simde_memcpy(ptr, &val_, sizeof(val_));
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vst1q_bf16
  #define vst1q_bf16(a, b) simde_vst1q_bf16((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif /* !defined(SIMDE_ARM_NEON_ST1_H) */
