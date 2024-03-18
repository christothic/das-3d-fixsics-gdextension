#include "das_fixed_vector3.h"

void DASFixedVector3::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_x"), &DASFixedVector3::get_x);
    ClassDB::bind_method(D_METHOD("set_x", "x"), &DASFixedVector3::set_x);
    ClassDB::bind_method(D_METHOD("get_y"), &DASFixedVector3::get_y);
    ClassDB::bind_method(D_METHOD("set_y", "y"), &DASFixedVector3::set_y);
    ClassDB::bind_method(D_METHOD("get_z"), &DASFixedVector3::get_z);
    ClassDB::bind_method(D_METHOD("set_z", "z"), &DASFixedVector3::set_z);

    ClassDB::bind_method(D_METHOD("clear"), &DASFixedVector3::clear);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "x", PROPERTY_HINT_NONE), "set_x",
                 "get_x");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "y", PROPERTY_HINT_NONE), "set_y",
                 "get_y");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "z", PROPERTY_HINT_NONE), "set_z",
                 "get_z");

    ClassDB::bind_method(D_METHOD("add", "value"), &DASFixedVector3::add);
    ClassDB::bind_method(D_METHOD("iadd", "value"), &DASFixedVector3::iadd);
    ClassDB::bind_method(D_METHOD("sub", "value"), &DASFixedVector3::sub);
    ClassDB::bind_method(D_METHOD("isub", "value"), &DASFixedVector3::isub);
    ClassDB::bind_method(D_METHOD("mul", "value"), &DASFixedVector3::mul);
    ClassDB::bind_method(D_METHOD("imul", "value"), &DASFixedVector3::imul);
    ClassDB::bind_method(D_METHOD("div", "value"), &DASFixedVector3::div);
    ClassDB::bind_method(D_METHOD("idiv", "value"), &DASFixedVector3::idiv);

    ClassDB::bind_method(D_METHOD("copy"), &DASFixedVector3::copy);
    ClassDB::bind_method(D_METHOD("abs"), &DASFixedVector3::abs);
    ClassDB::bind_method(D_METHOD("normalized"), &DASFixedVector3::normalized);
    ClassDB::bind_method(D_METHOD("is_normalized"),
                         &DASFixedVector3::is_normalized);
    ClassDB::bind_method(D_METHOD("length"), &DASFixedVector3::length);
    ClassDB::bind_method(D_METHOD("length_squared"),
                         &DASFixedVector3::length_squared);

    ClassDB::bind_method(D_METHOD("distance_to", "other_vector"),
                         &DASFixedVector3::distance_to);
    ClassDB::bind_method(D_METHOD("distance_squared_to", "other_vector"),
                         &DASFixedVector3::distance_squared_to);
    ClassDB::bind_method(D_METHOD("angle_to", "other_vector"),
                         &DASFixedVector3::angle_to);
    ClassDB::bind_method(D_METHOD("angle_to_point", "other_vector"),
                         &DASFixedVector3::angle_to_point);
    ClassDB::bind_method(D_METHOD("direction_to", "other_vector"),
                         &DASFixedVector3::direction_to);

    ClassDB::bind_method(D_METHOD("rotate", "radians"),
                         &DASFixedVector3::rotate);
    ClassDB::bind_method(D_METHOD("rotated", "radians"),
                         &DASFixedVector3::rotated);
    ClassDB::bind_method(D_METHOD("angle"), &DASFixedVector3::angle);

    ClassDB::bind_method(D_METHOD("dot", "other_vector"),
                         &DASFixedVector3::dot);
    ClassDB::bind_method(D_METHOD("cross", "other_vector"),
                         &DASFixedVector3::cross);

    ClassDB::bind_method(
        D_METHOD("linear_interpolate", "other_vector", "weight"),
        &DASFixedVector3::linear_interpolate);
    ClassDB::bind_method(D_METHOD("cubic_interpolate", "other_vector", "pre_a",
                                  "post_b", "weight"),
                         &DASFixedVector3::cubic_interpolate);

    ClassDB::bind_method(D_METHOD("slide", "normal"), &DASFixedVector3::slide);
    ClassDB::bind_method(D_METHOD("bounce", "normal"),
                         &DASFixedVector3::bounce);
    ClassDB::bind_method(D_METHOD("reflect", "normal"),
                         &DASFixedVector3::reflect);

    ClassDB::bind_method(D_METHOD("is_equal_approx", "other_vector"),
                         &DASFixedVector3::is_equal_approx);

    ClassDB::bind_method(D_METHOD("from_float", "float_vector"),
                         &DASFixedVector3::from_float);
    ClassDB::bind_method(D_METHOD("to_float"), &DASFixedVector3::to_float);
}

