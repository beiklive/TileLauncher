#include "tool.h"


/**
 * @brief 在布局中将新元素插入到当前元素的后一位
 * @param layout 布局指针（如 QVBoxLayout、QHBoxLayout、QGridLayout）
 * @param currentElement 当前元素（QWidget 或 QLayout）
 * @param newElement 要插入的新元素（QWidget 或 QLayout）
 * @return 是否插入成功
 */
bool insertAfterElement(QLayout* layout, QObject* currentElement, QObject* newElement) {
    // 1. 参数有效性检查
    if (!layout || !currentElement || !newElement) {
        qWarning() << "Invalid parameters: null pointer detected";
        return false;
    }

    // 2. 获取当前元素的索引位置
    int index = -1;
    if (auto widget = qobject_cast<QWidget*>(currentElement)) {
        index = layout->indexOf(widget);
    } else if (auto subLayout = qobject_cast<QLayout*>(currentElement)) {
        index = layout->indexOf(subLayout);
    }

    if (index == -1) {
        qWarning() << "Current element not found in layout";
        return false;
    }

    // 3. 根据布局类型处理插入
    if (auto boxLayout = qobject_cast<QBoxLayout*>(layout)) {
        // 处理垂直/水平布局
        if (auto newWidget = qobject_cast<QWidget*>(newElement)) {
            boxLayout->insertWidget(index + 1, newWidget);
        } else if (auto newSubLayout = qobject_cast<QLayout*>(newElement)) {
            boxLayout->insertLayout(index + 1, newSubLayout);
        } else {
            qWarning() << "Unsupported new element type for box layout";
            return false;
        }
    }
    else if (auto gridLayout = qobject_cast<QGridLayout*>(layout)) {
        // 处理网格布局
        int row, col, rowSpan, colSpan;
        gridLayout->getItemPosition(index, &row, &col, &rowSpan, &colSpan);

        if (auto newWidget = qobject_cast<QWidget*>(newElement)) {
            gridLayout->addWidget(newWidget, row, col + colSpan, rowSpan, colSpan);
        } else if (auto newSubLayout = qobject_cast<QLayout*>(newElement)) {
            gridLayout->addLayout(newSubLayout, row, col + colSpan, rowSpan, colSpan);
        } else {
            qWarning() << "Unsupported new element type for grid layout";
            return false;
        }
    }
    else {
        qWarning() << "Unsupported layout type:" << layout->metaObject()->className();
        return false;
    }

    return true;
}
// 获取UTF-8字符串的第一个完整字符（可能为多字节）
std::string getFirstUTF8Char(const std::string& str) {
    if (str.empty()) return "";

    unsigned char firstByte = static_cast<unsigned char>(str[0]);
    int charLen = 0;

    // 根据首字节确定字符长度
    if ((firstByte & 0x80) == 0) {       // 单字节（ASCII）
        charLen = 1;
    } else if ((firstByte & 0xE0) == 0xC0) {  // 2字节
        charLen = 2;
    } else if ((firstByte & 0xF0) == 0xE0) {  // 3字节（常见汉字）
        charLen = 3;
    } else if ((firstByte & 0xF8) == 0xF0) {  // 4字节
        charLen = 4;
    } else {
        return "";  // 非法UTF-8
    }

    // 检查字符串长度是否足够
    if (str.size() < charLen) return "";

    return str.substr(0, charLen);
}

std::string getFirstLetter(PinyinLookup *pinyin, const std::string &str) {
    if (str.empty()) {
        return "";
    }

    unsigned char firstChar = static_cast<unsigned char>(str[0]);

    // 1. 数字：直接返回
    if (isdigit(firstChar)) {
        return std::string(1, firstChar);
    }

    // 2. 西文字母：返回大写形式
    if (isalpha(firstChar)) {
        return std::string(1, static_cast<char>(toupper(firstChar)));
    }

    // 3. 中文：调用拼音接口获取首字母
    if (firstChar >= 0x80) {  // 简单判断是否为非ASCII字符（中文字符通常占2~4字节）
        std::string pinyin1 = pinyin->getPinyinFromHanzi(getFirstUTF8Char(str));
        if (!pinyin1.empty()) {
            return std::string(1, toupper(pinyin1[0]));  // 返回拼音首字母（大写）
        }
    }

    // 4. 其他情况（符号或无法识别的字符）：返回 #
    return "#";
}

QString generateUuid() {
    return QUuid::createUuid().toString(QUuid::WithoutBraces); // 格式: "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
}