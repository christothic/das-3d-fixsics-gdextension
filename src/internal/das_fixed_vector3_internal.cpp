#include "das_fixed_vector3_internal.h"

const fixed DASFixedVector3Internal::FIXED_UNIT_EPSILON = fixed(65);

const DASFixedVector3Internal DASFixedVector3Internal::ZERO =
    DASFixedVector3Internal(fixed::ZERO, fixed::ZERO, fixed::ZERO);

bool DASFixedVector3Internal::operator==(
    const DASFixedVector3Internal& p_v) const {
    return x == p_v.x && y == p_v.y;
}

bool DASFixedVector3Internal::operator!=(
    const DASFixedVector3Internal& p_v) const {
    return x != p_v.x || y != p_v.y;
}

fixed DASFixedVector3Internal::angle() const { return y.atan2(x); }

DASFixedVector3Internal
DASFixedVector3Internal::rotated(fixed p_rotation) const {
    DASFixedVector3Internal v;
    v.set_rotation(angle() + p_rotation);
    v *= length();
    return v;
}

void DASFixedVector3Internal::normalize() {
    // // For values less than 2048 we get really imprecise results. Since only
    // // direction matters, we can increase the vector's magnitude.
    // fixed x_abs = x.abs();
    // fixed y_abs = y.abs();
    // if ((x.value != 0 && x_abs.value < 2048) ||
    //     (y.value != 0 && y_abs.value < 2048)) {
    //     // Watch out for values that will overflow even 64 bits.
    //     // 1482910 = sqrt(MAX_SIGNED_64BIT_NUMBER) / 2048
    //     if (x_abs.value >= 1482910) {
    //         x = x.value > 0 ? fixed::ONE : fixed::NEG_ONE;
    //         y = fixed::ZERO;
    //     } else if (y_abs.value >= 1482910) {
    //         x = fixed::ZERO;
    //         y = y.value > 0 ? fixed::ONE : fixed::NEG_ONE;
    //     } else {
    //         // Multiply X and Y by 2048.
    //         fixed x_big = fixed(x.value << 11);
    //         fixed y_big = fixed(y.value << 11);
    //         fixed l = DASFixedVector3Internal(x_big, y_big).length();
    //         if (l != fixed::ZERO) {
    //             x = x_big / l;
    //             y = y_big / l;
    //         }
    //     }
    // } else {
    //     fixed l = length();
    //     if (l != fixed::ZERO) {
    //         x /= l;
    //         y /= l;
    //     }
    // }
}

DASFixedVector3Internal DASFixedVector3Internal::normalized() const {
    DASFixedVector3Internal v = *this;
    v.normalize();
    return v;
}

bool DASFixedVector3Internal::is_normalized() const {
    return fixed::is_equal_approx(length_squared(), fixed::ONE,
                                  DASFixedVector3Internal::FIXED_UNIT_EPSILON);
}

DASFixedVector3Internal DASFixedVector3Internal::safe_scale(
    const DASFixedVector3Internal& p_other) const {
    DASFixedVector3Internal ret = *this * p_other;

    // Don't allow scaling all the way down to zero.
    if (ret.x == fixed::ZERO && x != fixed::ZERO) {
        ret.x.value = x > fixed::ZERO ? 1 : -1;
    }
    if (ret.y == fixed::ZERO && y != fixed::ZERO) {
        ret.y.value = y > fixed::ZERO ? 1 : -1;
    }
    if (ret.z == fixed::ZERO && z != fixed::ZERO) {
        ret.z.value = z > fixed::ZERO ? 1 : -1;
    }

    return ret;
}

DASFixedVector3Internal
DASFixedVector3Internal::safe_scale(fixed p_scale) const {
    return safe_scale(DASFixedVector3Internal(p_scale, p_scale, p_scale));
}

fixed DASFixedVector3Internal::length() const {
    // By directly using 64-bit integers we can avoid a left shift, since
    // multiplying two fixed point numbers effectively shifts them left.
    int64_t length_squared =
        x.value * x.value + y.value * y.value + z.value * z.value;
    if (length_squared == 0) {
        return fixed::ZERO;
    }
    fixed length = fixed(sg_sqrt_64(length_squared));
    if (length == fixed::ZERO) {
        // If the vector was non-zero, then we must return some length.
        return fixed(1);
    }
    return length;
}

fixed DASFixedVector3Internal::length_squared() const {
    fixed ret = x * x + y * y + z * z;
    // Squaring a fixed-point number smaller than 15 will be 0, which means
    // that it's possible for ret to equal 0.
    if (ret == fixed::ZERO &&
        (x != fixed::ZERO || y != fixed::ZERO || z != fixed::ZERO)) {
        // If the vector was non-zero, then we must return some length.
        return fixed(1);
    }
    return ret;
}

