
#include "FramelessWindowHelper.h"

#include <QMouseEvent>
#include <QApplication>
#include <QCursor>
#include <QDebug>

CustomGrip::CustomGrip(QWidget *parent) : QFrame(parent)
{
    // Setup your grip here
}

void CustomGrip::mouseMoveEvent(QMouseEvent *event)
{
    // Your resize logic here
    // QFrame::mouseMoveEvent(event); // Call base class implementation
    QString name = this->objectName();
    QPoint delta = event->pos();
    if (name == "top_grip")
    {
        int height = qMax(this->parentWidget()->minimumHeight(),
                          this->parentWidget()->height() - delta.y());
        QRect geo = this->parentWidget()->geometry();
        geo.setTop(geo.bottom() - height);
        this->parentWidget()->setGeometry(geo);
    }
    else if (name == "bottom_grip")
    {
        int height = qMax(this->parentWidget()->minimumHeight(),
                          this->parentWidget()->height() + delta.y());
        this->parentWidget()->resize(this->parentWidget()->width(), height);
    }
    else if (name == "left_grip")
    {
        int width = qMax(this->parentWidget()->minimumWidth(),
                         this->parentWidget()->width() - delta.x());

        QRect geo = parentWidget()->geometry();
        geo.setLeft(geo.right() - width);
        this->parentWidget()->setGeometry(geo);
    }
    else if (name == "right_grip")
    {
        int width = qMax(this->parentWidget()->minimumWidth(),
                         this->parentWidget()->width() + delta.x());
        this->parentWidget()->resize(width, this->parentWidget()->height());
    }

    event->accept();
}

EdgeWidget::EdgeWidget() : top_left_grip(nullptr),
                           top_right_grip(nullptr),
                           bottom_left_grip(nullptr),
                           bottom_right_grip(nullptr),
                           top_grip(nullptr),
                           bottom_grip(nullptr),
                           left_grip(nullptr),
                           right_grip(nullptr)
{
}

EdgeWidget::~EdgeWidget()
{
    // Clean up allocated resources
    delete top_left_grip;
    delete top_right_grip;
    delete bottom_left_grip;
    delete bottom_right_grip;
    delete top_grip;
    delete bottom_grip;
    delete left_grip;
    delete right_grip;
}

void EdgeWidget::top_left(QWidget *form)
{
    top_left_grip = new CustomGrip(form);
    top_left_grip->setObjectName("top_left_grip");
    top_left_grip->setFixedSize(15, 15);
    top_left_grip->setStyleSheet("background-color: #333; border: 2px solid #55FF00;");
}

void EdgeWidget::top_right(QWidget *form)
{
    top_right_grip = new CustomGrip(form);
    top_right_grip->setObjectName("top_right_grip");
    top_right_grip->setFixedSize(15, 15);
    top_right_grip->setStyleSheet("background-color: #333; border: 2px solid #55FF00;");
}

void EdgeWidget::bottom_left(QWidget *form)
{
    bottom_left_grip = new CustomGrip(form);
    bottom_left_grip->setObjectName("bottom_left_grip");
    bottom_left_grip->setFixedSize(15, 15);
    bottom_left_grip->setStyleSheet("background-color: #333; border: 2px solid #55FF00;");
}

void EdgeWidget::bottom_right(QWidget *form)
{
    bottom_right_grip = new CustomGrip(form);
    bottom_right_grip->setObjectName("bottom_right_grip");
    bottom_right_grip->setFixedSize(15, 15);
    bottom_right_grip->setStyleSheet("background-color: #333; border: 2px solid #55FF00;");
}

void EdgeWidget::top(QWidget *form)
{
    top_grip = new CustomGrip(form);
    top_grip->setObjectName("top_grip");
    top_grip->setGeometry(QRect(0, 0, 500, 10));
    top_grip->setStyleSheet("background-color: rgb(154, 31, 202);");
    top_grip->setCursor(QCursor(Qt::SizeVerCursor));
}

void EdgeWidget::bottom(QWidget *form)
{
    bottom_grip = new CustomGrip(form);
    bottom_grip->setObjectName("bottom_grip");
    bottom_grip->setGeometry(QRect(0, 0, 500, 10));
    bottom_grip->setStyleSheet("background-color: rgb(192, 222, 58);");
    bottom_grip->setCursor(QCursor(Qt::SizeVerCursor));
}

