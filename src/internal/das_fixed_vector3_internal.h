#ifndef DAS_FIXED_VECTOR3_INTERNAL_H
#define DAS_FIXED_VECTOR3_INTERNAL_H

#include "das_fixed_number_internal.h"

struct DASFixedVector3Internal {
    enum Axis {
        AXIS_X,
        AXIS_Y,
        AXIS_Z,
    };

    union {
        fixed x;
        fixed width;
    };
    union {
        fixed y;
        fixed height;
    };
    union {
        fixed z;
        fixed depth;
    };

    static const fixed FIXED_UNIT_EPSILON;
    static const DASFixedVector3Internal ZERO;

    _FORCE_INLINE_ fixed& operator[](int p_idx) {
        switch (p_idx) {
        case 1:
            return y;
        case 2:
            return z;
        default:
            return x;
        }
    }
    _FORCE_INLINE_ const fixed& operator[](int p_idx) const {
        switch (p_idx) {
        case 1:
            return y;
        case 2:
            return z;
        default:
            return x;
        }
    }

    _FORCE_INLINE_ DASFixedVector3Internal
    operator+(const DASFixedVector3Internal& p_v) const {
        return DASFixedVector3Internal(x + p_v.x, y + p_v.y, z + p_v.z);
    }
    _FORCE_INLINE_ void operator+=(const DASFixedVector3Internal& p_v) {
        x += p_v.x;
        y += p_v.y;
        z += p_v.z;
    }
    _FORCE_INLINE_ DASFixedVector3Internal
    operator-(const DASFixedVector3Internal& p_v) const {
        return DASFixedVector3Internal(x - p_v.x, y - p_v.y, z - p_v.z);
    }
    _FORCE_INLINE_ void operator-=(const DASFixedVector3Internal& p_v) {
        x -= p_v.x;
        y -= p_v.y;
        z -= p_v.z;
    }
    _FORCE_INLINE_ DASFixedVector3Internal
    operator*(const DASFixedVector3Internal& p_v) const {
        return DASFixedVector3Internal(x * p_v.x, y * p_v.y, z * p_v.z);
    }
    _FORCE_INLINE_ void operator*=(const DASFixedVector3Internal& p_v) {
        x *= p_v.x;
        y *= p_v.y;
        z *= p_v.z;
    }
    _FORCE_INLINE_ DASFixedVector3Internal
    operator/(const DASFixedVector3Internal& p_v) const {
        return DASFixedVector3Internal(x / p_v.x, y / p_v.y, z / p_v.z);
    }
    _FORCE_INLINE_ void operator/=(const DASFixedVector3Internal& p_v) {
        x /= p_v.x;
        y /= p_v.y;
        z /= p_v.z;
    }

    _FORCE_INLINE_ DASFixedVector3Internal operator+(const fixed& p_v) const {
        return DASFixedVector3Internal(x + p_v, y + p_v, z + p_v);
    }
    _FORCE_INLINE_ void operator+=(const fixed& p_v) {
        x += p_v;
        y += p_v;
        z += p_v;
    }
    _FORCE_INLINE_ DASFixedVector3Internal operator-(const fixed& p_v) const {
        return DASFixedVector3Internal(x - p_v, y - p_v, z - p_v);
    }
    _FORCE_INLINE_ void operator-=(const fixed& p_v) {
        x -= p_v;
        y -= p_v;
        z -= p_v;
    }
    _FORCE_INLINE_ DASFixedVector3Internal operator*(const fixed& p_v) const {
        return DASFixedVector3Internal(x * p_v, y * p_v, z * p_v);
    }
    _FORCE_INLINE_ void operator*=(const fixed& p_v) {
        x *= p_v;
        y *= p_v;
        z *= p_v;
    }
    _FORCE_INLINE_ DASFixedVector3Internal operator/(const fixed& p_v) const {
        return DASFixedVector3Internal(x / p_v, y / p_v, z / p_v);
    }
    _FORCE_INLINE_ void operator/=(const fixed& p_v) {
        x /= p_v;
        y /= p_v;
        z /= p_v;
    }

