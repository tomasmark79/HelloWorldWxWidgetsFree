// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#ifndef __WXWIDGETSADAPTER_HPP
#define __WXWIDGETSADAPTER_HPP

#include <WxWidgetsAdapter/version.h>
#include <filesystem>
#include <string>

// Public API

namespace dotname {

  class WxWidgetsAdapter {

    const std::string libName_ = std::string ("WxWidgetsAdapter v.") + WXWIDGETSADAPTER_VERSION;
    std::filesystem::path assetsPath_;

  public:
    WxWidgetsAdapter ();
    WxWidgetsAdapter (const std::filesystem::path& assetsPath);
    ~WxWidgetsAdapter ();

    const std::filesystem::path getAssetsPath () const {
      return assetsPath_;
    }
    void setAssetsPath (const std::filesystem::path& assetsPath) {
      assetsPath_ = assetsPath;
    }
  };

} // namespace dotname

#endif // __WXWIDGETSADAPTER_HPP