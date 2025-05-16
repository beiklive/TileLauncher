// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-16
#ifndef _INCLUDE_APP_MAINWINDOW_H_
#define _INCLUDE_APP_MAINWINDOW_H_

#include "global.hpp"
#include "widgets/ui_FrameLessWindow/ui_FrameLessWindow.h"
#include "widgets/ui_sidebar/ui_sidebar.h"


namespace beiklive {

class App_MainWindow : public Ui_FrameLessWindow {
    // O_OBJECT
public:
    App_MainWindow(QWidget *parent = nullptr);
    ~App_MainWindow() = default;

    // Add member functions here
protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void _setupUI();
    int m_sidebarWidth;
    // Add member variables here
    Ui_FrameLessWindow *ui;
    QWidget *m_centralWidget{nullptr};
    Ui_Sidebar* m_sidebar{nullptr};
};

} // namespace beiklive

#endif // _INCLUDE_APP_MAINWINDOW_H_