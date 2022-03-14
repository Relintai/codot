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

extern _FORCE_INLINE_ Quat quat_create(real_t p_x, real_t p_y, real_t p_z, real_t p_w) {
	Quat q;

	q.x = p_x;
	q.y = p_y;
	q.z = p_z;
	q.w = p_z;

	return q;
}

extern _FORCE_INLINE_ Quat quat_createv(const Quat *other) {
	Quat q;

	q.x = other->x;
	q.y = other->y;
	q.z = other->z;
	q.w = other->w;

	return q;
}

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
	return quat_create(self->x + p_q->x, self->y + p_q->y, self->z + p_q->z, self->w + p_q->w);
}
extern _FORCE_INLINE_ void quat_add_eq(Quat *self, const Quat *p_q) {
	self->x += p_q->x;
	self->y += p_q->y;
	self->z += p_q->z;
	self->w += p_q->w;
}

extern _FORCE_INLINE_ Quat quat_subv(const Quat *self, const Quat *p_v) {
	return quat_create(self->x - p_v->x, self->y - p_v->y, self->z - p_v->z, self->w - p_v->w);
}
extern _FORCE_INLINE_ Quat quat_subvc(const Quat self, const Quat p_v) {
	return quat_create(self.x - p_v.x, self.y - p_v.y, self.z - p_v.z, self.w - p_v.w);
}
extern _FORCE_INLINE_ void quat_sub_eqv(Quat *self, const Quat *p_q) {
	self->x -= p_q->x;
	self->y -= p_q->y;
	self->z -= p_q->z;
	self->w -= p_q->w;
}

// Other
extern _FORCE_INLINE_ Quat quat_neg(const Quat *self) {
	return quat_create(-(self->x), -(self->y), -(self->z), -(self->w));
}
extern _FORCE_INLINE_ Quat quat_negc(const Quat self) {
	return quat_create(-(self.x), -(self.y), -(self.z), -(self.w));
}

extern _FORCE_INLINE_ Quat quat_mulq(const Quat *self, const Quat *p_v1) {
	return quat_create(self->x * p_v1->x, self->y * p_v1->y, self->z * p_v1->z, self->w * p_v1->w);
}
extern _FORCE_INLINE_ Quat quat_mulqc(const Quat self, const Quat p_q) {
	return quat_create(self.x * p_q.x, self.y * p_q.y, self.z * p_q.z, self.w * p_q.w);
}
extern _FORCE_INLINE_ void quat_mul_eqq(Quat *self, const Quat *rvalue) {
	self->x *= rvalue->x;
	self->y *= rvalue->y;
	self->z *= rvalue->z;
	self->w *= rvalue->w;
}

extern _FORCE_INLINE_ Quat quat_mulv(const Quat *self, const Vector3 *v) {
	return quat_create(self->w * v->x + self->y * v->z - self->z * v->y,
			self->w * v->y + self->z * v->x - self->x * v->z,
			self->w * v->z + self->x * v->y - self->y * v->x,
			-self->x * v->x - self->y * v->y - self->z * v->z);
}
extern _FORCE_INLINE_ Quat quat_mulvc(const Quat self, Vector3 v) {
	return quat_create(self.w * v.x + self.y * v.z - self.z * v.y,
			self.w * v.y + self.z * v.x - self.x * v.z,
			self.w * v.z + self.x * v.y - self.y * v.x,
			-self.x * v.x - self.y * v.y - self.z * v.z);
}

extern _FORCE_INLINE_ Quat quat_muls(const Quat *self, const real_t rvalue) {
	return quat_create(self->x * rvalue, self->y * rvalue, self->z * rvalue, self->w * rvalue);
};
extern _FORCE_INLINE_ Quat quat_mulsc(Quat self, const real_t rvalue) {
	return quat_create(self.x * rvalue, self.y * rvalue, self.z * rvalue, self.w * rvalue);
};
extern _FORCE_INLINE_ void quat_mul_eqs(Quat *self, const real_t rvalue) {
	self->x *= rvalue;
	self->y *= rvalue;
	self->z *= rvalue;
	self->w *= rvalue;
};