    bool operator==(const DASFixedVector3Internal& p_v) const;
    bool operator!=(const DASFixedVector3Internal& p_v) const;

    fixed angle() const;

    void set_rotation(fixed p_radians) {
        x = p_radians.cos();
        y = p_radians.sin();
    }

    _FORCE_INLINE_ DASFixedVector3Internal abs() const {
        return DASFixedVector3Internal(x.abs(), y.abs(), z.abs());
    }
    _FORCE_INLINE_ DASFixedVector3Internal operator-() const {
        return DASFixedVector3Internal(-x, -y, -z);
    }

    DASFixedVector3Internal rotated(fixed p_rotation) const;

    void normalize();
    DASFixedVector3Internal normalized() const;
    bool is_normalized() const;

    DASFixedVector3Internal
    safe_scale(const DASFixedVector3Internal& p_other) const;
    DASFixedVector3Internal safe_scale(fixed p_scale) const;

    fixed length() const;
    fixed length_squared() const;

    fixed distance_to(const DASFixedVector3Internal& p_other) const;
    fixed distance_squared_to(const DASFixedVector3Internal& p_other) const;
    fixed angle_to(const DASFixedVector3Internal& p_other) const;
    fixed angle_to_point(const DASFixedVector3Internal& p_other) const;
    _FORCE_INLINE_ DASFixedVector3Internal
    direction_to(const DASFixedVector3Internal& p_to) const;

    fixed dot(const DASFixedVector3Internal& p_other) const;
    fixed cross(const DASFixedVector3Internal& p_other) const;
    // fixed posmod(const fixed p_mod) const;
    // fixed posmodv(const DASFixedVector3Internal &p_modv) const;
    // DASFixedVector3Internal project(const DASFixedVector3Internal &p_to)
    // const;
    _FORCE_INLINE_ DASFixedVector3Internal tangent() const {
        return *this; // DASFixedVector3Internal(y, -x);
    }

    _FORCE_INLINE_ static DASFixedVector3Internal
    linear_interpolate(const DASFixedVector3Internal& p_a,
                       const DASFixedVector3Internal& p_b, fixed p_weight);

    DASFixedVector3Internal
    slide(const DASFixedVector3Internal& p_normal) const;
    DASFixedVector3Internal
    bounce(const DASFixedVector3Internal& p_normal) const;
    DASFixedVector3Internal
    reflect(const DASFixedVector3Internal& p_normal) const;

    bool is_equal_approx(const DASFixedVector3Internal& p_v) const;

    _FORCE_INLINE_ DASFixedVector3Internal(fixed p_x, fixed p_y, fixed p_z)
        : x(p_x), y(p_y), z(p_z) {}
    _FORCE_INLINE_ DASFixedVector3Internal()
        : x(fixed::ZERO), y(fixed::ZERO), z(fixed::ZERO) {}

    DASFixedVector3Internal
    cubic_interpolate(const DASFixedVector3Internal& p_b,
                      const DASFixedVector3Internal& p_pre_a,
                      const DASFixedVector3Internal& p_post_b,
                      fixed p_weight) const;

    static DASFixedVector3Internal
    get_closest_point_to_segment_2d(const DASFixedVector3Internal& p_point,
                                    const DASFixedVector3Internal* p_segment);
};

DASFixedVector3Internal DASFixedVector3Internal::direction_to(
    const DASFixedVector3Internal& p_to) const {
    DASFixedVector3Internal ret(p_to.x - x, p_to.y - y, p_to.z - z);
    ret.normalize();
    return ret;
}

DASFixedVector3Internal
DASFixedVector3Internal::linear_interpolate(const DASFixedVector3Internal& p_a,
                                            const DASFixedVector3Internal& p_b,
                                            fixed p_weight) {
    DASFixedVector3Internal res = p_a;
    res.x += (p_weight * (p_b.x - p_a.x));
    res.y += (p_weight * (p_b.y - p_a.y));
    res.z += (p_weight * (p_b.z - p_a.z));
    return res;
}

#endif
