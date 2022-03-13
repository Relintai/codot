/*************************************************************************/
/*  vector2.h                                                            */
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

#ifndef VECTOR2_H
#define VECTOR2_H

#include "core/math/math_funcs.h"

struct Vector2i;

static const int VECTOR2_AXIS_COUNT = 2;

enum Vector2Axis {
	VECTOR2_AXIS_X,
	VECTOR2_AXIS_Y,
};

typedef struct _NO_DISCARD_CLASS_ Vector2 {
	union {
		struct {
			union {
				real_t x;
				real_t width;
			};
			union {
				real_t y;
				real_t height;
			};
		};

		real_t coord[2];
	};
} Vector2;

static _FORCE_INLINE_ real_t vector2_get_axis(const Vector2 *v, int p_idx) {
	//DEV_ASSERT((unsigned int)p_idx < 2);
	return v->coord[p_idx];
}

/*
//not needed
static _FORCE_INLINE_ const real_t &operator[](int p_idx) const {
	DEV_ASSERT((unsigned int)p_idx < 2);
	return coord[p_idx];
}
*/

static _FORCE_INLINE_ void vector2_set_all(Vector2 *self, real_t p_value) {
	self->x = self->y = p_value;
}

static _FORCE_INLINE_ void vector2_set(Vector2 *self, real_t p_value_x, real_t p_value_y) {
	self->x = p_value_x;
	self->y = p_value_y;
}

static _FORCE_INLINE_ Vector2 vector2_create(real_t p_value_x, real_t p_value_y) {
	Vector2 v;

	v.x = p_value_x;
	v.y = p_value_y;

	return v;
}

static _FORCE_INLINE_ int vector2_min_axis(const Vector2 *v) {
	return v->x < v->y ? 0 : 1;
}
static _FORCE_INLINE_ int vector2_max_axis(const Vector2 *v) {
	return v->x < v->y ? 1 : 0;
}

// Vector2 - Vector2 operators
static _FORCE_INLINE_ Vector2 vector2_addv(const Vector2 *self, const Vector2 *p_v) {
	return vector2_create(self->x + p_v->x, self->y + p_v->y);
}
static _FORCE_INLINE_ void vector2_add_eqv(Vector2 *self, const Vector2 *p_v) {
	self->x += p_v->x;
	self->y += p_v->y;
}
static _FORCE_INLINE_ Vector2 vector2_subv(const Vector2 *self, const Vector2 *p_v) {
	return vector2_create(self->x - p_v->x, self->y - p_v->y);
}
static _FORCE_INLINE_ void vector2_sub_eqv(Vector2 *self, const Vector2 *p_v) {
	self->x -= p_v->x;
	self->y -= p_v->y;
}
static _FORCE_INLINE_ Vector2 vector2_mulv(const Vector2 *self, const Vector2 *p_v1) {
	return vector2_create(self->x * p_v1->x, self->y * p_v1->y);
}
static _FORCE_INLINE_ void vector2_mul_eqv(Vector2 *self, const Vector2 *rvalue) {
	self->x *= rvalue->x;
	self->y *= rvalue->y;
}
static _FORCE_INLINE_ Vector2 vector2_divv(const Vector2 *self, const Vector2 *p_v1) {
	return vector2_create(self->x / p_v1->x, self->y / p_v1->y);
}
static _FORCE_INLINE_ void vector2_div_eqv(Vector2 *self, const Vector2 *rvalue) {
	self->x /= rvalue->x;
	self->y /= rvalue->y;
}

// Vector2 - scalar operators
static _FORCE_INLINE_ Vector2 vector2_muls(const Vector2 *self, const real_t rvalue) {
	return vector2_create(self->x * rvalue, self->y * rvalue);
};
static _FORCE_INLINE_ void vector2_mul_eqs(Vector2 *self, const real_t rvalue) {
	self->x *= rvalue;
	self->y *= rvalue;
};

static _FORCE_INLINE_ Vector2 vector2_divs(const Vector2 *self, const real_t rvalue) {
	return vector2_create(self->x / rvalue, self->y / rvalue);
};

