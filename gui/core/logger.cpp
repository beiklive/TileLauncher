#include "logger.h"

void beiklive::set_log_level(const std::string &level_str)
{
    std::string level_lower = level_str;
    std::transform(level_lower.begin(), level_lower.end(), level_lower.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });

    static const std::unordered_map<std::string, spdlog::level::level_enum> level_map = {
        {"trace", spdlog::level::trace},
        {"debug", spdlog::level::debug},
        {"info", spdlog::level::info},
        {"warn", spdlog::level::warn},
        {"error", spdlog::level::err},
        {"critical", spdlog::level::critical},
        {"off", spdlog::level::off}};

    auto it = level_map.find(level_lower);
    if (it == level_map.end())
    {
        throw std::invalid_argument("Invalid log level: " + level_str);
    }

    spdlog::set_level(it->second);
}
