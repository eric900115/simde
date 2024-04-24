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
 *   2021      Evan Nemerson <evan@nemerson.com>
 *   2021      Atharva Nimbalkar <atharvakn@gmail.com>
 *   2023      Yung-Cheng Su <eric20607@gapp.nthu.edu.tw>
 */

#if !defined(SIMDE_ARM_NEON_CAGE_H)
#define SIMDE_ARM_NEON_CAGE_H

#include "types.h"
#include "abs.h"
#include "cge.h"

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
uint16_t
simde_vcageh_f16(simde_float16_t a, simde_float16_t b) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    return vcageh_f16(a, b);
  #else
    simde_float32_t a_ = simde_float16_to_float32(a);
    simde_float32_t b_ = simde_float16_to_float32(b);
    return (simde_math_fabsf(a_) >= simde_math_fabsf(b_)) ? UINT16_MAX : UINT16_C(0);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vcageh_f16
  #define vcageh_f16(a, b) simde_vcageh_f16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
uint32_t
simde_vcages_f32(simde_float32_t a, simde_float32_t b) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcages_f32(a, b);
  #else
    return (simde_math_fabsf(a) >= simde_math_fabsf(b)) ? ~UINT32_C(0) : UINT32_C(0);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vcages_f32
  #define vcages_f32(a, b) simde_vcages_f32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
uint64_t
simde_vcaged_f64(simde_float64_t a, simde_float64_t b) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcaged_f64(a, b);
  #else
    return (simde_math_fabs(a) >= simde_math_fabs(b)) ? ~UINT64_C(0) : UINT64_C(0);
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vcaged_f64
  #define vcaged_f64(a, b) simde_vcaged_f64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint16x4_t
simde_vcage_f16(simde_float16x4_t a, simde_float16x4_t b) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    return vcage_f16(a, b);
  #else
    simde_float16x4_private
      a_ = simde_float16x4_to_private(a),
      b_ = simde_float16x4_to_private(b);
    simde_uint16x4_private r_;

    #if defined(SIMDE_RISCV_V_NATIVE)
      vuint16m1_t
        vs_0 = __riscv_vmv_v_x_u16m1(UINT16_C(0), 4);
      vbool16_t mask = __riscv_vmfge_vv_f16m1_b16(
        __riscv_vfabs_v_f16m1(a_.sv64, 4),
        __riscv_vfabs_v_f16m1(b_.sv64, 4),
        4);
      r_.sv64 = __riscv_vmerge_vxm_u16m1(vs_0, -1, mask, 4);
    #else
      SIMDE_VECTORIZE
      for(size_t i = 0 ; i < (sizeof(r_) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = simde_vcageh_f16(a_.values[i], b_.values[i]);
      }
    #endif

    return simde_uint16x4_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES)
  #undef vcage_f16
  #define vcage_f16(a, b) simde_vcage_f16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint32x2_t
