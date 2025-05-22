#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <filesystem>
#include "tool.h"
#include "PinyinLookup.h"
namespace fs = std::filesystem;
using json = nlohmann::json;

extern nlohmann::json globalSettings;

json get_directory_structure(const std::string& root_path);
json get_sorted_directory_structure(const std::string& root_path);
std::string removeFileExtension(const std::string &fileName);