extern _FORCE_INLINE_ Quat quat_divs(const Quat *self, const real_t rvalue) {
	real_t r = 1 / rvalue;
	return quat_create(self->x * r, self->y * r, self->z * r, self->w * r);
};
extern _FORCE_INLINE_ Quat quat_divsc(Quat self, const real_t rvalue) {
	real_t r = 1 / rvalue;
	return quat_create(self.x * r, self.y * r, self.z * r, self.w * r);
};
extern _FORCE_INLINE_ void quat_div_eqs(Quat *self, const real_t rvalue) {
	real_t r = 1 / rvalue;

	self->x *= r;
	self->y *= r;
	self->z *= r;
	self->w *= r;
};

	/*


		bool is_equal_approx(const Quat &p_quat) const;
		real_t length() const;
		void normalize();
		Quat normalized() const;
		bool is_normalized() const;
		Quat inverse() const;

		real_t angle_to(const Quat &p_to) const;

		void set_euler_xyz(const Vector3 &p_euler);
		Vector3 get_euler_xyz() const;
		void set_euler_yxz(const Vector3 &p_euler);
		Vector3 get_euler_yxz() const;

		void set_euler(const Vector3 &p_euler) { set_euler_yxz(p_euler); };
		Vector3 get_euler() const { return get_euler_yxz(); };

		Quat slerp(const Quat &p_to, const real_t &p_weight) const;
		Quat slerpni(const Quat &p_to, const real_t &p_weight) const;
		Quat cubic_slerp(const Quat &p_b, const Quat &p_pre_a, const Quat &p_post_b, const real_t &p_weight) const;

		void set_axis_angle(const Vector3 &axis, const real_t &angle);
		_FORCE_INLINE_ void get_axis_angle(Vector3 &r_axis, real_t &r_angle) const {
			r_angle = 2 * Math::acos(w);
			real_t r = ((real_t)1) / Math::sqrt(1 - w * w);
			r_axis.x = x * r;
			r_axis.y = y * r;
			r_axis.z = z * r;
		}



		_FORCE_INLINE_ Vector3 xform(const Vector3 &v) const {
	#ifdef MATH_CHECKS
			ERR_FAIL_COND_V_MSG(!is_normalized(), v, "The quaternion must be normalized.");
	#endif
			Vector3 u(x, y, z);
			Vector3 uv = u.cross(v);
			return v + ((uv * w) + u.cross(uv)) * ((real_t)2);
		}

		operator String() const;

		inline void set(real_t p_x, real_t p_y, real_t p_z, real_t p_w) {
			x = p_x;
			y = p_y;
			z = p_z;
			w = p_w;
		}
		inline Quat(real_t p_x, real_t p_y, real_t p_z, real_t p_w) :
				x(p_x),
				y(p_y),
				z(p_z),
				w(p_w) {
		}
		Quat(const Vector3 &axis, const real_t &angle) { set_axis_angle(axis, angle); }

		Quat(const Vector3 &euler) { set_euler(euler); }
		Quat(const Quat &p_q) :
				x(p_q.x),
				y(p_q.y),
				z(p_q.z),
				w(p_q.w) {
		}

		Quat &operator=(const Quat &p_q) {
			x = p_q.x;
			y = p_q.y;
			z = p_q.z;
			w = p_q.w;
			return *this;
		}

		Quat(const Vector3 &v0, const Vector3 &v1) // shortest arc
		{
			Vector3 c = v0.cross(v1);
			real_t d = v0.dot(v1);

			if (d < -1 + (real_t)CMP_EPSILON) {
				x = 0;
				y = 1;
				z = 0;
				w = 0;
			} else {
				real_t s = Math::sqrt((1 + d) * 2);
				real_t rs = 1 / s;

				x = c.x * rs;
				y = c.y * rs;
				z = c.z * rs;
				w = s * 0.5f;
			}
		}

		inline Quat() :
				x(0),
				y(0),
				z(0),
				w(1) {
		}
	//-----




		_FORCE_INLINE_ bool operator==(const Quat &p_quat) const;
		_FORCE_INLINE_ bool operator!=(const Quat &p_quat) const;

	bool Quat::operator==(const Quat &p_quat) const {
		return x == p_quat.x && y == p_quat.y && z == p_quat.z && w == p_quat.w;
	}

	bool Quat::operator!=(const Quat &p_quat) const {
		return x != p_quat.x || y != p_quat.y || z != p_quat.z || w != p_quat.w;
	}
	*/

#endif
