#include "Coord.h"
SCE_START

constexpr Coord MAX_CONSOLE_SIZE    = { 154, 42 };
constexpr WORD  MAX_COLOR_SIZE      = 256;

/////////////////////////////////////////////////////////////////////////////////////////
struct Console::impl
{
    using ShapeInfo = std::tuple<bool, wchar_t, WORD>;
    using DrawInfo  = std::vector<std::pair<Coord, wchar_t>>;

    impl() noexcept
        : cfiOrigin{}
        , screenBuffer{}
        , screenIndex{}
        , screenSize{ MAX_CONSOLE_SIZE.x - 2, MAX_CONSOLE_SIZE.y - 2 }
        , depthBuffer{}
        , shapeBuffer{}
    {
        for (auto& drawInfo : drawInfoBuffer)
        {
            drawInfo.reserve(MAX_CONSOLE_SIZE.x * MAX_CONSOLE_SIZE.y);
        }
    }

    SHORT               SetScreenAndGetFontSizeForThisDesktop() noexcept;
    void                DrawInfoSetting() noexcept;
    void                DrawInfoPrint() noexcept;
    void                Print(const Coord& _pos, wchar_t _word) noexcept;

    CONSOLE_FONT_INFOEX cfiOrigin;
    HANDLE              screenBuffer[2];
    BYTE                screenIndex;
    Coord               screenSize;
    BYTE                depthBuffer[MAX_CONSOLE_SIZE.y][MAX_CONSOLE_SIZE.x];
    ShapeInfo           shapeBuffer[MAX_CONSOLE_SIZE.y][MAX_CONSOLE_SIZE.x];
    DrawInfo            drawInfoBuffer[MAX_COLOR_SIZE];
};

/////////////////////////////////////////////////////////////////////////////////////////
SHORT Console::impl::SetScreenAndGetFontSizeForThisDesktop() noexcept
{
    SHORT fontSize = 14;
    HWND hDesktop = GetDesktopWindow();
    RECT desktopSize;
    GetWindowRect(hDesktop, &desktopSize);
    if (desktopSize.bottom > 1440)
    {
        fontSize = 28;
    }
    else if (desktopSize.bottom > 1200)
    {
        fontSize = 24;
    }
    else if (desktopSize.bottom >= 1080)
    {
        fontSize = 22;
    }
    else if (desktopSize.bottom >= 900)
    {
        fontSize = 18;
    }
    else if (desktopSize.bottom >= 768)
    {
        fontSize = 16;
    }
    std::ostringstream oss;
    oss << "mode con: lines=" << MAX_CONSOLE_SIZE.y << " cols=" << MAX_CONSOLE_SIZE.x;
    system(oss.str().c_str());
    return fontSize;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Console::impl::DrawInfoSetting() noexcept
{
    for (short y = 0; y < MAX_CONSOLE_SIZE.y; ++y)
    {
        for (short x = 0; x < MAX_CONSOLE_SIZE.x; ++x)
        {
            auto& shape = shapeBuffer[y][x];
            if (std::get<0>(shape) == false)
                continue;

            auto form = std::get<1>(shape);
            auto color = std::get<2>(shape);
            drawInfoBuffer[color].push_back(std::make_pair(Coord{ x, y }, form));
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void Console::impl::DrawInfoPrint() noexcept
{
    for (WORD i = 0; i < MAX_COLOR_SIZE; ++i)
    {
        auto& drawInfo = drawInfoBuffer[i];
        if (drawInfo.empty())
            continue;

        // 아래의 콘솔 컬러 변환 함수가 꽤 비용이 큰 함수이기 때문에
        // 호출을 최소화하기 위해 이렇게 구현하였다.
        SetConsoleTextAttribute(screenBuffer[screenIndex], i);
        for (auto& draw : drawInfo)
        {
            Print(draw.first, draw.second);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void Console::impl::Print(const Coord& _pos, wchar_t _word) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(screenBuffer[screenIndex], { _pos.x, _pos.y });
    WriteConsole(screenBuffer[screenIndex], &_word, 1U, &dw, nullptr);
}

SCE_END
