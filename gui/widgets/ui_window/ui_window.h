// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-07
#ifndef _INCLUDE_UI_WINDOW_H_
#define _INCLUDE_UI_WINDOW_H_

#include <QApplication>
#include <QMainWindow>
#include<QWidget>
#include <QVBoxLayout>
#include <QPushButton>
namespace beiklive {
class Ui_Window : public QMainWindow {
public:
    Ui_Window();
#if BEIKLIVE_FRAMELESS
    void setFrameless();
#endif
    // Add member functions here

private:
    // Add member variables here
};

} // namespace beiklive

#endif // _INCLUDE_UI_WINDOW_H_