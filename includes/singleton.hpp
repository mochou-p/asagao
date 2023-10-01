// asagao/includes/singleton.hpp


#pragma once


#define _SINGLETON_START(Class) \
public: \
    static Class& get_instance() \
    { \
        static Class instance; \
        return instance; \
    } \
private:

#define _SINGLETON_END(Class) \
    Class(const Class&) = delete; \
    Class& operator=(const Class&) = delete;

// base
#define SINGLETON(Class) \
_SINGLETON_START(Class) \
    Class() = default; \
_SINGLETON_END(Class)

// allows a custom constructor
#define SINGLETON_C(Class) \
_SINGLETON_START(Class) \
    Class(); \
_SINGLETON_END(Class)

// allow a custom constructor and destructor
#define SINGLETON_CD(Class) \
_SINGLETON_START(Class) \
    Class(); \
    ~Class(); \
_SINGLETON_END(Class)
