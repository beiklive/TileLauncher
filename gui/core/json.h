#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using json = nlohmann::json;

extern nlohmann::json globalSettings;

json get_directory_structure(const std::string& root_path);