#include "stdafx.h"
#include "Console.h"
#include "Coord.h"
#include "Shape.h"
SCE_START

constexpr Coord MAX_CONSOLE_SIZE    = { 238, 70 };
constexpr WORD  MAX_COLOR_SIZE      = (WORD)256;

using ShapeInfo = std::tuple<bool, wchar_t, WORD>;
using DrawInfo  = std::vector<std::pair<Coord, wchar_t>>;


struct Console::impl
{
    impl() noexcept
        : cfiOrigin{}
        , stdHandle{}
        , screenBuffer{}
        , screenIndex{}
        , screenSize{}
        , depthBuffer{}
        , shapeBuffer{}
    {
        for (auto& drawInfo : drawInfoBuffer)
        {
            drawInfo.reserve(MAX_CONSOLE_SIZE.x * MAX_CONSOLE_SIZE.y);
        }
    }

    void                SetScreenAndFontSizeForThisDesktop(OUT SHORT& _fontSize) noexcept;
    void                DrawInfoSetting() noexcept;
    void                DrawInfoPrint() noexcept;
    void                Print(const Coord& _pos, wchar_t _word) noexcept;

    CONSOLE_FONT_INFOEX cfiOrigin;
    HANDLE              stdHandle;
    HANDLE              screenBuffer[2];
    BYTE                screenIndex;
    Coord               screenSize;
    BYTE                depthBuffer[MAX_CONSOLE_SIZE.y][MAX_CONSOLE_SIZE.x];
    ShapeInfo           shapeBuffer[MAX_CONSOLE_SIZE.y][MAX_CONSOLE_SIZE.x];
    DrawInfo            drawInfoBuffer[MAX_COLOR_SIZE];
};


Console::Console() noexcept
    : pimpl(std::make_unique<impl>())
{
}

Console::~Console()
{
}


void Console::Init() noexcept
{
    Release();

    HWND hConsole = GetConsoleWindow();
    MoveWindow(hConsole, 0, 0, 0, 0, TRUE);

    pimpl->stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi{ sizeof(cfi) };
    GetCurrentConsoleFontEx(pimpl->stdHandle, FALSE, &cfi);
    CopyMemory(&pimpl->cfiOrigin, &cfi, sizeof(cfi));
    CopyMemory(cfi.FaceName, L"굴림체", LF_FACESIZE);
    pimpl->SetScreenAndFontSizeForThisDesktop(cfi.dwFontSize.Y);

    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;

    for (auto& buffer : pimpl->screenBuffer)
    {
        buffer = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            0,
            nullptr,
            CONSOLE_TEXTMODE_BUFFER,
            nullptr);
        SetConsoleActiveScreenBuffer(buffer);
        SetCurrentConsoleFontEx(buffer, FALSE, &cfi);
        SetConsoleCursorInfo(buffer, &cci);
    }
}

void Console::Release() noexcept
{
    for (auto& buffer : pimpl->screenBuffer)
    {
        CloseHandle(buffer);
    }
    SetCurrentConsoleFontEx(pimpl->stdHandle, FALSE, &pimpl->cfiOrigin);
}


Coord Console::GetScreenSize() const noexcept
{
    return pimpl->screenSize;
}

short Console::GetScreenWidth() const noexcept
{
    return pimpl->screenSize.x;
}

short Console::GetScreenHeight() const noexcept
{
    return pimpl->screenSize.y;
}


void Console::Clear() noexcept
{
    DWORD dw;
    DWORD screenSize = (pimpl->screenSize.x + 2) * (pimpl->screenSize.y + 2);
    FillConsoleOutputCharacter(pimpl->screenBuffer[pimpl->screenIndex], L' ', screenSize, { 0,0 }, &dw);
    FillConsoleOutputAttribute(pimpl->screenBuffer[pimpl->screenIndex], NULL, screenSize, { 0,0 }, &dw);
    SetConsoleTextAttribute(pimpl->screenBuffer[pimpl->screenIndex], static_cast<WORD>(Color::WHITE));
    ZeroMemory(pimpl->depthBuffer, sizeof(pimpl->depthBuffer));
    ZeroMemory(pimpl->shapeBuffer, sizeof(pimpl->shapeBuffer));
    for (auto& drawInfo : pimpl->drawInfoBuffer)
    {
        drawInfo.clear();
    }
}

void Console::SwapBuffer() noexcept
{
    pimpl->DrawInfoSetting();
    pimpl->DrawInfoPrint();

    SetConsoleActiveScreenBuffer(pimpl->screenBuffer[pimpl->screenIndex]);
    pimpl->screenIndex = !pimpl->screenIndex;
}

void Console::PrintText(const Coord& _pos, const std::wstring& _text) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(pimpl->screenBuffer[pimpl->screenIndex], { _pos.x, _pos.y });
    WriteConsole(pimpl->screenBuffer[pimpl->screenIndex],
        _text.c_str(),
        static_cast<DWORD>(_text.length()),
        &dw,
        nullptr);
}

bool Console::DepthCheck(const Coord& _pos, BYTE _depth) noexcept
{
    if (_pos.x < 0 || _pos.x > pimpl->screenSize.x ||
        _pos.y < 0 || _pos.y > pimpl->screenSize.y ||
        pimpl->depthBuffer[_pos.y][_pos.x] > _depth)
    {
        return false;
    }
    pimpl->depthBuffer[_pos.y][_pos.x] = _depth + 1;
    return true;
}

void Console::StoreShape(const Coord& _pos, const Shape& _shape) noexcept
{
    auto color = static_cast<WORD>(_shape.color) + (static_cast<WORD>(_shape.bgColor) << 4);
    pimpl->shapeBuffer[_pos.y][_pos.x] = std::make_tuple(true, _shape.form, color);
}


void Console::impl::SetScreenAndFontSizeForThisDesktop(OUT SHORT& _fontSize) noexcept
{
    RECT desktopSize;
    HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktopSize);
    if (desktopSize.bottom > 1200)
    {
        screenSize = { 210, 63 };
        _fontSize = 16;
    }
    else if (desktopSize.bottom > 900)
    {
        screenSize = { 200, 60 };
        _fontSize = 16;
    }
    else if (desktopSize.bottom >= 768)
    {
        screenSize = { 158, 42 };
        _fontSize = 14;
    }
    else
    {
        screenSize = { 150, 40 };
        _fontSize = 14;
    }
    std::ostringstream oss;
    oss << "mode con: lines="   << screenSize.y + 2
        << " cols="             << screenSize.x + 2;
    system(oss.str().c_str());
}

void Console::impl::DrawInfoSetting() noexcept
{
    for (int y = 0; y < MAX_CONSOLE_SIZE.y; ++y)
    {
        for (int x = 0; x < MAX_CONSOLE_SIZE.x; ++x)
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

void Console::impl::DrawInfoPrint() noexcept
{
    for (int i = 0; i < MAX_COLOR_SIZE; ++i)
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

void Console::impl::Print(const Coord& _pos, wchar_t _word) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(screenBuffer[screenIndex], { _pos.x, _pos.y });
    WriteConsole(screenBuffer[screenIndex], &_word, 1U, &dw, nullptr);
}

SCE_END
