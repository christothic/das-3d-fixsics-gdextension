

#ifndef DAS_FIXED_VECTOR3_H
#define DAS_FIXED_VECTOR3_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "das_fixed_number_internal.h"

using namespace godot;

struct _NO_DISCARD_ DASFixedVector3Internal {
    static const int AXIS_COUNT = 3;

    enum Axis {
        AXIS_X,
        AXIS_Y,
        AXIS_Z,
    };

    union {
        struct {
            fixed x;
            fixed y;
            fixed z;
        };

        fixed coord[3] = {fixed(0)};
    };

    _FORCE_INLINE_ const fixed& operator[](const int p_axis) const {
        DEV_ASSERT((unsigned int)p_axis < 3);
        return coord[p_axis];
    }

    _FORCE_INLINE_ fixed& operator[](const int p_axis) {
        DEV_ASSERT((unsigned int)p_axis < 3);
        return coord[p_axis];
    }

    _FORCE_INLINE_ DASFixedVector3Internal::Axis min_axis_index() const {
        return x < y ? (x < z ? DASFixedVector3Internal::AXIS_X
                              : DASFixedVector3Internal::AXIS_Z)
                     : (y < z ? DASFixedVector3Internal::AXIS_Y
                              : DASFixedVector3Internal::AXIS_Z);
    }

    _FORCE_INLINE_ DASFixedVector3Internal::Axis max_axis_index() const {
        return x < y ? (y < z ? DASFixedVector3Internal::AXIS_Z
                              : DASFixedVector3Internal::AXIS_Y)
                     : (x < z ? DASFixedVector3Internal::AXIS_Z
                              : DASFixedVector3Internal::AXIS_X);
    }

    DASFixedVector3Internal
    min(const DASFixedVector3Internal& p_vector3) const {
        return DASFixedVector3Internal(MIN(x, p_vector3.x), MIN(y, p_vector3.y),
                                       MIN(z, p_vector3.z));
    }

    DASFixedVector3Internal
    max(const DASFixedVector3Internal& p_vector3) const {
        return DASFixedVector3Internal(MAX(x, p_vector3.x), MAX(y, p_vector3.y),
                                       MAX(z, p_vector3.z));
    }

    _FORCE_INLINE_ DASFixedVector3Internal() {}
    _FORCE_INLINE_ DASFixedVector3Internal(const fixed p_x, const fixed p_y,
                                           const fixed p_z) {
        x = p_x;
        y = p_y;
        z = p_z;
    }
    // _FORCE_INLINE_ int64_t get_x() const { return x.value; }
    // _FORCE_INLINE_ int64_t get_y() const { return y.value; }
    // _FORCE_INLINE_ int64_t get_z() const { return z.value; }
    //
    // void set_x(int64_t p_x) {
    //     value.x.value = p_x;
    //     if (watcher) {
    //         watcher->fixed_vector3_changed(this);
    //     }
    // }
    //
    // void set_y(int64_t p_y) {
    //     value.y.value = p_y;
    //     if (watcher) {
    //         watcher->fixed_vector3_changed(this);
    //     }
    // }
    //
    // void set_z(int64_t p_z) {
    //     value.z.value = p_z;
    //     if (watcher) {
    //         watcher->fixed_vector3_changed(this);
    //     }
    // }
    //
    // void clear() {
    //     value.x.value = 0;
    //     value.y.value = 0;
    //     if (watcher) {
    //         watcher->fixed_vector3_changed(this);
    //     }
    // }
    //
    // _FORCE_INLINE_ void set_watcher(DASFixedDASFixedVector3Watcher*
    // p_watcher) const
    // {
    //     watcher = p_watcher;
    // }
    //
    // Ref<DASFixedDASFixedVector3> add(const Variant& p_other) const;
    // void iadd(const Variant& p_other);
    // Ref<DASFixedDASFixedVector3> sub(const Variant& p_other) const;
    // void isub(const Variant& p_other);
    // Ref<DASFixedDASFixedVector3> mul(const Variant& p_other) const;
    // void imul(const Variant& p_other);
    // Ref<DASFixedDASFixedVector3> div(const Variant& p_other) const;
    // void idiv(const Variant& p_other);
    //
    // Ref<DASFixedDASFixedVector3> copy() const;
    //
    // Ref<DASFixedDASFixedVector3> abs() const;
    // Ref<DASFixedDASFixedVector3> normalized() const;
    // bool is_normalized() const;
    //
    // int64_t length() const;
    // int64_t length_squared() const;
    //
    // int64_t distance_to(const Ref<DASFixedDASFixedVector3>& p_other) const;
    // int64_t distance_squared_to(const Ref<DASFixedDASFixedVector3>& p_other)
    // const; int64_t angle_to(const Ref<DASFixedDASFixedVector3>& p_other)
    // const; int64_t angle_to_point(const Ref<DASFixedDASFixedVector3>&
    // p_other) const; Ref<DASFixedDASFixedVector3> direction_to(const
    // Ref<DASFixedDASFixedVector3>& p_other) const;
    //
    // void rotate(int64_t p_rotation);
    // Ref<DASFixedDASFixedVector3> rotated(int64_t p_rotation) const;
    // int64_t angle() const;
    //
    // int64_t dot(const Ref<DASFixedDASFixedVector3>& p_other) const;
    // int64_t cross(const Ref<DASFixedDASFixedVector3>& p_other) const;
    //
    // Ref<DASFixedDASFixedVector3> linear_interpolate(const
    // Ref<DASFixedDASFixedVector3>& p_to,
    //                                         int64_t weight) const;
    // Ref<DASFixedDASFixedVector3> cubic_interpolate(const
    // Ref<DASFixedDASFixedVector3>& p_b,
    //                                        const
    //                                        Ref<DASFixedDASFixedVector3>&
    //                                        p_pre_a, const
    //                                        Ref<DASFixedDASFixedVector3>&
    //                                        p_post_b, int64_t p_weight) const;
    //
    // Ref<DASFixedDASFixedVector3> slide(const Ref<DASFixedDASFixedVector3>&
    // p_normal) const; Ref<DASFixedDASFixedVector3> bounce(const
    // Ref<DASFixedDASFixedVector3>& p_normal) const;
    // Ref<DASFixedDASFixedVector3> reflect(const Ref<DASFixedDASFixedVector3>&
    // p_normal) const;
    //
    // bool is_equal_approx(const Ref<DASFixedDASFixedVector3>& p_other) const;
    //
    // void from_float(DASFixedVector3 p_float_vector);
    // DASFixedVector3 to_float() const;
    //
    // // Won't trigger the "changed" signal. Meant only for internal use.
    // _FORCE_INLINE_ DASFixedDASFixedVector3Internal get_internal() const {
    //     return value;
    // }
    // _FORCE_INLINE_ void set_internal(DASFixedDASFixedVector3Internal p_value)
    // {
    //     value = p_value;
    // }
    //
    // _FORCE_INLINE_ static Ref<DASFixedDASFixedVector3>
    // from_internal(const DASFixedDASFixedVector3Internal& p_internal) {
    //     return
    //     Ref<DASFixedDASFixedVector3>(memnew(DASFixedDASFixedVector3(p_internal)));
    // }
    //
    // DASFixedDASFixedVector3() { watcher = nullptr; }
    // DASFixedDASFixedVector3(const DASFixedDASFixedVector3Internal&
    // p_internal_vector) {
    //     value = p_internal_vector;
    //     watcher = nullptr;
    // }
};

#endif
