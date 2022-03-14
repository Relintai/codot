/*************************************************************************/
/*  basis.h                                                              */
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

#ifndef BASIS_H
#define BASIS_H

#include "core/math/quat.h"
#include "core/math/vector3.h"

typedef struct _NO_DISCARD_CLASS_ Basis {
	Vector3 elements[3];
} Basis;

extern _FORCE_INLINE_ Basis basis_create() {
	Basis b;

	vector3_set(&b.elements[0], 1, 0, 0);
	vector3_set(&b.elements[1], 0, 1, 0);
	vector3_set(&b.elements[2], 0, 0, 1);

	return b;
}

extern _FORCE_INLINE_ Basis basis_createv(const Vector3 *row0, const Vector3 *row1, const Vector3 *row2) {
	Basis b;

	b.elements[0] = *row0;
	b.elements[1] = *row1;
	b.elements[2] = *row2;

	return b;
}

/*
Basis(const Quat &p_quat) {
	set_quat(p_quat);
}
Basis(const Quat &p_quat, const Vector3 &p_scale) {
	set_quat_scale(p_quat, p_scale);
}

Basis(const Vector3 &p_euler) {
	set_euler(p_euler);
}
Basis(const Vector3 &p_euler, const Vector3 &p_scale) {
	set_euler_scale(p_euler, p_scale);
}

Basis(const Vector3 &p_axis, real_t p_phi) {
	set_axis_angle(p_axis, p_phi);
}
Basis(const Vector3 &p_axis, real_t p_phi, const Vector3 &p_scale) {
	set_axis_angle_scale(p_axis, p_phi, p_scale);
}
*/

extern _FORCE_INLINE_ Basis basis_creater(real_t xx, real_t xy, real_t xz, real_t yx, real_t yy, real_t yz, real_t zx, real_t zy, real_t zz) {
	Basis b;
	b.elements[0].coord[0] = xx;
	b.elements[0].coord[1] = xy;
	b.elements[0].coord[2] = xz;
	b.elements[1].coord[0] = yx;
	b.elements[1].coord[1] = yy;
	b.elements[1].coord[2] = yz;
	b.elements[2].coord[0] = zx;
	b.elements[2].coord[1] = zy;
	b.elements[2].coord[2] = zz;
	return b;
}

extern _FORCE_INLINE_ const Vector3 basis_get_axis(const Basis *b, int p_axis) {
	// get actual basis axis (elements is transposed for performance)
	return vector3_create(b->elements[0].coord[p_axis], b->elements[1].coord[p_axis], b->elements[2].coord[p_axis]);
}

extern _FORCE_INLINE_ void basis_set_axis(Basis *b, int p_axis, const Vector3 *p_value) {
	// get actual basis axis (elements is transposed for performance)
	b->elements[0].coord[p_axis] = p_value->x;
	b->elements[1].coord[p_axis] = p_value->y;
	b->elements[2].coord[p_axis] = p_value->z;
}

extern _FORCE_INLINE_ void basis_setr(Basis *b, real_t xx, real_t xy, real_t xz, real_t yx, real_t yy, real_t yz, real_t zx, real_t zy, real_t zz) {
	b->elements[0].coord[0] = xx;
	b->elements[0].coord[1] = xy;
	b->elements[0].coord[2] = xz;
	b->elements[1].coord[0] = yx;
	b->elements[1].coord[1] = yy;
	b->elements[1].coord[2] = yz;
	b->elements[2].coord[0] = zx;
	b->elements[2].coord[1] = zy;
	b->elements[2].coord[2] = zz;
}

extern _FORCE_INLINE_ void basis_setv(Basis *b, const Vector3 *p_x, const Vector3 *p_y, const Vector3 *p_z) {
	basis_set_axis(b, 0, p_x);
	basis_set_axis(b, 1, p_y);
	basis_set_axis(b, 2, p_z);
}