void EdgeWidget::left(QWidget *form)
{
    left_grip = new CustomGrip(form);
    left_grip->setObjectName("left_grip");
    left_grip->setGeometry(QRect(0, 10, 10, 480));
    left_grip->setMinimumSize(QSize(10, 0));
    left_grip->setCursor(QCursor(Qt::SizeHorCursor));
    left_grip->setStyleSheet("background-color: rgb(255, 121, 198);");
}

void EdgeWidget::right(QWidget *form)
{
    right_grip = new CustomGrip(form);
    right_grip->setObjectName("right_grip");
    right_grip->setGeometry(QRect(0, 0, 10, 500));
    right_grip->setMinimumSize(QSize(10, 0));
    right_grip->setCursor(QCursor(Qt::SizeHorCursor));
    right_grip->setStyleSheet("background-color: rgb(255, 0, 127);");
}

EdgeGrips::EdgeGrips(QWidget *parent, EdgePosition edgePosition, bool showColor) : QWidget(parent), m_targetWidget(parent)
{
    if (m_targetWidget)
    {
        m_edgeWidget = new EdgeWidget();
        switch (edgePosition)
        {
        case Top:
            m_edgeWidget->top(m_targetWidget);
            m_edgeWidget->top_grip->setGeometry(QRect(0, 5, m_targetWidget->width(), 10));
            m_edgeWidget->top_grip->setMaximumHeight(10);

            if (showColor)
                m_edgeWidget->top_grip->setStyleSheet("background-color: transparent");
            break;
        case Bottom:
            m_edgeWidget->bottom(m_targetWidget);
            m_edgeWidget->bottom_grip->setGeometry(QRect(0, m_targetWidget->height() - 10, m_targetWidget->width(), 10));
            m_edgeWidget->bottom_grip->setMaximumHeight(10);

            if (showColor)
                m_edgeWidget->bottom_grip->setStyleSheet("background-color: transparent");
            break;
        case Left:
            m_edgeWidget->left(m_targetWidget);
            m_edgeWidget->left_grip->setGeometry(QRect(0, 5, 10, m_targetWidget->height()-10));
            m_edgeWidget->left_grip->setMaximumWidth(10);

            if (showColor)
                m_edgeWidget->left_grip->setStyleSheet("background-color: transparent");
            break;
        case Right:
            m_edgeWidget->right(m_targetWidget);
            m_edgeWidget->right_grip->setGeometry(QRect(m_targetWidget->width() - 10, 5, 10, m_targetWidget->height()-10));
            m_edgeWidget->right_grip->setMaximumWidth(10);

            if (showColor)
                m_edgeWidget->right_grip->setStyleSheet("background-color: transparent");
            break;
        case TopLeft:
            m_edgeWidget->top_left(m_targetWidget);
            grip = new QSizeGrip(m_edgeWidget->top_left_grip);
            grip->setFixedSize(m_edgeWidget->top_left_grip->size());
            m_edgeWidget->top_left_grip->setGeometry(QRect(5, 5, 15, 15));
            if (showColor)
                m_edgeWidget->top_left_grip->setStyleSheet("background-color: transparent");
            break;
        case TopRight:
            m_edgeWidget->top_right(m_targetWidget);
            grip = new QSizeGrip(m_edgeWidget->top_right_grip);
            grip->setFixedSize(m_edgeWidget->top_right_grip->size());
            m_edgeWidget->top_right_grip->setGeometry(QRect(m_targetWidget->width() - 20, 5, 15, 15));
            if (showColor)
                m_edgeWidget->top_right_grip->setStyleSheet("background-color: transparent");
            break;
        case BottomLeft:
            m_edgeWidget->bottom_left(m_targetWidget);
            grip = new QSizeGrip(m_edgeWidget->bottom_left_grip);
            grip->setFixedSize(m_edgeWidget->bottom_left_grip->size());
            m_edgeWidget->bottom_left_grip->setGeometry(QRect(5, m_targetWidget->height() - 20, 15, 15));
            if (showColor)
                m_edgeWidget->bottom_left_grip->setStyleSheet("background-color: transparent");
            break;
        case BottomRight:
            m_edgeWidget->bottom_right(m_targetWidget);
            grip = new QSizeGrip(m_edgeWidget->bottom_right_grip);
            grip->setFixedSize(m_edgeWidget->bottom_right_grip->size());
            m_edgeWidget->bottom_right_grip->setGeometry(QRect(m_targetWidget->width() - 20, m_targetWidget->height() - 20, 15, 15));
            if (showColor)
                m_edgeWidget->bottom_right_grip->setStyleSheet("background-color: transparent");
            break;
        default:
            break;
        }
    }
}

