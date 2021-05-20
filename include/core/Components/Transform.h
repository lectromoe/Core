#ifndef CORE_COMPONENT_TRANSFORM_H
#define CORE_COMPONENT_TRANSFORM_H

#include <core/Essential.h>
#include <core/Component.h>
#include <core/Math.h>

namespace core {

class Transform : public Component {
public:
    explicit Transform(Entity* parent = nullptr,
                       const string& name = "Transform");

    void Update() override;

    /**
     * Sets current position of transform to vec
     * @note new position will not take effect until next update cycle
     */
    void SetPosition(const Vector3& vec);

    /**
     * Sets current position of transform to vec
     * @note new position will not take effect until next update cycle
     */
    void SetPosition(const Vector3&& vec);

    /**
     * Sets current rotation of transform to vec
     * @note new position will not take effect until next update cycle
     */
    void SetRotation(const Vector3& vec);

    /**
     * Sets current rotation of transform to vec
     * @note new position will not take effect until next update cycle
     */
    void SetRotation(const Vector3&& vec);

    /**
     * Sets current scale of transform to vec
     * @note new position will not take effect until next update cycle
     */
    void SetScale(const Vector3& vec);

    /**
     * Sets current scale of transform to vec
     * @note new position will not take effect until next update cycle
     */
    void SetScale(const Vector3&& vec);

    /**
     * Transform matrix that describes current position, rotation and scale of entity in world space
     */
    Matrix4 matrix { Matrix4::identity };

    /**
     * Vector representing position of the entity in world space
     */
    Vector3 position { 0, 0, 0 };

    /**
     * Vector representing rotation of the entity along x, y and z axis in world space
     */
    Vector3 rotation {0, 0, 0 };

    /**
     * Vector representing scale of the entity in world space
     */
    Vector3 scale { 1, 1, 1 };

protected:

    void UpdateMatrix();

private:

};


}

#endif //CORE_COMPONENT_TRANSFORM_H
