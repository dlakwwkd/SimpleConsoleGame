// Reference 1: https://msdn.microsoft.com/ko-kr/library/aa985953.aspx
// Reference 2: https://github.com/zeliard/EasyGameServer/blob/master/EasyServer/EasyServer/ObjectPool.h
#pragma once
SCE_START


struct _objectPoolDeleteHelper
{
    static std::vector<uint8_t*> poolList;
    _objectPoolDeleteHelper()
    {
        poolList.reserve(1000);
    }
    ~_objectPoolDeleteHelper()
    {
        for (auto& pool : poolList)
        {
            delete[] pool;
        }
    }
};


template<typename T>
class ObjectPool
{
    const int ALLOC_COUNT = 100;
public:
    using value_type = T;

    // default ctor not required by STL
    ObjectPool() noexcept {}

    // A converting copy constructor:
    template<typename U> ObjectPool(const ObjectPool<U>&) noexcept {}
    template<typename U> bool operator==(const ObjectPool<U>&) const noexcept { return true; }
    template<typename U> bool operator!=(const ObjectPool<U>&) const noexcept { return false; }

    T*              allocate(const size_t n) const noexcept;
    void            deallocate(T* const obj, size_t) const noexcept;

    template<typename... Args>
    static std::shared_ptr<T> Get(Args&&... _Args) noexcept
    {
        return std::allocate_shared<T>(ObjectPool(), std::forward<Args>(_Args)...);
    }

    template<typename... Args>
    static std::shared_ptr<T> GetWithInit(Args&&... _Args) noexcept
    {
        auto obj = std::allocate_shared<T>(ObjectPool(), std::forward<Args>(_Args)...);
        obj->Init();
        return obj;
    }

private:
    static uint8_t*	m_FreeList;
    static int		m_TotalAllocCount;  // for tracing
    static int		m_CurrentUseCount;  // for tracing
};


template<typename T> uint8_t*   ObjectPool<T>::m_FreeList           = nullptr;
template<typename T> int        ObjectPool<T>::m_TotalAllocCount    = 0;
template<typename T> int        ObjectPool<T>::m_CurrentUseCount    = 0;


template<typename T>
T* ObjectPool<T>::allocate(const size_t n) const noexcept
{
    // 객체의 크기는 반드시 포인터 크기보다 커야 한다.
    static_assert(sizeof(T) > sizeof(size_t), "object size must bigger then pointer size!");

    // 무조건 1개의 할당만을 허용한다. (배열 할당 안됨)
    if (n != 1)
        return nullptr;

    // 여유 객체가 없다면
    if (!m_FreeList)
    {
        // 새롭게 객체를 allocCount만큼 할당하고
        m_FreeList = new uint8_t[sizeof(T) * ALLOC_COUNT];
        assert(m_FreeList);
        if (!m_FreeList)
            return nullptr;

        // 프로그램 종료시 메모리 해제를 위해 실제 할당된 포인터를 따로 저장한다.
        _objectPoolDeleteHelper::poolList.push_back(m_FreeList);

        // 객체의 크기를 기준으로 구분하여 각 객체 포인터 마다
        // 다음 여유 객체의 주소를 보관한다. (일종의 링크드 리스트)
        uint8_t*    pNext = m_FreeList;
        uint8_t**   ppCur = reinterpret_cast<uint8_t**>(m_FreeList);
        for (int i = 0; i < ALLOC_COUNT - 1; ++i)
        {
            pNext += sizeof(T);
            *ppCur = pNext;
            ppCur = reinterpret_cast<uint8_t**>(pNext);
        }
        *ppCur = 0; // 마지막은 0으로 표시
        m_TotalAllocCount += ALLOC_COUNT;
    }

    // 여유 객체 리스트에서 첫번째를 가져온다.
    uint8_t* pAvailable = m_FreeList;
    assert(pAvailable);

    // 리스트를 다음 여유 객체의 주소로 재지정한다.
    m_FreeList = *reinterpret_cast<uint8_t**>(pAvailable);

    ++m_CurrentUseCount;
    return reinterpret_cast<T*>(pAvailable);
}

template<typename T>
void ObjectPool<T>::deallocate(T* const obj, size_t) const noexcept
{
    assert(m_CurrentUseCount > 0);
    if (--m_CurrentUseCount < 0)
        return;

    // 현재의 첫번째 여유 객체 주소를 반환된 obj포인터에 보관하고
    *reinterpret_cast<uint8_t**>(obj) = m_FreeList;

    // obj포인터를 첫번째 여유 객체 주소로 지정한다. (insert to front of list)
    m_FreeList = reinterpret_cast<uint8_t*>(obj);
}

SCE_END
