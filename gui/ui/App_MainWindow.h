// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-09
#ifndef _INCLUDE_MAINWINDOW_H_
#define _INCLUDE_MAINWINDOW_H_

#include "global.hpp"
#include "ui_window/ui_window.h"
#include "ui_sidebar/ui_sidebar.h"
#include "ui_button/ui_button.h"
#include "ui_effects/AcrylicEffect.h"

#include <QMainWindow>
#include <QResizeEvent>
class App_MainWindow :  public beiklive::Ui_Window {
public:
    App_MainWindow(QWidget *parent = nullptr);
    ~App_MainWindow() = default;

    // Add member functions here

protected:
    // void resizeEvent(QResizeEvent *event) override;


private:
    // Add member variables here
};


#endif // _INCLUDE_MAINWINDOW_H_