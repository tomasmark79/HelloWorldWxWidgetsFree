#ifndef LOGGER_HPP
#define LOGGER_HPP

// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#ifdef _WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  // Disable min/max macros in windows.h to avoid conflicts with std::min/max
  // cxxopts.hpp uses std::min/max
  #endif

  // Undefine Raylib functions to avoid conflicts
  #define Rectangle WindowsRectangle
  #define CloseWindow WindowsCloseWindow
  #define ShowCursor WindowsShowCursor
  #define DrawText WindowsDrawText
  #define PlaySound WindowsPlaySound
  #define PlaySoundA WindowsPlaySoundA
  #define PlaySoundW WindowsPlaySoundW
  #define LoadImage WindowsLoadImage
  #define DrawTextEx WindowsDrawTextEx

  #include <windows.h>

  // Restore Raylib functions
  #undef Rectangle
  #undef CloseWindow
  #undef ShowCursor
  #undef DrawText
  #undef PlaySound
  #undef PlaySoundA
  #undef PlaySoundW
  #undef LoadImage
  #undef DrawTextEx

#endif

// Function name macros for different compilers
#if defined(__GNUC__) || defined(__clang__)
  #define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
  #define FUNCTION_NAME __FUNCSIG__
#else
  #define FUNCTION_NAME __func__
#endif

class Logger
{
public:
  enum class Level
  {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
  };

  static Logger &getInstance () // Meyers' Singleton
  {
    static Logger instance;
    return instance;
  }

  Logger (const Logger &) = delete;            // Delete copy constructor
  Logger &operator= (const Logger &) = delete; // Delete copy assignment
  Logger &operator<< (Level level)             // Set log level
  {
    m_currentLevel = level;
    return *this; // Return reference to Logger
  }

  Logger &setCallingFunction (const std::string &caller)
  {
    m_callingFunction = caller;
    return *this;
  }

  Logger &
  operator<< (std::ostream &(*manip) (std::ostream &)) // Handle std::endl
  {
    if (manip == static_cast<std::ostream &(*)(std::ostream &)> (std::endl))
    {
      log (m_currentLevel, m_messageStream.str (), m_callingFunction);
      // Reset state
      m_messageStream.str ("");
      m_messageStream.clear ();
      m_callingFunction = "";
    }
    else
    {
      m_messageStream << manip;
    }
    return *this;
  }

  template <typename T> Logger &operator<< (const T &message) // Handle message
  {
    std::lock_guard<std::mutex> lock (m_logMutex);
    m_messageStream << message;
    return *this;
  }

  void debug (const std::string &message, const std::string &caller = "")
  {
    log (Level::LOG_DEBUG, message, caller);
  }

  void info (const std::string &message, const std::string &caller = "")
  {
    log (Level::LOG_INFO, message, caller);
  }

  void warning (const std::string &message, const std::string &caller = "")
  {
    log (Level::LOG_WARNING, message, caller);
  }

  void error (const std::string &message, const std::string &caller = "")
  {
    log (Level::LOG_ERROR, message, caller);
  }

  void critical (const std::string &message, const std::string &caller = "")
  {
    log (Level::LOG_CRITICAL, message, caller);
  }

  bool enableFileLogging (const std::string &filename)
  {
    std::lock_guard<std::mutex> lock (m_logMutex);
    try
    {
      m_logFile.open (filename, std::ios::out | std::ios::app);
      return m_logFile.is_open ();
    }
    catch (...)
    {
      return false;
    }
  }

  void disableFileLogging ()
  {
    std::lock_guard<std::mutex> lock (m_logMutex);
    if (m_logFile.is_open ())
    {
      m_logFile.close ();
    }
  }

  void setApplicationName (const std::string &appName)
  {
    std::lock_guard<std::mutex> lock (m_logMutex);
    m_name = appName;
  }

private:
  std::string m_name = "DotNameLib";
  std::mutex m_logMutex;
  std::string m_callingFunction;
  std::ostringstream m_messageStream;
  std::ofstream m_logFile;
  Level m_currentLevel = Level::LOG_INFO;

  Logger () = default;
  ~Logger ()
  {
    if (m_logFile.is_open ())
    {
      m_logFile.close ();
    }
  }

  std::string levelToString (Level level) const
  {
    switch (level)
    {
    case Level::LOG_DEBUG:
      return "DBG";
    case Level::LOG_INFO:
      return "INF";
    case Level::LOG_WARNING:
      return "WRN";
    case Level::LOG_ERROR:
      return "ERR";
    case Level::LOG_CRITICAL:
      return "CRI";
    default:
      return "INF";
    }
  }

