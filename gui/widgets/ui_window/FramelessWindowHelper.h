// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-07
#ifndef _INCLUDE_WINDOW_FRAMELESS_H_
#define _INCLUDE_WINDOW_FRAMELESS_H_


#include "global.hpp"

#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QCursor>
#include <QRect>
#include <QSize>
#include <QPoint>
#include <QSizeGrip>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QVBoxLayout>

class CustomGrip;  // 边缘拖动控件
class EdgeWidget;  // 边缘拖动控件生成器
class EdgeGrips;   
class FramelessWindowHelper; // 无边框窗口辅助类

// 边缘位置枚举
enum EdgePosition
{
    None,
    Top,
    Bottom,
    Left,
    Right,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

class CustomGrip : public QFrame {
    Q_OBJECT
public:
    explicit CustomGrip(QWidget* parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
};


// 边缘控件，用来标记窗口边缘可拖动
class EdgeWidget
{
public:
    EdgeWidget();
    ~EdgeWidget();

    void top_left(QWidget *form);
    void top_right(QWidget *form);
    void bottom_left(QWidget *form);
    void bottom_right(QWidget *form);
    void top(QWidget *form);
    void bottom(QWidget *form);
    void left(QWidget *form);
    void right(QWidget *form);

public:
    CustomGrip *top_left_grip;
    CustomGrip *top_right_grip;
    CustomGrip *bottom_left_grip;
    CustomGrip *bottom_right_grip;
    CustomGrip *top_grip;
    CustomGrip *bottom_grip;
    CustomGrip *left_grip;
    CustomGrip *right_grip;
};

class EdgeGrips
{
public:
    EdgeGrips(QWidget *parent = nullptr, EdgePosition edgePosition = None, bool showColor = false);
    void setGeo(int x, int y, int w, int h);
    ~EdgeGrips() = default;

private:
    QWidget* m_window;
    QWidget *m_targetWidget;
    EdgeWidget *m_edgeWidget;
    bool m_showColor;
    QSizeGrip *grip;
};

class FramelessWindowHelper : public QObject
{
    Q_OBJECT
public:
    explicit FramelessWindowHelper(QWidget *parent = nullptr);
    void setResizable(bool resizable);

    void resizeGrips();

private:
    void _addEdgeWidgets();
private:
    QWidget *m_targetWidget; // 目标窗口
    bool m_resizable;        // 是否可调整大小
    int m_titleBarHeight;    // 标题栏高度




    EdgeGrips *top_left_grip;
    EdgeGrips *top_right_grip;
    EdgeGrips *bottom_left_grip;
    EdgeGrips *bottom_right_grip;
    EdgeGrips *top_grip;
    EdgeGrips *bottom_grip;
    EdgeGrips *left_grip;
    EdgeGrips *right_grip;
};
#endif // _INCLUDE_WINDOW_FRAMELESS_H_