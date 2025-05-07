// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-07
#ifndef _INCLUDE_WINDOW_FRAMELESS_H_
#define _INCLUDE_WINDOW_FRAMELESS_H_

#if BEIKLIVE_FRAMELESS

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QRect>

class FramelessWindowHelper : public QObject
{
    Q_OBJECT
public:
    explicit FramelessWindowHelper(QWidget *parent = nullptr);

    // 设置是否可调整窗口大小
    void setResizable(bool resizable);
    // 设置是否可移动窗口
    void setMovable(bool movable);
    // 设置边框宽度（用于调整窗口大小）
    void setBorderWidth(int width);
    // 设置标题栏高度（用于窗口移动）
    void setTitleBarHeight(int height);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QWidget *m_targetWidget; // 目标窗口
    bool m_resizable;        // 是否可调整大小
    bool m_movable;          // 是否可移动
    int m_borderWidth;       // 边框宽度
    int m_titleBarHeight;    // 标题栏高度

    bool m_isPressed;      // 鼠标是否按下
    QPoint m_startPos;     // 鼠标按下时的位置
    QRect m_startGeometry; // 窗口开始时的几何形状

    // 计算鼠标在窗口边缘的位置
    int calculateMousePosition(const QPoint &pos);

    // 处理鼠标按下事件
    void handleMousePress(QMouseEvent *event);
    // 处理鼠标移动事件
    void handleMouseMove(QMouseEvent *event);
    // 处理鼠标释放事件
    void handleMouseRelease(QMouseEvent *event);

    // 更新鼠标光标形状
    void updateCursorShape(const QPoint &pos);

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

    int m_edgePosition; // 当前边缘位置
};
#endif
#endif // _INCLUDE_WINDOW_FRAMELESS_H_