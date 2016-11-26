#include "stdafx.h"
#include "Console.h"
SCE_START

constexpr Coord MAX_CONSOLE_SIZE = { 238, 70 };


struct Console::impl
{
    impl() noexcept
        : cfiOrigin{}
        , stdHandle{}
        , screenBuffer{}
        , screenIndex{}
        , screenSize{}
        , drawCall{}
        , depthBuffer{}
    {
    }

    void                SetScreenAndFontSizeForThisDesktop(OUT SHORT& _fontSize) noexcept;

    CONSOLE_FONT_INFOEX cfiOrigin;
    HANDLE              stdHandle;
    HANDLE              screenBuffer[2];
    BYTE                screenIndex;
    Coord               screenSize;
    size_t              drawCall;
    BYTE                depthBuffer[MAX_CONSOLE_SIZE.y][MAX_CONSOLE_SIZE.x];
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


size_t Console::GetDrawCallNum() const noexcept
{
    return pimpl->drawCall;
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


void Console::PrintText(const Coord& _pos, const std::wstring& _text) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(pimpl->screenBuffer[pimpl->screenIndex], { _pos.x, _pos.y });
    WriteConsole(pimpl->screenBuffer[pimpl->screenIndex],
        _text.c_str(),
        static_cast<DWORD>(_text.length()),
        &dw,
        nullptr);
    pimpl->drawCall++;
}

void Console::Print(const Coord& _pos, wchar_t _word) noexcept
{
    DWORD dw;
    SetConsoleCursorPosition(pimpl->screenBuffer[pimpl->screenIndex], { _pos.x, _pos.y });
    WriteConsole(pimpl->screenBuffer[pimpl->screenIndex],
        &_word,
        1U,
        &dw,
        nullptr);
    pimpl->drawCall++;
}

void Console::SetColor(Color _textColor, Color _bgColor) const noexcept
{
    WORD color = static_cast<WORD>(_textColor) + (static_cast<WORD>(_bgColor) << 4);
    SetConsoleTextAttribute(pimpl->screenBuffer[pimpl->screenIndex], color);
}

void Console::Clear() noexcept
{
    DWORD dw;
    DWORD screenSize = (pimpl->screenSize.x + 2) * (pimpl->screenSize.y + 2);
    FillConsoleOutputCharacter(pimpl->screenBuffer[pimpl->screenIndex], L' ', screenSize, { 0,0 }, &dw);
    FillConsoleOutputAttribute(pimpl->screenBuffer[pimpl->screenIndex], NULL, screenSize, { 0,0 }, &dw);

    ZeroMemory(pimpl->depthBuffer, sizeof(pimpl->depthBuffer[0][0]) * MAX_CONSOLE_SIZE.x * MAX_CONSOLE_SIZE.y);
}

void Console::SwapBuffer() noexcept
{
    SetConsoleActiveScreenBuffer(pimpl->screenBuffer[pimpl->screenIndex]);
    pimpl->screenIndex = !pimpl->screenIndex;
    pimpl->drawCall = 0;
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

SCE_END
