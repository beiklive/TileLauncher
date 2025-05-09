// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-09
#ifndef _INCLUDE_MAINWINDOW_H_
#define _INCLUDE_MAINWINDOW_H_

#include "ui_window/ui_window.h"
#include <QMainWindow>

class App_MainWindow :  public beiklive::Ui_Window {
public:
    App_MainWindow(QWidget *parent = nullptr);
    ~App_MainWindow() = default;

    // Add member functions here

private:
    // Add member variables here
};


#endif // _INCLUDE_MAINWINDOW_H_