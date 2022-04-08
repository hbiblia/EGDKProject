#ifndef ERMINE_CONFIG_H
#define ERMINE_CONFIG_H
#include <stdio.h>
#include <stdlib.h>

#define ERMINE_VERSION "0.1-dev"

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

#endif // ERMINE_CONFIG_H