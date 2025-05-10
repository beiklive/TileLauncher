// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-07
#ifndef _INCLUDE_UI_WINDOW_H_
#define _INCLUDE_UI_WINDOW_H_

#include "global.hpp"
#include "FramelessWindowHelper.h"
#include <QDebug>
#include <QPainter>

#include <QGraphicsEffect>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>

#include <QApplication>
#include <QMainWindow>
#include <QWidget>

#include <QResizeEvent>
#include <QMouseEvent>
#include <QPaintEvent>

#include <QSpacerItem>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QStyle>
#include <QIcon>

namespace beiklive {



class TitleBar : public QWidget
{
public:
    TitleBar(QWidget* parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent* event) override;

    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QWidget* m_parentWidget;
    QPoint m_dragPosition;
};









class Ui_Window : public QWidget {
public:
    Ui_Window();

    void addTitleBarToWidget(QWidget* widget, const QString& title = "");
    // Add member functions here
    QWidget *getWindow() const;
    void hideTitleBar();

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    void functionsSetup();
    void styleSetup();
private:
    // Add member variables here
    FramelessWindowHelper *m_helper;
    QWidget *m_window;
    TitleBar *titleBar;
    QVBoxLayout *windowlayout;
};

} // namespace beiklive

#endif // _INCLUDE_UI_WINDOW_H_