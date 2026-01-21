cmake_minimum_required(VERSION 3.16)

option(BUILD_TESTING "Build tests" OFF)

# OpenWrt / offline build: use vendored libtuntap instead of downloading
if(DEFINED FPTN_NO_FETCHCONTENT AND FPTN_NO_FETCHCONTENT)
  message(STATUS "OpenWrt/offline: using vendor/libtuntap (no download)")

  set(Libtuntap_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/libtuntap")
  set(Libtuntap_BINARY_DIR "${CMAKE_BINARY_DIR}/_deps/libtuntap-build")
  set(Libtuntap_INCLUDE_DIR "${Libtuntap_BINARY_DIR}/include")

  set(BUILD_TESTING OFF)
  set(LIBTUNTAP_BUILD_TESTS OFF CACHE BOOL "Disable libtuntap tests")

  add_subdirectory("${Libtuntap_SOURCE_DIR}" "${Libtuntap_BINARY_DIR}" EXCLUDE_FROM_ALL)
  include_directories("${Libtuntap_SOURCE_DIR}/libtuntap/")
  include_directories("${Libtuntap_SOURCE_DIR}/libtuntap/bindings/cpp")
  link_directories("${Libtuntap_BINARY_DIR}/lib/")
  return()
endif()

include(FetchContent)

FetchContent_Declare(
  Libtuntap
  URL https://github.com/LaKabane/libtuntap/archive/ec1213733eb2e66e033ff8864d9fd476f9e35ffe.zip
)

FetchContent_GetProperties(Libtuntap)
if(NOT Libtuntap_POPULATED)
  FetchContent_Populate(Libtuntap)
endif()

set(Libtuntap_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/libtuntap-src")
set(Libtuntap_BINARY_DIR "${CMAKE_BINARY_DIR}/_deps/libtuntap-build")
set(Libtuntap_INCLUDE_DIR "${Libtuntap_BINARY_DIR}/include")

set(BUILD_TESTING OFF)
set(LIBTUNTAP_BUILD_TESTS OFF CACHE BOOL "Disable libtuntap tests")

add_subdirectory("${Libtuntap_SOURCE_DIR}" "${Libtuntap_BINARY_DIR}" EXCLUDE_FROM_ALL)
include_directories("${Libtuntap_SOURCE_DIR}/libtuntap/")
include_directories("${Libtuntap_SOURCE_DIR}/libtuntap/bindings/cpp")
link_directories("${Libtuntap_BINARY_DIR}/lib/")
