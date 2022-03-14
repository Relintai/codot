/*************************************************************************/
/*  vector3.h                                                            */
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

#ifndef VECTOR3_H
#define VECTOR3_H

#include "core/math/math_funcs.h"
//#include "core/ustring.h"

struct Basis;

static const int VECTOR3_AXIS_COUNT = 3;

enum Vector3Axis {
	VECTOR3_AXIS_X = 0,
	VECTOR3_AXIS_Y,
	VECTOR3_AXIS_Z,
};

typedef struct _NO_DISCARD_CLASS_ Vector3 {
	union {
		struct {
			real_t x;
			real_t y;
			real_t z;
		};

		real_t coord[3];
	};
} Vector3;

extern _FORCE_INLINE_ void vector3_set_axis(Vector3 *v, int p_axis, real_t p_value) {
	v->coord[p_axis] = p_value;
}

extern _FORCE_INLINE_ const real_t vector3_get_axis(const Vector3 *v, int p_axis) {
	//DEV_ASSERT((unsigned int)p_axis < 3);
	return v->coord[p_axis];
}

/*
_FORCE_INLINE_ real_t &operator[](int p_axis) {
	DEV_ASSERT((unsigned int)p_axis < 3);
	return coord[p_axis];
}
*/

extern _FORCE_INLINE_ int vector3_min_axis(const Vector3 *v) {
	return v->x < v->y ? (v->x < v->z ? 0 : 2) : (v->y < v->z ? 1 : 2);
}

extern _FORCE_INLINE_ int vector3_max_axis(const Vector3 *v) {
	return v->x < v->y ? (v->y < v->z ? 2 : 1) : (v->x < v->z ? 2 : 0);
}

extern _FORCE_INLINE_ void vector3_set_all(Vector3 *self, real_t p_value) {
	self->x = self->y = self->z = p_value;
}

extern _FORCE_INLINE_ void vector3_set(Vector3 *self, real_t p_value_x, real_t p_value_y, real_t p_value_z) {
	self->x = p_value_x;
	self->y = p_value_y;
	self->z = p_value_z;
}

extern _FORCE_INLINE_ void vector3_setv(Vector3 *self, const Vector3 *other) {
	self->x = other->x;
	self->y = other->y;
	self->z = other->z;
}

extern _FORCE_INLINE_ Vector3 vector3_create(real_t p_value_x, real_t p_value_y, real_t p_value_z) {
	Vector3 v;

	v.x = p_value_x;
	v.y = p_value_y;
	v.z = p_value_z;

	return v;
}

extern _FORCE_INLINE_ Vector3 vector3_createv(const Vector3 *other) {
	Vector3 v;

	v.x = other->x;
	v.y = other->y;
	v.z = other->z;

	return v;
}

extern _FORCE_INLINE_ real_t vector3_length(const Vector3 *v) {
	real_t x2 = v->x * v->x;
	real_t y2 = v->y * v->y;
	real_t z2 = v->z * v->z;

	return math_sqrtf(x2 + y2 + z2);
}
extern _FORCE_INLINE_ real_t vector3_lengthc(const Vector3 v) {
	real_t x2 = v.x * v.x;
	real_t y2 = v.y * v.y;
	real_t z2 = v.z * v.z;

	return math_sqrtf(x2 + y2 + z2);
}

extern _FORCE_INLINE_ real_t vector3_length_squared(const Vector3 *v) {
	real_t x2 = v->x * v->x;
	real_t y2 = v->y * v->y;
	real_t z2 = v->z * v->z;

	return x2 + y2 + z2;
}
extern _FORCE_INLINE_ real_t vector3_length_squaredc(const Vector3 v) {
	real_t x2 = v.x * v.x;
	real_t y2 = v.y * v.y;
	real_t z2 = v.z * v.z;

	return x2 + y2 + z2;
}