fixed DASFixedVector3Internal::distance_to(
    const DASFixedVector3Internal& p_other) const {
    DASFixedVector3Internal vec = p_other - *this;
    return vec.length();
}

fixed DASFixedVector3Internal::distance_squared_to(
    const DASFixedVector3Internal& p_other) const {
    DASFixedVector3Internal vec = p_other - *this;
    return vec.length_squared();
}

fixed DASFixedVector3Internal::angle_to(
    const DASFixedVector3Internal& p_other) const {
    return cross(p_other).atan2(dot(p_other));
}

fixed DASFixedVector3Internal::angle_to_point(
    const DASFixedVector3Internal& p_other) const {
    return (y - p_other.y).atan2(x - p_other.x);
}

fixed DASFixedVector3Internal::dot(
    const DASFixedVector3Internal& p_other) const {
    return x * p_other.x + y * p_other.y;
}

fixed DASFixedVector3Internal::cross(
    const DASFixedVector3Internal& p_other) const {
    return x * p_other.y - y * p_other.x;
}

/*
fixed DASFixedVector3Internal::posmod(const fixed p_mod) const {

}

fixed DASFixedVector3Internal::posmodv(const DASFixedVector3Internal &p_modv)
const {

}

DASFixedVector3Internal DASFixedVector3Internal::project(const
DASFixedVector3Internal &p_to) const { return p_to * (dot(p_to) /
p_to.length_squared());
}
*/

DASFixedVector3Internal
DASFixedVector3Internal::slide(const DASFixedVector3Internal& p_normal) const {
#ifdef MATH_CHECKS
    ERR_FAIL_COND_V_MSG(
        !p_normal.is_normalized(), DASFixedVector3Internal(),
        "The normal DASFixedVector3Internal must be normalized.");
#endif
    return *this - p_normal * this->dot(p_normal);
}

DASFixedVector3Internal
DASFixedVector3Internal::bounce(const DASFixedVector3Internal& p_normal) const {
    return -reflect(p_normal);
}

DASFixedVector3Internal DASFixedVector3Internal::reflect(
    const DASFixedVector3Internal& p_normal) const {
#ifdef MATH_CHECKS
    ERR_FAIL_COND_V_MSG(
        !p_normal.is_normalized(), DASFixedVector3Internal(),
        "The normal DASFixedVector3Internal must be normalized.");
#endif
    return p_normal * fixed::TWO * this->dot(p_normal) - *this;
}

bool DASFixedVector3Internal::is_equal_approx(
    const DASFixedVector3Internal& p_v) const {
    return fixed::is_equal_approx(x, p_v.x) &&
           fixed::is_equal_approx(y, p_v.y) && fixed::is_equal_approx(z, p_v.z);
}

DASFixedVector3Internal DASFixedVector3Internal::cubic_interpolate(
    const DASFixedVector3Internal& p_b, const DASFixedVector3Internal& p_pre_a,
    const DASFixedVector3Internal& p_post_b, fixed p_weight) const {
    DASFixedVector3Internal p0 = p_pre_a;
    DASFixedVector3Internal p1 = *this;
    DASFixedVector3Internal p2 = p_b;
    DASFixedVector3Internal p3 = p_post_b;

    fixed t = p_weight;
    fixed t2 = t * t;
    fixed t3 = t2 * t;

    // from original floating point compute:
    // out = 0.5 *
    //	((p1 * 2.0) +
    //		(-p0 + p2) * t +
    //		(2.0 * p0 - 5.0 * p1 + 4 * p2 - p3) * t2 +
    //		(-p0 + 3.0 * p1 - 3.0 * p2 + p3) * t3);
    DASFixedVector3Internal out =
        ((p1 * fixed(131072)) + (-p0 + p2) * t +
         ((p0 * fixed(131072)) - p1 * fixed(327680) + (p2 * fixed(262144)) -
          p3) *
             t2 +
         (-p0 + p1 * fixed(196608) - p2 * fixed(196608) + p3) * t3) *
        fixed(32768);
    return out;
}

DASFixedVector3Internal
DASFixedVector3Internal::get_closest_point_to_segment_2d(
    const DASFixedVector3Internal& p_point,
    const DASFixedVector3Internal* p_segment) {
    DASFixedVector3Internal p = p_point - p_segment[0];
    DASFixedVector3Internal n = p_segment[1] - p_segment[0];
    fixed l2 = n.length();
    if (l2 == fixed::ZERO) {
        return p_segment[0]; // Both points are the same, just give any.
    }

    fixed d = (n / l2).dot(p / l2);

    if (d <= fixed::ZERO) {
        return p_segment[0]; // Before first point.
    } else if (d >= fixed::ONE) {
        return p_segment[1]; // After first point.
    } else {
        return p_segment[0] + n * d; // Inside.
    }
}
