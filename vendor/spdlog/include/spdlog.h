#pragma once
// Minimal spdlog stub for OpenWrt builds (header-only, no dependencies).
// Provides a tiny subset of the spdlog API used by many projects.
// If you later add real spdlog, this stub can be removed.

#include <cstdio>
#include <cstdarg>
#include <memory>
#include <string>

namespace spdlog {

enum level_enum { trace, debug, info, warn, err, critical, off };

inline void set_level(level_enum) {}
inline void set_pattern(const std::string&) {}
inline void flush_on(level_enum) {}

class logger {
public:
  template <typename... Args>
  void log(level_enum, const char* fmt, Args... args) {
    std::fprintf(stderr, "[fptn] ");
    std::fprintf(stderr, fmt, args...);
    std::fprintf(stderr, "\n");
  }
  template <typename... Args> void info(const char* fmt, Args... args) { log(spdlog::info, fmt, args...); }
  template <typename... Args> void warn(const char* fmt, Args... args) { log(spdlog::warn, fmt, args...); }
  template <typename... Args> void error(const char* fmt, Args... args) { log(spdlog::err, fmt, args...); }
  template <typename... Args> void debug(const char* fmt, Args... args) { log(spdlog::debug, fmt, args...); }
};

inline std::shared_ptr<logger> default_logger() {
  static std::shared_ptr<logger> l = std::make_shared<logger>();
  return l;
}
inline void set_default_logger(std::shared_ptr<logger>) {}

template <typename... Args> inline void info(const char* fmt, Args... args) { default_logger()->info(fmt, args...); }
template <typename... Args> inline void warn(const char* fmt, Args... args) { default_logger()->warn(fmt, args...); }
template <typename... Args> inline void error(const char* fmt, Args... args) { default_logger()->error(fmt, args...); }
template <typename... Args> inline void debug(const char* fmt, Args... args) { default_logger()->debug(fmt, args...); }

} // namespace spdlog
