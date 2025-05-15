// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-15
#ifndef _INCLUDE_UI_FRAMELESSWINDOW_H_
#define _INCLUDE_UI_FRAMELESSWINDOW_H_

#include <global.hpp>

#include <QWidget>
#include <QPoint>

#include <QMouseEvent>

namespace beiklive {

class Ui_FrameLessWindow : public QWidget {
public:
    Ui_FrameLessWindow(QWidget *parent = nullptr);
    ~Ui_FrameLessWindow() = default;

    // Add member functions here
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private:
    // Add member variables here
    void updateCursorShape(const QPoint &pos);


    bool isMousePressed = false;
};

} // namespace beiklive

#endif // _INCLUDE_UI_FRAMELESSWINDOW_H_