void EdgeGrips::setGeo(int x, int y, int w, int h)
{
    if(m_edgeWidget == nullptr)
        return;

    if (m_edgeWidget->top_grip)
    {
        m_edgeWidget->top_grip->setGeometry(x, y, w, h);
    }
    else if (m_edgeWidget->bottom_grip)
    {
        m_edgeWidget->bottom_grip->setGeometry(x, y, w, h);
    }
    else if (m_edgeWidget->left_grip)
    {
        m_edgeWidget->left_grip->setGeometry(x, y, w, h);
    }
    else if (m_edgeWidget->right_grip)
    {
        m_edgeWidget->right_grip->setGeometry(x, y, w, h);
    }
    else if (m_edgeWidget->top_right_grip)
    {
        m_edgeWidget->top_right_grip->setGeometry(x, y, w, h);
    }
    else if (m_edgeWidget->bottom_left_grip)
    {
        m_edgeWidget->bottom_left_grip->setGeometry(x, y, w, h);
    }
    else if (m_edgeWidget->bottom_right_grip)
    {
        m_edgeWidget->bottom_right_grip->setGeometry(x, y, w, h);
    }
}


FramelessWindowHelper::FramelessWindowHelper(QWidget *parent) : QObject(parent),
                                                                m_targetWidget(parent)

{
    if (m_targetWidget)
    {
        if(m_useCustomTitleBar)
        {
            m_targetWidget->setWindowFlags(m_targetWidget->windowFlags() | Qt::FramelessWindowHint);
        }
    }
}

void FramelessWindowHelper::setResizable(bool resizable)
{
    m_resizable = resizable;
    if (m_targetWidget && resizable)
    {
        m_targetWidget->setMinimumWidth(100);
        m_targetWidget->setMinimumHeight(100);
        _addEdgeWidgets();
    }
}

void FramelessWindowHelper::_addEdgeWidgets()
{
    bool showColor = false;
    top_grip = new EdgeGrips(m_targetWidget, Top, showColor);
    bottom_grip = new EdgeGrips(m_targetWidget, Bottom, showColor);
    left_grip = new EdgeGrips(m_targetWidget, Left, showColor);
    right_grip = new EdgeGrips(m_targetWidget, Right, showColor);
    top_left_grip = new EdgeGrips(m_targetWidget, TopLeft, showColor);
    top_right_grip = new EdgeGrips(m_targetWidget, TopRight, showColor);
    bottom_left_grip = new EdgeGrips(m_targetWidget, BottomLeft, showColor);
    bottom_right_grip = new EdgeGrips(m_targetWidget, BottomRight, showColor);
}

void FramelessWindowHelper::resizeGrips()
{
    if (m_targetWidget && m_resizable)
    {
        left_grip->setGeo(5, 5, 10, m_targetWidget->height()-10);
        right_grip->setGeo(m_targetWidget->width() - 15, 5, 10, m_targetWidget->height()-10);
        top_grip->setGeo(5, 5, m_targetWidget->width() - 10, 10);
        bottom_grip->setGeo(5, m_targetWidget->height() - 15, m_targetWidget->width() - 10, 10);
        top_right_grip->setGeo(m_targetWidget->width() - 20, 5, 15, 15);
        top_left_grip->setGeo(5, 5, 15, 15);
        bottom_left_grip->setGeo(5, m_targetWidget->height() - 20, 15, 15);
        bottom_right_grip->setGeo(m_targetWidget->width() - 20, m_targetWidget->height() - 20, 15, 15);
    }
}
