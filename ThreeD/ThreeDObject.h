//
// Created by yanis on 29/05/2023.
//

#ifndef MATH_THREEDOBJECT_H
#define MATH_THREEDOBJECT_H

#include "../math/Vector3.hpp"
#include "../math/Quaternion.hpp"

namespace ThreeD {
    class ThreeDObject {

    public:

        ThreeDObject(const Math::Vector3 &position, const Math::Quaternion &rotation);

        ThreeDObject();

        Math::Vector3 position;
        Math::Quaternion rotation;

        const Math::Vector3 &getPosition() const;

        void setPosition(const Math::Vector3 &position);

        void setRotation(const Math::Quaternion &rotation);

        const Math::Quaternion &getRotation() const;

        Math::Vector3 up() const;

        Math::Vector3 forward() const;

        Math::Vector3 right() const;
    };

}
#endif //MATH_THREEDOBJECT_H