extern _FORCE_INLINE_ Vector3 basis_get_column(const Basis *b, int i) {
	return vector3_create(b->elements[0].coord[i], b->elements[1].coord[i], b->elements[2].coord[i]);
}
extern _FORCE_INLINE_ Vector3 basis_get_row(const Basis *b, int i) {
	return vector3_create(b->elements[i].coord[0], b->elements[i].coord[1], b->elements[i].coord[2]);
}
extern _FORCE_INLINE_ Vector3 basis_get_main_diagonal(const Basis *b) {
	return vector3_create(b->elements[0].coord[0], b->elements[1].coord[1], b->elements[2].coord[2]);
}

extern _FORCE_INLINE_ void basis_set_row(Basis *b, int i, const Vector3 *p_row) {
	b->elements[i].coord[0] = p_row->x;
	b->elements[i].coord[1] = p_row->y;
	b->elements[i].coord[2] = p_row->z;
}

extern _FORCE_INLINE_ void basis_set_zero(Basis *b) {
	vector3_zero(&b->elements[0]);
	vector3_zero(&b->elements[1]);
	vector3_zero(&b->elements[2]);
}

extern _FORCE_INLINE_ Basis basis_transpose_xform(const Basis *b, const Basis *m) {
	return basis_creater(
			b->elements[0].x * m->elements[0].x + b->elements[1].x * m->elements[1].x + b->elements[2].x * m->elements[2].x,
			b->elements[0].x * m->elements[0].y + b->elements[1].x * m->elements[1].y + b->elements[2].x * m->elements[2].y,
			b->elements[0].x * m->elements[0].z + b->elements[1].x * m->elements[1].z + b->elements[2].x * m->elements[2].z,
			b->elements[0].y * m->elements[0].x + b->elements[1].y * m->elements[1].x + b->elements[2].y * m->elements[2].x,
			b->elements[0].y * m->elements[0].y + b->elements[1].y * m->elements[1].y + b->elements[2].y * m->elements[2].y,
			b->elements[0].y * m->elements[0].z + b->elements[1].y * m->elements[1].z + b->elements[2].y * m->elements[2].z,
			b->elements[0].z * m->elements[0].x + b->elements[1].z * m->elements[1].x + b->elements[2].z * m->elements[2].x,
			b->elements[0].z * m->elements[0].y + b->elements[1].z * m->elements[1].y + b->elements[2].z * m->elements[2].y,
			b->elements[0].z * m->elements[0].z + b->elements[1].z * m->elements[1].z + b->elements[2].z * m->elements[2].z);
}

