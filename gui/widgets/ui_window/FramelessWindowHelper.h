// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-07
#ifndef _INCLUDE_WINDOW_FRAMELESS_H_
#define _INCLUDE_WINDOW_FRAMELESS_H_

/*
无边框窗口辅助类
功能：
1. 给窗口添加标题栏以及控制按钮
2. 实现窗口边缘的可拖动
*/

#if BEIKLIVE_FRAMELESS
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

class EdgeWidget;
class EdgeGrips;
class FramelessWindowHelper;

// 边缘位置枚举
enum EdgePosition
{
    None = 0,
    Top = 1,
    Bottom = 2,
    Left = 4,
    Right = 8,
    TopLeft = Top | Left,
    TopRight = Top | Right,
    BottomLeft = Bottom | Left,
    BottomRight = Bottom | Right
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

class EdgeGrips : public QWidget
{
public:
    EdgeGrips(QWidget *parent = nullptr, EdgePosition edgePosition = None, bool showColor = false);
    ~EdgeGrips() = default;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
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

private:
    void _addEdgeWidgets();

private:
    QWidget *m_targetWidget; // 目标窗口
    bool m_resizable;        // 是否可调整大小
    bool m_movable;          // 是否可移动
    int m_borderWidth;       // 边框宽度
    int m_titleBarHeight;    // 标题栏高度

    bool m_isPressed;      // 鼠标是否按下
    QPoint m_startPos;     // 鼠标按下时的位置
    QRect m_startGeometry; // 窗口开始时的几何形状

    int m_edgePosition; // 当前边缘位置



    EdgeGrips *top_left_grip;
    EdgeGrips *top_right_grip;
    EdgeGrips *bottom_left_grip;
    EdgeGrips *bottom_right_grip;
    EdgeGrips *top_grip;
    EdgeGrips *bottom_grip;
    EdgeGrips *left_grip;
    EdgeGrips *right_grip;
};
#endif
#endif // _INCLUDE_WINDOW_FRAMELESS_H_