// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-16
#ifndef _INCLUDE_APP_MAINWINDOW_H_
#define _INCLUDE_APP_MAINWINDOW_H_

#include "global.hpp"
#include "widgets/ui_FrameLessWindow/ui_FrameLessWindow.h"
#include "widgets/ui_sidebar/ui_sidebar.h"
#include "widgets/ui_title_bar/ui_title_bar.h"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QGuiApplication>
#include <QScreen>

#include <QPropertyAnimation>
#include <QPaintEvent>
namespace beiklive
{

    class App_MainWindow : public Ui_FrameLessWindow
    {
        Q_OBJECT


    public:
        App_MainWindow(QWidget *parent = nullptr);
        ~App_MainWindow() = default;

        void menuMode(bool enable);
        void animaShow();
        // Add member functions here


    protected:
        void resizeEvent(QResizeEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
    public slots:
        void window_maximize();
        void window_restore();
        void _onAnimationFinished();

    private:
        void _setupUI();
        void _initSidebar();
        void moveWindowToBottomLeft(QWidget *window);
        void createTrayIcon();

        void drawBackground(beiklive::Ui_Sidebar_Button *btn, const QPoint &center);

        // Add member variables here
        Qt::WindowFlags m_windowFlags;
        QSystemTrayIcon *trayIcon;
        QPropertyAnimation *animation;
        QHBoxLayout *layout;

        int m_app_margin{10};
        int m_margin;
        Ui_FrameLessWindow *ui;
        QWidget *m_centralWidget{nullptr};
        Ui_Sidebar *m_sidebar{nullptr};
        Ui_Title_Bar *titleBar{nullptr};
        QWidget *m_bodywidget{nullptr};
        QGraphicsDropShadowEffect *shadow;


    };

} // namespace beiklive

#endif // _INCLUDE_APP_MAINWINDOW_H_