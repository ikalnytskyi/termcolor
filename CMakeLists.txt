project (termcolor)
cmake_minimum_required (VERSION 2.8)

#
# compiler settings
#

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set (CMAKE_COMPILER_IS_CLANG True)
endif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)
  set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -fvisibility=hidden")
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_INIT} -g")
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_INIT} -O2")
endif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG)


#
# project settings
#

set (TERMCOLOR_INCLUDE ${termcolor_SOURCE_DIR}/include)
include_directories(${TERMCOLOR_INCLUDE})

set (TEST_EXECUTABLE "${CMAKE_PROJECT_NAME}-test")
add_executable (test_${CMAKE_PROJECT_NAME} test/test.cpp)

install (DIRECTORY "${TERMCOLOR_INCLUDE}/termcolor"
    DESTINATION     include
)


#
# cpack settings
#

set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Igor Kalnitsky")

set (CPACK_PACKAGE_VERSION_MAJOR "0")
set (CPACK_PACKAGE_VERSION_MINOR "1")
set (CPACK_PACKAGE_VERSION_PATCH "0")

set (CPACK_PACKAGE_VENDOR "Igor Kalnitsky")
set (CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "print colored messages on terminal
 Termcolor is a header-only C++ library for printing colored messages
 to the terminal. Written just for fun with a help of the Force."
)

include (CPack)
