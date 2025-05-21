#include "PinyinLookup.h"
#include <fstream>
#include <sstream>
#include <algorithm>
bool PinyinLookup::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        // 去除行尾换行符和空格
        line.erase(std::remove_if(line.begin(), line.end(), 
                  [](char c) { return c == '\r' || c == '\n'; }), line.end());

        // 按冒号分割行
        std::vector<std::string> parts;
        std::istringstream iss(line);
        std::string part;
        while (std::getline(iss, part, ':')) {
            part.erase(0, part.find_first_not_of(" \t")); // 去除前导空格
            part.erase(part.find_last_not_of(" \t") + 1); // 去除尾部空格
            parts.push_back(part);
        }

        // 确保分割出至少两个字段（Unicode 和拼音）
        if (parts.size() >= 2) {
            unicodeToPinyin[parts[0]] = parts[1];
            if (parts.size() >= 3) {
                hanziToUnicode[parts[2]] = parts[0]; // 可选：存储汉字到 Unicode 的映射
            }
        }
    }
    return true;
}

// 将 UTF-8 字符串转换为 Unicode 码点列表（32 位）
std::vector<char32_t> PinyinLookup::utf8ToUnicode(const std::string& utf8Str) {
    std::vector<char32_t> unicodePoints;
    size_t i = 0;
    while (i < utf8Str.size()) {
        char32_t codePoint = 0;
        unsigned char c = utf8Str[i];

        // 解析 UTF-8 编码
        if ((c & 0x80) == 0) {          // 1 字节（ASCII）
            codePoint = c;
            i += 1;
        } else if ((c & 0xE0) == 0xC0) { // 2 字节
            codePoint = ((c & 0x1F) << 6) | (utf8Str[i+1] & 0x3F);
            i += 2;
        } else if ((c & 0xF0) == 0xE0) { // 3 字节（汉字在此）
            codePoint = ((c & 0x0F) << 12) | ((utf8Str[i+1] & 0x3F) << 6) | (utf8Str[i+2] & 0x3F);
            i += 3;
        } else if ((c & 0xF8) == 0xF0) { // 4 字节
            codePoint = ((c & 0x07) << 18) | ((utf8Str[i+1] & 0x3F) << 12) | ((utf8Str[i+2] & 0x3F) << 6) | (utf8Str[i+3] & 0x3F);
            i += 4;
        } else {
            // 非法 UTF-8 序列
            throw std::runtime_error("Invalid UTF-8 sequence");
        }
        unicodePoints.push_back(codePoint);
    }
    return unicodePoints;
}

std::string PinyinLookup::toUnicodeHexString(char32_t codePoint) {
    std::ostringstream oss;
    oss << "U+" << std::uppercase << std::hex << std::setw(4) << std::setfill('0') 
        << static_cast<uint32_t>(codePoint); // 关键：转换为 uint32_t
    return oss.str();
}




std::string PinyinLookup::getPinyinFromHanzi(const std::string& hanzi)  {
    return getPinyinFromUnicode(toUnicodeHexString(utf8ToUnicode(hanzi)[0]));
}

std::string PinyinLookup::getPinyinFromUnicode(const std::string& unicode)  {
    auto it = unicodeToPinyin.find(unicode);
    return (it != unicodeToPinyin.end()) ? it->second : "";
}