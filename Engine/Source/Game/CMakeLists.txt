# EDITOR

set(SOUCE_EDITOR
    src/main.c
)

add_executable(EGDKGame ${SOUCE_EDITOR})
target_link_libraries(EGDKGame ${EGDK_LIBS} Ermine)

if(EGDK_PLATFORM STREQUAL WINDOWS)
    target_compile_options(EGDKGame PRIVATE /W3)
elseif(EGDK_PLATFORM STREQUAL LINUX)
    target_compile_options(EGDKGame PRIVATE -Wall -Wextra -Wpedantic)
elseif(EGDK_PLATFORM STREQUAL DARWIN)
endif()