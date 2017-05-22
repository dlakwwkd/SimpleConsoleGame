#include "stdafx.h"
#include "Console.h"
#include "ConsoleImpl.hpp"
#include "Color.hpp"
#include "Coord.h"
#include "Shape.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
Console::Console() noexcept
    : pimpl(std::make_unique<impl>())
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Console::~Console()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Console::Init() noexcept
{
    Release();

    // 화면 좌상단으로 콘솔 위치 설정
    HWND hConsole = GetConsoleWindow();
    MoveWindow(hConsole, 0, 0, 0, 0, TRUE);

    // 기존 폰트 설정 보관 및 교체할 폰트 설정
    CONSOLE_FONT_INFOEX cfi{ sizeof(cfi) };
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    CopyMemory(&pimpl->cfiOrigin, &cfi, sizeof(cfi));
    CopyMemory(cfi.FaceName, L"굴림체", LF_FACESIZE);

    // 화면 크기 및 폰트 크기 설정
    cfi.dwFontSize.Y = pimpl->SetScreenAndGetFontSizeForThisDesktop();

    // 커서 설정
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;

    // 더블버퍼 모두에 설정 적용
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

/////////////////////////////////////////////////////////////////////////////////////////
void Console::Release() noexcept
{
    for (auto& buffer : pimpl->screenBuffer)
    {
        CloseHandle(buffer);
    }
    // 기존 폰트 설정으로 복구
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &pimpl->cfiOrigin);
}

/////////////////////////////////////////////////////////////////////////////////////////
Coord Console::GetScreenSize() const noexcept
{
    return pimpl->screenSize;
}

/////////////////////////////////////////////////////////////////////////////////////////
short Console::GetScreenWidth() const noexcept
{
    return pimpl->screenSize.x;
}

/////////////////////////////////////////////////////////////////////////////////////////
short Console::GetScreenHeight() const noexcept
{
    return pimpl->screenSize.y;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Console::Clear() noexcept
{
    DWORD dw;
    DWORD screenSize = (pimpl->screenSize.x + 2) * (pimpl->screenSize.y + 2);
    FillConsoleOutputCharacter(pimpl->screenBuffer[pimpl->screenIndex], L' ', screenSize, { 0,0 }, &dw);
    FillConsoleOutputAttribute(pimpl->screenBuffer[pimpl->screenIndex], NULL, screenSize, { 0,0 }, &dw);
    SetConsoleTextAttribute(pimpl->screenBuffer[pimpl->screenIndex], Color::WHITE);
    ZeroMemory(pimpl->depthBuffer, sizeof(pimpl->depthBuffer));
    ZeroMemory(pimpl->shapeBuffer, sizeof(pimpl->shapeBuffer));
    for (auto& drawInfo : pimpl->drawInfoBuffer)
    {
        drawInfo.clear();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void Console::SwapBuffer() noexcept
{
    pimpl->DrawInfoSetting();
    pimpl->DrawInfoPrint();

    SetConsoleActiveScreenBuffer(pimpl->screenBuffer[pimpl->screenIndex]);
    pimpl->screenIndex = !pimpl->screenIndex;
}

/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
void Console::StoreShape(const Coord& _pos, const Shape& _shape) noexcept
{
    WORD color =  _shape.color + (_shape.bgColor << 4);
    if (color < MAX_COLOR_SIZE)
    {
        pimpl->shapeBuffer[_pos.y][_pos.x] = std::make_tuple(true, _shape.form, color);
        return;
    }
    assert(!"color size is overflow!");
}
