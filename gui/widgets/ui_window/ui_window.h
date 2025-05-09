// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-07
#ifndef _INCLUDE_UI_WINDOW_H_
#define _INCLUDE_UI_WINDOW_H_

#include "global.hpp"
#include "FramelessWindowHelper.h"
#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include<QWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
namespace beiklive {
class Ui_Window : public QMainWindow {
public:
    Ui_Window();

    void functionsSetup();
    void setFrameless();
    // Add member functions here

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    // Add member variables here
    FramelessWindowHelper *m_helper;
};

} // namespace beiklive

#endif // _INCLUDE_UI_WINDOW_H_