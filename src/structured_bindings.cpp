// SPDX-License-Identifier: GPL-3.0

// This file shows some usecases of structured bindings in C++

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <tuple>
#include <utility>

using namespace std::chrono;

std::ostream& operator <<(std::ostream& o, const time_point<system_clock>& t)
{
    const auto time_t = system_clock::to_time_t(t);
    return o << std::ctime(&time_t);
}

std::pair<std::string, time_point<system_clock>>
get_last_user_login()
{
    // ...
    return std::make_pair("Tachyon", system_clock::now() + 24h);
}

struct temperature
{
    int temp;
    explicit temperature(int temperature) : temp(temperature) { }
    operator int() const { return temp; }
};

struct volume
{
    int vol;
    explicit volume(int volume) : vol(volume) { }
    operator int() const { return vol; }
};

std::tuple<temperature, volume, milliseconds>
get_measurements()
{
    return std::make_tuple(temperature{89}, volume{321}, 12s + 12ms);
}

int main()
{
    // std::pair decomposition
    {
      const auto& [user, last_login] = get_last_user_login();
      std::cout << "User " << std::quoted(user) << " last logged in at " << last_login;
    }


    {
      // std::tuple decomposition
      auto [temp, vol, dur] = get_measurements();
      std::cout << "Beverage temperature: " << temp
                << "\nDispensed millilitres: " << vol
                << "\nDispensing for: " << dur.count() << " ms\n";
    }


    // Decomposition of user defined struct
    {
      struct order_info
      {
        int order_id = 98'765'433;
        int beverage_id = 3;
        time_point<system_clock> ordered_at = time_point<system_clock>{64'336h};
        bool leave_space = false;
      };

      const auto& [id, bev, t, space] = order_info{};

      std::cout << "Order info:\n"
                << "  id: " << id
                << "\n  beverage: " << bev
                << "\n  ordered: " << t
                << "\n  leave space: " << space << "\n";
    }

    
    // Iterating over std::map
    {
      const std::map<int, std::string> users_by_id = {
          {344, "Tachyon"},
          {7, "Walter"},
          {3, "Der Papst"},
      };

      for (const auto& [user_id, user_name] : users_by_id)
      {
          std::cout << "User " << std::quoted(user_name) << " has the id " << user_id << "\n";
      }
    }


    return 0;
}