extern _FORCE_INLINE_ void vector3_normalize(Vector3 *v) {
	real_t lengthsq = vector3_length_squared(v);
	if (lengthsq == 0) {
		v->x = v->y = v->z = 0;
	} else {
		real_t length = math_sqrtf(lengthsq);
		v->x /= length;
		v->y /= length;
		v->z /= length;
	}
}

extern _FORCE_INLINE_ Vector3 vector3_normalized(const Vector3 *v) {
	Vector3 ve = *v;
	vector3_normalize(&ve);
	return ve;
}

extern _FORCE_INLINE_ bool vector3_is_normalized(const Vector3 *v) {
	// use length_squared() instead of length() to avoid sqrt(), makes it more stringent.
	return math_is_equal_approxft(vector3_length_squared(v), 1, (real_t)UNIT_EPSILON);
}

extern _FORCE_INLINE_ Vector3 vector3_inverse(const Vector3 *v) {
	return vector3_create(1 / v->x, 1 / v->y, 1 / v->z);
}

extern _FORCE_INLINE_ void vector3_zero(Vector3 *v) {
	v->x = v->y = v->z = 0;
}

extern _FORCE_INLINE_ Vector3 vector3_cross(const Vector3 *v, const Vector3 *p_b) {
	return vector3_create(
			(v->y * p_b->z) - (v->z * p_b->y),
			(v->z * p_b->x) - (v->x * p_b->z),
			(v->x * p_b->y) - (v->y * p_b->x));
}

extern _FORCE_INLINE_ real_t vector3_dot(const Vector3 *v, const Vector3 *p_b) {
	return v->x * p_b->x + v->y * p_b->y + v->z * p_b->z;
}

extern _FORCE_INLINE_ Vector3 vector3_abs(const Vector3 *v) {
	return vector3_create(math_absf(v->x), math_absf(v->y), math_absf(v->z));
}

extern _FORCE_INLINE_ Vector3 vector3_sign(const Vector3 *v) {
	return vector3_create(SGN(v->x), SGN(v->y), SGN(v->z));
}

extern _FORCE_INLINE_ Vector3 vector3_floor(const Vector3 *v) {
	return vector3_create(math_floorf(v->x), math_floorf(v->y), math_floorf(v->z));
}

extern _FORCE_INLINE_ Vector3 vector3_ceil(const Vector3 *v) {
	return vector3_create(math_ceilf(v->x), math_ceilf(v->y), math_ceilf(v->z));
}

extern _FORCE_INLINE_ Vector3 vector3_round(const Vector3 *v) {
	return vector3_create(math_roundf(v->x), math_roundf(v->y), math_roundf(v->z));
}


// Operators 

extern _FORCE_INLINE_ Vector3 vector3_addv(const Vector3 *self, const Vector3 *p_v) {
	return vector3_create(self->x + p_v->x, self->y + p_v->y, self->z + p_v->z);
}
extern _FORCE_INLINE_ void vector3_add_eqv(Vector3 *self, const Vector3 *p_v) {
	self->x += p_v->x;
	self->y += p_v->y;
	self->z += p_v->z;
}

extern _FORCE_INLINE_ Vector3 vector3_subv(const Vector3 *self, const Vector3 *p_v) {
	return vector3_create(self->x - p_v->x, self->y - p_v->y, self->z - p_v->z);
}
extern _FORCE_INLINE_ Vector3 vector3_subvc(Vector3 self, Vector3 p_v) {
	return vector3_create(self.x - p_v.x, self.y - p_v.y, self.z - p_v.z);
}
extern _FORCE_INLINE_ void vector3_sub_eqv(Vector3 *self, const Vector3 *p_v) {
	self->x -= p_v->x;
	self->y -= p_v->y;
	self->z -= p_v->z;
}

