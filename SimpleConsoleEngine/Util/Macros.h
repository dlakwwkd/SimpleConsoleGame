#pragma once
/////////////////////////////////////////////////////////////////////////////////////////
// namespace 관련
#define SCE_START   namespace SimpleConsoleEngine{
#define SCE_END     } namespace SCE = SimpleConsoleEngine;
#define SCE_USE     using namespace SimpleConsoleEngine;

/////////////////////////////////////////////////////////////////////////////////////////
// 복사/이동 관련
#define _SPECIALFUNC_COPY(T, TOKEN)     \
    public:                             \
        T(const T&)             TOKEN;  \
        T& operator=(const T&)  TOKEN;  \
    private:
#define _SPECIALFUNC_MOVE(T, TOKEN)     \
    public:                             \
        T(T&&)                  TOKEN;  \
        T& operator=(T&&)       TOKEN;  \
    private:
#define SPECIALFUNC_COPY_SET(T, SET)    _SPECIALFUNC_COPY(T, = SET)
#define SPECIALFUNC_MOVE_SET(T, SET)    _SPECIALFUNC_MOVE(T, = SET)
#define SPECIALFUNC_SET(T, SET)         _SPECIALFUNC_COPY(T, = SET) _SPECIALFUNC_MOVE(T, = SET)
#define SPECIALFUNC_COPY_DECLARE(T)     _SPECIALFUNC_COPY(T, )
#define SPECIALFUNC_MOVE_DECLARE(T)     _SPECIALFUNC_MOVE(T, )
#define SPECIALFUNC_DECLARE(T)          _SPECIALFUNC_COPY(T, )      _SPECIALFUNC_MOVE(T, )

/////////////////////////////////////////////////////////////////////////////////////////
// 싱글톤 관련
#define _CREATE_SINGLETON(T, SET)       \
public:                                 \
    static T& GetInstance() SET         \
    {                                   \
        static T instance;              \
        return instance;                \
    }                                   \
    SPECIALFUNC_SET(T, delete)          \
private:                                \
    T() SET;
#define CREATE_SINGLETON(T)             _CREATE_SINGLETON(T, ) ~T();
#define CREATE_SINGLETON_V(T)           _CREATE_SINGLETON(T, ) virtual ~T();
#define CREATE_SINGLETON_NOEXCEPT(T)    _CREATE_SINGLETON(T, noexcept) ~T();
#define CREATE_SINGLETON_NOEXCEPT_V(T)  _CREATE_SINGLETON(T, noexcept) virtual ~T();

/////////////////////////////////////////////////////////////////////////////////////////
// Pimpl
#define DECLARE_PIMPL                   \
protected:                              \
    struct impl;                        \
    std::unique_ptr<impl> pimpl;        \
private:

/////////////////////////////////////////////////////////////////////////////////////////
// type name to string
#define TO_STRING(T) std::string(#T)
