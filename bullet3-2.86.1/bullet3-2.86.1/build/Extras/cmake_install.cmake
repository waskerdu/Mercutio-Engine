# Install script for directory: C:/Users/riley/Documents/Visual Studio 2015/Projects/MercutioEngine/bullet3-2.86.1/bullet3-2.86.1/Extras

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/BULLET_PHYSICS")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/riley/Documents/Visual Studio 2015/Projects/MercutioEngine/bullet3-2.86.1/bullet3-2.86.1/build/Extras/Serialize/cmake_install.cmake")
  include("C:/Users/riley/Documents/Visual Studio 2015/Projects/MercutioEngine/bullet3-2.86.1/bullet3-2.86.1/build/Extras/ConvexDecomposition/cmake_install.cmake")
  include("C:/Users/riley/Documents/Visual Studio 2015/Projects/MercutioEngine/bullet3-2.86.1/bullet3-2.86.1/build/Extras/HACD/cmake_install.cmake")
  include("C:/Users/riley/Documents/Visual Studio 2015/Projects/MercutioEngine/bullet3-2.86.1/bullet3-2.86.1/build/Extras/GIMPACTUtils/cmake_install.cmake")
  include("C:/Users/riley/Documents/Visual Studio 2015/Projects/MercutioEngine/bullet3-2.86.1/bullet3-2.86.1/build/Extras/InverseDynamics/cmake_install.cmake")

endif()

