# NtpClient.cmake
# Patched for OpenWrt/offline builds
#
# When FPTN_NO_FETCHCONTENT=ON, do NOT download anything.
# This prevents FetchContent from accessing the network in CI/OpenWrt.

if(FPTN_NO_FETCHCONTENT)
  message(STATUS "FPTN_NO_FETCHCONTENT=ON: skipping NTP-client FetchContent")
  return()
endif()

include(FetchContent)

FetchContent_Declare(
  ntp_client
  URL https://github.com/batchar2/NTP-client/archive/refs/heads/master.zip
)

FetchContent_GetProperties(ntp_client)
if(NOT ntp_client_POPULATED)
  FetchContent_Populate(ntp_client)

  set(ntp_client_SOURCE_DIR "${ntp_client_SOURCE_DIR}")
  set(ntp_client_BINARY_DIR "${ntp_client_BINARY_DIR}")
  set(ntp_client_INCLUDE_DIR "${ntp_client_SOURCE_DIR}/include")

  add_subdirectory("${ntp_client_SOURCE_DIR}" "${ntp_client_BINARY_DIR}" EXCLUDE_FROM_ALL)
  include_directories("${ntp_client_INCLUDE_DIR}")
endif()
