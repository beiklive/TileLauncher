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
class Ui_Window : public QWidget {
public:
    Ui_Window();

    void functionsSetup();
    void styleSetup();

    // Add member functions here
    void addCloseButton();
protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    // Add member variables here
    FramelessWindowHelper *m_helper;
    QWidget *m_window;
};

} // namespace beiklive

#endif // _INCLUDE_UI_WINDOW_H_