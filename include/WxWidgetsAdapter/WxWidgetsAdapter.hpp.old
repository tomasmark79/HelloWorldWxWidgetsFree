#ifndef __WXWIDGETSADAPTER_H__
#define __WXWIDGETSADAPTER_H__

// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include <string>
// Public API

namespace library
{

  class WxWidgetsAdapter
  {
  public:
    WxWidgetsAdapter (const std::string &assetsPath);
    ~WxWidgetsAdapter ();

    // alternatively, you can use a getter function
    const std::string getAssetsPath () const { return m_assetsPath; }

  private:
    std::string m_assetsPath;
  };

} // namespace library

#endif // __WXWIDGETSADAPTER_H__