Ref<DASFixedVector3> DASFixedVector3::add(const Variant& p_other) const {
    if (p_other.get_type() == Variant::INT) {
        return DASFixedVector3::from_internal(value + fixed(p_other));
    }

    Ref<DASFixedVector3> other_vector =
        Object::cast_to<DASFixedVector3>(p_other);
    ERR_FAIL_COND_V_MSG(!other_vector.is_valid(), Variant(), "Invalid type.");

    return DASFixedVector3::from_internal(value + other_vector->get_internal());
}

void DASFixedVector3::iadd(const Variant& p_other) {
    if (p_other.get_type() == Variant::INT) {
        value += fixed(p_other);
    } else {
        Ref<DASFixedVector3> other_vector =
            Object::cast_to<DASFixedVector3>(p_other);
        ERR_FAIL_COND_MSG(!other_vector.is_valid(), "Invalid type.");

        value += other_vector->get_internal();
    }
    if (watcher) {
        watcher->fixed_vector3_changed(this);
    }
}

Ref<DASFixedVector3> DASFixedVector3::sub(const Variant& p_other) const {
    if (p_other.get_type() == Variant::INT) {
        return DASFixedVector3::from_internal(value - fixed(p_other));
    }

    Ref<DASFixedVector3> other_vector =
        Object::cast_to<DASFixedVector3>(p_other);
    ERR_FAIL_COND_V_MSG(!other_vector.is_valid(), Variant(), "Invalid type.");

    return DASFixedVector3::from_internal(value - other_vector->get_internal());
}

void DASFixedVector3::isub(const Variant& p_other) {
    if (p_other.get_type() == Variant::INT) {
        value -= fixed(p_other);
    } else {
        Ref<DASFixedVector3> other_vector =
            Object::cast_to<DASFixedVector3>(p_other);
        ERR_FAIL_COND_MSG(!other_vector.is_valid(), "Invalid type.");

        value -= other_vector->get_internal();
    }
    if (watcher) {
        watcher->fixed_vector3_changed(this);
    }
}

Ref<DASFixedVector3> DASFixedVector3::mul(const Variant& p_other) const {
    if (p_other.get_type() == Variant::INT) {
        return DASFixedVector3::from_internal(value * fixed(p_other));
    }

    Ref<DASFixedVector3> other_vector =
        Object::cast_to<DASFixedVector3>(p_other);
    ERR_FAIL_COND_V_MSG(!other_vector.is_valid(), Variant(), "Invalid type.");

    return DASFixedVector3::from_internal(value * other_vector->get_internal());
}

void DASFixedVector3::imul(const Variant& p_other) {
    if (p_other.get_type() == Variant::INT) {
        value *= fixed(p_other);
    } else {
        Ref<DASFixedVector3> other_vector =
            Object::cast_to<DASFixedVector3>(p_other);
        ERR_FAIL_COND_MSG(!other_vector.is_valid(), "Invalid type.");

        value *= other_vector->get_internal();
    }
    if (watcher) {
        watcher->fixed_vector3_changed(this);
    }
}

Ref<DASFixedVector3> DASFixedVector3::div(const Variant& p_other) const {
    if (p_other.get_type() == Variant::INT) {
        return DASFixedVector3::from_internal(value / fixed(p_other));
    }

    Ref<DASFixedVector3> other_vector =
        Object::cast_to<DASFixedVector3>(p_other);
    ERR_FAIL_COND_V_MSG(!other_vector.is_valid(), Variant(), "Invalid type.");

    return DASFixedVector3::from_internal(value / other_vector->get_internal());
}

void DASFixedVector3::idiv(const Variant& p_other) {
    if (p_other.get_type() == Variant::INT) {
        value /= fixed(p_other);
    } else {
        Ref<DASFixedVector3> other_vector =
            Object::cast_to<DASFixedVector3>(p_other);
        ERR_FAIL_COND_MSG(!other_vector.is_valid(), "Invalid type.");

        value /= other_vector->get_internal();
    }
    if (watcher) {
        watcher->fixed_vector3_changed(this);
    }
}

Ref<DASFixedVector3> DASFixedVector3::copy() const {
    return DASFixedVector3::from_internal(value);
}

Ref<DASFixedVector3> DASFixedVector3::abs() const {
    return DASFixedVector3::from_internal(value.abs());
}

Ref<DASFixedVector3> DASFixedVector3::normalized() const {
    return DASFixedVector3::from_internal(value.normalized());
}

bool DASFixedVector3::is_normalized() const { return value.is_normalized(); }

int64_t DASFixedVector3::length() const { return value.length().value; }

int64_t DASFixedVector3::length_squared() const {
    return value.length_squared().value;
}

int64_t
DASFixedVector3::distance_to(const Ref<DASFixedVector3>& p_other) const {
    ERR_FAIL_COND_V(!p_other.is_valid(), 0);
    return value.distance_to(p_other->get_internal()).value;
}