static _FORCE_INLINE_ void vector2_div_eqs(Vector2 *self, const real_t rvalue) {
	self->x /= rvalue;
	self->y /= rvalue;
};

/*
static _FORCE_INLINE_ Vector2 operator*(real_t p_scalar, const Vector2 *p_vec) {
	return p_vec * p_scalar;
}
*/

// Other
static _FORCE_INLINE_ Vector2 vector2_neg(const Vector2 *self) {
	return vector2_create(-(self->x), -(self->y));
}


real_t length(const Vector2 *v);
real_t length_squared(const Vector2 *v);

void vector2_normalize(Vector2 *v);
Vector2 vector2_normalized(Vector2 v);
bool vector2_is_normalized(const Vector2 *v);

real_t vector2_dot(const Vector2 *self, const Vector2 *p_other);
real_t vector2_cross(const Vector2 *self, const Vector2 *p_other);

real_t vector2_distance_to(const Vector2 *self, const Vector2 *p_vector2);
real_t vector2_distance_squared_to(const Vector2 *self, const Vector2 *p_vector2);
real_t vector2_angle_to(const Vector2 *self, const Vector2 *p_vector2);
real_t vector2_angle_to_point(const Vector2 *self, const Vector2 *p_vector2);

static _FORCE_INLINE_ Vector2 vector2_direction_to(const Vector2 *self, const Vector2 *p_to) {
	Vector2 ret;
	vector2_set(&ret, p_to->x - self->x, p_to->y - self->y);

	vector2_normalize(&ret);

	return ret;
}

real_t vector2_angle(const Vector2 *self);

static _FORCE_INLINE_ void vector2_set_rotation(Vector2 *self, real_t p_radians) {
	self->x = math_cosf(p_radians);
	self->y = math_sinf(p_radians);
}

static _FORCE_INLINE_ Vector2 vector2_abs(const Vector2 *self) {
	return vector2_create(math_absf(self->x), math_absf(self->y));
}

Vector2 vector2_rotated(const Vector2 *self, real_t p_by);
Vector2 vector2_tangent(const Vector2 *self) {
	return vector2_create(self->y, -(self->x));
}


