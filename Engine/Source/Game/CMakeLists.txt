# EDITOR

set(SOUCE_EDITOR
    src/main.c
)
set(CXX_FLAGS -DUSE_LIBTYPE_SHARED)

add_executable(EGDKGame ${SOUCE_EDITOR})
target_link_libraries(EGDKGame ${EGDK_LIBS} Ermine flecs)
target_compile_options(EGDKGame PRIVATE ${CXX_FLAGS})

if(EGDK_PLATFORM STREQUAL WINDOWS)
    # # VS
    # target_compile_options(EGDKGame PRIVATE /W3)
    # MSYS2
    target_compile_options(EGDKGame PRIVATE -Wall -Wextra -Wpedantic -lResource -mwin32 -O2)
elseif(EGDK_PLATFORM STREQUAL LINUX)
    target_compile_options(EGDKGame PRIVATE -Wall -Wextra -Wpedantic -lResource)
elseif(EGDK_PLATFORM STREQUAL DARWIN)
endif()