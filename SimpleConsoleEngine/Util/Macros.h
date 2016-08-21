#pragma once

#ifdef SIMPLECONSOLEENGINE_EXPORTS
#define SCE_API __declspec(dllexport)
#else
#define SCE_API __declspec(dllimport)
#endif

//----------------------------------------------------------------------------------------------------
// namespace 관련
//----------------------------------------------------------------------------------------------------
#define SCE_START   namespace SimpleConsoleEngine{
#define SCE_END     }
#define SCE_USE     using namespace SimpleConsoleEngine;
#define SCE         SimpleConsoleEngine

//----------------------------------------------------------------------------------------------------
// 매크로 함수
//----------------------------------------------------------------------------------------------------
// 이동,복사 생성자/대입 연산자
#define SPECIALFUNC_COPY_SET(T, SET)    \
public:                                 \
    T(const T&)             = SET;      \
    T& operator=(const T&)  = SET;      \
private:

#define SPECIALFUNC_MOVE_SET(T, SET)    \
public:                                 \
    T(T&&)              = SET;          \
    T& operator=(T&&)   = SET;          \
private:

#define SPECIALFUNC_SET(T, SET) SPECIALFUNC_COPY_SET(T, SET) SPECIALFUNC_MOVE_SET(T, SET)

//----------------------------------------------------------------------------------------------------
// 싱글톤
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

//----------------------------------------------------------------------------------------------------
// 템플릿 태그 체크 (Refer to Effective Modern C++)
#define CHECKED_T(T)        typename T, typename
#define IS_SAME(T, Other)   typename T, typename = std::enable_if_t<std::is_same<Other, std::decay_t<T>>::value>
#define IS_BASE_OF(T, Base) typename T, typename = std::enable_if_t<std::is_base_of<Base, std::decay_t<T>>::value>
