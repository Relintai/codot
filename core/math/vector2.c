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
	return math_is_equal_approxft(length_squared(v), 1, (real_t)UNIT_EPSILON);
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
	return math_atan2f(cross(self, p_vector2), dot(self, p_vector2));
}

real_t vector2_angle_to_point(const Vector2 *self, const Vector2 *p_vector2) {
	return math_atan2f(self->y - p_vector2->y, self->x - p_vector2->x);
}



/*

real_t vector2_angle() {
	return Math::atan2(y, x);
}

Vector2 vector2_sign() {
	return Vector2(SGN(x), SGN(y));
}

Vector2 vector2_floor() {
	return Vector2(Math::floor(x), Math::floor(y));
}

Vector2 vector2_ceil() {
	return Vector2(Math::ceil(x), Math::ceil(y));
}

Vector2 vector2_round() {
	return Vector2(Math::round(x), Math::round(y));
}

Vector2 vector2_rotated(real_t p_by) {
	Vector2 v;
	v.set_rotation(angle() + p_by);
	v *= length();
	return v;
}

Vector2 vector2_posmod(const real_t p_mod) {
	return Vector2(Math::fposmod(x, p_mod), Math::fposmod(y, p_mod));
}

Vector2 vector2_posmodv(const Vector2 &p_modv) {
	return Vector2(Math::fposmod(x, p_modv.x), Math::fposmod(y, p_modv.y));
}

Vector2 vector2_project(const Vector2 &p_to) {
	return p_to * (dot(p_to) / p_to.length_squared());
}

Vector2 vector2_snapped(const Vector2 &p_by) {
	return Vector2(
			Math::stepify(x, p_by.x),
			Math::stepify(y, p_by.y));
}

Vector2 vector2_clamped(real_t p_len) {
	WARN_DEPRECATED_MSG("'Vector2.clamped()' is deprecated because it has been renamed to 'limit_length'.");
	real_t l = length();
	Vector2 v = *this;
	if (l > 0 && p_len < l) {
		v /= l;
		v *= p_len;
	}

	return v;
}

Vector2 vector2_limit_length(const real_t p_len) {
	const real_t l = length();
	Vector2 v = *this;
	if (l > 0 && p_len < l) {
		v /= l;
		v *= p_len;
	}

	return v;
}

Vector2 vector2_cubic_interpolate(const Vector2 &p_b, const Vector2 &p_pre_a, const Vector2 &p_post_b, real_t p_weight) const {
	Vector2 p0 = p_pre_a;
	Vector2 p1 = *this;
	Vector2 p2 = p_b;
	Vector2 p3 = p_post_b;

	real_t t = p_weight;
	real_t t2 = t * t;
	real_t t3 = t2 * t;

	Vector2 out;
	out = 0.5f *
			((p1 * 2) +
					(-p0 + p2) * t +
					(2 * p0 - 5 * p1 + 4 * p2 - p3) * t2 +
					(-p0 + 3 * p1 - 3 * p2 + p3) * t3);
	return out;
}

Vector2 vector2_move_toward(const Vector2 &p_to, const real_t p_delta) {
	Vector2 v = *this;
	Vector2 vd = p_to - v;
	real_t len = vd.length();
	return len <= p_delta || len < (real_t)CMP_EPSILON ? p_to : v + vd / len * p_delta;
}

// slide returns the component of the vector along the given plane, specified by its normal vector.
Vector2 vector2_slide(const Vector2 &p_normal) {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector2(), "The normal Vector2 must be normalized.");
#endif
	return *this - p_normal * this->dot(p_normal);
}

Vector2 vector2_bounce(const Vector2 &p_normal) {
	return -reflect(p_normal);
}

Vector2 vector2_reflect(const Vector2 &p_normal) {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector2(), "The normal Vector2 must be normalized.");
#endif
	return 2 * p_normal * this->dot(p_normal) - *this;
}

bool vector2_is_equal_approx(const Vector2 &p_v) {
	return Math::is_equal_approx(x, p_v.x) && Math::is_equal_approx(y, p_v.y);
}

// Vector2i

Vector2i Vector2i::operator+(const Vector2i &p_v) {
	return Vector2i(x + p_v.x, y + p_v.y);
}
void Vector2i::operator+=(const Vector2i &p_v) {
	x += p_v.x;
	y += p_v.y;
}
Vector2i Vector2i::operator-(const Vector2i &p_v) {
	return Vector2i(x - p_v.x, y - p_v.y);
}
void Vector2i::operator-=(const Vector2i &p_v) {
	x -= p_v.x;
	y -= p_v.y;
}

Vector2i Vector2i::operator*(const Vector2i &p_v1) {
	return Vector2i(x * p_v1.x, y * p_v1.y);
};

Vector2i Vector2i::operator*(const int &rvalue) {
	return Vector2i(x * rvalue, y * rvalue);
};
void Vector2i::operator*=(const int &rvalue) {
	x *= rvalue;
	y *= rvalue;
};

Vector2i Vector2i::operator/(const Vector2i &p_v1) {
	return Vector2i(x / p_v1.x, y / p_v1.y);
};

Vector2i Vector2i::operator/(const int &rvalue) {
	return Vector2i(x / rvalue, y / rvalue);
};

void Vector2i::operator/=(const int &rvalue) {
	x /= rvalue;
	y /= rvalue;
};

Vector2i Vector2i::operator-() {
	return Vector2i(-x, -y);
}

bool Vector2i::operator==(const Vector2i &p_vec2) {
	return x == p_vec2.x && y == p_vec2.y;
}
bool Vector2i::operator!=(const Vector2i &p_vec2) {
	return x != p_vec2.x || y != p_vec2.y;
}
*/