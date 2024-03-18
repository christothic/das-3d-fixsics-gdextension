

#ifndef DAS_FIXED_VECTOR3_H
#define DAS_FIXED_VECTOR3_H

#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "../internal/das_fixed_vector3_internal.h"

using namespace godot;

class DASFixedVector3;

class DASFixedVector3Watcher {
public:
    virtual void fixed_vector3_changed(DASFixedVector3* p_vector) = 0;
};

class DASFixedVector3 : public RefCounted {
    GDCLASS(DASFixedVector3, RefCounted);

    mutable DASFixedVector3Watcher* watcher;
    DASFixedVector3Internal value;

protected:
    static void _bind_methods();

public:
    _FORCE_INLINE_ int64_t get_x() const { return value.x.value; }
    _FORCE_INLINE_ int64_t get_y() const { return value.y.value; }
    _FORCE_INLINE_ int64_t get_z() const { return value.z.value; }

    void set_x(int64_t p_x) {
        value.x.value = p_x;
        if (watcher) {
            watcher->fixed_vector3_changed(this);
        }
    }

    void set_y(int64_t p_y) {
        value.y.value = p_y;
        if (watcher) {
            watcher->fixed_vector3_changed(this);
        }
    }

    void set_z(int64_t p_z) {
        value.z.value = p_z;
        if (watcher) {
            watcher->fixed_vector3_changed(this);
        }
    }

    void clear() {
        value.x.value = 0;
        value.y.value = 0;
        if (watcher) {
            watcher->fixed_vector3_changed(this);
        }
    }

    _FORCE_INLINE_ void set_watcher(DASFixedVector3Watcher* p_watcher) const {
        watcher = p_watcher;
    }

    Ref<DASFixedVector3> add(const Variant& p_other) const;
    void iadd(const Variant& p_other);
    Ref<DASFixedVector3> sub(const Variant& p_other) const;
    void isub(const Variant& p_other);
    Ref<DASFixedVector3> mul(const Variant& p_other) const;
    void imul(const Variant& p_other);
    Ref<DASFixedVector3> div(const Variant& p_other) const;
    void idiv(const Variant& p_other);

    Ref<DASFixedVector3> copy() const;

    Ref<DASFixedVector3> abs() const;
    Ref<DASFixedVector3> normalized() const;
    bool is_normalized() const;

    int64_t length() const;
    int64_t length_squared() const;

    int64_t distance_to(const Ref<DASFixedVector3>& p_other) const;
    int64_t distance_squared_to(const Ref<DASFixedVector3>& p_other) const;
    int64_t angle_to(const Ref<DASFixedVector3>& p_other) const;
    int64_t angle_to_point(const Ref<DASFixedVector3>& p_other) const;
    Ref<DASFixedVector3>
    direction_to(const Ref<DASFixedVector3>& p_other) const;

    void rotate(int64_t p_rotation);
    Ref<DASFixedVector3> rotated(int64_t p_rotation) const;
    int64_t angle() const;

    int64_t dot(const Ref<DASFixedVector3>& p_other) const;
    int64_t cross(const Ref<DASFixedVector3>& p_other) const;

    Ref<DASFixedVector3> linear_interpolate(const Ref<DASFixedVector3>& p_to,
                                            int64_t weight) const;
    Ref<DASFixedVector3> cubic_interpolate(const Ref<DASFixedVector3>& p_b,
                                           const Ref<DASFixedVector3>& p_pre_a,
                                           const Ref<DASFixedVector3>& p_post_b,
                                           int64_t p_weight) const;

    Ref<DASFixedVector3> slide(const Ref<DASFixedVector3>& p_normal) const;
    Ref<DASFixedVector3> bounce(const Ref<DASFixedVector3>& p_normal) const;
    Ref<DASFixedVector3> reflect(const Ref<DASFixedVector3>& p_normal) const;

    bool is_equal_approx(const Ref<DASFixedVector3>& p_other) const;

    void from_float(Vector3 p_float_vector);
    Vector3 to_float() const;

    // Won't trigger the "changed" signal. Meant only for internal use.
    _FORCE_INLINE_ DASFixedVector3Internal get_internal() const {
        return value;
    }
    _FORCE_INLINE_ void set_internal(DASFixedVector3Internal p_value) {
        value = p_value;
    }

    _FORCE_INLINE_ static Ref<DASFixedVector3>
    from_internal(const DASFixedVector3Internal& p_internal) {
        return Ref<DASFixedVector3>(memnew(DASFixedVector3(p_internal)));
    }

    DASFixedVector3() { watcher = nullptr; }
    DASFixedVector3(const DASFixedVector3Internal& p_internal_vector) {
        value = p_internal_vector;
        watcher = nullptr;
    }

    ~DASFixedVector3(){};
};

#endif
