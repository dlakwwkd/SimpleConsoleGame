#pragma once
/////////////////////////////////////////////////////////////////////////////////////////
// namespace 관련
#define SCE_START   namespace SimpleConsoleEngine{
#define SCE_END     }
#define SCE_USE     using namespace SimpleConsoleEngine;
#define SCE         SimpleConsoleEngine

/////////////////////////////////////////////////////////////////////////////////////////
// 매크로 함수
/////////////////////////////////////////////////////////////////////////////////////////
// - 복사/이동 관련
#define SPECIALFUNC_COPY_SET(T, SET)    \
    public:                             \
        T(const T&)             = SET;  \
        T& operator=(const T&)  = SET;  \
    private:

#define SPECIALFUNC_MOVE_SET(T, SET)    \
    public:                             \
        T(T&&)                  = SET;  \
        T& operator=(T&&)       = SET;  \
    private:

#define SPECIALFUNC_SET(T, SET)         \
    SPECIALFUNC_COPY_SET(T, SET)        \
    SPECIALFUNC_MOVE_SET(T, SET)

#define SPECIALFUNC_COPY_DECLARE(T) \
    public:                         \
        T(const T&);                \
        T& operator=(const T&);     \
    private:

#define SPECIALFUNC_MOVE_DECLARE(T) \
    public:                         \
        T(T&&);                     \
        T& operator=(T&&);          \
    private:

#define SPECIALFUNC_DECLARE(T)      \
    SPECIALFUNC_COPY_DECLARE(T)     \
    SPECIALFUNC_MOVE_DECLARE(T)

#define SPECIALFUNC_COPY_DECLARE_NOEXCEPT(T)    \
    public:                                     \
        T(const T&) noexcept;                   \
        T& operator=(const T&) noexcept;        \
    private:

#define SPECIALFUNC_MOVE_DECLARE_NOEXCEPT(T)    \
    public:                                     \
        T(T&&) noexcept;                        \
        T& operator=(T&&) noexcept;             \
    private:

#define SPECIALFUNC_DECLARE_NOEXCEPT(T)         \
    SPECIALFUNC_COPY_DECLARE_NOEXCEPT(T)        \
    SPECIALFUNC_MOVE_DECLARE_NOEXCEPT(T)

/////////////////////////////////////////////////////////////////////////////////////////
// - 싱글톤 관련
#define _CREATE_SINGLETON(T)    \
public:                         \
    static T& GetInstance()     \
    {                           \
        static T instance;      \
        return instance;        \
    }                           \
    SPECIALFUNC_SET(T, delete)  \
private:                        \
    T();
#define CREATE_SINGLETON(T)     _CREATE_SINGLETON(T) ~T();
#define CREATE_SINGLETON_V(T)   _CREATE_SINGLETON(T) virtual ~T();

#define _CREATE_SINGLETON_NOEXCEPT(T)   \
public:                                 \
    static T& GetInstance() noexcept    \
    {                                   \
        static T instance;              \
        return instance;                \
    }                                   \
    SPECIALFUNC_SET(T, delete)          \
private:                                \
    T() noexcept;
#define CREATE_SINGLETON_NOEXCEPT(T)    _CREATE_SINGLETON_NOEXCEPT(T) ~T();
#define CREATE_SINGLETON_NOEXCEPT_V(T)  _CREATE_SINGLETON_NOEXCEPT(T) virtual ~T();

/////////////////////////////////////////////////////////////////////////////////////////
// - Pimpl
#define DECLARE_PIMPL               \
protected:                          \
    struct impl;                    \
    std::unique_ptr<impl> pimpl;    \
private:

/////////////////////////////////////////////////////////////////////////////////////////
// - 기타
#define CONVERT_STRING(T) std::string(#T)
