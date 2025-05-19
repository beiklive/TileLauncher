
// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-17
#ifndef _INCLUDE_UI_TITLE_BUTTON_H_
#define _INCLUDE_UI_TITLE_BUTTON_H_

#include "global.hpp"
#include <QPushButton>
#include <QEnterEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QEvent>

namespace beiklive {

class Ui_Title_Button : public QPushButton {
    Q_OBJECT
public:
    Ui_Title_Button(QWidget *parent = nullptr, std::string icon_path=ICON_DEFAULT);
    ~Ui_Title_Button() = default;
    // Add member functions here

    void setIconPath(std::string icon_path);

protected:
    void paintEvent(QPaintEvent *event) override;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void enterEvent(QEnterEvent *event) override;
#else
    void enterEvent(QEvent *event) override;
#endif
    void leaveEvent(QEvent *event) override;
    // void mousePressEvent(QMouseEvent* event) override;
    // void mouseReleaseEvent(QMouseEvent* event) override;

private:
    // Add member variables here
    void iconPaint(QPainter *qp, const QString &imagePath, const QRect &rect, const QColor &color);
    bool m_is_hover = false;
    int m_button_size = 0;
    int m_icon_size = 0;
    std::string m_icon_path;
    QColor m_set_icon_color;
};

} // namespace beiklive

#endif // _INCLUDE_UI_TITLE_BUTTON_H_