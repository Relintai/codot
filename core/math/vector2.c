/*************************************************************************/
/*  vector2.cpp                                                          */
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

#include "vector2.h"

real_t vector2_length(const Vector2 *v) {
	return math_sqrtf(v->x * v->x + v->y * v->y);
}

real_t vector2_length_squared(const Vector2 *v) {
	return v->x * v->x + v->y * v->y;
}

void vector2_normalize(Vector2 *v) {
	real_t l = v->x * v->x + v->y * v->y;
	if (l != 0) {
		l = math_sqrtf(l);
		v->x /= l;
		v->y /= l;
	}
}

Vector2 vector2_normalized(Vector2 v) {
	vector2_normalize(&v);

	return v;
}

bool vector2_is_normalized(const Vector2 *v) {
	// use length_squared() instead of length() to avoid sqrt(), makes it more stringent.
	return math_is_equal_approxft(vector2_length_squared(v), 1, (real_t)UNIT_EPSILON);
}

real_t vector2_dot(const Vector2 *self, const Vector2 *p_other) {
	return self->x * p_other->x + self->y * p_other->y;
}

real_t vector2_cross(const Vector2 *self, const Vector2 *p_other) {
	return self->x * p_other->y - self->y * p_other->x;
}


real_t vector2_distance_to(const Vector2 *self, const Vector2 *p_vector2) {
	return math_sqrtf((self->x - p_vector2->x) * (self->x - p_vector2->x) + (self->y - p_vector2->y) * (self->y - p_vector2->y));
}

real_t vector2_distance_squared_to(const Vector2 *self, const Vector2 *p_vector2) {
	return (self->x - p_vector2->x) * (self->x - p_vector2->x) + (self->y - p_vector2->y) * (self->y - p_vector2->y);
}

real_t vector2_angle_to(const Vector2 *self, const Vector2 *p_vector2) {
	return math_atan2f(vector2_cross(self, p_vector2), vector2_dot(self, p_vector2));
}

real_t vector2_angle_to_point(const Vector2 *self, const Vector2 *p_vector2) {
	return math_atan2f(self->y - p_vector2->y, self->x - p_vector2->x);
}

real_t vector2_angle(const Vector2 *self) {
	return math_atan2f(self->y, self->x);
}

Vector2 vector2_rotated(const Vector2 *self, real_t p_by) {
	Vector2 v;

	vector2_set_rotation(&v, vector2_angle(self) + p_by);
	vector2_mul_eqs(&v, vector2_length(&v));

	return v;
}

Vector2 vector2_posmod(Vector2 *self, const real_t p_mod) {
	return vector2_create(math_fposmodf(self->x, p_mod), math_fposmodf(self->y, p_mod));
}

Vector2 vector2_posmodv(Vector2 *self, const Vector2 *p_modv) {
	return vector2_create(math_fposmodf(self->x, p_modv->x), math_fposmodf(self->y, p_modv->y));
}

Vector2 vector2_project(Vector2 *self, const Vector2 *p_to) {
	return vector2_muls(p_to, (vector2_dot(self, p_to) / vector2_length_squared(p_to)));
}

Vector2 vector2_clamped(Vector2 *self, real_t p_len) {
	//WARN_DEPRECATED_MSG("'Vector2.clamped()' is deprecated because it has been renamed to 'limit_length'.");
	real_t l = vector2_length(self);
	Vector2 v = vector2_createv(self);
	if (l > 0 && p_len < l) {
		vector2_div_eqs(&v, l);
		vector2_mul_eqs(&v, p_len);
	}

	return v;
}

Vector2 vector2_limit_length(Vector2 *self, const real_t p_len) {
	const real_t l = vector2_length(self);
	Vector2 v = vector2_createv(self);
	if (l > 0 && p_len < l) {
		vector2_div_eqs(&v, l);
		vector2_mul_eqs(&v, p_len);
	}

	return v;
}

Vector2 vector2_limit_length1(Vector2 *self) {
	const real_t l = vector2_length(self);
	Vector2 v = vector2_createv(self);
	vector2_div_eqs(&v, 1);

	return v;
}

Vector2 vector2_sign(Vector2 *self) {
	return vector2_create(SGN(self->x), SGN(self->y));
}

Vector2 vector2_floor(Vector2 *self) {
	return vector2_create(math_floorf(self->x), math_floorf(self->y));
}

Vector2 vector2_ceil(Vector2 *self) {
	return vector2_create(math_ceilf(self->x), math_ceilf(self->y));
}

Vector2 vector2_round(Vector2 *self) {
	return vector2_create(math_roundf(self->x), math_roundf(self->y));
}

Vector2 vector2_snapped(Vector2 *self, const Vector2 *p_by) {
	return vector2_create(
			math_stepifyf(self->x, p_by->x),
			math_stepifyf(self->y, p_by->y));
}

Vector2 vector2_cubic_interpolate(const Vector2 *self, const Vector2 *p_b, const Vector2 *p_pre_a, const Vector2 *p_post_b, real_t p_weight) {
	Vector2 p0 = *p_pre_a;
	Vector2 p1 = *self;
	Vector2 p2 = *p_b;
	Vector2 p3 = *p_post_b;
	Vector2 np0 = vector2_neg(&p0);

	real_t t = p_weight;
	real_t t2 = t * t;
	real_t t3 = t2 * t;

/*
	Vector2 out;
	out = 0.5f *
			((p1 * 2) +
					(-p0 + p2) * t +
					(2 * p0 - 5 * p1 + 4 * p2 - p3) * t2 +
					(-p0 + 3 * p1 - 3 * p2 + p3) * t3);
*/
	real_t x = 0.5f * ((p1.x * 2) + (np0.x + p2.x) * t + (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 + (np0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3);
	real_t y = 0.5f * ((p1.y * 2) + (np0.y + p2.y) * t + (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 + (np0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3);

	return vector2_create(x, y);
}

Vector2 vector2_move_toward(const Vector2 *self, const Vector2 *p_to, const real_t p_delta) {
	Vector2 v = *self;
	Vector2 vd = vector2_subv(p_to, &v);
	real_t len = vector2_length(&vd);
	return len <= p_delta || len < (real_t)CMP_EPSILON ? *p_to : vector2_divsc(vector2_addv(&v, &vd), len * p_delta);
}

// slide returns the component of the vector along the given plane, specified by its normal vector.
Vector2 vector2_slide(const Vector2 *self, const Vector2 *p_normal) {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector2(), "The normal Vector2 must be normalized.");
#endif
	return vector2_mulsc(vector2_subv(self, p_normal), vector2_dot(self, p_normal));
}

Vector2 vector2_bounce(const Vector2 *self, const Vector2 *p_normal) {
	return vector2_negc(vector2_reflect(self, p_normal));
}

Vector2 vector2_reflect(const Vector2 *self, const Vector2 *p_normal) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector2(), "The normal Vector2 must be normalized.");
#endif
	return vector2_subvc(vector2_mulsc(vector2_muls(p_normal, vector2_dot(self, p_normal)), 2), *self);
}

bool vector2_is_equal_approx(const Vector2 *self, const Vector2 *p_v) {
	return math_is_equal_approxf(self->x, p_v->x) && math_is_equal_approxf(self->y, p_v->y);
}

