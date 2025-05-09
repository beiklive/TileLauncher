// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-09
#ifndef _INCLUDE_LOGGER_H_
#define _INCLUDE_LOGGER_H_
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>    // 文件输出
#include <spdlog/sinks/stdout_color_sinks.h> // 彩色控制台输出
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace beiklive {

    void set_log_level(const std::string &level_str);
    

} // namespace beiklive

#endif // _INCLUDE_LOGGER_H_