cmake_minimum_required(VERSION 3.0)
project(termcolor)

# define target to install and link tests against
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# ALIAS same as in configure file
# the ALIAS can be used to create examples which use the same syntax as a client
# application, which uses `find_package(libdivide CONFIG)`
# create the alias libdivide::libdivide
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

option(ENABLE_TESTING "enable testing with CTEST" ON)
if(ENABLE_TESTING)
  enable_testing()
  add_executable(test_${PROJECT_NAME} test/test.cpp)
  # add compiler flags for test target only for GCC and Clang
  target_compile_options(test_${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:
      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Werror -Wall -pedantic>>
    )

  add_test(test_${PROJECT_NAME} test_${PROJECT_NAME})
  target_link_libraries(test_${PROJECT_NAME} PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})
  add_custom_target(run COMMAND test_${PROJECT_NAME})
endif()

# create install target
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-targets
  INCLUDES DESTINATION include # set include path for installed library target
  )
install(
  FILES include/termcolor/termcolor.hpp
  DESTINATION include/termcolor
  )

# Include module for fuctions
# - 'write_basic_package_version_file'
# - 'configure_package_config_file'
include(CMakePackageConfigHelpers)

# generate and install termcolor-config.cmake file
# Configure '<PROJECT-NAME>-config.cmake'
configure_package_config_file(
  "cmake/config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/termcolor-config.cmake"
  INSTALL_DESTINATION "lib/cmake/termcolor"
)
# install config file
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/generated/termcolor-config.cmake"
  DESTINATION "lib/cmake/termcolor"
)
# install targets file
install(
  EXPORT "${PROJECT_NAME}-targets"
  NAMESPACE "${PROJECT_NAME}::"
  DESTINATION "lib/cmake/termcolor"
)
