#ifndef core_hpp
#define core_hpp

#include "platformDetection.hpp"

// * asserts
#ifdef MGL_ENABLE_ASSERTS
    #define MGL_ASSERT(x, ...) { if (!(x)) { MGL_ERROR("Assertion Failed: {}", __VA_ARGS__); raise(SIGTRAP); } }
    #define MGL_CORE_ASSERT(x, ...) { if (!(x)) { MGL_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); raise(SIGTRAP); } }
#else
    #define MGL_ASSERT(x, ...)
    #define MGL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define MGL_BIND_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif