// SPDX-License-Identifier: GPL-3.0

#include <iostream>
#include <algorithm>

/** The algorithms library defines functions for a variety of purposes
 *  (e.g. searching, sorting, counting, manipulating)
 *  that operate on ranges of elements.
 *
 * This provides just a few out of many std::algorithms
*/

#include <iostream>
#include <vector>

enum class SettingsType {
    boolean = 0,
    number,
    enumeration
};

class Setting {
public:
    Setting(SettingsType _type, int _min_value, int _max_value, int _value)
    : type(_type), min_value(_min_value), max_value(_max_value), value(_value)
    {
    }

    SettingsType getType() const {
        return type;
    }

    void setValue(int _value) {
        value = std::clamp(_value, min_value, max_value);
    }
    int getValue() const {
        return value;
    }

    bool is_valid() const {
        return value <= std::max(min_value, max_value) && value >= std::min(max_value, min_value);
    }

private:
    SettingsType type;
    int min_value = -(1 << 7);
    int max_value = (1 << 7) -1;
    int value;
};

std::vector<Setting> getSettings() {
    std::vector<Setting> settings;
    settings.push_back(Setting(SettingsType::boolean, 0, 1, 1));
    settings.push_back(Setting(SettingsType::number, 0, 10, 5));
    settings.push_back(Setting(SettingsType::number, 50, 100, 80));
    settings.push_back(Setting(SettingsType::enumeration, 0, 5, 3));
    settings.push_back(Setting(SettingsType::enumeration, 0, 2, 0));
    return settings;
}

int main(int, char **) {
    // all_of, any_of, none_of
    const auto settings = getSettings();

    std::cout << std::boolalpha
    << "All settings valid: " << std::all_of(settings.begin(), settings.end(),
     [](const Setting& setting) { return setting.is_valid(); }) << std::endl;

    // count, count_if
    std::cout
    << "Number of enumeration settings: " << std::count_if(settings.begin(), settings.end(),
    [](const Setting& setting) { return setting.getType() == SettingsType::enumeration; }) << std::endl;

    // find, find_if
    std::cout
    << "Boolean setting: " << std::find_if(settings.begin(), settings.end(),
    [](const Setting& setting) { return setting.getType() == SettingsType::boolean; })->getValue() << std::endl;

    // transform
    std::vector<Setting> invalidatedSettings;
    std::transform(settings.begin(), settings.end(), std::back_inserter(invalidatedSettings),
     [](const Setting& setting) { return Setting(setting.getType(), 0, 10, -1); });
     std::cout
     << "Invalidated Settings: any_of valid? " << std::any_of(invalidatedSettings.begin(), invalidatedSettings.end(),
     [] (const Setting& setting) { return setting.is_valid(); }) << std::endl;

    // replace
    std::replace_if(invalidatedSettings.begin(), invalidatedSettings.end(),
     [](const Setting& setting) { return setting.getType() == SettingsType::boolean; },
      Setting(SettingsType::enumeration, 0, 5, 1) );

    return 0;
}