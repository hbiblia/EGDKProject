#ifndef ERMINE_H_
#define ERMINE_H_
#include <stdio.h>

#define ERMINE_VERSION "0.1-dev"
// #define USE_LIBTYPE_SHARED

#define VD(v, m, d) v == m ? d : v

#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #define ermine_public __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define ermine_public __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

#ifndef ermine_public
    #define ermine_public
#endif

#ifndef ermine_private
    #define ermine_private
#endif

#endif // ERMINE_H_