simde_vcage_f32(simde_float32x2_t a, simde_float32x2_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcage_f32(a, b);
  #elif defined(SIMDE_RISCV_V_NATIVE)
    simde_float32x2_private
      a_ = simde_float32x2_to_private(a),
      b_ = simde_float32x2_to_private(b);
    simde_uint32x2_private r_;

    vuint32m1_t
      vs_0 = __riscv_vmv_v_x_u32m1(UINT32_C(0), 2);
    vbool32_t mask = __riscv_vmfge_vv_f32m1_b32(
      __riscv_vfabs_v_f32m1(a_.sv64, 2),
      __riscv_vfabs_v_f32m1(b_.sv64, 2),
      2);
    r_.sv64 = __riscv_vmerge_vxm_u32m1(vs_0, -1, mask, 2);

    return simde_uint32x2_from_private(r_);
  #else
    return simde_vcge_f32(simde_vabs_f32(a), simde_vabs_f32(b));
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vcage_f32
  #define vcage_f32(a, b) simde_vcage_f32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint64x1_t
simde_vcage_f64(simde_float64x1_t a, simde_float64x1_t b) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcage_f64(a, b);
  #elif defined(SIMDE_RISCV_V_NATIVE)
    simde_float64x1_private
      a_ = simde_float64x1_to_private(a),
      b_ = simde_float64x1_to_private(b);
    simde_uint64x1_private r_;

    vuint64m1_t
      vs_0 = __riscv_vmv_v_x_u64m1(UINT64_C(0), 1);
    vbool64_t mask = __riscv_vmfge_vv_f64m1_b64(
      __riscv_vfabs_v_f64m1(a_.sv64, 1),
      __riscv_vfabs_v_f64m1(b_.sv64, 1),
      1);
    r_.sv64 = __riscv_vmerge_vxm_u64m1(vs_0, -1, mask, 1);

    return simde_uint64x1_from_private(r_);
  #else
    return simde_vcge_f64(simde_vabs_f64(a), simde_vabs_f64(b));
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vcage_f64
  #define vcage_f64(a, b) simde_vcage_f64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint16x8_t
simde_vcageq_f16(simde_float16x8_t a, simde_float16x8_t b) {
  #if defined(SIMDE_ARM_NEON_A32V8_NATIVE) && defined(SIMDE_ARM_NEON_FP16)
    return vcageq_f16(a, b);
  #else
    simde_float16x8_private
      a_ = simde_float16x8_to_private(a),
      b_ = simde_float16x8_to_private(b);
    simde_uint16x8_private r_;

    #if defined(SIMDE_RISCV_V_NATIVE)
      vuint16m1_t
        vs_0 = __riscv_vmv_v_x_u16m1(UINT16_C(0), 8);
      vbool16_t mask = __riscv_vmfge_vv_f16m1_b16(
        __riscv_vfabs_v_f16m1(a_.sv128, 8),
        __riscv_vfabs_v_f16m1(b_.sv128, 8),
        8);
      r_.sv128 = __riscv_vmerge_vxm_u16m1(vs_0, -1, mask, 8);
    #else
      SIMDE_VECTORIZE
      for(size_t i = 0 ; i < (sizeof(r_) / sizeof(r_.values[0])) ; i++) {
        r_.values[i] = simde_vcageh_f16(a_.values[i], b_.values[i]);
      }
    #endif

    return simde_uint16x8_from_private(r_);
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V8_ENABLE_NATIVE_ALIASES)
  #undef vcageq_f16
  #define vcageq_f16(a, b) simde_vcageq_f16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint32x4_t
simde_vcageq_f32(simde_float32x4_t a, simde_float32x4_t b) {
  #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
    return vcageq_f32(a, b);
  #elif defined(SIMDE_RISCV_V_NATIVE)
    simde_float32x4_private
      a_ = simde_float32x4_to_private(a),
      b_ = simde_float32x4_to_private(b);
    simde_uint32x4_private r_;

    vuint32m1_t
      vs_0 = __riscv_vmv_v_x_u32m1(UINT32_C(0), 4);
    vbool32_t mask = __riscv_vmfge_vv_f32m1_b32(
      __riscv_vfabs_v_f32m1(a_.sv128, 4),
      __riscv_vfabs_v_f32m1(b_.sv128, 4),
      4);
    r_.sv128 = __riscv_vmerge_vxm_u32m1(vs_0, -1, mask, 4);

    return simde_uint32x4_from_private(r_);
  #else
    return simde_vcgeq_f32(simde_vabsq_f32(a), simde_vabsq_f32(b));
  #endif
}
#if defined(SIMDE_ARM_NEON_A32V7_ENABLE_NATIVE_ALIASES)
  #undef vcageq_f32
  #define vcageq_f32(a, b) simde_vcageq_f32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde_uint64x2_t
simde_vcageq_f64(simde_float64x2_t a, simde_float64x2_t b) {
  #if defined(SIMDE_ARM_NEON_A64V8_NATIVE)
    return vcageq_f64(a, b);
  #elif defined(SIMDE_RISCV_V_NATIVE)
    simde_float64x2_private
      a_ = simde_float64x2_to_private(a),
      b_ = simde_float64x2_to_private(b);
    simde_uint64x2_private r_;

    vuint64m1_t
      vs_0 = __riscv_vmv_v_x_u64m1(UINT64_C(0), 2);
    vbool64_t mask = __riscv_vmfge_vv_f64m1_b64(
      __riscv_vfabs_v_f64m1(a_.sv128, 2),
      __riscv_vfabs_v_f64m1(b_.sv128, 2),
      2);
    r_.sv128 = __riscv_vmerge_vxm_u64m1(vs_0, -1, mask, 2);

    return simde_uint64x2_from_private(r_);
  #else
    return simde_vcgeq_f64(simde_vabsq_f64(a), simde_vabsq_f64(b));
  #endif
}
#if defined(SIMDE_ARM_NEON_A64V8_ENABLE_NATIVE_ALIASES)
  #undef vcageq_f64
  #define vcageq_f64(a, b) simde_vcageq_f64((a), (b))
#endif

SIMDE_END_DECLS_
HEDLEY_DIAGNOSTIC_POP

#endif /* !defined(SIMDE_ARM_NEON_CAGE_H) */
