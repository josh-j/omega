#pragma once

#include <cstdio>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "singleton.h"

namespace lgr {

static std::string ptr(const void* ptr) {
  char buffer[256];
  sprintf(buffer, "0x%p", ptr);
  buffer[255] = '\0';
  return buffer;
}

static std::string time() {
  char buffer[256];
  time_t rawtime;
  
  ::time(&rawtime);
  tm* timeinfo = localtime(&rawtime);

  if (timeinfo->tm_hour > 12)
    timeinfo->tm_hour -= 12;

  sprintf(buffer, "%d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
  buffer[255] = '\0';
  return buffer;
}

enum LogLevel {
  kNull = 0,
  kTrace,
  kInfo,
  kExtremeInfo,
  kWarn,
  kError,
  kFatal,
  kDebug
};

const char* const kLogLevelNames[] = {
  "null", "trace", "info", "extreme", "warn", "error", "fatal", "debug"
};

template <class SINK>
class Emitter {
  Emitter(const Emitter&);
  Emitter& operator=(const Emitter&);
public:
  Emitter() : level_(kInfo) {}
  Emitter(LogLevel level) {
    level_ = level;
    *this << "[" << kLogLevelNames[level] << "]: ";
  }

  Emitter(LogLevel level, const char* const filename, unsigned line) {
    level_ = level;
    *this << "[" << kLogLevelNames[level] << ", " << filename << ", " << line << "]: ";
  }

  Emitter(const char* const filename, unsigned line) {
    level_ = kInfo;
    *this << "[" << filename << ", " << line << "]: ";
  }

  ~Emitter() {
    pre::Singleton<SINK>::instance().HandleEmit(os_.str());
  }

  template <class T>
  inline std::ostringstream& operator<<(const T& t) {
    if (level_ <= pre::Singleton<SINK>::instance().max_log_level())
      os_ << t;
    return os_;
  }

 private:
  std::ostringstream os_; // TODO replace with std::string and printf
  LogLevel level_;
};

struct SinkInterface {
  SinkInterface() : max_log_level_(kDebug), old_max_log_level_(kDebug) {}

  virtual void HandleEmit(const std::string& emit) = 0;

  void enable() {
    max_log_level_ = old_max_log_level_;
  }

  void disable() {
    if (max_log_level_ > kNull)
      old_max_log_level_ = max_log_level_;
    max_log_level_ = kNull;
  }

  bool is_enabled() const { return max_log_level_ > kNull; }
  void set_max_log_level(LogLevel max_log_level) { max_log_level_ = max_log_level; }
  LogLevel max_log_level() const { return max_log_level_; }

 protected:
  LogLevel max_log_level_;
  LogLevel old_max_log_level_;
};

struct Sink_Ofstream : public SinkInterface {
  Sink_Ofstream() : is_buffering_(true) {}
  virtual ~Sink_Ofstream() { Close(); }

  static void Init(const std::string& filepath, bool buffer, bool append) {
    assert(!filepath.empty());
    typedef pre::Singleton<Sink_Ofstream> sink;
    sink::instance().Open(filepath, append);
    sink::instance().set_is_buffering(buffer);
  }

  static void Shutdown() {
    typedef pre::Singleton<Sink_Ofstream> sink;
    sink::instance().Close();
  }

  inline virtual void HandleEmit(const std::string& emit) {
    assert(ofs_.is_open());
    ofs_ << emit;
    if (is_buffering_)
      ofs_ << "\n";
    else
      ofs_ << std::endl;
  }

  void Open(const std::string& filepath, bool append) {
    if (ofs_.is_open())
      ofs_.close();
    if (append)
      ofs_.open(filepath, std::ios_base::app);
    else
      ofs_.open(filepath);
  }

  void Close() {
    ofs_.close();
  }

  bool is_open() const { return ofs_.is_open(); }
  // buffering is faster but not as safe -- crash could lose logs
  void set_is_buffering(bool setting) { is_buffering_ = setting; }

 protected:
  std::ofstream ofs_;
  bool is_buffering_;
};

struct Sink_Generic : public SinkInterface {
  Sink_Generic() : outputfn_(nullptr) {}
  virtual ~Sink_Generic() {}

  typedef void (*output_t)(const std::string& emit);

  static void Init(output_t outputfn) {
    typedef pre::Singleton<Sink_Generic> sink;
    sink::instance().outputfn_ = outputfn;
  }
  static void Shutdown() {
  }
  virtual void HandleEmit(const std::string& emit) {
    if (outputfn_ != nullptr)
      outputfn_(emit);
  }
  output_t outputfn_;
};

typedef Emitter<Sink_Ofstream> emit;
typedef Emitter<Sink_Generic> gemit;

#define FILEPOS __FILE__, __LINE__

} // namespace lgr

// TODO needs a inline function that handles emit, so whatever is in that function can be disabled
