#include "json.h"


QColor parseColor(const std::string& colorStr) {
    if (colorStr.empty()) return QColor(); // 无效颜色

    QString qColorStr = QString::fromStdString(colorStr).trimmed();

    // 1. 检查是否是预定义颜色名称（如 "red", "transparent"）
    QColor namedColor(qColorStr);
    if (namedColor.isValid()) return namedColor;

    // 2. 检查十六进制格式 (#RGB, #RRGGBB, #AARRGGBB)
    static QRegularExpression hexRegex("^#([A-Fa-f0-9]{3}|[A-Fa-f0-9]{6}|[A-Fa-f0-9]{8})$");
    if (hexRegex.match(qColorStr).hasMatch()) {
        return QColor(qColorStr);
    }

    // 3. 检查 rgb/rgba 格式
    static QRegularExpression rgbaRegex(R"(^rgba?$\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*(?:,\s*([\d.]+)\s*)?$$)");
    auto match = rgbaRegex.match(qColorStr);
    if (match.hasMatch()) {
        int r = match.captured(1).toInt();
        int g = match.captured(2).toInt();
        int b = match.captured(3).toInt();
        
        // 处理 alpha 通道（如果存在）
        if (match.capturedLength(4) > 0) {
            qreal a = match.captured(4).toDouble();
            return QColor(r, g, b, static_cast<int>(a * 255)); // 转换 [0,1] -> [0,255]
        } else {
            return QColor(r, g, b);
        }
    }

    // 4. 其他格式尝试（如不带 # 的十六进制或 Qt 特殊值）
    return QColor(qColorStr); // 最终尝试，可能返回无效颜色
}