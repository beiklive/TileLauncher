// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-15
#ifndef _INCLUDE_UI_FRAMELESSWINDOW_H_
#define _INCLUDE_UI_FRAMELESSWINDOW_H_

#include <global.hpp>

#include <QWidget>
#include <QPoint>
#include <QRadialGradient>
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
    void SetupUi();
    void SetupStyle(); 
    // Add member variables here
    void updateCursorShape(const QPoint &pos);


    QWidget *m_centralWidget = nullptr;
    bool m_dragging{false};
    QPoint m_startPos;
    bool m_enableResize[4]; // 四个边的拖动状态，索引0-3分别对应左、上、右、下
    bool m_enableCorner[4]; // 四个角的拖动状态，索引0-3分别对应左上、右上、左下、右下
};

} // namespace beiklive

#endif // _INCLUDE_UI_FRAMELESSWINDOW_H_