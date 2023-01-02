// SPDX-License-Identifier: GPL-3.0

/**
 * @brief std::variant is a C++-style typesafe union.
 */


#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>


using config_value = std::variant<bool, int, double, std::string>;


int main()
{
  std::unordered_map<std::string, config_value> config;

  config["window_width"] = 500;
  config["window_full_screen"] = false;
  config["database_user"] = "db_user_1";

  const auto window_width = config["window_width"];

  if (std::holds_alternative<int>(window_width))
  {
    std::cout << std::get<int>(window_width) << "\n";
  }

  if (const auto ww = std::get_if<int>(&window_width))
  {
    std::cout << *ww << "\n";
  }

  for (const auto& [what, val] : config)
  {
    std::visit([&what](const auto& val) -> void
    {
      std::cout << what << ": " << val << "\n";
    }, val);
  }

  return 0;
}