extern _FORCE_INLINE_ Vector3 vector3_mulv(const Vector3 *self, const Vector3 *p_v1) {
	return vector3_create(self->x * p_v1->x, self->y * p_v1->y, self->z * p_v1->z);
}
extern _FORCE_INLINE_ Vector3 vector3_mulvc(Vector3 self, Vector3 p_v1) {
	return vector3_create(self.x * p_v1.x, self.y * p_v1.y, self.z * p_v1.z);
}
extern _FORCE_INLINE_ void vector3_mul_eqv(Vector3 *self, const Vector3 *rvalue) {
	self->x *= rvalue->x;
	self->y *= rvalue->y;
	self->z *= rvalue->z;
}

extern _FORCE_INLINE_ Vector3 vector3_divv(const Vector3 *self, const Vector3 *p_v1) {
	return vector3_create(self->x / p_v1->x, self->y / p_v1->y, self->z / p_v1->z);
}
extern _FORCE_INLINE_ void vector3_div_eqv(Vector3 *self, const Vector3 *rvalue) {
	self->x /= rvalue->x;
	self->y /= rvalue->y;
	self->z /= rvalue->z;
}

// Vector3 - scalar operators
extern _FORCE_INLINE_ Vector3 vector3_muls(const Vector3 *self, const real_t rvalue) {
	return vector3_create(self->x * rvalue, self->y * rvalue, self->z * rvalue);
};
extern _FORCE_INLINE_ Vector3 vector3_mulsc(Vector3 self, const real_t rvalue) {
	return vector3_create(self.x * rvalue, self.y * rvalue, self.z * rvalue);
};
extern _FORCE_INLINE_ void vector3_mul_eqs(Vector3 *self, const real_t rvalue) {
	self->x *= rvalue;
	self->y *= rvalue;
	self->z *= rvalue;
};

extern _FORCE_INLINE_ Vector3 vector3_divs(const Vector3 *self, const real_t rvalue) {
	return vector3_create(self->x / rvalue, self->y / rvalue, self->z / rvalue);
};
extern _FORCE_INLINE_ Vector3 vector3_divsc(Vector3 self, const real_t rvalue) {
	return vector3_create(self.x / rvalue, self.y / rvalue, self.z / rvalue);
};

extern _FORCE_INLINE_ void vector3_div_eqs(Vector3 *self, const real_t rvalue) {
	self->x /= rvalue;
	self->y /= rvalue;
	self->z /= rvalue;
};

/*
static _FORCE_INLINE_ Vector3 operator*(real_t p_scalar, const Vector3 *p_vec) {
	return p_vec * p_scalar;
}
*/

// Other
static _FORCE_INLINE_ Vector3 vector3_neg(const Vector3 *self) {
	return vector3_create(-(self->x), -(self->y), -(self->z));
}
static _FORCE_INLINE_ Vector3 vector3_negc(Vector3 self) {
	return vector3_create(-(self.x), -(self.y), -(self.z));
}

//operator==
static _FORCE_INLINE_ bool vector3_eq(const Vector3 *self, const Vector3 *p_vec3) {
	return self->x == p_vec3->x && self->y == p_vec3->y && self->z == p_vec3->z;
}
//operator!=
static _FORCE_INLINE_ bool vector3_neq(const Vector3 *self, const Vector3 *p_vec3) {
	return self->x != p_vec3->x || self->y != p_vec3->y || self->z != p_vec3->z;
}

