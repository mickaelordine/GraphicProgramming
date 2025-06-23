#pragma once
#include "Component.h"
#include "Math.h"
#include "Component.h"

class SquareComponent : public Component {
public:
    SquareComponent(Actor* owner);

    float GetWidth() const { return m_Width; }
    float GetHeight() const { return m_Height; }
    void SetWidth(float width) { m_Width = width; }
    void SetHeight(float height) { m_Height = height; }

    const Vector2& GetCenter() const;

private:
    float m_Width;
    float m_Height;
};

