/*************************************************************************/
/*  quat.cpp                                                             */
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

#include "quat.h"

//#include "core/math/basis.h"
//#include "core/print_string.h"

void quat_set_axis_angle(Quat *self, const Vector3 *axis, const real_t angle) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_MSG(!axis.is_normalized(), "The axis Vector3 must be normalized.");
#endif
	real_t d = vector3_length(axis);
	if (d == 0) {
		quat_set(self, 0, 0, 0, 0);
	} else {
		real_t sin_angle = math_sinf(angle * 0.5f);
		real_t cos_angle = math_cosf(angle * 0.5f);
		real_t s = sin_angle / d;
		quat_set(self, axis->x * s, axis->y * s, axis->z * s, cos_angle);
	}
}

Quat quat_create_ae(const Vector3 *axis, const real_t angle) {
	Quat q;
	quat_set_axis_angle(&q, axis, angle);
	return q;
}

Quat quat_create_euler(const Vector3 *euler) {
	Quat q;
	quat_set_euler(&q, euler);
	return q;
}

real_t quat_angle_to(const Quat *self, const Quat *p_to) {
	real_t d = quat_dot(self, p_to);
	return math_acosf(CLAMP(d * d * 2 - 1, -1, 1));
}

// set_euler_xyz expects a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses XYZ convention (Z is the first rotation).
void quat_set_euler_xyz(Quat *self, const Vector3 *p_euler) {
	real_t half_a1 = p_euler->x * 0.5f;
	real_t half_a2 = p_euler->y * 0.5f;
	real_t half_a3 = p_euler->z * 0.5f;

	// R = X(a1).Y(a2).Z(a3) convention for Euler angles.
	// Conversion to quaternion as listed in https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf (page A-2)
	// a3 is the angle of the first rotation, following the notation in this reference.

	real_t cos_a1 = math_cosf(half_a1);
	real_t sin_a1 = math_sinf(half_a1);
	real_t cos_a2 = math_cosf(half_a2);
	real_t sin_a2 = math_sinf(half_a2);
	real_t cos_a3 = math_cosf(half_a3);
	real_t sin_a3 = math_sinf(half_a3);

	quat_set(self, 
			sin_a1 * cos_a2 * cos_a3 + sin_a2 * sin_a3 * cos_a1,
			-sin_a1 * sin_a3 * cos_a2 + sin_a2 * cos_a1 * cos_a3,
			sin_a1 * sin_a2 * cos_a3 + sin_a3 * cos_a1 * cos_a2,
			-sin_a1 * sin_a2 * sin_a3 + cos_a1 * cos_a2 * cos_a3);
}

// get_euler_xyz returns a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses XYZ convention (Z is the first rotation).
Vector3 quat_get_euler_xyz(const Quat *self) {
	//Basis m(*this);
	//return m.get_euler_xyz();

	return vector3_create(0, 0, 0);
}

// set_euler_yxz expects a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses YXZ convention (Z is the first rotation).
void quat_set_euler_yxz(Quat *self, const Vector3 *p_euler) {
	real_t half_a1 = p_euler->y * 0.5f;
	real_t half_a2 = p_euler->x * 0.5f;
	real_t half_a3 = p_euler->z * 0.5f;

	// R = Y(a1).X(a2).Z(a3) convention for Euler angles.
	// Conversion to quaternion as listed in https://ntrs.nasa.gov/archive/nasa/casi.ntrs.nasa.gov/19770024290.pdf (page A-6)
	// a3 is the angle of the first rotation, following the notation in this reference.

	real_t cos_a1 = math_cosf(half_a1);
	real_t sin_a1 = math_sinf(half_a1);
	real_t cos_a2 = math_cosf(half_a2);
	real_t sin_a2 = math_sinf(half_a2);
	real_t cos_a3 = math_cosf(half_a3);
	real_t sin_a3 = math_sinf(half_a3);

	quat_set(self,
			sin_a1 * cos_a2 * sin_a3 + cos_a1 * sin_a2 * cos_a3,
			sin_a1 * cos_a2 * cos_a3 - cos_a1 * sin_a2 * sin_a3,
			-sin_a1 * sin_a2 * cos_a3 + cos_a1 * cos_a2 * sin_a3,
			sin_a1 * sin_a2 * sin_a3 + cos_a1 * cos_a2 * cos_a3);
}

// get_euler_yxz returns a vector containing the Euler angles in the format
// (ax,ay,az), where ax is the angle of rotation around x axis,
// and similar for other axes.
// This implementation uses YXZ convention (Z is the first rotation).
Vector3 quat_get_euler_yxz(const Quat *self) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_V_MSG(!is_normalized(), Vector3(0, 0, 0), "The quaternion must be normalized.");
#endif
	//Basis m(*this);
	//return m.get_euler_yxz();

	return vector3_create(0, 0, 0);
}

