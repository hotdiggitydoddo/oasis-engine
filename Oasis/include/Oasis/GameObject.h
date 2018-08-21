#pragma once

#include <glm/glm.hpp>

namespace Oasis
{
    class GameObject
    {
    public:
        glm::vec2 GetPosition() const
        { return _position; }

        void SetPosition(float x, float y);

        void SetPosition(const glm::vec2& newPos);

    protected:
        glm::vec2 _position;
    };
}



