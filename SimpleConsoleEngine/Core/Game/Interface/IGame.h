#pragma once
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
__interface IGame
{
    void Init();
    void Release();
    void Update(float _dt);
    void Render();
};

SCE_END