//operator<
static _FORCE_INLINE_ bool vector3_lt(const Vector3 *self, const Vector3 *p_v) {
	if (self->x == p_v->x) {
		if (self->y == p_v->y) {
			return self->z < p_v->z;
		} else {
			return self->y < p_v->y;
		}
	} else {
		return self->x < p_v->x;
	}
}
static _FORCE_INLINE_ bool vector3_ltc(const Vector3 self, const Vector3 p_v) {
	if (self.x == p_v.x) {
		if (self.y == p_v.y) {
			return self.z < p_v.z;
		} else {
			return self.y < p_v.y;
		}
	} else {
		return self.x < p_v.x;
	}
}
//operator>
static _FORCE_INLINE_ bool vector3_gt(const Vector3 *self, const Vector3 *p_v) {
	if (self->x == p_v->x) {
		if (self->y == p_v->y) {
			return self->z > p_v->z;
		} else {
			return self->y > p_v->y;
		}
	} else {
		return self->x > p_v->x;
	}
}
static _FORCE_INLINE_ bool vector3_gtc(const Vector3 self, const Vector3 p_v) {
	if (self.x == p_v.x) {
		if (self.y == p_v.y) {
			return self.z > p_v.z;
		} else {
			return self.y > p_v.y;
		}
	} else {
		return self.x > p_v.x;
	}
}
//operator<=
static _FORCE_INLINE_ bool vector3_lte(const Vector3 *self, const Vector3 *p_v) {
	if (self->x == p_v->x) {
		if (self->y == p_v->y) {
			return self->z <= p_v->z;
		} else {
			return self->y < p_v->y;
		}
	} else {
		return self->x < p_v->x;
	}
}
static _FORCE_INLINE_ bool vector3_ltec(const Vector3 self, const Vector3 p_v) {
	if (self.x == p_v.x) {
		if (self.y == p_v.y) {
			return self.z <= p_v.z;
		} else {
			return self.y < p_v.y;
		}
	} else {
		return self.x < p_v.x;
	}
}
//operator>=
static _FORCE_INLINE_ bool vector3_gte(const Vector3 *self, const Vector3 *p_v) {
	if (self->x == p_v->x) {
		if (self->y == p_v->y) {
			return self->z >= p_v->z;
		} else {
			return self->y > p_v->y;
		}
	} else {
		return self->x > p_v->x;
	}
}
static _FORCE_INLINE_ bool vector3_gtec(const Vector3 self, const Vector3 p_v) {
	if (self.x == p_v.x) {
		if (self.y == p_v.y) {
			return self.z >= p_v.z;
		} else {
			return self.y > p_v.y;
		}
	} else {
		return self.x > p_v.x;
	}
}

/*
void rotate(const Vector3 &p_axis, real_t p_phi);
Vector3 rotated(const Vector3 &p_axis, real_t p_phi) const;
*/

extern _FORCE_INLINE_ Vector3 vector3_linear_interpolate(const Vector3 *v, const Vector3 *p_to, real_t p_weight) {
	return vector3_create(
			v->x + (p_weight * (p_to->x - v->x)),
			v->y + (p_weight * (p_to->y - v->y)),
			v->z + (p_weight * (p_to->z - v->z)));
}

/*
extern _FORCE_INLINE_ Vector3 vector3_slerp(const Vector3 *v, const Vector3 *p_to, real_t p_weight) {
	real_t theta = vector3_angle_to(p_to);
	Vector3 vc = vector3_cross(p_to);
	vector3_normalize(&vc);

	return vector3_rotated(&vc, theta * p_weight);
}
*/

/*
extern Vector3 vector3_limit_length(const Vector3 *vec);
extern Vector3 vector3_limit_lengthl(const Vector3 *vec, const real_t p_len);
*/

