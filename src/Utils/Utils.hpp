#ifndef UTILS_HPP
#define UTILS_HPP

// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include "Logger/Logger.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// fullfilled from ../cmake/tmplt-assets.cmake)
#ifndef UTILS_ASSET_PATH
  #define UTILS_ASSET_PATH ""
#endif
// fullfilled from ../cmake/tmplt-assets.cmake)
#ifndef UTILS_FIRST_ASSET_FILE
  #define UTILS_FIRST_ASSET_FILE ""
#endif
// fullfilled from ../cmake/tmplt-assets.cmake)
#ifndef UTILS_ASSET_FILES_DIVIDED_BY_COMMAS
  #define UTILS_ASSET_FILES_DIVIDED_BY_COMMAS ""
#endif

// We need to avoid conflicts with other libraries
#ifdef _WIN32
  #include <windows.h>
#elif defined(__APPLE__)
  #include <limits.h>
  #include <mach-o/dyld.h>
#else // Linux
  #include <limits.h>
  #include <unistd.h>
#endif

namespace Utils {

  namespace FileIO {
    inline std::string readFile (const std::filesystem::path& filePath) {
      std::ifstream file (filePath, std::ios::in);
      if (!file.is_open ()) {
        throw std::ios_base::failure ("Failed to open file: " + filePath.string ());
      }
      std::stringstream buffer;
      buffer << file.rdbuf ();
      return buffer.str ();
    }

    inline void writeFile (const std::filesystem::path& filePath, const std::string& content) {
      std::ofstream file (filePath, std::ios::out | std::ios::trunc);
      if (!file.is_open ()) {
        throw std::ios_base::failure ("Failed to open file: " + filePath.string ());
      }
      file << content;
    }
  } // namespace FileIO

  namespace PathUtils {
    inline std::filesystem::path getParentPath (const std::filesystem::path& filePath) {
      return filePath.parent_path ();
    }

    inline std::string getFileName (const std::filesystem::path& filePath) {
      return filePath.filename ().string ();
    }

    inline bool fileExists (const std::filesystem::path& filePath) {
      return std::filesystem::exists (filePath);
    }

    inline std::filesystem::path getStandalonePath () {
      std::filesystem::path path;

#ifdef _WIN32
      char buffer[MAX_PATH];
      GetModuleFileNameA (NULL, buffer, MAX_PATH);
      path = buffer;
#elif defined(__APPLE__)
      char buffer[PATH_MAX];
      uint32_t bufferSize = PATH_MAX;
      if (_NSGetExecutablePath (buffer, &bufferSize) == 0) {
        path = buffer;
      }
#else
      char buffer[PATH_MAX];
      ssize_t count = readlink ("/proc/self/exe", buffer, PATH_MAX);
      if (count != -1) {
        buffer[count] = '\0';
        path = buffer;
      }
#endif
      return path;
    }

  } // namespace PathUtils

  namespace FileManager {
    inline void createDirectory (const std::filesystem::path& dirPath) {
      if (!std::filesystem::exists (dirPath)) {
        std::filesystem::create_directories (dirPath);
      }
    }

    inline void remove (const std::filesystem::path& path) {
      if (std::filesystem::exists (path)) {
        std::filesystem::remove_all (path);
      }
    }

    inline std::vector<std::filesystem::path> listFiles (const std::filesystem::path& dirPath) {
      std::vector<std::filesystem::path> files;
      for (const auto& entry : std::filesystem::directory_iterator (dirPath)) {
        files.push_back (entry.path ());
      }
      return files;
    }
  } // namespace FileManager
} // namespace Utils

#endif // UTILS_HPP