bool quat_is_equal_approx(const Quat *self, const Quat *p_quat) {
	return math_is_equal_approxf(self->x, p_quat->x) && math_is_equal_approxf(self->y, p_quat->y) && math_is_equal_approxf(self->z, p_quat->z) && math_is_equal_approxf(self->w, p_quat->w);
}

real_t quat_length(const Quat *self) {
	return math_sqrtf(quat_length_squared(self));
}

void quat_normalize(Quat *self) {
	quat_div_eqs(self, quat_length(self));
}

Quat quat_normalized(const Quat *self) {
	return quat_divs(self, quat_length(self));
}

bool quat_is_normalized(const Quat *self) {
	return math_is_equal_approxft(quat_length_squared(self), 1, (real_t)UNIT_EPSILON); //use less epsilon
}

Quat quat_inverse(const Quat *self) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_V_MSG(!is_normalized(), Quat(), "The quaternion must be normalized.");
#endif
	return quat_creater(-self->x, -self->y, -self->z, self->w);
}

Quat quat_slerp(const Quat *self, const Quat *p_to, const real_t p_weight) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_V_MSG(!is_normalized(), Quat(), "The start quaternion must be normalized.");
	//ERR_FAIL_COND_V_MSG(!p_to.is_normalized(), Quat(), "The end quaternion must be normalized.");
#endif
	Quat to1;
	real_t omega, cosom, sinom, scale0, scale1;

	// calc cosine
	cosom = quat_dot(self, p_to);

	// adjust signs (if necessary)
	if (cosom < 0) {
		cosom = -cosom;
		to1.x = -p_to->x;
		to1.y = -p_to->y;
		to1.z = -p_to->z;
		to1.w = -p_to->w;
	} else {
		to1.x = p_to->x;
		to1.y = p_to->y;
		to1.z = p_to->z;
		to1.w = p_to->w;
	}

	// calculate coefficients

	if ((1 - cosom) > (real_t)CMP_EPSILON) {
		// standard case (slerp)
		omega = math_acosf(cosom);
		sinom = math_sinf(omega);
		scale0 = math_sinf((1 - p_weight) * omega) / sinom;
		scale1 = math_sinf(p_weight * omega) / sinom;
	} else {
		// "from" and "to" quaternions are very close
		//  ... so we can do a linear interpolation
		scale0 = 1 - p_weight;
		scale1 = p_weight;
	}
	// calculate final values
	return quat_creater(
			scale0 * self->x + scale1 * to1.x,
			scale0 * self->y + scale1 * to1.y,
			scale0 * self->z + scale1 * to1.z,
			scale0 * self->w + scale1 * to1.w);
}

Quat quat_slerpni(const Quat *self, const Quat *p_to, const real_t p_weight) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_V_MSG(!is_normalized(), Quat(), "The start quaternion must be normalized.");
	//ERR_FAIL_COND_V_MSG(!p_to.is_normalized(), Quat(), "The end quaternion must be normalized.");
#endif
	real_t dot = quat_dot(self, p_to);

	if (math_absf(dot) > 0.9999f) {
		return quat_createq(self);
	}

	real_t theta = math_acosf(dot),
		   sinT = 1 / math_sinf(theta),
		   newFactor = math_sinf(p_weight * theta) * sinT,
		   invFactor = math_sinf((1 - p_weight) * theta) * sinT;

	return quat_creater(invFactor * self->x + newFactor * p_to->x,
			invFactor * self->y + newFactor * p_to->y,
			invFactor * self->z + newFactor * p_to->z,
			invFactor * self->w + newFactor * p_to->w);
}

Quat quat_cubic_slerp(const Quat *self, const Quat *p_b, const Quat *p_pre_a, const Quat *p_post_b, const real_t p_weight) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_V_MSG(!is_normalized(), Quat(), "The start quaternion must be normalized.");
	//ERR_FAIL_COND_V_MSG(!p_b.is_normalized(), Quat(), "The end quaternion must be normalized.");
#endif
	//the only way to do slerp :|
	real_t t2 = (1 - p_weight) * p_weight * 2;
	Quat sp = quat_slerp(self, p_b, p_weight);
	Quat sq = quat_slerpni(p_pre_a, p_post_b, p_weight);
	return quat_slerpni(&sp, &sq, t2);
}

/*
quat_operator String() const {
	return String::num(x) + ", " + String::num(y) + ", " + String::num(z) + ", " + String::num(w);
}
*/
