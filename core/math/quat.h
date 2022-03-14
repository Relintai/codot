/*************************************************************************/
/*  quat.h                                                               */
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

#ifndef QUAT_H
#define QUAT_H

#include "core/math/math_defs.h"
#include "core/math/math_funcs.h"
#include "core/math/vector3.h"
//#include "core/ustring.h"

typedef struct _NO_DISCARD_CLASS_ Quat {
	real_t x, y, z, w;
} Quat;

extern _FORCE_INLINE_ void quat_set(Quat *self, real_t p_x, real_t p_y, real_t p_z, real_t p_w) {
	self->x = p_x;
	self->y = p_y;
	self->z = p_z;
	self->w = p_z;
}

extern _FORCE_INLINE_ void quat_setq(Quat *self, const Quat *p_q) {
	self->x = p_q->x;
	self->y = p_q->y;
	self->z = p_q->z;
	self->w = p_q->w;
}

extern _FORCE_INLINE_ Quat quat_create() {
	Quat q;

	q.x = 0;
	q.y = 0;
	q.z = 0;
	q.w = 1;

	return q;
}

extern _FORCE_INLINE_ Quat quat_creater(real_t p_x, real_t p_y, real_t p_z, real_t p_w) {
	Quat q;

	q.x = p_x;
	q.y = p_y;
	q.z = p_z;
	q.w = p_z;

	return q;
}

extern _FORCE_INLINE_ Quat quat_createq(const Quat *other) {
	Quat q;

	q.x = other->x;
	q.y = other->y;
	q.z = other->z;
	q.w = other->w;

	return q;
}

extern _FORCE_INLINE_ Quat quat_createv(const Vector3 *v0, const Vector3 *v1) {
	Quat q;

	Vector3 c = vector3_cross(v0, v1);
	real_t d = vector3_dot(v0, v1);

	if (d < -1 + (real_t)CMP_EPSILON) {
		q.x = 0;
		q.y = 1;
		q.z = 0;
		q.w = 0;
	} else {
		real_t s = math_sqrtf((1 + d) * 2);
		real_t rs = 1 / s;

		q.x = c.x * rs;
		q.y = c.y * rs;
		q.z = c.z * rs;
		q.w = s * 0.5f;
	}

	return q;
}

Quat quat_create_ae(const Vector3 *axis, const real_t angle);
Quat quat_create_euler(const Vector3 *euler);

real_t quat_dot(const Quat *self, const Quat *p_q) {
	return self->x * p_q->x + self->y * p_q->y + self->z * p_q->z + self->w * p_q->w;
}
real_t quat_dotc(const Quat self, const Quat p_q) {
	return self.x * p_q.x + self.y * p_q.y + self.z * p_q.z + self.w * p_q.w;
}

real_t quat_length_squared(const Quat *self) {
	return quat_dot(self, self);
}
real_t quat_length_squaredc(const Quat self) {
	return quat_dotc(self, self);
}

extern _FORCE_INLINE_ Quat quat_add(const Quat *self, const Quat *p_q) {
	return quat_creater(self->x + p_q->x, self->y + p_q->y, self->z + p_q->z, self->w + p_q->w);
}
extern _FORCE_INLINE_ void quat_add_eq(Quat *self, const Quat *p_q) {
	self->x += p_q->x;
	self->y += p_q->y;
	self->z += p_q->z;
	self->w += p_q->w;
}

extern _FORCE_INLINE_ Quat quat_subv(const Quat *self, const Quat *p_v) {
	return quat_creater(self->x - p_v->x, self->y - p_v->y, self->z - p_v->z, self->w - p_v->w);
}
extern _FORCE_INLINE_ Quat quat_subvc(const Quat self, const Quat p_v) {
	return quat_creater(self.x - p_v.x, self.y - p_v.y, self.z - p_v.z, self.w - p_v.w);
}
extern _FORCE_INLINE_ void quat_sub_eqv(Quat *self, const Quat *p_q) {
	self->x -= p_q->x;
	self->y -= p_q->y;
	self->z -= p_q->z;
	self->w -= p_q->w;
}

// Other
extern _FORCE_INLINE_ Quat quat_neg(const Quat *self) {
	return quat_creater(-(self->x), -(self->y), -(self->z), -(self->w));
}
extern _FORCE_INLINE_ Quat quat_negc(const Quat self) {
	return quat_creater(-(self.x), -(self.y), -(self.z), -(self.w));
}

extern _FORCE_INLINE_ Quat quat_mulq(const Quat *self, const Quat *p_v1) {
	return quat_creater(self->x * p_v1->x, self->y * p_v1->y, self->z * p_v1->z, self->w * p_v1->w);
}
extern _FORCE_INLINE_ Quat quat_mulqc(const Quat self, const Quat p_q) {
	return quat_creater(self.x * p_q.x, self.y * p_q.y, self.z * p_q.z, self.w * p_q.w);
}
extern _FORCE_INLINE_ void quat_mul_eqq(Quat *self, const Quat *p_q) {
	quat_set(self,
			self->w * p_q->x + self->x * p_q->w + self->y * p_q->z - self->z * p_q->y,
			self->w * p_q->y + self->y * p_q->w + self->z * p_q->x - self->x * p_q->z,
			self->w * p_q->z + self->z * p_q->w + self->x * p_q->y - self->y * p_q->x,
			self->w * p_q->w - self->x * p_q->x - self->y * p_q->y - self->z * p_q->z);
}

