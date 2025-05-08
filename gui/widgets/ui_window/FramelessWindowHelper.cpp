
#include "FramelessWindowHelper.h"

#if BEIKLIVE_FRAMELESS
#include <QMouseEvent>
#include <QApplication>
#include <QCursor>
#include <QDebug>

FramelessWindowHelper::FramelessWindowHelper(QWidget *parent) : QObject(parent),
                                                                m_targetWidget(parent),
                                                                m_resizable(true),
                                                                m_movable(true),
                                                                m_borderWidth(5),
                                                                m_titleBarHeight(30),
                                                                m_isPressed(false),
                                                                m_edgePosition(None)
{
    if (m_targetWidget)
    {
        m_targetWidget->setWindowFlags(m_targetWidget->windowFlags() | Qt::FramelessWindowHint);
        m_targetWidget->installEventFilter(this);
    }
}

void FramelessWindowHelper::setResizable(bool resizable)
{
    m_resizable = resizable;
}

void FramelessWindowHelper::setMovable(bool movable)
{
    m_movable = movable;
}

void FramelessWindowHelper::setBorderWidth(int width)
{
    m_borderWidth = width;
}

void FramelessWindowHelper::setTitleBarHeight(int height)
{
    m_titleBarHeight = height;
}

bool FramelessWindowHelper::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_targetWidget)
    {
        switch (event->type())
        {
        case QEvent::MouseButtonPress:
            handleMousePress(static_cast<QMouseEvent *>(event));
            break;
        case QEvent::MouseButtonRelease:
            handleMouseRelease(static_cast<QMouseEvent *>(event));
            break;
        case QEvent::MouseMove:
            handleMouseMove(static_cast<QMouseEvent *>(event));
            break;
        case QEvent::Leave:
            if (!m_isPressed)
            {
                m_targetWidget->unsetCursor();
            }
            break;
        default:
            break;
        }
    }

    return QObject::eventFilter(watched, event);
}

int FramelessWindowHelper::calculateMousePosition(const QPoint &pos)
{
    int edgePosition = None;
    QRect rect = m_targetWidget->rect();

    if (pos.x() <= m_borderWidth)
    {
        edgePosition |= Left;
    }
    if (pos.x() >= rect.width() - m_borderWidth)
    {
        edgePosition |= Right;
    }
    if (pos.y() <= m_borderWidth)
    {
        edgePosition |= Top;
    }
    if (pos.y() >= rect.height() - m_borderWidth)
    {
        edgePosition |= Bottom;
    }

    return edgePosition;
}

void FramelessWindowHelper::handleMousePress(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        m_startPos = event->globalPos();
        m_startGeometry = m_targetWidget->geometry();

        // 计算鼠标在窗口边缘的位置
        m_edgePosition = calculateMousePosition(event->pos());

        // 如果在标题栏区域且可移动，则设置边缘为None
        if (m_movable && event->pos().y() < m_titleBarHeight && m_edgePosition == None)
        {
            m_edgePosition = None;
        }
    }
}

void FramelessWindowHelper::handleMouseMove(QMouseEvent *event)
{
    if (!m_isPressed)
    {
        // 更新鼠标光标形状
        updateCursorShape(event->pos());
        return;
    }

    if (!m_resizable && !m_movable)
    {
        return;
    }

    QPoint delta = event->globalPos() - m_startPos;

    if (m_edgePosition == None && m_movable)
    {
        // 移动窗口
        m_targetWidget->move(m_startGeometry.topLeft() + delta);
    }
    else if (m_resizable)
    {
        // 调整窗口大小
        QRect newGeometry = m_startGeometry;

        if (m_edgePosition & Top)
        {
            newGeometry.setTop(newGeometry.top() + delta.y());
            if (newGeometry.height() < m_targetWidget->minimumHeight())
            {
                newGeometry.setTop(newGeometry.bottom() - m_targetWidget->minimumHeight());
            }
        }

        if (m_edgePosition & Bottom)
        {
            newGeometry.setBottom(newGeometry.bottom() + delta.y());
            if (newGeometry.height() < m_targetWidget->minimumHeight())
            {
                newGeometry.setBottom(newGeometry.top() + m_targetWidget->minimumHeight());
            }
        }

        if (m_edgePosition & Left)
        {
            newGeometry.setLeft(newGeometry.left() + delta.x());
            if (newGeometry.width() < m_targetWidget->minimumWidth())
            {
                newGeometry.setLeft(newGeometry.right() - m_targetWidget->minimumWidth());
            }
        }

        if (m_edgePosition & Right)
        {
            newGeometry.setRight(newGeometry.right() + delta.x());
            if (newGeometry.width() < m_targetWidget->minimumWidth())
            {
                newGeometry.setRight(newGeometry.left() + m_targetWidget->minimumWidth());
            }
        }

        m_targetWidget->setGeometry(newGeometry);
    }
}

void FramelessWindowHelper::handleMouseRelease(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = false;
        m_edgePosition = None;
    }
}

void FramelessWindowHelper::updateCursorShape(const QPoint &pos)
{
    if (!m_resizable)
    {
        m_targetWidget->unsetCursor();
        return;
    }

    int edgePosition = calculateMousePosition(pos);

    switch (edgePosition)
    {
    case Top:
    case Bottom:
        m_targetWidget->setCursor(Qt::SizeVerCursor);
        break;
    case Left:
    case Right:
        m_targetWidget->setCursor(Qt::SizeHorCursor);
        break;
    case TopLeft:
    case BottomRight:
        m_targetWidget->setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRight:
    case BottomLeft:
        m_targetWidget->setCursor(Qt::SizeBDiagCursor);
        break;
    default:
        m_targetWidget->unsetCursor();
        break;
    }
}

#endif