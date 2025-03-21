#ifndef UTILS_HPP
#define UTILS_HPP

// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include "Logger/Logger.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// CMAKE generating definitions
// ../cmake/tmplt-assets.cmake)

#ifndef UTILS_ASSET_PATH
  #define UTILS_ASSET_PATH ""
#endif
#ifndef UTILS_FIRST_ASSET_FILE
  #define UTILS_FIRST_ASSET_FILE ""
#endif
#ifndef UTILS_ASSET_FILES_DIVIDED_BY_COMMAS
  #define UTILS_ASSET_FILES_DIVIDED_BY_COMMAS ""
#endif

#ifdef _WIN32
  #include <windows.h>
#elif defined(__APPLE__)
  #include <limits.h>
  #include <mach-o/dyld.h>
#else // Linux
  #include <limits.h>
  #include <unistd.h>
#endif

namespace Utils
{
  namespace FSManager
  {
    inline std::string read (const std::string &filename)
    {
      std::ifstream file;
      file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
      std::stringstream file_stream;
      try
      {
        file.open (filename.c_str ());
        file_stream << file.rdbuf ();
        file.close ();
      }
      catch (const std::ifstream::failure &e)
      {
        LOG_E << e.what () << std::endl;
      }
      return file_stream.str ();
    }

    inline std::string getExecutePath ()
    {
      std::string path;

#ifdef _WIN32
      char buffer[MAX_PATH];
      GetModuleFileNameA (NULL, buffer, MAX_PATH);
      path = buffer;
      size_t pos = path.find_last_of ("\\/");
      if (pos != std::string::npos)
      {
        path = path.substr (0, pos);
      }
#elif defined(__APPLE__)
      char buffer[PATH_MAX];
      uint32_t bufferSize = PATH_MAX;
      if (_NSGetExecutablePath (buffer, &bufferSize) == 0)
      {
        char realPath[PATH_MAX];
        if (realpath (buffer, realPath) != nullptr)
        {
          path = realPath;
          size_t pos = path.find_last_of ("/");
          if (pos != std::string::npos)
          {
            path = path.substr (0, pos);
          }
        }
      }
#else
      char buffer[PATH_MAX];
      ssize_t count = readlink ("/proc/self/exe", buffer, PATH_MAX);
      if (count != -1)
      {
        buffer[count] = '\0';
        path = buffer;
        size_t pos = path.find_last_of ("/");
        if (pos != std::string::npos)
        {
          path = path.substr (0, pos);
        }
      }
#endif

      return path;
    }

  }; // namespace FSManager

} // namespace Utils

#endif // UTILS_HPP