/*


Vector2 posmod(const real_t p_mod);
Vector2 posmodv(const Vector2 &p_modv);
Vector2 project(const Vector2 &p_to);

Vector2 plane_project(real_t p_d, const Vector2 &p_vec);

Vector2 clamped(real_t p_len);
Vector2 limit_length(const real_t p_len = 1.0);

_FORCE_INLINE_ static Vector2 linear_interpolate(const Vector2 &p_a, const Vector2 &p_b, real_t p_weight);
_FORCE_INLINE_ Vector2 linear_interpolate(const Vector2 &p_to, real_t p_weight);
_FORCE_INLINE_ Vector2 slerp(const Vector2 &p_to, real_t p_weight);
Vector2 cubic_interpolate(const Vector2 &p_b, const Vector2 &p_pre_a, const Vector2 &p_post_b, real_t p_weight);
Vector2 move_toward(const Vector2 &p_to, const real_t p_delta);

Vector2 slide(const Vector2 &p_normal);
Vector2 bounce(const Vector2 &p_normal);
Vector2 reflect(const Vector2 &p_normal);

bool is_equal_approx(const Vector2 &p_v);

bool operator==(const Vector2 &p_vec2);
bool operator!=(const Vector2 &p_vec2);

bool operator<(const Vector2 &p_vec2) const {
	return x == p_vec2.x ? (y < p_vec2.y) : (x < p_vec2.x);
}
bool operator>(const Vector2 &p_vec2) const {
	return x == p_vec2.x ? (y > p_vec2.y) : (x > p_vec2.x);
}
bool operator<=(const Vector2 &p_vec2) const {
	return x == p_vec2.x ? (y <= p_vec2.y) : (x < p_vec2.x);
}
bool operator>=(const Vector2 &p_vec2) const {
	return x == p_vec2.x ? (y >= p_vec2.y) : (x > p_vec2.x);
}

Vector2 sign();
Vector2 floor();
Vector2 ceil();
Vector2 round();
Vector2 snapped(const Vector2 &p_by);
real_t aspect() const {
	return width / height;
}

operator String() const {
	return String::num(x) + ", " + String::num(y);
}

_FORCE_INLINE_ Vector2(real_t p_x, real_t p_y) {
	x = p_x;
	y = p_y;
}
_FORCE_INLINE_ Vector2() {
	x = y = 0;
}

_FORCE_INLINE_ Vector2 Vector2::plane_project(real_t p_d, const Vector2 &p_vec) const {
	return p_vec - *this * (dot(p_vec) - p_d);
}

_FORCE_INLINE_ bool Vector2::operator==(const Vector2 &p_vec2) const {
	return x == p_vec2.x && y == p_vec2.y;
}
_FORCE_INLINE_ bool Vector2::operator!=(const Vector2 &p_vec2) const {
	return x != p_vec2.x || y != p_vec2.y;
}

Vector2 Vector2::linear_interpolate(const Vector2 &p_to, real_t p_weight) const {
	Vector2 res = *this;

	res.x += (p_weight * (p_to.x - x));
	res.y += (p_weight * (p_to.y - y));

	return res;
}

Vector2 Vector2::slerp(const Vector2 &p_to, real_t p_weight) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!is_normalized(), Vector2(), "The start Vector2 must be normalized.");
#endif
	real_t theta = angle_to(p_to);
	return rotated(theta * p_weight);
}



Vector2 Vector2::linear_interpolate(const Vector2 &p_a, const Vector2 &p_b, real_t p_weight) {
	Vector2 res = p_a;

	res.x += (p_weight * (p_b.x - p_a.x));
	res.y += (p_weight * (p_b.y - p_a.y));

	return res;
}

typedef Vector2 Size2;
typedef Vector2 Point2;

// INTEGER STUFF

struct _NO_DISCARD_CLASS_ Vector2i {
	enum Axis {
		AXIS_X,
		AXIS_Y,
	};

	union {
		struct {
			union {
				int x;
				int width;
			};
			union {
				int y;
				int height;
			};
		};

		int coord[2];
	};

	_FORCE_INLINE_ int &operator[](int p_idx) {
		DEV_ASSERT((unsigned int)p_idx < 2);
		return coord[p_idx];
	}
	_FORCE_INLINE_ const int &operator[](int p_idx) const {
		DEV_ASSERT((unsigned int)p_idx < 2);
		return coord[p_idx];
	}

	Vector2i operator+(const Vector2i &p_v);
	void operator+=(const Vector2i &p_v);
	Vector2i operator-(const Vector2i &p_v);
	void operator-=(const Vector2i &p_v);
	Vector2i operator*(const Vector2i &p_v1);

	Vector2i operator*(const int &rvalue);
	void operator*=(const int &rvalue);

	Vector2i operator/(const Vector2i &p_v1);

	Vector2i operator/(const int &rvalue);

	void operator/=(const int &rvalue);

	Vector2i operator-();
	bool operator<(const Vector2i &p_vec2) const { return (x == p_vec2.x) ? (y < p_vec2.y) : (x < p_vec2.x); }
	bool operator>(const Vector2i &p_vec2) const { return (x == p_vec2.x) ? (y > p_vec2.y) : (x > p_vec2.x); }

	bool operator==(const Vector2i &p_vec2);
	bool operator!=(const Vector2i &p_vec2);

	real_t get_aspect() const { return width / (real_t)height; }

	operator String() const { return String::num(x) + ", " + String::num(y); }

	operator Vector2() const { return Vector2(x, y); }
	inline Vector2i(const Vector2 &p_vec2) {
		x = (int)p_vec2.x;
		y = (int)p_vec2.y;
	}
	inline Vector2i(int p_x, int p_y) {
		x = p_x;
		y = p_y;
	}
	inline Vector2i() {
		x = 0;
		y = 0;
	}
};

typedef Vector2i Size2i;
typedef Vector2i Point2i;

*/

#endif // VECTOR2_H
