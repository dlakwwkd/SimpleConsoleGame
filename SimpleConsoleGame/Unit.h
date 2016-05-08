#pragma once
#include "Core/Game/Object.h"


class Unit : public SCE::Object
{
public:
    Unit();
    virtual ~Unit();

    void Init() override;
    void Release() override;
    void Update(float dt) override;
    void Render() const noexcept override;
};

