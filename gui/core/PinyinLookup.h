#ifndef PINYIN_LOOKUP_H
#define PINYIN_LOOKUP_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <sstream>
#include <iomanip>

class PinyinLookup {
public:
    // 加载拼音数据文件（默认：pinyin_formatted.txt）
    bool load(const std::string& filename = "pinyin_formatted.txt");

    // 通过汉字查询拼音（如 "中" -> "zhōng/zhòng"）
    std::string getPinyinFromHanzi(const std::string& hanzi) ;

    // 通过 Unicode 码点查询拼音（如 "U+4E2D" -> "zhōng/zhòng"）
    std::string getPinyinFromUnicode(const std::string& unicode) ;

    std::vector<char32_t> utf8ToUnicode(const std::string& utf8Str);
    std::string toUnicodeHexString(char32_t codePoint);
private:
    // 存储 Unicode 码点到拼音的映射（如 "U+4E2D" -> "zhōng/zhòng"）
    std::unordered_map<std::string, std::string> unicodeToPinyin;

    // 存储汉字到 Unicode 码点的映射（如 "中" -> "U+4E2D"）
    std::unordered_map<std::string, std::string> hanziToUnicode;
};

#endif // PINYIN_LOOKUP_H