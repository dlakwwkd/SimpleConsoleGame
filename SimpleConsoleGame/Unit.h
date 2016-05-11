#pragma once
#include "Core/Game/Object.h"
#include "Core/Game/Vec2.h"


class Unit : public SCE::Object
{
    SPECIALFUNC_SET(Unit, default)
public:
    Unit();
    ~Unit() override;

    void Init()                     override;
    void Release()                  override;
    void Update(float dt)           override;
    void Render() const noexcept    override;

    inline void AddMovePower(const SCE::Vec2& addPower) noexcept { *m_MovePower += addPower; }

protected:
    std::unique_ptr<SCE::Vec2>  m_MovePower;
    float                       m_Speed;
};
