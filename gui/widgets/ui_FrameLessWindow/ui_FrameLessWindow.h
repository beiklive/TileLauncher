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
    QPoint m_mousePos;
    bool m_mousePressed;
    QPoint m_dragPosition;
    bool m_resizing;
    QPoint m_resizeStartPos;
    QRect m_resizeStartGeometry;
};

} // namespace beiklive

#endif // _INCLUDE_UI_FRAMELESSWINDOW_H_