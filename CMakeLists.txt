cmake_minimum_required(VERSION 3.0)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(TERMCOLOR_SUBPROJECT OFF)
else()
  set(TERMCOLOR_SUBPROJECT OFF)
endif()

project(termcolor)

#
# target
#

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)

#
# tests
#

option(TERMCOLOR_TESTS "Build termcolor tests." OFF)

if(TERMCOLOR_TESTS)
  add_executable(test_${PROJECT_NAME} test/test.cpp test/subtest.cpp)
  target_link_libraries(
    test_${PROJECT_NAME} ${PROJECT_NAME}::${PROJECT_NAME})
endif()

#
# install
#

if(NOT TERMCOLOR_SUBPROJECT)
  include(CMakePackageConfigHelpers)

  # Installation paths
  include(GNUInstallDirs)

  configure_package_config_file(
    cmake/config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
  
  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_NAME}-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

  install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

  install(
    EXPORT ${PROJECT_NAME}-targets
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
endif()
