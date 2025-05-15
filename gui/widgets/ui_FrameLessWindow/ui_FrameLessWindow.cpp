#include "ui_FrameLessWindow.h"


beiklive::Ui_FrameLessWindow::Ui_FrameLessWindow(QWidget *parent) : QWidget(parent)
{
    
    
    
    // 设置无边框窗口
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(
        globalSettings["window"]["min_window_width"].get<int>(), 
        globalSettings["window"]["min_window_height"].get<int>()
    );
    resize(
        globalSettings["window"]["window_width"].get<int>(), 
        globalSettings["window"]["window_height"].get<int>()
    );
    move(
        globalSettings["window"]["window_x"].get<int>(), 
        globalSettings["window"]["window_y"].get<int>()
    );
    setMouseTracking(true);

    SetupUi();
    SetupStyle();


}

void beiklive::Ui_FrameLessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_mousePressed)
    {
        updateCursorShape(event->pos());
        return;
    }

}

void beiklive::Ui_FrameLessWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_mousePressed = true;
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
    }
}

void beiklive::Ui_FrameLessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_mousePressed = false;
    m_resizing = false;
}

void beiklive::Ui_FrameLessWindow::SetupUi()
{
    // 创建主布局
    m_centralWidget = new QWidget(this);
    m_centralWidget->setProperty("styleclass", "centralWidget");
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_centralWidget);
    m_centralWidget->setMouseTracking(true);

}

void beiklive::Ui_FrameLessWindow::SetupStyle()
{
    std::string style_str = R"(
        [styleclass="centralWidget"] {
            background-color: rgb(255, 255, 255);
            border: 1px solid rgb(200, 200, 200);
            border-radius: 5px;
        }
    )";

    m_centralWidget->setStyleSheet(style_str.c_str());

}

void beiklive::Ui_FrameLessWindow::updateCursorShape(const QPoint &pos)
{
    const int margin = 5;
    if (pos.x() <= margin && pos.y() <= margin)
    {
        // 左上角
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (pos.x() >= width() - margin && pos.y() >= height() - margin)
    {
        // 右下角
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (pos.x() <= margin && pos.y() >= height() - margin)
    {
        // 左下角
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