int64_t DASFixedVector3::distance_squared_to(
    const Ref<DASFixedVector3>& p_other) const {
    ERR_FAIL_COND_V(!p_other.is_valid(), 0);
    return value.distance_squared_to(p_other->get_internal()).value;
}

int64_t DASFixedVector3::angle_to(const Ref<DASFixedVector3>& p_other) const {
    ERR_FAIL_COND_V(!p_other.is_valid(), 0);
    return value.angle_to(p_other->get_internal()).value;
}

int64_t
DASFixedVector3::angle_to_point(const Ref<DASFixedVector3>& p_other) const {
    ERR_FAIL_COND_V(!p_other.is_valid(), 0);
    return value.angle_to_point(p_other->get_internal()).value;
}

Ref<DASFixedVector3>
DASFixedVector3::direction_to(const Ref<DASFixedVector3>& p_other) const {
    ERR_FAIL_COND_V(!p_other.is_valid(), Ref<DASFixedVector3>());
    return DASFixedVector3::from_internal(
        value.direction_to(p_other->get_internal()));
}

void DASFixedVector3::rotate(int64_t p_rotation) {
    value = value.rotated(fixed(p_rotation));

    if (watcher) {
        watcher->fixed_vector3_changed(this);
    }
}

int64_t DASFixedVector3::angle() const { return value.angle().value; }

int64_t DASFixedVector3::dot(const Ref<DASFixedVector3>& p_other) const {
    ERR_FAIL_COND_V(!p_other.is_valid(), 0);
    return value.dot(p_other->get_internal()).value;
}

int64_t DASFixedVector3::cross(const Ref<DASFixedVector3>& p_other) const {
    ERR_FAIL_COND_V(!p_other.is_valid(), 0);
    return value.cross(p_other->get_internal()).value;
}

Ref<DASFixedVector3> DASFixedVector3::rotated(int64_t p_rotation) const {
    return DASFixedVector3::from_internal(value.rotated(fixed(p_rotation)));
}

Ref<DASFixedVector3>
DASFixedVector3::linear_interpolate(const Ref<DASFixedVector3>& p_to,
                                    int64_t weight) const {
    ERR_FAIL_COND_V(!p_to.is_valid(), Ref<DASFixedVector3>());
    return DASFixedVector3::from_internal(
        DASFixedVector3Internal::linear_interpolate(value, p_to->get_internal(),
                                                    fixed(weight)));
}

Ref<DASFixedVector3>
DASFixedVector3::slide(const Ref<DASFixedVector3>& p_normal) const {
    ERR_FAIL_COND_V(!p_normal.is_valid(), Ref<DASFixedVector3>());
    Ref<DASFixedVector3> v(memnew(DASFixedVector3));
    v->value = value.slide(p_normal->value);
    return v;
}

Ref<DASFixedVector3>
DASFixedVector3::bounce(const Ref<DASFixedVector3>& p_normal) const {
    ERR_FAIL_COND_V(!p_normal.is_valid(), Ref<DASFixedVector3>());
    Ref<DASFixedVector3> v(memnew(DASFixedVector3));
    v->value = value.bounce(p_normal->value);
    return v;
}

Ref<DASFixedVector3>
DASFixedVector3::reflect(const Ref<DASFixedVector3>& p_normal) const {
    ERR_FAIL_COND_V(!p_normal.is_valid(), Ref<DASFixedVector3>());
    Ref<DASFixedVector3> v(memnew(DASFixedVector3));
    v->value = value.reflect(p_normal->value);
    return v;
}

bool DASFixedVector3::is_equal_approx(
    const Ref<DASFixedVector3>& p_other) const {
    ERR_FAIL_COND_V(!p_other.is_valid(), false);
    return value.is_equal_approx(p_other->get_internal());
}

void DASFixedVector3::from_float(Vector3 p_float_vector) {
    value.x = fixed::from_float(p_float_vector.x);
    value.y = fixed::from_float(p_float_vector.y);
    value.z = fixed::from_float(p_float_vector.z);

    if (watcher) {
        watcher->fixed_vector3_changed(this);
    }
}

Vector3 DASFixedVector3::to_float() const {
    return Vector3(value.x.to_float(), value.y.to_float(), value.z.to_float());
}

Ref<DASFixedVector3> DASFixedVector3::cubic_interpolate(
    const Ref<DASFixedVector3>& p_b, const Ref<DASFixedVector3>& p_pre_a,
    const Ref<DASFixedVector3>& p_post_b, int64_t p_weight) const {
    return DASFixedVector3::from_internal(
        value.cubic_interpolate(p_b->get_internal(), p_pre_a->get_internal(),
                                p_post_b->get_internal(), fixed(p_weight)));
}
