#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include "ui_list_button.h"



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    FileSelectorWindow window;
    window.setWindowTitle("文件选择器示例");
    window.resize(400, 500);
    window.show();
    
    return app.exec();
}


// #include <iostream>
// #include <string>
// #include <cctype>


// #include <iostream>
// #include <fstream>
// #include <unordered_map>
// #include <string>
// #include <vector>
// #include <algorithm>

// class PinyinLookup {
// private:
//     std::unordered_map<char32_t, std::string> pinyinMap; // 存储 Unicode 字符到拼音的映射

//     // 解析单行拼音数据（格式如 "U+4E2D: zhōng,zhòng"）
//     void parseLine(const std::string& line) {
//         if (line.empty() || line[0] == '#') return; // 跳过注释行

//         size_t colonPos = line.find(':');
//         if (colonPos == std::string::npos) return;

//         // 提取 Unicode 码点（如 "U+4E2D"）
//         std::string codePointStr = line.substr(0, colonPos);
//         char32_t codePoint = std::stoul(codePointStr.substr(2), nullptr, 16); // 去掉 "U+" 并转为十六进制

//         // 提取拼音（取第一个拼音）
//         std::string pinyinPart = line.substr(colonPos + 1);
//         size_t commaPos = pinyinPart.find(',');
//         std::string firstPinyin = (commaPos != std::string::npos) ? 
//                                   pinyinPart.substr(0, commaPos) : 
//                                   pinyinPart;

//         // 去除拼音前后的空格
//         firstPinyin.erase(0, firstPinyin.find_first_not_of(" \t"));
//         firstPinyin.erase(firstPinyin.find_last_not_of(" \t") + 1);

//         if (!firstPinyin.empty()) {
//             pinyinMap[codePoint] = firstPinyin;
//         }
//     }

// public:
//     // 从文件加载拼音数据（默认使用 pinyin.txt）
//     bool load(const std::string& filename = "pinyin.txt") {
//         std::ifstream file(filename);
//         if (!file.is_open()) {
//             std::cerr << "Error: Failed to open file " << filename << std::endl;
//             return false;
//         }

//         std::string line;
//         while (std::getline(file, line)) {
//             parseLine(line);
//         }
//         file.close();
//         return true;
//     }

//     // 查询汉字的第一个拼音（返回空字符串表示未找到）
//     std::string getFirstPinyin(const std::string& hanzi) {
//         if (hanzi.empty()) return "";

//         // 仅处理第一个字符（支持多字符字符串，但只查第一个字）
//         char32_t codePoint = static_cast<char32_t>(hanzi[0]);
//         auto it = pinyinMap.find(codePoint);
//         return (it != pinyinMap.end()) ? it->second : "";
//     }
// };


// class LanguageProcessor {
// public:
//     static char getFirstLetter(const std::string& str) {
//         if (str.empty()) return '#';
        
//         // 检查第一个字符是否是数字
//         if (isdigit(str[0])) {
//             return str[0];
//         }
//         // 检查第一个字符是否是英文字母
//         else if (isEnglishChar(str[0])) {
//             return toupper(str[0]);
//         }
//         // 检查是否是中文字符
//         else if (isChineseChar(str)) {
//             return getChineseFirstLetter(str);
//         }
//         // 无法识别的字符
//         else {
//             return '#';
//         }
//     }

// private:
//     static bool isEnglishChar(char c) {
//         // ASCII码中，英文字符(包括大小写字母)的范围是65-90和97-122
//         return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
//     }

//     static bool isChineseChar(const std::string& str) {
//         if (str.empty()) return false;
        
//         // 检查是否是中文字符(UTF-8编码)
//         unsigned char c = static_cast<unsigned char>(str[0]);
//         if ((c >= 0xE4 && c <= 0xE9) && str.size() >= 3) {
//             // 检查后续字节是否符合UTF-8中文编码规则
//             unsigned char c1 = static_cast<unsigned char>(str[1]);
//             unsigned char c2 = static_cast<unsigned char>(str[2]);
//             return (c1 & 0xC0) == 0x80 && (c2 & 0xC0) == 0x80;
//         }
//         return false;
//     }

//     static char getChineseFirstLetter(const std::string& str) {
//         if (str.size() < 3) return '#';
        
//         // 获取汉字的前两个字节(GB2312编码)
//         unsigned char high = static_cast<unsigned char>(str[0]);
//         unsigned char low = static_cast<unsigned char>(str[1]);
//         int code = (high << 8) + low;
        
//         // 根据GB2312编码范围确定拼音首字母
//         if (code >= 0xB0A1 && code <= 0xB0C4) return 'A';
//         if (code >= 0xB0C5 && code <= 0xB2C0) return 'B';
//         if (code >= 0xB2C1 && code <= 0xB4ED) return 'C';
//         if (code >= 0xB4EE && code <= 0xB6E9) return 'D';
//         if (code >= 0xB6EA && code <= 0xB7A1) return 'E';
//         if (code >= 0xB7A2 && code <= 0xB8C0) return 'F';
//         if (code >= 0xB8C1 && code <= 0xB9FD) return 'G';
//         if (code >= 0xB9FE && code <= 0xBBF6) return 'H';
//         if (code >= 0xBBF7 && code <= 0xBFA5) return 'J';
//         if (code >= 0xBFA6 && code <= 0xC0AB) return 'K';
//         if (code >= 0xC0AC && code <= 0xC2E7) return 'L';
//         if (code >= 0xC2E8 && code <= 0xC4C2) return 'M';
//         if (code >= 0xC4C3 && code <= 0xC5B5) return 'N';
//         if (code >= 0xC5B6 && code <= 0xC5BD) return 'O';
//         if (code >= 0xC5BE && code <= 0xC6D9) return 'P';
//         if (code >= 0xC6DA && code <= 0xC8BA) return 'Q';
//         if (code >= 0xC8BB && code <= 0xC8F5) return 'R';
//         if (code >= 0xC8F6 && code <= 0xCBF0) return 'S';
//         if (code >= 0xCBFA && code <= 0xCDD9) return 'T';
//         if (code >= 0xCDDA && code <= 0xCEF3) return 'W';
//         if (code >= 0xCEF4 && code <= 0xD188) return 'X';
//         if (code >= 0xD1B9 && code <= 0xD4D0) return 'Y';
//         if (code >= 0xD4D1 && code <= 0xD7F9) return 'Z';
        
//         return '#';
//     }
// };

// int main() {
//     std::cout << LanguageProcessor::getFirstLetter("hello") << std::endl;  // 输出: H
//     std::cout << LanguageProcessor::getFirstLetter("中国") << std::endl;   // 输出: Z
//     std::cout << LanguageProcessor::getFirstLetter("123") << std::endl;    // 输出: #
//     std::cout << LanguageProcessor::getFirstLetter("こんにちは") << std::endl; // 输出: #
    
//     return 0;
// }