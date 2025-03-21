// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include "WxWidgetsAdapter/WxWidgetsAdapter.hpp"
#include "Utils/Utils.hpp"
#include "Logger/Logger.hpp"

#include <cxxopts.hpp>
#include <fstream>
#include <iostream>
#include <memory>

constexpr char standaloneName[] = "HWWxWidgets";

std::string executablePath = Utils::FSManager::getExecutePath ();

/// @brief Main Standalone entry point
int mainIsOmited (int argc, const char *argv[])
{
  // ---basic-information------is-safe-to-delete 👇🏻
  LOG_I << standaloneName << " / C++ = " << __cplusplus << std::endl;
  LOG_I << "executablePath = " << executablePath << std::endl;
  // ----------------------------------delete me 👆🏻

  // ---assets-testing---------is-safe-to-delete 👇🏻
  std::string assetFp = executablePath + "/"
                        + static_cast<std::string> (UTILS_ASSET_PATH) + "/"
                        + static_cast<std::string> (UTILS_FIRST_ASSET_FILE);
  std::ifstream file (assetFp);
  try
  {
    if (file.is_open ())
    {
      LOG_I << "1st asset file = " << assetFp << std::endl;
      LOG_I << "1st asset file content = " << Utils::FSManager::read (assetFp)
            << std::endl;
    }
    else
      LOG_E << "Error opening first asset file: " << assetFp << std::endl;
  }
  catch (const std::exception &e)
  {
    LOG_E << "Error reading first asset file: " << e.what () << std::endl;
  }
  // ----------------------------------delete me 👆🏻

  // ---argument-parsing-------is-safe-to-delete 👇🏻
  try
  {
    auto options
      = std::make_unique<cxxopts::Options> (argv[0], standaloneName);
    options->positional_help ("[optional args]").show_positional_help ();
    options->set_width (70)
      .set_tab_expansion ()
      .allow_unrecognised_options ()
      .add_options () ("h,help", "Show help") (
        "o,omit", "Omit library loading",
        cxxopts::value<bool> ()->default_value ("false")) (
        "l,log2file", "Log to file",
        cxxopts::value<bool> ()->default_value ("false"));

    const auto result = options->parse (argc, argv);

    if (result.count ("help"))
    {
      LOG_I << options->help ({ "", "Group" }) << std::endl;
      return 0;
    }

    if (result["log2file"].as<bool> ())
    {
      LOG.enableFileLogging (std::string (standaloneName) + ".log");
      LOG_I << "Logging to file enabled [-l]" << std::endl;
    }

    if (!result.count ("omit"))
    {
      const std::string assetsPath
        = executablePath + "/" + static_cast<std::string> (UTILS_ASSET_PATH);
      std::unique_ptr<library::WxWidgetsAdapter> lib
        = std::make_unique<library::WxWidgetsAdapter> (assetsPath);
    }
    else
    {
      LOG_W << "Loading library omitted [-o]" << std::endl;
    }
  }
  catch (const cxxopts::exceptions::exception &e)
  {
    LOG_E << "error parsing options: " << e.what ();
    return 1;
  }
  // ----------------------------------delete me 👆🏻

  return 0;
}