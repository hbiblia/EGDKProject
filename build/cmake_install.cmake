# Install script for directory: /d/Github/EGDK_/EGDKProyect

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/mingw64/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/d/Github/EGDK_/EGDKProyect/build/Engine/Source/Ermine/cmake_install.cmake")
  include("/d/Github/EGDK_/EGDKProyect/build/Engine/Source/Editor/cmake_install.cmake")
  include("/d/Github/EGDK_/EGDKProyect/build/Engine/Source/Game/cmake_install.cmake")
  include("/d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/cimgui/cmake_install.cmake")
  include("/d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/flecs/cmake_install.cmake")
  include("/d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/parson/cmake_install.cmake")
  include("/d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol/cmake_install.cmake")
  include("/d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/stb/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/d/Github/EGDK_/EGDKProyect/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
