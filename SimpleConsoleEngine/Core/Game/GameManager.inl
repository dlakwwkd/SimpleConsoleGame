#include "../../Util/AssertPack.h"
SCE_START


template<typename GameType>
inline void GameManager::Run()
{
    static_assert(std::is_convertible<GameType, GameBase>::value, "only allowed when IGame");
    if (m_IsRun || m_Game)
    {
        return;
    }
    m_Game = Safe::New<GameType>();
    if (m_Game)
    {
        Init();
        MainLoop();
        Release();
        Safe::Delete(m_Game);
    }
}

SCE_END
