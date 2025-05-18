// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-16
#ifndef _INCLUDE_UI_SIDEBAR_BUTTON_H_
#define _INCLUDE_UI_SIDEBAR_BUTTON_H_

#include "global.hpp"
#include <QPushButton>
#include <QPixmap>
#include <QEnterEvent>
#include <QEvent>
namespace beiklive {

class Ui_Sidebar_Button : public QPushButton {
    Q_OBJECT
public:
    Ui_Sidebar_Button(QWidget *parent = nullptr, std::string icon_path = ICON_DEFAULT, std::string text = "");
    ~Ui_Sidebar_Button() = default;

    // Add member functions here
    void hide_text(bool hide);
    void set_icon(std::string icon_path);
    void set_text(std::string text);

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void clickedAtPosition(const QPoint &pos);  // 发射点击位置

private:
    void _setup_ui();
    void _init_icon(std::string icon_path);
    void _init_text(std::string text);
    void iconPaint(QPainter* qp, const QString& imagePath, const QRect& rect, const QColor& color);
    // Add member variables here
    std::string m_icon_path{ICON_DEFAULT};
    std::string m_text{};

    bool m_is_hover{false};
    bool m_hide_text{true};
    int m_expand_width;
    int m_normal_width;
    int m_icon_width{0};
    QColor m_set_icon_color{QColor(255, 255, 255)};
    QColor m_set_text_color{QColor(255, 255, 255)};

};

} // namespace beiklive

#endif // _INCLUDE_UI_SIDEBAR_BUTTON_H_