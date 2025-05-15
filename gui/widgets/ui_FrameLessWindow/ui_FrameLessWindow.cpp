#include "ui_FrameLessWindow.h"

namespace beiklive
{

Ui_FrameLessWindow::Ui_FrameLessWindow(QWidget *parent) : QWidget(parent)
{
    // 设置无边框窗口
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(800, 600);

    // 创建主布局
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setCentralWidget(centralWidget);


    setMouseTracking(true);
}

void Ui_FrameLessWindow::updateCursorShape(const QPoint &pos)
{
    const int margin = 5;
    if (pos.x() <= margin && pos.y() <= margin)
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (pos.x() >= width() - margin && pos.y() >= height() - margin)
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (pos.x() <= margin && pos.y() >= height() - margin)
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if (pos.x() >= width() - margin && pos.y() <= margin)
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if (pos.x() <= margin || pos.x() >= width() - margin)
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if (pos.y() <= margin || pos.y() >= height() - margin)
    {
        setCursor(Qt::SizeVerCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}

} // namespace beiklive
