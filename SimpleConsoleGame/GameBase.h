#pragma once
class GameBase
{
public:
    GameBase() : m_GameName(L"") {}
    virtual ~GameBase() = default;

    virtual void Init()             = 0;
    virtual void Release()          = 0;

    virtual void Update(float dt)   = 0;
    virtual void Render()           = 0;

    inline const std::wstring& GetGameName() const { return m_GameName; }

protected:
    std::wstring m_GameName;
};
