#ifndef core_hpp
#define core_hpp

// * throw an error if the platform is not OSX
#ifndef MGL_PLATFORM_OSX
    #error MGL ONLY SUPPORTS OSX
#endif

// * asserts
#ifdef MGL_ENABLE_ASSERTS
    #define MGL_ASSERT(x, ...) { if (!(x)) { MGL_ERROR("Assertion Failed: {}", __VA_ARGS__); raise(SIGTRAP); } }
    #define MGL_CORE_ASSERT(x, ...) { if (!(x)) { MGL_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__); raise(SIGTRAP); } }
#else
    #define MGL_ASSERT(x, ...)
    #define MGL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#endif