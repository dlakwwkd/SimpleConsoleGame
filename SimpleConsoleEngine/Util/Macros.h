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
#define DELETE_COPY(T) T(const T&)  = delete;   T& operator=(const T&)  = delete;
#define DELETE_MOVE(T) T(T&&)       = delete;   T& operator=(T&&)       = delete;
#define DELETE_DEF_OPER(T) DELETE_COPY(T) DELETE_MOVE(T)

#define _CREATE_SINGLETON(T) \
public: \
    static T& GetInstance() \
    { \
        static T instance; \
        return instance; \
    } \
    DELETE_DEF_OPER(T) \
private: \
    T();

#define CREATE_SINGLETON(T)     _CREATE_SINGLETON(T) ~T();
#define CREATE_SINGLETON_V(T)   _CREATE_SINGLETON(T) virtual ~T();
