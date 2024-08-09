

#ifndef DAS_FIXED_VECTOR3_H
#define DAS_FIXED_VECTOR3_H

#include "godot_cpp/variant/vector3.hpp"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "../internal/das_fixed_vector3_internal.hpp"

using namespace godot;

class DASFixedVector3 : public RefCounted {
    GDCLASS(DASFixedVector3, RefCounted);

protected:
    static void _bind_methods();

public:
};

#endif
