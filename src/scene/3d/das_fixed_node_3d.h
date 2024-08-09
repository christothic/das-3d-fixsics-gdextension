#ifndef SG_FIXED_NODE_2D_H
#define SG_FIXED_NODE_2D_H

#include <godot_cpp/classes/node3d.hpp>

#include "../../math/das_fixed_vector3.h"
// #include "../../math/sg_fixed_transform_2d.h"

namespace godot {

// class SGCollisionObject2D;

class DASFixedNode3D : public Node3D, public DASFixedVector3Watcher {
    GDCLASS(DASFixedNode3D, Node3D);

    //     friend SGCollisionObject2D;

    //     Ref<SGFixedTransform2D> fixed_transform;
    Ref<DASFixedVector3> fixed_scale;
    //     int64_t fixed_rotation;
    //     bool fixed_xform_dirty;

#if defined(TOOLS_ENABLED) || defined(DEBUG_ENABLED)
    bool updating_transform;
#endif

protected:
    static void _bind_methods();
    void _notification(int p_what);

#if defined(TOOLS_ENABLED) || defined(DEBUG_ENABLED)
    // virtual void _changed_callback(Object *p_changed, const char*p_prop)
    // override;
#endif

    void _update_fixed_transform_rotation_and_scale();

    //     _FORCE_INLINE_ SGFixedTransform2DInternal
    //     get_fixed_transform_internal() const {
    //         return fixed_transform->get_internal();
    //     }
    //     SGFixedTransform2DInternal get_global_fixed_transform_internal()
    //     const;

    //     void update_fixed_transform_internal(
    //         const SGFixedTransform2DInternal& p_transform);
    //     void update_global_fixed_transform_internal(
    //         const SGFixedTransform2DInternal& p_global_transform);

    int64_t _get_fixed_position_x() const;
    void _set_fixed_position_x(int64_t p_x);
    int64_t _get_fixed_position_y() const;
    void _set_fixed_position_y(int64_t p_y);
    int64_t _get_fixed_position_z() const;
    void _set_fixed_position_z(int64_t p_z);

    int64_t _get_fixed_scale_x() const;
    void _set_fixed_scale_x(int64_t p_x);
    int64_t _get_fixed_scale_y() const;
    void _set_fixed_scale_y(int64_t p_y);
    int64_t _get_fixed_scale_z() const;
    void _set_fixed_scale_z(int64_t p_z);

    //     void transform_changed();

public:
    //     void set_fixed_transform(const Ref<SGFixedTransform2D>& p_transform);
    //     Ref<SGFixedTransform2D> get_fixed_transform() const;

    // void set_fixed_position(const Ref<DASFixedVector3>& p_fixed_position);
    // Ref<DASFixedVector3> get_fixed_position() const;

    // void set_fixed_scale(const Ref<DASFixedVector3>& p_fixed_scale);
    // Ref<DASFixedVector3> get_fixed_scale() const;

    // void set_fixed_rotation(int64_t p_fixed_rotation);
    // int64_t get_fixed_rotation() const;

    //     void set_global_fixed_transform(
    //         const Ref<SGFixedTransform2D>& p_global_transform);
    //     Ref<SGFixedTransform2D> get_global_fixed_transform() const;

    // void
    // set_global_fixed_position(const Ref<DASFixedVector3>& p_fixed_position);
    // Ref<DASFixedVector3> get_global_fixed_position();

    // void set_fixed_position_internal(
    //     const DASFixedVector3Internal& p_fixed_position);
    // void set_global_fixed_position_internal(
    //     const DASFixedVector3Internal& p_fixed_position);

    // void set_global_fixed_rotation(int64_t p_fixed_rotation);
    // int64_t get_global_fixed_rotation() const;

    // void update_float_transform();

    // void fixed_vector3_changed(DASFixedVector3* p_vector) override;

    DASFixedNode3D();
    ~DASFixedNode3D();
};

#endif
}