  void resetConsoleColor ()
  {
#ifdef _WIN32
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             FOREGROUND_RED | FOREGROUND_GREEN
                               | FOREGROUND_BLUE);
#else
    std::cout << "\033[0m"; // Reset
#endif
  }

#ifdef _WIN32
  // Pomocná funkce pro Windows
  void setConsoleColorWindows (Level level)
  {
    const std::map<Level, WORD> colorMap
      = { { Level::LOG_DEBUG,
            FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY },
          { Level::LOG_INFO, FOREGROUND_GREEN | FOREGROUND_INTENSITY },
          { Level::LOG_WARNING,
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY },
          { Level::LOG_ERROR, FOREGROUND_RED | FOREGROUND_INTENSITY },
          { Level::LOG_CRITICAL,
            FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE } };

    auto it = colorMap.find (level);
    if (it != colorMap.end ())
    {
      SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), it->second);
    }
    else
    {
      resetConsoleColor ();
    }
  }
#else
  // Pomocná funkce pro Unix (ANSI escape kódy)
  void setConsoleColorUnix (Level level)
  {
    static const std::map<Level, const char *> colorMap
      = { { Level::LOG_DEBUG, "\033[34m" },
          { Level::LOG_INFO, "\033[32m" },
          { Level::LOG_WARNING, "\033[33m" },
          { Level::LOG_ERROR, "\033[31m" },
          { Level::LOG_CRITICAL, "\033[95m" } };

    auto it = colorMap.find (level);
    if (it != colorMap.end ())
    {
      std::cout << it->second;
    }
    else
    {
      resetConsoleColor ();
    }
  }
#endif

  // Upravená metoda setConsoleColor (bez #ifdef uvnitř těla)
  void setConsoleColor (Level level)
  {
#ifdef _WIN32
    setConsoleColorWindows (level);
#else
    setConsoleColorUnix (level);
#endif
  }

  void log (Level level, const std::string &message,
            const std::string &caller = "")
  {
    std::lock_guard<std::mutex> lock (m_logMutex);

    auto now = std::chrono::system_clock::now ();
    auto now_time = std::chrono::system_clock::to_time_t (now);

    // Use thread-safe localtime
    std::tm now_tm;
#ifdef _WIN32
    localtime_s (&now_tm, &now_time);
#else
    localtime_r (&now_time, &now_tm);
#endif

    // cerr output
    if (level == Level::LOG_ERROR || level == Level::LOG_CRITICAL)
    {
      std::cerr << "[" << std::put_time (&now_tm, "%d-%m-%Y %H:%M:%S") << "] ";
      if (!caller.empty ())
      {
        std::cerr << "[" << caller << "] ";
      }
      std::cerr << "[" << levelToString (level) << "] ";
      setConsoleColor (level);
      std::cerr << message;
      resetConsoleColor ();
      std::cerr << std::endl;
    }

    // cout output
    if (level == Level::LOG_DEBUG || level == Level::LOG_INFO
        || level == Level::LOG_WARNING)
    {
      std::cout << "[" << std::put_time (&now_tm, "%d-%m-%Y %H:%M:%S") << "] ";
      if (!caller.empty ())
      {
        std::cout << "[" << caller << "] ";
      }
      std::cout << "[" << levelToString (level) << "] ";
      setConsoleColor (level);
      std::cout << message;
      resetConsoleColor ();
      std::cout << std::endl;
    }

    // file output
    if (m_logFile.is_open ())
    {
      m_logFile << "[" << std::put_time (&now_tm, "%d-%m-%Y %H:%M:%S") << "] ";
      if (!caller.empty ())
      {
        m_logFile << "[" << caller << "] ";
      }
      m_logFile << "[" << levelToString (level) << "] " << message
                << std::endl;
    }
  }

}; // class Logger

#define LOG Logger::getInstance ()

#define LOG_DEBUG(msg) LOG.debug (msg, FUNCTION_NAME)
#define LOG_INFO(msg) LOG.info (msg, FUNCTION_NAME)
#define LOG_WARING(msg) LOG.warning (msg, FUNCTION_NAME)
#define LOG_ERROR(msg) LOG.error (msg, FUNCTION_NAME)
#define LOG_CRITICAL(msg) LOG.critical (msg, FUNCTION_NAME)

#define LOG_WITH_CALLER LOG.setCallingFunction (FUNCTION_NAME)

#define LOG_D LOG_WITH_CALLER << Logger::Level::LOG_DEBUG
#define LOG_I LOG_WITH_CALLER << Logger::Level::LOG_INFO
#define LOG_W LOG_WITH_CALLER << Logger::Level::LOG_WARNING
#define LOG_E LOG_WITH_CALLER << Logger::Level::LOG_ERROR
#define LOG_C LOG_WITH_CALLER << Logger::Level::LOG_CRITICAL

#endif // LOGGER_HPP