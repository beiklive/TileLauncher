// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-16
#ifndef _INCLUDE_APP_MAINWINDOW_H_
#define _INCLUDE_APP_MAINWINDOW_H_

#include "global.hpp"
#include "widgets/ui_FrameLessWindow/ui_FrameLessWindow.h"
#include "widgets/ui_sidebar/ui_sidebar.h"
#include "widgets/ui_title_bar/ui_title_bar.h"


namespace beiklive {

class App_MainWindow : public Ui_FrameLessWindow {
    // O_OBJECT
public:
    App_MainWindow(QWidget *parent = nullptr);
    ~App_MainWindow() = default;

    // Add member functions here
protected:
    void resizeEvent(QResizeEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;
    // void mouseMoveEvent(QMouseEvent *event) override;
    // void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void window_maximize();
    void window_restore();


private:
    void _setupUI();
    int m_margin;
    // Add member variables here
    Ui_FrameLessWindow *ui;
    QWidget *m_centralWidget{nullptr};
    Ui_Sidebar* m_sidebar{nullptr};
    Ui_Title_Bar* titleBar{nullptr};
    QWidget *m_bodywidget{nullptr};
    QGraphicsDropShadowEffect *shadow;
};

} // namespace beiklive

#endif // _INCLUDE_APP_MAINWINDOW_H_