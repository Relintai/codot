/*************************************************************************/
/*  math_funcs.h                                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

#include "core/math/math_defs.h"
#include "core/typedefs.h"

#include <float.h>
#include <math.h>

// Not using 'RANDOM_MAX' to avoid conflict with system headers on some OSes (at least NetBSD).
static const uint64_t MATH_RANDOM_32BIT_MAX = 0xFFFFFFFF;

static _ALWAYS_INLINE_ double math_sind(double p_x) {
	return sin(p_x);
}
static _ALWAYS_INLINE_ float math_sinf(float p_x) {
	return sinf(p_x);
}

static _ALWAYS_INLINE_ double math_cosd(double p_x) {
	return cos(p_x);
}
static _ALWAYS_INLINE_ float math_cosf(float p_x) {
	return cosf(p_x);
}

static _ALWAYS_INLINE_ double math_tand(double p_x) {
	return tan(p_x);
}
static _ALWAYS_INLINE_ float math_tanf(float p_x) {
	return tanf(p_x);
}

static _ALWAYS_INLINE_ double math_sinhd(double p_x) {
	return sinh(p_x);
}
static _ALWAYS_INLINE_ float math_sinhf(float p_x) {
	return sinhf(p_x);
}

static _ALWAYS_INLINE_ float math_sincf(float p_x) {
	return p_x == 0 ? 1 : sinf(p_x) / p_x;
}
static _ALWAYS_INLINE_ double math_sincd(double p_x) {
	return p_x == 0 ? 1 : sin(p_x) / p_x;
}

static _ALWAYS_INLINE_ float math_sincnf(float p_x) {
	return math_sincf((float)Math_PI * p_x);
}
static _ALWAYS_INLINE_ double math_sincnd(double p_x) {
	return math_sincd(Math_PI * p_x);
}

static _ALWAYS_INLINE_ double math_coshd(double p_x) {
	return cosh(p_x);
}
static _ALWAYS_INLINE_ float math_coshf(float p_x) {
	return coshf(p_x);
}

static _ALWAYS_INLINE_ double math_tanhd(double p_x) {
	return tanh(p_x);
}
static _ALWAYS_INLINE_ float math_tanhf(float p_x) {
	return tanhf(p_x);
}

static _ALWAYS_INLINE_ double math_asind(double p_x) {
	return asin(p_x);
}
static _ALWAYS_INLINE_ float math_asinf(float p_x) {
	return asinf(p_x);
}

static _ALWAYS_INLINE_ double math_acosd(double p_x) {
	return acos(p_x);
}
static _ALWAYS_INLINE_ float math_acosf(float p_x) {
	return acosf(p_x);
}

static _ALWAYS_INLINE_ double math_atand(double p_x) {
	return atan(p_x);
}
static _ALWAYS_INLINE_ float math_atanf(float p_x) {
	return atanf(p_x);
}

static _ALWAYS_INLINE_ double math_atan2d(double p_y, double p_x) {
	return atan2(p_y, p_x);
}
static _ALWAYS_INLINE_ float math_atan2f(float p_y, float p_x) {
	return atan2f(p_y, p_x);
}

static _ALWAYS_INLINE_ double math_sqrtd(double p_x) {
	return sqrt(p_x);
}
static _ALWAYS_INLINE_ float math_sqrtf(float p_x) {
	return sqrtf(p_x);
}

static _ALWAYS_INLINE_ double math_fmodd(double p_x, double p_y) {
	return fmod(p_x, p_y);
}
static _ALWAYS_INLINE_ float math_fmodf(float p_x, float p_y) {
	return fmodf(p_x, p_y);
}

static _ALWAYS_INLINE_ double math_floord(double p_x) {
	return floor(p_x);
}
static _ALWAYS_INLINE_ float math_floorf(float p_x) {
	return floorf(p_x);
}

static _ALWAYS_INLINE_ double math_ceild(double p_x) {
	return ceil(p_x);
}
static _ALWAYS_INLINE_ float math_ceilf(float p_x) {
	return ceilf(p_x);
}

static _ALWAYS_INLINE_ double math_powd(double p_x, double p_y) {
	return pow(p_x, p_y);
}
static _ALWAYS_INLINE_ float math_powf(float p_x, float p_y) {
	return powf(p_x, p_y);
}

static _ALWAYS_INLINE_ double math_logd(double p_x) {
	return log(p_x);
}
static _ALWAYS_INLINE_ float math_logf(float p_x) {
	return logf(p_x);
}

static _ALWAYS_INLINE_ double math_expd(double p_x) {
	return exp(p_x);
}
static _ALWAYS_INLINE_ float math_expf(float p_x) {
	return expf(p_x);
}

static _ALWAYS_INLINE_ bool math_is_nand(double p_val) {
#ifdef _MSC_VER
	return _isnan(p_val);
#elif defined(__GNUC__) && __GNUC__ < 6
	union {
		uint64_t u;
		double f;
	} ieee754;
	ieee754.f = p_val;
	// (unsigned)(0x7ff0000000000001 >> 32) : 0x7ff00000
	return ((((unsigned)(ieee754.u >> 32) & 0x7fffffff) + ((unsigned)ieee754.u != 0)) > 0x7ff00000);
#else
	return isnan(p_val);
#endif
}

static _ALWAYS_INLINE_ bool math_is_nanf(float p_val) {
#ifdef _MSC_VER
	return _isnan(p_val);
#elif defined(__GNUC__) && __GNUC__ < 6
	union {
		uint32_t u;
		float f;
	} ieee754;
	ieee754.f = p_val;
	// -----------------------------------
	// (single-precision floating-point)
	// NaN : s111 1111 1xxx xxxx xxxx xxxx xxxx xxxx
	//     : (> 0x7f800000)
	// where,
	//   s : sign
	//   x : non-zero number
	// -----------------------------------
	return ((ieee754.u & 0x7fffffff) > 0x7f800000);
#else
	return isnan(p_val);
#endif
}

static _ALWAYS_INLINE_ bool math_is_infd(double p_val) {
#ifdef _MSC_VER
	return !_finite(p_val);
// use an inline implementation of isinf as a workaround for problematic libstdc++ versions from gcc 5.x era
#elif defined(__GNUC__) && __GNUC__ < 6
	union {
		uint64_t u;
		double f;
	} ieee754;
	ieee754.f = p_val;
	return ((unsigned)(ieee754.u >> 32) & 0x7fffffff) == 0x7ff00000 &&
			((unsigned)ieee754.u == 0);
#else
	return isinf(p_val);
#endif
}

static _ALWAYS_INLINE_ bool math_is_inff(float p_val) {
#ifdef _MSC_VER
	return !_finite(p_val);
// use an inline implementation of isinf as a workaround for problematic libstdc++ versions from gcc 5.x era
#elif defined(__GNUC__) && __GNUC__ < 6
	union {
		uint32_t u;
		float f;
	} ieee754;
	ieee754.f = p_val;
	return (ieee754.u & 0x7fffffff) == 0x7f800000;
#else
	return isinf(p_val);
#endif
}

static _ALWAYS_INLINE_ float math_absf(float g) {
	union {
		float f;
		uint32_t i;
	} u;

	u.f = g;
	u.i &= 2147483647u;
	return u.f;
}

static _ALWAYS_INLINE_ double math_absd(double g) {
	union {
		double d;
		uint64_t i;
	} u;
	u.d = g;
	u.i &= (uint64_t)9223372036854775807ll;
	return u.d;
}

static _ALWAYS_INLINE_ int math_absi(int g) {
	return g > 0 ? g : -g;
}
static _ALWAYS_INLINE_ int64_t math_absi64(int64_t g) {
	return g > 0 ? g : -g;
}

static _ALWAYS_INLINE_ double math_fposmodd(double p_x, double p_y) {
	double value = math_fmodd(p_x, p_y);
	if (((value < 0) && (p_y > 0)) || ((value > 0) && (p_y < 0))) {
		value += p_y;
	}
	value += 0.0;
	return value;
}
static _ALWAYS_INLINE_ float math_fposmodf(float p_x, float p_y) {
	float value = math_fmodf(p_x, p_y);
	if (((value < 0) && (p_y > 0)) || ((value > 0) && (p_y < 0))) {
		value += p_y;
	}
	value += 0.0f;
	return value;
}
static _ALWAYS_INLINE_ int64_t math_posmodi(int64_t p_x, int64_t p_y) {
	int64_t value = p_x % p_y;
	if (((value < 0) && (p_y > 0)) || ((value > 0) && (p_y < 0))) {
		value += p_y;
	}
	return value;
}

static _ALWAYS_INLINE_ double math_deg2radd(double p_y) {
	return p_y * Math_PI / 180.0;
}
static _ALWAYS_INLINE_ float math_deg2radf(float p_y) {
	return p_y * (float)(Math_PI / 180.0);
}

static _ALWAYS_INLINE_ double math_rad2degd(double p_y) {
	return p_y * 180.0 / Math_PI;
}
static _ALWAYS_INLINE_ float math_rad2degf(float p_y) {
	return p_y * (float)(180.0 / Math_PI);
}

static _ALWAYS_INLINE_ double math_lerpd(double p_from, double p_to, double p_weight) {
	return p_from + (p_to - p_from) * p_weight;
}
static _ALWAYS_INLINE_ float math_lerpf(float p_from, float p_to, float p_weight) {
	return p_from + (p_to - p_from) * p_weight;
}

static _ALWAYS_INLINE_ double math_lerp_angled(double p_from, double p_to, double p_weight) {
	double difference = fmod(p_to - p_from, Math_TAU);
	double distance = fmod(2.0 * difference, Math_TAU) - difference;
	return p_from + distance * p_weight;
}
static _ALWAYS_INLINE_ float math_lerp_anglef(float p_from, float p_to, float p_weight) {
	float difference = fmodf(p_to - p_from, (float)Math_TAU);
	float distance = fmodf(2.0f * difference, (float)Math_TAU) - difference;
	return p_from + distance * p_weight;
}

static _ALWAYS_INLINE_ double math_inverse_lerpd(double p_from, double p_to, double p_value) {
	return (p_value - p_from) / (p_to - p_from);
}
static _ALWAYS_INLINE_ float math_inverse_lerpf(float p_from, float p_to, float p_value) {
	return (p_value - p_from) / (p_to - p_from);
}

static _ALWAYS_INLINE_ double math_range_lerpd(double p_value, double p_istart, double p_istop, double p_ostart, double p_ostop) {
	return math_lerpd(p_ostart, p_ostop, math_inverse_lerpd(p_istart, p_istop, p_value));
}
static _ALWAYS_INLINE_ float math_range_lerpf(float p_value, float p_istart, float p_istop, float p_ostart, float p_ostop) {
	return math_lerpf(p_ostart, p_ostop, math_inverse_lerpf(p_istart, p_istop, p_value));
}

static _ALWAYS_INLINE_ double math_linear2dbd(double p_linear) {
	return math_logd(p_linear) * 8.6858896380650365530225783783321;
}
static _ALWAYS_INLINE_ float math_linear2dbf(float p_linear) {
	return math_logf(p_linear) * (float)8.6858896380650365530225783783321;
}

static _ALWAYS_INLINE_ double math_db2lineard(double p_db) {
	return math_expd(p_db * 0.11512925464970228420089957273422);
}
static _ALWAYS_INLINE_ float math_db2linearf(float p_db) {
	return math_expf(p_db * (float)0.11512925464970228420089957273422);
}

static _ALWAYS_INLINE_ double math_roundd(double p_val) {
	return round(p_val);
}
static _ALWAYS_INLINE_ float math_roundf(float p_val) {
	return roundf(p_val);
}

// double only, as these functions are mainly used by the editor and not performance-critical,
static double ease(double p_x, double p_c);
int step_decimals(double p_step);
static int range_step_decimals(double p_step);
static double stepify(double p_value, double p_step);
static double dectime(double p_value, double p_amount, double p_step);

static uint32_t larger_prime(uint32_t p_val);

static void seed(uint64_t x);
static void randomize();
static uint32_t rand_from_seed(uint64_t *seed);
uint32_t rand();
static _ALWAYS_INLINE_ double randd() {
	return (double)rand() / (double)MATH_RANDOM_32BIT_MAX;
}
static _ALWAYS_INLINE_ float randf() {
	return (float)rand() / (float)MATH_RANDOM_32BIT_MAX;
}

static double math_randomd(double from, double to);
static float math_randomf(float from, float to);

static real_t math_randomr(int from, int to) {
	return (real_t)math_randomf((real_t)from, (real_t)to);
}

static _ALWAYS_INLINE_ bool math_is_equal_approx_ratio(real_t a, real_t b) {
	// this is an approximate way to check that numbers are close, as a ratio of their average size
	// helps compare approximate numbers that may be very big or very small
	real_t diff = math_absf(a - b);
	if (diff == 0 || diff < CMP_EPSILON) {
		return true;
	}
	real_t avg_size = (math_absf(a) + math_absf(b)) / 2;
	diff /= avg_size;
	return diff < CMP_EPSILON;
}

static _ALWAYS_INLINE_ bool math_is_equal_approx_ratioe(real_t a, real_t b, real_t epsilon) {
	// this is an approximate way to check that numbers are close, as a ratio of their average size
	// helps compare approximate numbers that may be very big or very small
	real_t diff = math_absf(a - b);
	if (diff == 0 || diff < CMP_EPSILON) {
		return true;
	}
	real_t avg_size = (math_absf(a) + math_absf(b)) / 2;
	diff /= avg_size;
	return diff < epsilon;
}

static _ALWAYS_INLINE_ bool math_is_equal_approx_ratioem(real_t a, real_t b, real_t epsilon, real_t min_epsilon) {
	// this is an approximate way to check that numbers are close, as a ratio of their average size
	// helps compare approximate numbers that may be very big or very small
	real_t diff = math_absf(a - b);
	if (diff == 0 || diff < min_epsilon) {
		return true;
	}
	real_t avg_size = (math_absf(a) + math_absf(b)) / 2;
	diff /= avg_size;
	return diff < epsilon;
}

static _ALWAYS_INLINE_ bool math_is_equal_approxf(float a, float b) {
	// Check for exact equality first, required to handle "infinity" values.
	if (a == b) {
		return true;
	}
	// Then check for approximate equality.
	float tolerance = (float)CMP_EPSILON * math_absf(a);
	if (tolerance < (float)CMP_EPSILON) {
		tolerance = (float)CMP_EPSILON;
	}
	return math_absf(a - b) < tolerance;
}

static _ALWAYS_INLINE_ bool math_is_equal_approxft(float a, float b, float tolerance) {
	// Check for exact equality first, required to handle "infinity" values.
	if (a == b) {
		return true;
	}
	// Then check for approximate equality.
	return math_absf(a - b) < tolerance;
}

static _ALWAYS_INLINE_ bool math_is_zero_approxf(float s) {
	return math_absf(s) < (float)CMP_EPSILON;
}

static _ALWAYS_INLINE_ bool math_is_equal_approxd(double a, double b) {
	// Check for exact equality first, required to handle "infinity" values.
	if (a == b) {
		return true;
	}
	// Then check for approximate equality.
	double tolerance = CMP_EPSILON * math_absd(a);
	if (tolerance < CMP_EPSILON) {
		tolerance = CMP_EPSILON;
	}
	return math_absd(a - b) < tolerance;
}

static _ALWAYS_INLINE_ bool math_is_equal_approxdt(double a, double b, double tolerance) {
	// Check for exact equality first, required to handle "infinity" values.
	if (a == b) {
		return true;
	}
	// Then check for approximate equality.
	return math_absd(a - b) < tolerance;
}

static _ALWAYS_INLINE_ bool math_is_zero_approxd(double s) {
	return math_absd(s) < CMP_EPSILON;
}

static _ALWAYS_INLINE_ double math_smoothstepd(double p_from, double p_to, double p_s) {
	if (math_is_equal_approxd(p_from, p_to)) {
		return p_from;
	}
	double s = CLAMP((p_s - p_from) / (p_to - p_from), 0.0, 1.0);
	return s * s * (3.0 - 2.0 * s);
}
static _ALWAYS_INLINE_ float math_smoothstepf(float p_from, float p_to, float p_s) {
	if (math_is_equal_approxf(p_from, p_to)) {
		return p_from;
	}
	float s = CLAMP((p_s - p_from) / (p_to - p_from), 0.0f, 1.0f);
	return s * s * (3.0f - 2.0f * s);
}
static _ALWAYS_INLINE_ double math_move_towardd(double p_from, double p_to, double p_delta) {
	return math_absd(p_to - p_from) <= p_delta ? p_to : p_from + SGN(p_to - p_from) * p_delta;
}
static _ALWAYS_INLINE_ float math_move_towardf(float p_from, float p_to, float p_delta) {
	return math_absf(p_to - p_from) <= p_delta ? p_to : p_from + SGN(p_to - p_from) * p_delta;
}

static _ALWAYS_INLINE_ int64_t math_wrapi(int64_t value, int64_t min, int64_t max) {
	int64_t range = max - min;
	return range == 0 ? min : min + ((((value - min) % range) + range) % range);
}
static _ALWAYS_INLINE_ double math_wrapd(double value, double min, double max) {
	double range = max - min;
	return math_is_zero_approxd(range) ? min : value - (range * math_floord((value - min) / range));
}
static _ALWAYS_INLINE_ float math_wrapf(float value, float min, float max) {
	float range = max - min;
	return math_is_zero_approxf(range) ? min : value - (range * math_floorf((value - min) / range));
}

// This function should be as fast as possible and rounding mode should not matter.
static _ALWAYS_INLINE_ int math_fast_ftoi(float a) {
	// Assuming every supported compiler has `lrint()`.
	return lrintf(a);
}

static _ALWAYS_INLINE_ uint32_t math_halfbits_to_floatbits(uint16_t h) {
	uint16_t h_exp, h_sig;
	uint32_t f_sgn, f_exp, f_sig;

	h_exp = (h & 0x7c00u);
	f_sgn = ((uint32_t)h & 0x8000u) << 16;
	switch (h_exp) {
		case 0x0000u: /* 0 or subnormal */
			h_sig = (h & 0x03ffu);
			/* Signed zero */
			if (h_sig == 0) {
				return f_sgn;
			}
			/* Subnormal */
			h_sig <<= 1;
			while ((h_sig & 0x0400u) == 0) {
				h_sig <<= 1;
				h_exp++;
			}
			f_exp = ((uint32_t)(127 - 15 - h_exp)) << 23;
			f_sig = ((uint32_t)(h_sig & 0x03ffu)) << 13;
			return f_sgn + f_exp + f_sig;
		case 0x7c00u: /* inf or NaN */
			/* All-ones exponent and a copy of the significand */
			return f_sgn + 0x7f800000u + (((uint32_t)(h & 0x03ffu)) << 13);
		default: /* normalized */
			/* Just need to adjust the exponent and shift */
			return f_sgn + (((uint32_t)(h & 0x7fffu) + 0x1c000u) << 13);
	}
}

