#pragma once

#ifdef SIMPLECONSOLEENGINE_EXPORTS
#define SCE_API __declspec(dllexport)
#else
#define SCE_API __declspec(dllimport)
#endif

//────────────────────────────────────────────────────────────────────────────────────────────────────
// namespace 관련
//────────────────────────────────────────────────────────────────────────────────────────────────────
#define SCE_START   namespace SimpleConsoleEngine{
#define SCE_END     }
#define SCE_USE     using namespace SimpleConsoleEngine;
#define SCE         SimpleConsoleEngine

//────────────────────────────────────────────────────────────────────────────────────────────────────
// 매크로 함수
//────────────────────────────────────────────────────────────────────────────────────────────────────
#define _CREATE_SINGLETON(T) \
public: \
    static T& GetInstance() \
    { \
        static T instance; \
        return instance; \
    } \
    T(const T&)             = delete; \
    T(T&&)                  = delete; \
    T& operator=(const T&)  = delete; \
    T& operator=(T&&)       = delete; \
private: \
    T();

#define CREATE_SINGLETON(T)     _CREATE_SINGLETON(T) ~T();
#define CREATE_SINGLETON_V(T)   _CREATE_SINGLETON(T) virtual ~T();