extern _FORCE_INLINE_ Quat quat_mulv(const Quat *self, const Vector3 *v) {
	return quat_creater(self->w * v->x + self->y * v->z - self->z * v->y,
			self->w * v->y + self->z * v->x - self->x * v->z,
			self->w * v->z + self->x * v->y - self->y * v->x,
			-self->x * v->x - self->y * v->y - self->z * v->z);
}
extern _FORCE_INLINE_ Quat quat_mulvc(const Quat self, Vector3 v) {
	return quat_creater(self.w * v.x + self.y * v.z - self.z * v.y,
			self.w * v.y + self.z * v.x - self.x * v.z,
			self.w * v.z + self.x * v.y - self.y * v.x,
			-self.x * v.x - self.y * v.y - self.z * v.z);
}

extern _FORCE_INLINE_ Quat quat_muls(const Quat *self, const real_t rvalue) {
	return quat_creater(self->x * rvalue, self->y * rvalue, self->z * rvalue, self->w * rvalue);
};
extern _FORCE_INLINE_ Quat quat_mulsc(Quat self, const real_t rvalue) {
	return quat_creater(self.x * rvalue, self.y * rvalue, self.z * rvalue, self.w * rvalue);
};
extern _FORCE_INLINE_ void quat_mul_eqs(Quat *self, const real_t rvalue) {
	self->x *= rvalue;
	self->y *= rvalue;
	self->z *= rvalue;
	self->w *= rvalue;
};

extern _FORCE_INLINE_ Quat quat_divs(const Quat *self, const real_t rvalue) {
	real_t r = 1 / rvalue;
	return quat_creater(self->x * r, self->y * r, self->z * r, self->w * r);
};
extern _FORCE_INLINE_ Quat quat_divsc(Quat self, const real_t rvalue) {
	real_t r = 1 / rvalue;
	return quat_creater(self.x * r, self.y * r, self.z * r, self.w * r);
};
extern _FORCE_INLINE_ void quat_div_eqs(Quat *self, const real_t rvalue) {
	real_t r = 1 / rvalue;

	self->x *= r;
	self->y *= r;
	self->z *= r;
	self->w *= r;
};

//operator==
extern _FORCE_INLINE_ bool quat_eq(const Quat *self, const Quat *p_q) {
	return self->x == p_q->x && self->y == p_q->y && self->z == p_q->z && self->w == p_q->w;
}
//operator!=
extern _FORCE_INLINE_ bool quat_neq(const Quat *self, const Quat *p_q) {
	return self->x != p_q->x || self->y != p_q->y || self->z != p_q->z || self->w != p_q->w;
}

void quat_set_axis_angle(Quat *self, const Vector3 *axis, const real_t angle);
extern _FORCE_INLINE_ void quat_get_axis_angle(const Quat *self, Vector3 *r_axis, real_t *r_angle) {
	*r_angle = 2 * math_acosf(self->w);
	real_t r = ((real_t)1) / math_sqrtf(1 - self->w * self->w);
	r_axis->x = self->x * r;
	r_axis->y = self->y * r;
	r_axis->z = self->z * r;
}

extern _FORCE_INLINE_ Vector3 quat_xform(const Quat *self, const Vector3 *v) {
#ifdef MATH_CHECKS
	//ERR_FAIL_COND_V_MSG(!is_normalized(), v, "The quaternion must be normalized.");
#endif
	Vector3 u = vector3_create(self->x, self->y, self->z);
	Vector3 uv = vector3_cross(&u, v);
	Vector3 uvc = vector3_cross(&u, &uv);
	Vector3 uvw = vector3_muls(&uv, self->w);
	Vector3 f = vector3_mulsc(vector3_addv(&uvw, &uvc), ((real_t)2));
	return vector3_addv(v, &f);
}

real_t quat_angle_to(const Quat *self, const Quat *p_to);

bool quat_is_equal_approx(const Quat *self, const Quat *p_quat);
real_t quat_length(const Quat *self);
void quat_normalize(Quat *self);
Quat quat_normalized(const Quat *self);
bool quat_is_normalized(const Quat *self);
Quat quat_inverse(const Quat *self);

void quat_set_euler_xyz(Quat *self, const Vector3 *p_euler);
Vector3 quat_get_euler_xyz(const Quat *self);
void quat_set_euler_yxz(Quat *self, const Vector3 *p_euler);
Vector3 quat_get_euler_yxz(const Quat *self);

void quat_set_euler(Quat *self, const Vector3 *p_euler) {
	quat_set_euler_yxz(self, p_euler);
};
Vector3 quat_get_euler(const Quat *self) {
	return quat_get_euler_yxz(self);
};

Quat quat_slerp(const Quat *self, const Quat *p_to, const real_t p_weight);
Quat quat_slerpni(const Quat *self, const Quat *p_to, const real_t p_weight);
Quat quat_cubic_slerp(const Quat *self, const Quat *p_b, const Quat *p_pre_a, const Quat *p_post_b, const real_t p_weight);

/*
	operator String() const;
*/

#endif