static _ALWAYS_INLINE_ float math_halfptr_to_float(const uint16_t *h) {
	union {
		uint32_t u32;
		float f32;
	} u;

	u.u32 = math_halfbits_to_floatbits(*h);
	return u.f32;
}

static _ALWAYS_INLINE_ float math_half_to_float(const uint16_t h) {
	return math_halfptr_to_float(&h);
}

static _ALWAYS_INLINE_ uint16_t math_make_half_float(float f) {
	union {
		float fv;
		uint32_t ui;
	} ci;
	ci.fv = f;

	uint32_t x = ci.ui;
	uint32_t sign = (unsigned short)(x >> 31);
	uint32_t mantissa;
	uint32_t exp;
	uint16_t hf;

	// get mantissa
	mantissa = x & ((1 << 23) - 1);
	// get exponent bits
	exp = x & (0xFF << 23);
	if (exp >= 0x47800000) {
		// check if the original single precision float number is a NaN
		if (mantissa && (exp == (0xFF << 23))) {
			// we have a single precision NaN
			mantissa = (1 << 23) - 1;
		} else {
			// 16-bit half-float representation stores number as Inf
			mantissa = 0;
		}
		hf = (((uint16_t)sign) << 15) | (uint16_t)((0x1F << 10)) |
				(uint16_t)(mantissa >> 13);
	}
	// check if exponent is <= -15
	else if (exp <= 0x38000000) {
		/*// store a denorm half-float value or zero
	exp = (0x38000000 - exp) >> 23;
	mantissa >>= (14 + exp);

	hf = (((uint16_t)sign) << 15) | (uint16_t)(mantissa);
	*/
		hf = 0; //denormals do not work for 3D, convert to zero
	} else {
		hf = (((uint16_t)sign) << 15) |
				(uint16_t)((exp - 0x38000000) >> 13) |
				(uint16_t)(mantissa >> 13);
	}

	return hf;
}

float math_stepifyf(float p_value, float p_step);
double math_stepifyd(double p_value, double p_step);

static _ALWAYS_INLINE_ float math_snap_scalar(float p_offset, float p_step, float p_target) {
	return p_step != 0 ? math_stepifyf(p_target - p_offset, p_step) + p_offset : p_target;
}

static _ALWAYS_INLINE_ float math_snap_scalar_separation(float p_offset, float p_step, float p_target, float p_separation) {
	if (p_step != 0) {
		float a = math_stepifyf(p_target - p_offset, p_step + p_separation) + p_offset;
		float b = a;
		if (p_target >= 0) {
			b -= p_separation;
		} else {
			b += p_step;
		}
		return (math_absf(p_target - a) < math_absf(p_target - b)) ? a : b;
	}
	return p_target;
}

#endif // MATH_FUNCS_H
