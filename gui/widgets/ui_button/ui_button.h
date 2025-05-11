// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-11
#ifndef _INCLUDE_UI_BUTTON_H_
#define _INCLUDE_UI_BUTTON_H_

#include "global.hpp"

#include <QWidget>
#include <QLabel>

#include <QIcon>
#include <QPixmap>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QEvent>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QEnterEvent>
// #include <QLeaveEvent>
using EnterEventType = QEnterEvent;
// using LeaveEventType = QLeaveEvent;
#else
using EnterEventType = QEvent;
// using LeaveEventType = QEvent;
#endif


namespace beiklive {

class Ui_Button : public beiklive::BaseWidget {
    Q_OBJECT
public:
    Ui_Button();
    Ui_Button(const QString &text, const QIcon &icon);
    ~Ui_Button() = default;
    // Add member functions here

    void hideText(bool hide);
    
protected:
    void mousePressEvent(QMouseEvent *) override { emit clicked(); }
    void enterEvent(EnterEventType   *) override;
    void leaveEvent(QEvent  *) override;
signals:
    void clicked();   
    
private:
    void setIcon(const QIcon &icon);
    void setText(const QString &text);
    // Add member variables here
    QLabel *iconLabel;
    QLabel *textLabel;
    QHBoxLayout *layout;
};

} // namespace beiklive

#endif // _INCLUDE_UI_BUTTON_H_