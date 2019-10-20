#pragma once
#include "../Interface/IComponent.h"
SCE_START
enum Color : uint16_t;
struct Coord;
struct Shape;

/////////////////////////////////////////////////////////////////////////////////////////
class RenderComponent : public IComponentCRTP<RenderComponent>
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(RenderComponent, default)
public:
    enum class RenderType
    {
        CmdConsole,
        Window,
    };
public:
    RenderComponent(const CompositeRef& _owner) noexcept;
    virtual ~RenderComponent() override;

    virtual std::string     GetComponentName() const override;
    virtual CompositePtr    GetOwner() const override;

    void                    Render();

    bool                    IsShow() const noexcept;
    BYTE                    GetDepth() const noexcept;
    const Coord&            GetCoord() const noexcept;
    const Shape&            GetShape() const noexcept;
    wchar_t                 GetForm() const noexcept;
    Color                   GetColor() const noexcept;
    Color                   GetBGColor() const noexcept;

    void                    SetShow(bool _isShow) noexcept;
    void                    SetDepth(BYTE _depth) noexcept;
    void                    SetCoord(const Coord& _coord) noexcept;
    void                    SetCoord(short _x, short _y) noexcept;
    void                    SetShape(const Shape& _shape) noexcept;
    void                    SetShape(wchar_t _form) noexcept;
    void                    SetColor(Color _color) noexcept;
    void                    SetBGColor(Color _bgColor) noexcept;
};

SCE_END
