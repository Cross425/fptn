project(fptn-protocol-lib LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# include(${CMAKE_SOURCE_DIR}/depends/cmake/NtpClient.cmake)
include(../../depends/cmake/NtpClient.cmake)
if (IOS)
  find_library(SECURITY Security)
  find_library(CFNETWORK CFNetwork)
  find_library(SYSTEMCONFIGURATION SystemConfiguration)

  add_compile_definitions(FPTN_USER_OS=\"iOS\")
elseif(__ANDROID__)
  add_compile_definitions(FPTN_USER_OS=\"Android\")
elseif(APPLE)
  add_compile_definitions(FPTN_USER_OS=\"MacOS\")
elseif(WIN32)
  add_compile_definitions(FPTN_USER_OS=\"Windows\")
elseif(UNIX)
  add_compile_definitions(FPTN_USER_OS=\"Linux\")
else()
  message(FATAL_ERROR "Unsupported platform")
endif()

# NTP-client is provided via depends/cmake/NtpClient.cmake.
# In OpenWrt/offline builds it may be disabled; link only if the target exists.
set(NTP_CLIENT_LIB "")
if (TARGET ntp_client)
  set(NTP_CLIENT_LIB ntp_client)
else()
  message(STATUS "ntp_client target not present: building without NTP client support")
  add_compile_definitions(FPTN_DISABLE_NTP)
endif()

find_package(absl QUIET)
set(Protobuf_PROTOC_EXECUTABLE "" CACHE FILEPATH "" FORCE)
find_package(Protobuf REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(spdlog QUIET)
if (NOT spdlog_FOUND)
  find_path(SPDLOG_INCLUDE_DIR spdlog/spdlog.h)
  if (NOT SPDLOG_INCLUDE_DIR)
    message(FATAL_ERROR "spdlog not found (no CMake config and no headers)")
  endif()
  message(STATUS "spdlog: using header-only from ${SPDLOG_INCLUDE_DIR}")
  add_library(spdlog::spdlog INTERFACE IMPORTED)
  set_target_properties(spdlog::spdlog PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SPDLOG_INCLUDE_DIR}"
  )
endif()
find_package(fmt REQUIRED)
find_package(re2 REQUIRED)

find_package(Boost REQUIRED COMPONENTS random filesystem nowide locale)
find_package(ZLIB REQUIRED)
find_package(nlohmann_json REQUIRED)

if (FPTN_BUILD_ONLY_FPTN_LIB)
  # build fptnlib without pcappp
  set(FPTN_IP_ADDRESS_WITHOUT_PCAP ON)
endif()

if (FPTN_WITH_LIBIDN2)
  find_package(libidn2 REQUIRED)
endif ()

if(NOT FPTN_IP_ADDRESS_WITHOUT_PCAP)
  find_package(PcapPlusPlus REQUIRED)
endif()

include_directories(${nlohmann_json_INCLUDE_DIRS})

# include
if(ABSL_INCLUDE_DIRS)
  include_directories(${ABSL_INCLUDE_DIRS})
endif()
if(absl_INCLUDE_DIRS)
  include_directories(${absl_INCLUDE_DIRS})
endif()

if(PROTOBUF_INCLUDE_DIR)
  include_directories(${PROTOBUF_INCLUDE_DIR})
endif()
if(protobuf_INCLUDE_DIRS)
  include_directories(${protobuf_INCLUDE_DIRS})
endif()
if(Protobuf_INCLUDE_DIRS)
  include_directories(${Protobuf_INCLUDE_DIRS})
endif()
if(CONAN_INCLUDE_DIRS_PROTOBUF)
  include_directories(${CONAN_INCLUDE_DIRS_PROTOBUF})
endif()
include_directories(${SOURCE_DIR} ${INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/fptn_protocol)
include_directories(${CMAKE_BINARY_DIR}/src/fptn-protocol-lib/protobuf)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/protobuf")

# Generate C++ source and header files from the .proto files
set(protobuf_files protobuf/protocol.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${protobuf_files})

# --- disable clang-tidy for protobuf generated code ---
set_source_files_properties($<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/protocol.pb.h> PROPERTIES SKIP_CLANG_TIDY ON)
set_source_files_properties($<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/protocol.pb.сс> PROPERTIES SKIP_CLANG_TIDY ON)
set(DISABLE_TIDY_DIR "${CMAKE_BINARY_DIR}/src/fptn-protocol-lib/protobuf/")
file(MAKE_DIRECTORY "${DISABLE_TIDY_DIR}")
file(
  WRITE "${DISABLE_TIDY_DIR}/.clang-tidy"
  "Checks: '-*,readability-inconsistent-declaration-parameter-name'
WarningsAsErrors: ''
    ")

set(FPTN_CLIENT_PROTOCOL_SOURCES
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    https/api_client/api_client.h
    https/api_client/api_client.cpp
    https/obfuscator/methods/tls/tls_obfuscator.cpp
    https/obfuscator/methods/tls/tls_obfuscator.h
    https/obfuscator/methods/obfuscator_interface.h
    https/obfuscator/tcp_stream/tcp_stream.h
    https/utils/tls/tls.h
    https/utils/tls/tls.cpp
    https/websocket_client/websocket_client.h
    https/websocket_client/websocket_client.cpp
    protobuf/protocol.h
    protobuf/protocol.cpp
    time/time_provider.h
    time/time_provider.cpp
    https/obfuscator/methods/detector.h)

add_library("${PROJECT_NAME}_static" STATIC ${FPTN_CLIENT_PROTOCOL_SOURCES})

foreach(target "${PROJECT_NAME}_static")
  if(FPTN_IP_ADDRESS_WITHOUT_PCAP)
    set(PCAP_LIB "")
  else()
    set(PCAP_LIB PcapPlusPlus::PcapPlusPlus)
  endif()

  if(FPTN_WITH_LIBIDN2)
    set(LIBIDN2_LIB libidn2::libidn2)
  else()
    set(LIBIDN2_LIB "")
  endif()
  
  if(MSVC)
    target_compile_options(${target} PRIVATE /wd4100 /wd4702) # disable warning C4100
  endif()

  if(IOS)
    set(IOS_LIBS "${SECURITY} ${CFNETWORK} ${SYSTEMCONFIGURATION} -framework Foundation z resolv")
  else()
    set(IOS_LIBS "")
  endif()

  if (IOS)
    set_target_properties(${target}
      PROPERTIES
          CXX_STANDARD 17
          CXX_STANDARD_REQUIRED ON
          CXX_EXTENSIONS OFF
          XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
          XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "NO"
          XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    )
  endif()

  target_include_directories(${target} INTERFACE ${CMAKE_CURRENT_BINARY_DIR} protobuf::protobuf)
  target_link_libraries(
    ${target}
    ${Protobuf_LIBRARIES}
    ${protobuf_LIBRARIES}
    protobuf::libprotobuf
    ZLIB::ZLIB
    Boost::boost
    Boost::nowide
    Boost::random
    Boost::locale
    OpenSSL::SSL
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    fmt::fmt
    ${NTP_CLIENT_LIB}
    re2::re2
    ${PCAP_LIB}
    ${LIBIDN2_LIB}
    ${IOS_LIBS}
  )
endforeach()
