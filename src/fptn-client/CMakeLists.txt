project(fptn-client)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(APPLE OR UNIX)
  set(TUNTAP_LIB tuntap++)
else()
  set(TUNTAP_LIB Wintun rpcrt4 iphlpapi Kernel32.lib)
endif()

find_package(OpenSSL REQUIRED)
find_package(argparse REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

# Make PcapPlusPlus optional (OpenWrt minimal builds)
find_package(PcapPlusPlus QUIET)
if (NOT PcapPlusPlus_FOUND)
  message(WARNING "PcapPlusPlus not found: building without it (FPTN_IP_ADDRESS_WITHOUT_PCAP)")
  add_compile_definitions(FPTN_IP_ADDRESS_WITHOUT_PCAP)
endif()

find_package(Boost REQUIRED COMPONENTS random filesystem process locale)
find_package(ZLIB REQUIRED)
find_package(httplib REQUIRED)
find_package(libidn2 REQUIRED)
find_package(re2 REQUIRED)
find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})

## brotli
find_package(brotli REQUIRED)
find_path(BROTLI_INCLUDE_DIR "brotli/decode.h" REQUIRED)
include_directories(${BROTLI_INCLUDE_DIR})
find_library(BROTLI_DEC_LIB NAMES brotlidec REQUIRED)
find_library(BROTLI_COMMON_LIB NAMES brotlicommon REQUIRED)
find_library(BROTLI_ENC_LIB NAMES brotlienc REQUIRED)

# fptn-client-cli
add_executable(
  "${PROJECT_NAME}-cli"
  fptn-client-cli.cpp
  vpn/vpn_client.h
  vpn/vpn_client.cpp
  vpn/http/client.h
  vpn/http/client.cpp
  routing/route_manager.h
  routing/route_manager.cpp
  config/config_file.cpp
  config/config_file.h
  plugins/split/tunneling.h
  plugins/split/tunneling.cpp
  plugins/blacklist/domain_blacklist.h
  plugins/blacklist/domain_blacklist.cpp
  utils/speed_estimator/speed_estimator.cpp
  utils/speed_estimator/speed_estimator.h
  utils/speed_estimator/server_info.h)

if (NOT PcapPlusPlus_FOUND)
  target_compile_definitions("${PROJECT_NAME}-cli" PRIVATE FPTN_IP_ADDRESS_WITHOUT_PCAP)
endif()

target_link_libraries(
  "${PROJECT_NAME}-cli"
  PRIVATE ZLIB::ZLIB
          Boost::boost
          Boost::random
          Boost::filesystem
          Boost::process
          Boost::locale
          OpenSSL::SSL
          OpenSSL::Crypto
          argparse::argparse
          nlohmann_json::nlohmann_json
          spdlog::spdlog
          fmt::fmt
          libidn2::libidn2
          re2::re2
          fptn-protocol-lib_static
          "${TUNTAP_LIB}"
          "${BROTLI_DEC_LIB}"
          "${BROTLI_COMMON_LIB}")

if (PcapPlusPlus_FOUND)
  target_link_libraries("${PROJECT_NAME}-cli" PRIVATE PcapPlusPlus::PcapPlusPlus)
endif()
