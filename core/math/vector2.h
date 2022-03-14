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
	VECTOR2_AXIS_X = 0,
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

static _FORCE_INLINE_ Vector2 vector2_createv(const Vector2 *other) {
	Vector2 v;

	v.x = other->x;
	v.y = other->y;

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
static _FORCE_INLINE_ Vector2 vector2_subvc(Vector2 self, Vector2 p_v) {
	return vector2_create(self.x - p_v.x, self.y - p_v.y);
}
static _FORCE_INLINE_ void vector2_sub_eqv(Vector2 *self, const Vector2 *p_v) {
	self->x -= p_v->x;
	self->y -= p_v->y;
}
static _FORCE_INLINE_ Vector2 vector2_mulv(const Vector2 *self, const Vector2 *p_v1) {
	return vector2_create(self->x * p_v1->x, self->y * p_v1->y);
}
static _FORCE_INLINE_ Vector2 vector2_mulvc(Vector2 self, Vector2 p_v1) {
	return vector2_create(self.x * p_v1.x, self.y * p_v1.y);
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
static _FORCE_INLINE_ Vector2 vector2_mulsc(Vector2 self, const real_t rvalue) {
	return vector2_create(self.x * rvalue, self.y * rvalue);
};
static _FORCE_INLINE_ void vector2_mul_eqs(Vector2 *self, const real_t rvalue) {
	self->x *= rvalue;
	self->y *= rvalue;
};

static _FORCE_INLINE_ Vector2 vector2_divs(const Vector2 *self, const real_t rvalue) {
	return vector2_create(self->x / rvalue, self->y / rvalue);
};
static _FORCE_INLINE_ Vector2 vector2_divsc(Vector2 self, const real_t rvalue) {
	return vector2_create(self.x / rvalue, self.y / rvalue);
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
static _FORCE_INLINE_ Vector2 vector2_negc(Vector2 self) {
	return vector2_create(-(self.x), -(self.y));
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
static _FORCE_INLINE_ Vector2 vector2_tangent(const Vector2 *self) {
	return vector2_create(self->y, -(self->x));
}

Vector2 vector2_posmod(Vector2 *self, const real_t p_mod);
Vector2 vector2_posmodv(Vector2 *self, const Vector2 *p_modv);
Vector2 vector2_project(Vector2 *self, const Vector2 *p_to);

static _FORCE_INLINE_ Vector2 vector2_plane_project(const Vector2 *self, real_t p_d, const Vector2 *p_vec) {
	Vector2 v = vector2_muls(self, vector2_dot(self, p_vec) - p_d);
	return vector2_subv(p_vec, &v);
}

Vector2 vector2_clamped(Vector2 *self, real_t p_len);
Vector2 vector2_limit_length(Vector2 *self, const real_t p_len);
Vector2 vector2_limit_length1(Vector2 *self);

real_t vector2_aspect(const Vector2 *self) {
	return self->width / self->height;
}

/*
String vector2_to_string(const Vector2 *self) const {
	return String::num(x) + ", " + String::num(y);
}
*/

//operator==
static _FORCE_INLINE_ bool vector2_eq(const Vector2 *self, const Vector2 *p_vec2) {
	return self->x == p_vec2->x && self->y == p_vec2->y;
}
//operator!=
static _FORCE_INLINE_ bool vector2_neq(const Vector2 *self, const Vector2 *p_vec2) {
	return self->x != p_vec2->x || self->y != p_vec2->y;
}

static _FORCE_INLINE_ Vector2 vector2_linear_interpolate(const Vector2 *p_a, const Vector2 *p_b, real_t p_weight) {
	Vector2 res = vector2_createv(p_a);

	res.x += (p_weight * (p_b->x - p_a->x));
	res.y += (p_weight * (p_b->y - p_a->y));

	return res;
}

static _FORCE_INLINE_ Vector2 vector2_vector2_slerp(const Vector2 *self, const Vector2 *p_to, real_t p_weight) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_V_MSG(!is_normalized(), Vector2(), "The start Vector2 must be normalized.");
#endif
	real_t theta = vector2_angle_to(self, p_to);
	return vector2_rotated(self, theta * p_weight);
}

//operator<
static _FORCE_INLINE_ bool vector2_lt(const Vector2 *self, const Vector2 *p_vec2) {
	return self->x == p_vec2->x ? (self->y < p_vec2->y) : (self->x < p_vec2->x);
}
//operator>
static _FORCE_INLINE_ bool vector2_gt(const Vector2 *self, const Vector2 *p_vec2) {
	return self->x == p_vec2->x ? (self->y > p_vec2->y) : (self->x > p_vec2->x);
}
//operator<=
static _FORCE_INLINE_ bool vector2_lte(const Vector2 *self, const Vector2 *p_vec2) {
	return self->x == p_vec2->x ? (self->y <= p_vec2->y) : (self->x < p_vec2->x);
}
//operator>=
static _FORCE_INLINE_ bool vector2_gte(const Vector2 *self, const Vector2 *p_vec2) {
	return self->x == p_vec2->x ? (self->y >= p_vec2->y) : (self->x > p_vec2->x);
}

Vector2 vector2_sign(Vector2 *self);
Vector2 vector2_floor(Vector2 *self);
Vector2 vector2_ceil(Vector2 *self);
Vector2 vector2_round(Vector2 *self);
Vector2 vector2_snapped(Vector2 *self, const Vector2 *p_by);

Vector2 vector2_cubic_interpolate(const Vector2 *self, const Vector2 *p_b, const Vector2 *p_pre_a, const Vector2 *p_post_b, real_t p_weight);
Vector2 vector2_move_toward(const Vector2 *self, const Vector2 *p_to, const real_t p_delta);

Vector2 vector2_slide(const Vector2 *self, const Vector2 *p_normal);
Vector2 vector2_bounce(const Vector2 *self, const Vector2 *p_normal);
Vector2 vector2_reflect(const Vector2 *self, const Vector2 *p_normal);

bool vector2_is_equal_approx(const Vector2 *self, const Vector2 *p_v);

typedef Vector2 Size2;
typedef Vector2 Point2;

// INTEGER STUFF

typedef struct _NO_DISCARD_CLASS_ Vector2i {
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
} Vector2i;

static _FORCE_INLINE_ int vector2i_get_axis(const Vector2i *v, int p_idx) {
	//DEV_ASSERT((unsigned int)p_idx < 2);
	return v->coord[p_idx];
}

/*
//not needed
static _FORCE_INLINE_ const int &operator[](int p_idx) const {
	DEV_ASSERT((unsigned int)p_idx < 2);
	return coord[p_idx];
}
*/

static _FORCE_INLINE_ void vector2i_set_all(Vector2i *self, real_t p_value) {
	self->x = self->y = p_value;
}

static _FORCE_INLINE_ void vector2i_set(Vector2i *self, real_t p_value_x, real_t p_value_y) {
	self->x = p_value_x;
	self->y = p_value_y;
}

static _FORCE_INLINE_ Vector2i vector2i_create(real_t p_value_x, real_t p_value_y) {
	Vector2i v;

	v.x = p_value_x;
	v.y = p_value_y;

	return v;
}

static _FORCE_INLINE_ Vector2i vector2i_createv(const Vector2i *other) {
	Vector2i v;

	v.x = other->x;
	v.y = other->y;

	return v;
}

// Vector2i - Vector2i operators
static _FORCE_INLINE_ Vector2i vector2i_addv(const Vector2i *self, const Vector2i *p_v) {
	return vector2i_create(self->x + p_v->x, self->y + p_v->y);
}
static _FORCE_INLINE_ void vector2i_add_eqv(Vector2i *self, const Vector2i *p_v) {
	self->x += p_v->x;
	self->y += p_v->y;
}
static _FORCE_INLINE_ Vector2i vector2i_subv(const Vector2i *self, const Vector2i *p_v) {
	return vector2i_create(self->x - p_v->x, self->y - p_v->y);
}
static _FORCE_INLINE_ Vector2i vector2i_subvc(Vector2i self, Vector2i p_v) {
	return vector2i_create(self.x - p_v.x, self.y - p_v.y);
}
static _FORCE_INLINE_ void vector2i_sub_eqv(Vector2i *self, const Vector2i *p_v) {
	self->x -= p_v->x;
	self->y -= p_v->y;
}
static _FORCE_INLINE_ Vector2i vector2i_mulv(const Vector2i *self, const Vector2i *p_v1) {
	return vector2i_create(self->x * p_v1->x, self->y * p_v1->y);
}
static _FORCE_INLINE_ Vector2i vector2i_mulvc(Vector2i self, Vector2i p_v1) {
	return vector2i_create(self.x * p_v1.x, self.y * p_v1.y);
}
static _FORCE_INLINE_ void vector2i_mul_eqv(Vector2i *self, const Vector2i *rvalue) {
	self->x *= rvalue->x;
	self->y *= rvalue->y;
}
static _FORCE_INLINE_ Vector2i vector2i_divv(const Vector2i *self, const Vector2i *p_v1) {
	return vector2i_create(self->x / p_v1->x, self->y / p_v1->y);
}
static _FORCE_INLINE_ void vector2i_div_eqv(Vector2i *self, const Vector2i *rvalue) {
	self->x /= rvalue->x;
	self->y /= rvalue->y;
}

// Vector2i - scalar operators
static _FORCE_INLINE_ Vector2i vector2i_muls(const Vector2i *self, const int rvalue) {
	return vector2i_create(self->x * rvalue, self->y * rvalue);
};
static _FORCE_INLINE_ Vector2i vector2i_mulsc(Vector2i self, const int rvalue) {
	return vector2i_create(self.x * rvalue, self.y * rvalue);
};
static _FORCE_INLINE_ void vector2i_mul_eqs(Vector2i *self, const int rvalue) {
	self->x *= rvalue;
	self->y *= rvalue;
};

static _FORCE_INLINE_ Vector2i vector2i_divs(const Vector2i *self, const int rvalue) {
	return vector2i_create(self->x / rvalue, self->y / rvalue);
};
static _FORCE_INLINE_ Vector2i vector2i_divsc(Vector2i self, const int rvalue) {
	return vector2i_create(self.x / rvalue, self.y / rvalue);
};

static _FORCE_INLINE_ void vector2i_div_eqs(Vector2i *self, const int rvalue) {
	self->x /= rvalue;
	self->y /= rvalue;
};

/*
static _FORCE_INLINE_ Vector2i operator*(real_t p_scalar, const Vector2i *p_vec) {
	return p_vec * p_scalar;
}
*/

// Other
static _FORCE_INLINE_ Vector2i vector2i_neg(const Vector2i *self) {
	return vector2i_create(-(self->x), -(self->y));
}
static _FORCE_INLINE_ Vector2i vector2i_negc(Vector2i self) {
	return vector2i_create(-(self.x), -(self.y));
}

//operator==
static _FORCE_INLINE_ bool vector2i_eq(const Vector2i *self, const Vector2i *p_vec2) {
	return self->x == p_vec2->x && self->y == p_vec2->y;
}
//operator!=
static _FORCE_INLINE_ bool vector2i_neq(const Vector2i *self, const Vector2i *p_vec2) {
	return self->x != p_vec2->x || self->y != p_vec2->y;
}
//operator<
static _FORCE_INLINE_ bool vector2i_lt(const Vector2i *self, const Vector2i *p_vec2) {
	return self->x == p_vec2->x ? (self->y < p_vec2->y) : (self->x < p_vec2->x);
}
//operator>
static _FORCE_INLINE_ bool vector2i_gt(const Vector2i *self, const Vector2i *p_vec2) {
	return self->x == p_vec2->x ? (self->y > p_vec2->y) : (self->x > p_vec2->x);
}
//operator<=
static _FORCE_INLINE_ bool vector2i_lte(const Vector2i *self, const Vector2i *p_vec2) {
	return self->x == p_vec2->x ? (self->y <= p_vec2->y) : (self->x < p_vec2->x);
}
//operator>=
static _FORCE_INLINE_ bool vector2i_gte(const Vector2i *self, const Vector2i *p_vec2) {
	return self->x == p_vec2->x ? (self->y >= p_vec2->y) : (self->x > p_vec2->x);
}

static _FORCE_INLINE_ real_t vector2i_get_aspect(const Vector2i *self) {
	return (self->width / (real_t)self->height);
}

/*
String vector2i_to_string(const Vector2i *self) const {
	return String::num(x) + ", " + String::num(y);
}
*/

static _FORCE_INLINE_ Vector2 vector2i_to_vector2(const Vector2i *self) {
	return vector2_create(self->x, self->y);
}

typedef Vector2i Size2i;
typedef Vector2i Point2i;

#endif // VECTOR2_H