/*
extern _FORCE_INLINE_ real_t vector3_distance_to(const Vector3 *v, const Vector3 *p_to) {
	return vector3_lengthc(vector3_sub(p_to, v));
}

extern _FORCE_INLINE_ real_t vector3_distance_squared_to(const Vector3 *v, const Vector3 *p_to) {
	return vector3_length_quaredc(vector3_sub(p_to, v));
}

extern _FORCE_INLINE_ Vector3 vector3_posmod(const Vector3 *v, const real_t p_mod) {
	return Vector3(Math::fposmod(x, p_mod), Math::fposmod(y, p_mod), Math::fposmod(z, p_mod));
}

extern _FORCE_INLINE_ Vector3 vector3_posmodv(const Vector3 *v, const Vector3 *p_modv) {
	return Vector3(Math::fposmod(x, p_modv.x), Math::fposmod(y, p_modv.y), Math::fposmod(z, p_modv.z));
}

extern _FORCE_INLINE_ Vector3 vector3_project(const Vector3 *v, const Vector3 *p_to) {
	return p_to * (dot(p_to) / p_to.length_squared());
}

extern _FORCE_INLINE_ real_t vector3_angle_to(const Vector3 *v, const Vector3 *p_to) {
	return math_atan2f(cross(p_to).length(), dot(p_to));
}

extern _FORCE_INLINE_ real_t vector3_signed_angle_to(const Vector3 *v, const Vector3 *p_to, const Vector3 *p_axis) {
	Vector3 cross_to = cross(p_to);
	real_t unsigned_angle = Math::atan2(cross_to.length(), dot(p_to));
	real_t sign = cross_to.dot(p_axis);
	return (sign < 0) ? -unsigned_angle : unsigned_angle;
}

extern _FORCE_INLINE_ Vector3 vector3_direction_to(const Vector3 *v, const Vector3 *p_to) {
	Vector3 ret(p_to.x - x, p_to.y - y, p_to.z - z);
	ret.normalize();
	return ret;
}
*/


/*

void snap(Vector3 p_val);
Vector3 snapped(Vector3 p_val) const;


// Static Methods between 2 vector3s 

Vector3 cubic_interpolate(const Vector3 &p_b, const Vector3 &p_pre_a, const Vector3 &p_post_b, real_t p_weight) const;
Vector3 cubic_interpolaten(const Vector3 &p_b, const Vector3 &p_pre_a, const Vector3 &p_post_b, real_t p_weight) const;
Vector3 move_toward(const Vector3 &p_to, const real_t p_delta) const;


Basis outer(const Vector3 &p_b) const;
Basis to_diagonal_matrix() const;

_FORCE_INLINE_ Vector3 slide(const Vector3 &p_normal) const;
_FORCE_INLINE_ Vector3 bounce(const Vector3 &p_normal) const;
_FORCE_INLINE_ Vector3 reflect(const Vector3 &p_normal) const;

bool is_equal_approx(const Vector3 &p_v) const;
inline bool is_equal_approx(const Vector3 &p_v, real_t p_tolerance) const;

operator String() const;

_FORCE_INLINE_ Vector3(real_t p_x, real_t p_y, real_t p_z) {
	x = p_x;
	y = p_y;
	z = p_z;
}
_FORCE_INLINE_ Vector3() {
	x = y = z = 0;
}

*/

//----

/*

_FORCE_INLINE_ Vector3 vec3_cross(const Vector3 &p_a, const Vector3 &p_b) {
	return p_a.cross(p_b);
}

_FORCE_INLINE_ real_t vec3_dot(const Vector3 &p_a, const Vector3 &p_b) {
	return p_a.dot(p_b);
}

// slide returns the component of the vector along the given plane, specified by its normal vector.
Vector3 Vector3::slide(const Vector3 &p_normal) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector3(), "The normal Vector3 must be normalized.");
#endif
	return *this - p_normal * this->dot(p_normal);
}

Vector3 Vector3::bounce(const Vector3 &p_normal) const {
	return -reflect(p_normal);
}

Vector3 Vector3::reflect(const Vector3 &p_normal) const {
#ifdef MATH_CHECKS
	ERR_FAIL_COND_V_MSG(!p_normal.is_normalized(), Vector3(), "The normal Vector3 must be normalized.");
#endif
	return 2 * p_normal * this->dot(p_normal) - *this;
}

bool Vector3::is_equal_approx(const Vector3 &p_v, real_t p_tolerance) const {
	return Math::is_equal_approx(x, p_v.x, p_tolerance) && Math::is_equal_approx(y, p_v.y, p_tolerance) && Math::is_equal_approx(z, p_v.z, p_tolerance);
}

*/

#endif // VECTOR3_H
