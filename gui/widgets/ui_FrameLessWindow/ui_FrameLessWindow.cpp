#include "ui_FrameLessWindow.h"

beiklive::Ui_FrameLessWindow::Ui_FrameLessWindow(QWidget *parent) : QWidget(parent)
{
    custom_window = globalSettings["window"]["custom_window"];
    if (custom_window)
    {
        // 设置无边框窗口
        setWindowFlags(Qt::FramelessWindowHint);
        setAttribute(Qt::WA_TranslucentBackground);
    }
    setMinimumSize(
        globalSettings["window"]["min_window_width"].get<int>(),
        globalSettings["window"]["min_window_height"].get<int>());
    resize(
        globalSettings["window"]["window_width"].get<int>(),
        globalSettings["window"]["window_height"].get<int>());
    move(
        globalSettings["window"]["window_x"].get<int>(),
        globalSettings["window"]["window_y"].get<int>());
    setMouseTracking(true);

    SetupUi();
}

QWidget *beiklive::Ui_FrameLessWindow::get_centralWidget()
{
    return m_centralWidget;
}

void beiklive::Ui_FrameLessWindow::hideGrips(bool hide)
{
    if(hide){
        m_top_grop->hide();
        m_bottom_grop->hide();
        m_left_grop->hide();
        m_right_grop->hide();
        m_topleft_grop->hide();
        m_topright_grop->hide();
        m_bottomleft_grop->hide();
        m_bottomright_grop->hide();
    }else{
        m_top_grop->show();
        m_bottom_grop->show();
        m_left_grop->show();
        m_right_grop->show();
        m_topleft_grop->show();
        m_topright_grop->show();
        m_bottomleft_grop->show();
        m_bottomright_grop->show();
    }
}



void beiklive::Ui_FrameLessWindow::resizeEvent(QResizeEvent *event)
{
    updateGrip();

    if(titleBar){
        titleBar->setGeometry(0, 0, m_centralWidget->width(), 30);
    }


}
void beiklive::Ui_FrameLessWindow::SetupUi()
{
    // 创建主布局
    m_centralWidget = new QWidget(this);
    THEME_NAME(m_centralWidget, "centralWidget")
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    
    if (custom_window)
    {
        initGrip();
        mainLayout->setContentsMargins(10, 10, 10, 10);
    }
    else
    {
        mainLayout->setContentsMargins(0, 0, 0, 0);
    }
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_centralWidget);
    m_centralWidget->setMouseTracking(true);





    spdlog::debug("窗口大小 {} {}", width(), height());
    spdlog::debug("主视图大小 {} {}, pos {} {}", 
        m_centralWidget->width(), m_centralWidget->height(),
        m_centralWidget->x(), m_centralWidget->y());
    if(titleBar){
        spdlog::debug("标题栏大小 {} {}, pos {} {}", 
            titleBar->width(), titleBar->height(),
            titleBar->x(), titleBar->y());
    }


}



void beiklive::Ui_FrameLessWindow::initGrip()
{
    bool hideColor = globalSettings["window"]["hide_border_color"];
    m_top_grop = new Ui_GripItem(this, WindowParts::TOP, hideColor);
    m_bottom_grop = new Ui_GripItem(this, WindowParts::BOTTOM, hideColor);
    m_left_grop = new Ui_GripItem(this, WindowParts::LEFT, hideColor);
    m_right_grop = new Ui_GripItem(this, WindowParts::RIGHT, hideColor);
    m_topleft_grop = new Ui_GripItem(this, WindowParts(WindowParts::TOP | WindowParts::LEFT), hideColor);
    m_topright_grop = new Ui_GripItem(this, WindowParts(WindowParts::TOP | WindowParts::RIGHT), hideColor);
    m_bottomleft_grop = new Ui_GripItem(this, WindowParts(WindowParts::BOTTOM | WindowParts::LEFT), hideColor);
    m_bottomright_grop = new Ui_GripItem(this, WindowParts(WindowParts::BOTTOM | WindowParts::RIGHT), hideColor);
}

void beiklive::Ui_FrameLessWindow::updateGrip()
{
    if (custom_window)
    {

        m_top_grop->setGeo(5, 5, width() - 10, 10);
        m_bottom_grop->setGeo(5, height() - 15, width() - 10, 10);
        m_left_grop->setGeo(5, 5, 10, height() - 10);
        m_right_grop->setGeo(width() - 15, 5, 10, height() - 10);
        m_topleft_grop->setGeo(5, 5, 15, 15);
        m_topright_grop->setGeo(width() - 20, 5, 15, 15);
        m_bottomleft_grop->setGeo(5, height() - 20, 15, 15);
        m_bottomright_grop->setGeo(width() - 20, height() - 20, 15, 15);
    }
}

