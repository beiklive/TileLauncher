#include "ui_GripItem.h"

beiklive::Ui_GripItem::Ui_GripItem(QWidget *parent, WindowParts parts, bool hideColor) : QWidget(parent),
                                                                                         m_parts(parts),
                                                                                         m_hideColor(hideColor),
                                                                                         m_parent(parent)
{
}

void beiklive::Ui_GripItem::setGeo(int x, int y, int w, int h)
{
    setGeometry(x, y, w, h);
}

void beiklive::Ui_GripItem::mouseMoveEvent(QMouseEvent *event)
{
    spdlog::debug("{} mouseMoveEvent", int(m_parts));
    QPoint delta = event->pos();
    int height = 0;
    int width = 0;
    QRect geo = this->parentWidget()->geometry();
    switch (m_parts)
    {
    case WindowParts::TOP:
        height = qMax(this->parentWidget()->minimumHeight(),
                          this->parentWidget()->height() - delta.y());
        geo.setTop(geo.bottom() - height);
        this->parentWidget()->setGeometry(geo);
        break;
    case WindowParts::BOTTOM:
        height = qMax(this->parentWidget()->minimumHeight(),
                          this->parentWidget()->height() + delta.y());
        this->parentWidget()->resize(this->parentWidget()->width(), height);
        break;
    case WindowParts::LEFT:
        width = qMax(this->parentWidget()->minimumWidth(),
                         this->parentWidget()->width() - delta.x());

        geo.setLeft(geo.right() - width);
        this->parentWidget()->setGeometry(geo);
        break;
    case WindowParts::RIGHT:
        width = qMax(this->parentWidget()->minimumWidth(),
                         this->parentWidget()->width() + delta.x());
        this->parentWidget()->resize(width, this->parentWidget()->height());
        break;
    default:
        break;
    }

    event->accept();
}

void beiklive::Ui_GripItem::InitUI()
{
    switch (m_parts)
    {
    case WindowParts::TOP:
        /* code */
        setGeometry(QRect(0, 5, m_parent->width(), 10));
        setMaximumHeight(10);
        setStyleSheet("background-color: rgb(154, 31, 202);");
        setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case WindowParts::BOTTOM:
        /* code */
        setGeometry(QRect(0, m_parent->height() - 10, m_parent->width(), 10));
        setMaximumHeight(10);
        setStyleSheet("background-color: rgb(154, 31, 202);");
        setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case WindowParts::LEFT:
        /* code */
        setGeometry(QRect(0, 5, 10, m_parent->height() - 10));
        setMaximumWidth(10);
        setStyleSheet("background-color: rgb(154, 31, 202);");
        setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case WindowParts::RIGHT:
        /* code */
        setGeometry(QRect(m_parent->width() - 10, 5, 10, m_parent->height() - 10));
        setMaximumWidth(10);
        setStyleSheet("background-color: rgb(154, 31, 202);");
        setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case WindowParts::TOP | WindowParts::LEFT:
        m_grip = new QSizeGrip(this);
        m_grip->setFixedSize(size());
        setGeometry(QRect(5, 5, 15, 15));
        setStyleSheet("background-color: #333; border: 2px solid #55FF00;");
        break;
    case WindowParts::TOP | WindowParts::RIGHT:
        /* code */
        m_grip = new QSizeGrip(this);
        m_grip->setFixedSize(size());
        setGeometry(QRect(m_parent->width() - 20, 5, 15, 15));
        setStyleSheet("background-color: #333; border: 2px solid #55FF00;");
        break;
    case WindowParts::BOTTOM | WindowParts::LEFT:
        /* code */
        m_grip = new QSizeGrip(this);
        m_grip->setFixedSize(size());
        setGeometry(QRect(5, m_parent->height() - 20, 15, 15));
        setStyleSheet("background-color: #333; border: 2px solid #55FF00;");
        break;
    case WindowParts::BOTTOM | WindowParts::RIGHT:
        /* code */
        m_grip = new QSizeGrip(this);
        m_grip->setFixedSize(size());
        setGeometry(QRect(m_parent->width() - 20, m_parent->height() - 20, 15, 15));
        setStyleSheet("background-color: #333; border: 2px solid #55FF00;");
        break;
    default:
        break;
    }

    if (m_hideColor)
        setStyleSheet("background-color: transparent");
}
