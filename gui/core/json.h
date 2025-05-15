#pragma once
#include <QColor>
#include <QString>
#include <QRegularExpression>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


/**
 * 将字符串解析为 QColor，支持以下格式：
 * 1. 十六进制: "#RGB", "#RRGGBB", "#AARRGGBB"
 * 2. RGB/RGBA: "rgb(r,g,b)", "rgba(r,g,b,a)"
 * 3. 颜色名称: "red", "green", "transparent" 等
 * 4. Qt 特殊值: "transparent", "black" 等
 */
QColor parseColor(const std::string& colorStr);