/*
	void invert();
	void transpose();

	Basis inverse() const;
	Basis transposed() const;

	_FORCE_INLINE_ real_t determinant() const;

	void from_z(const Vector3 &p_z);

	void rotate(const Vector3 &p_axis, real_t p_phi);
	Basis rotated(const Vector3 &p_axis, real_t p_phi) const;

	void rotate_local(const Vector3 &p_axis, real_t p_phi);
	Basis rotated_local(const Vector3 &p_axis, real_t p_phi) const;

	void rotate(const Vector3 &p_euler);
	Basis rotated(const Vector3 &p_euler) const;

	void rotate(const Quat &p_quat);
	Basis rotated(const Quat &p_quat) const;

	Vector3 get_rotation_euler() const;
	void get_rotation_axis_angle(Vector3 &p_axis, real_t &p_angle) const;
	void get_rotation_axis_angle_local(Vector3 &p_axis, real_t &p_angle) const;
	Quat get_rotation_quat() const;
	Vector3 get_rotation() const { return get_rotation_euler(); };

	Vector3 rotref_posscale_decomposition(Basis &rotref) const;

	Vector3 get_euler_xyz() const;
	void set_euler_xyz(const Vector3 &p_euler);

	Vector3 get_euler_xzy() const;
	void set_euler_xzy(const Vector3 &p_euler);

	Vector3 get_euler_yzx() const;
	void set_euler_yzx(const Vector3 &p_euler);

	Vector3 get_euler_yxz() const;
	void set_euler_yxz(const Vector3 &p_euler);

	Vector3 get_euler_zxy() const;
	void set_euler_zxy(const Vector3 &p_euler);

	Vector3 get_euler_zyx() const;
	void set_euler_zyx(const Vector3 &p_euler);

	Quat get_quat() const;
	void set_quat(const Quat &p_quat);

	Vector3 get_euler() const { return get_euler_yxz(); }
	void set_euler(const Vector3 &p_euler) { set_euler_yxz(p_euler); }

	void get_axis_angle(Vector3 &r_axis, real_t &r_angle) const;
	void set_axis_angle(const Vector3 &p_axis, real_t p_phi);

	void scale(const Vector3 &p_scale);
	Basis scaled(const Vector3 &p_scale) const;

	void scale_local(const Vector3 &p_scale);
	Basis scaled_local(const Vector3 &p_scale) const;

	Vector3 get_scale() const;
	Vector3 get_scale_abs() const;
	Vector3 get_scale_local() const;

	void set_axis_angle_scale(const Vector3 &p_axis, real_t p_phi, const Vector3 &p_scale);
	void set_euler_scale(const Vector3 &p_euler, const Vector3 &p_scale);
	void set_quat_scale(const Quat &p_quat, const Vector3 &p_scale);

	// transposed dot products
	_FORCE_INLINE_ real_t tdotx(const Vector3 &v) const {
		return elements[0][0] * v[0] + elements[1][0] * v[1] + elements[2][0] * v[2];
	}
	_FORCE_INLINE_ real_t tdoty(const Vector3 &v) const {
		return elements[0][1] * v[0] + elements[1][1] * v[1] + elements[2][1] * v[2];
	}
	_FORCE_INLINE_ real_t tdotz(const Vector3 &v) const {
		return elements[0][2] * v[0] + elements[1][2] * v[1] + elements[2][2] * v[2];
	}

	bool is_equal_approx(const Basis &p_basis) const;
	// For complicated reasons, the second argument is always discarded. See #45062.
	bool is_equal_approx(const Basis &a, const Basis &b) const { return is_equal_approx(a); }
	bool is_equal_approx_ratio(const Basis &a, const Basis &b, real_t p_epsilon = UNIT_EPSILON) const;

	bool operator==(const Basis &p_matrix) const;
	bool operator!=(const Basis &p_matrix) const;

	_FORCE_INLINE_ Vector3 xform(const Vector3 &p_vector) const;
	_FORCE_INLINE_ Vector3 xform_inv(const Vector3 &p_vector) const;
	_FORCE_INLINE_ void operator*=(const Basis &p_matrix);
	_FORCE_INLINE_ Basis operator*(const Basis &p_matrix) const;
	_FORCE_INLINE_ void operator+=(const Basis &p_matrix);
	_FORCE_INLINE_ Basis operator+(const Basis &p_matrix) const;
	_FORCE_INLINE_ void operator-=(const Basis &p_matrix);
	_FORCE_INLINE_ Basis operator-(const Basis &p_matrix) const;
	_FORCE_INLINE_ void operator*=(real_t p_val);
	_FORCE_INLINE_ Basis operator*(real_t p_val) const;

	int get_orthogonal_index() const;
	void set_orthogonal_index(int p_index);

	void set_diagonal(const Vector3 &p_diag);

	bool is_orthogonal() const;
	bool is_diagonal() const;
	bool is_rotation() const;

	Basis slerp(const Basis &p_to, const real_t &p_weight) const;
	_FORCE_INLINE_ Basis lerp(const Basis &p_to, const real_t &p_weight) const;

	operator String() const;

	// create / set

	void orthonormalize();
	Basis orthonormalized() const;

	bool is_symmetric() const;
	Basis diagonalize();

	// The following normal xform functions are correct for non-uniform scales.
	// Use these two functions in combination to xform a series of normals.
	// First use get_normal_xform_basis() to precalculate the inverse transpose.
	// Then apply xform_normal_fast() multiple times using the inverse transpose basis.
	Basis get_normal_xform_basis() const { return inverse().transposed(); }

	// N.B. This only does a normal transform if the basis used is the inverse transpose!
	// Otherwise use xform_normal().
	Vector3 xform_normal_fast(const Vector3 &p_vector) const { return xform(p_vector).normalized(); }

	// This function does the above but for a single normal vector. It is considerably slower, so should usually
	// only be used in cases of single normals, or when the basis changes each time.
	Vector3 xform_normal(const Vector3 &p_vector) const { return get_normal_xform_basis().xform_normal_fast(p_vector); }

	operator Quat() const { return get_quat(); }


//--------

_FORCE_INLINE_ void Basis::operator*=(const Basis &p_matrix) {
	set(
			p_matrix.tdotx(elements[0]), p_matrix.tdoty(elements[0]), p_matrix.tdotz(elements[0]),
			p_matrix.tdotx(elements[1]), p_matrix.tdoty(elements[1]), p_matrix.tdotz(elements[1]),
			p_matrix.tdotx(elements[2]), p_matrix.tdoty(elements[2]), p_matrix.tdotz(elements[2]));
}

_FORCE_INLINE_ Basis Basis::operator*(const Basis &p_matrix) const {
	return Basis(
			p_matrix.tdotx(elements[0]), p_matrix.tdoty(elements[0]), p_matrix.tdotz(elements[0]),
			p_matrix.tdotx(elements[1]), p_matrix.tdoty(elements[1]), p_matrix.tdotz(elements[1]),
			p_matrix.tdotx(elements[2]), p_matrix.tdoty(elements[2]), p_matrix.tdotz(elements[2]));
}

_FORCE_INLINE_ void Basis::operator+=(const Basis &p_matrix) {
	elements[0] += p_matrix.elements[0];
	elements[1] += p_matrix.elements[1];
	elements[2] += p_matrix.elements[2];
}

_FORCE_INLINE_ Basis Basis::operator+(const Basis &p_matrix) const {
	Basis ret(*this);
	ret += p_matrix;
	return ret;
}

_FORCE_INLINE_ void Basis::operator-=(const Basis &p_matrix) {
	elements[0] -= p_matrix.elements[0];
	elements[1] -= p_matrix.elements[1];
	elements[2] -= p_matrix.elements[2];
}

_FORCE_INLINE_ Basis Basis::operator-(const Basis &p_matrix) const {
	Basis ret(*this);
	ret -= p_matrix;
	return ret;
}

_FORCE_INLINE_ void Basis::operator*=(real_t p_val) {
	elements[0] *= p_val;
	elements[1] *= p_val;
	elements[2] *= p_val;
}

_FORCE_INLINE_ Basis Basis::operator*(real_t p_val) const {
	Basis ret(*this);
	ret *= p_val;
	return ret;
}

Vector3 Basis::xform(const Vector3 &p_vector) const {
	return Vector3(
			elements[0].dot(p_vector),
			elements[1].dot(p_vector),
			elements[2].dot(p_vector));
}

Vector3 Basis::xform_inv(const Vector3 &p_vector) const {
	return Vector3(
			(elements[0][0] * p_vector.x) + (elements[1][0] * p_vector.y) + (elements[2][0] * p_vector.z),
			(elements[0][1] * p_vector.x) + (elements[1][1] * p_vector.y) + (elements[2][1] * p_vector.z),
			(elements[0][2] * p_vector.x) + (elements[1][2] * p_vector.y) + (elements[2][2] * p_vector.z));
}

real_t Basis::determinant() const {
	return elements[0][0] * (elements[1][1] * elements[2][2] - elements[2][1] * elements[1][2]) -
			elements[1][0] * (elements[0][1] * elements[2][2] - elements[2][1] * elements[0][2]) +
			elements[2][0] * (elements[0][1] * elements[1][2] - elements[1][1] * elements[0][2]);
}

Basis Basis::lerp(const Basis &p_to, const real_t &p_weight) const {
	Basis b;
	b.elements[0] = elements[0].linear_interpolate(p_to.elements[0], p_weight);
	b.elements[1] = elements[1].linear_interpolate(p_to.elements[1], p_weight);
	b.elements[2] = elements[2].linear_interpolate(p_to.elements[2], p_weight);

	return b;
}
*/

#endif // BASIS_H
