// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-15
#ifndef _INCLUDE_UI_FRAMELESSWINDOW_H_
#define _INCLUDE_UI_FRAMELESSWINDOW_H_

#include "global.hpp"
#include "ui_GripItem.h"

#include <QWidget>
#include <QPushButton>
#include <QPoint>
#include <QRadialGradient>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>

namespace beiklive
{


    class Ui_FrameLessWindow : public QWidget
    {
        Q_OBJECT
    public:
        Ui_FrameLessWindow(QWidget *parent = nullptr);
        ~Ui_FrameLessWindow() = default;

        QWidget *centralWidget() const;
        // Add member functions here
    protected:
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

        void resizeEvent(QResizeEvent *event) override;

    private:
        void SetupUi();

        void initGrip();
        void updateGrip();
        // Add member variables here

        bool custom_window;
        QWidget *titleBar = nullptr;
        QWidget *m_centralWidget = nullptr;

        Ui_GripItem *m_top_grop = nullptr;
        Ui_GripItem *m_bottom_grop = nullptr;
        Ui_GripItem *m_left_grop = nullptr;
        Ui_GripItem *m_right_grop = nullptr;
        Ui_GripItem *m_topleft_grop = nullptr;
        Ui_GripItem *m_topright_grop = nullptr;
        Ui_GripItem *m_bottomleft_grop = nullptr;
        Ui_GripItem *m_bottomright_grop = nullptr;
    };

} // namespace beiklive

#endif // _INCLUDE_UI_FRAMELESSWINDOW_H_