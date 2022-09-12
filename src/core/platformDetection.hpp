// #ifndef platformDetection_hpp
// #define platformDetection_hpp

// #ifdef _WIN32
//     #ifdef _WIN64
//         #define MGL_PLATFORM_WINDOWS
//         #error "Windows not supported yet"
//     #else
//         #define MGL_PLATFORM_WINDOWS
//         #error "Windows x86 not supported yet"
//     #endif
// #elif defined(__APPLE__) || defined(__MACH__)
//     #include <TargetConditionals.h>
// 	/* TARGET_OS_MAC exists on all the platforms
// 	 * so we must check all of them (in this order)
// 	 * to ensure that we're running on MAC
// 	 * and not some other Apple platform */
// 	#if TARGET_IPHONE_SIMULATOR == 1
// 		#error "IOS simulator is not supported!"
// 	#elif TARGET_OS_IPHONE == 1
// 		#define HZ_PLATFORM_IOS
// 		#error "IOS is not supported!"
// 	#elif TARGET_OS_MAC == 1
// 		#define MGL_PLATFORM_OSX
// 	#else
// 		#error "Unknown Apple platform!"
// 	#endif
// #elif defined(__ANDROID__)
//     #define MGL_PLATFORM_ANDRIOID
//     #error "Andrioid is not supported"
// #elif defined(__linux__)
//     #define MGL_PLATFORM_LINUX
//     #error "Linux is not supported"
// #else
//     #error "Unknown Platform
// #endif

// #endif