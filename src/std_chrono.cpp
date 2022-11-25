// SPDX-License-Identifier: GPL-3.0

#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;  // <- For the literals min, s, ms, ...
using namespace std::chrono;

// Duration as function parameter
void sleepFor(const nanoseconds& duration)
{
    std::this_thread::sleep_for(duration);
}

void longRunningOperation()
{
    // Duration arithmetics and automatic conversion
    sleepFor(2s + 5ms + 623us);
}

int main()
{
    // Measure duration
    const auto start = steady_clock::now();
    longRunningOperation();
    const auto duration = steady_clock::now() - start;

    // Splitting into parts
    std::cout << duration / 1s << " s "
              << (duration % 1s) / 1ms << " ms "
              << (duration % 1ms) / 1us << " μs" << "\n";

    // Rounding durations
    const auto one_hour = ceil<hours>(duration);
    assert(one_hour.count() == 1);

    const auto still_one_hour = round<hours>(one_hour + 29min);
    assert(still_one_hour.count() == 1);

    const auto two_hours = round<hours>(one_hour + 30min);
    assert(two_hours.count() == 2);

    const auto one_hour_again = floor<hours>(one_hour + 59min);
    assert(one_hour_again.count() == 1);

    // How many times does one duration fit into another?
    const auto second_duration = 765ms + 13us + 987ns;
    const int this_many_times = duration / second_duration;
    std::cout << this_many_times << " times\n";

    // And what is the remaining duration of such a division?
    const nanoseconds remaining_duration = duration % second_duration;
    std::cout << remaining_duration.count() << " ns\n";

    return 0;
}
