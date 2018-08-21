#include "GameObject.h"

void Oasis::GameObject::SetPosition(float x, float y)
{
    _position = glm::vec2(x, y);
}

void Oasis::GameObject::SetPosition(const glm::vec2& newPos)
{
    _position = newPos;
}
