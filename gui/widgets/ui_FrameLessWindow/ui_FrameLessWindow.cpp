#include "ui_FrameLessWindow.h"

beiklive::Ui_FrameLessWindow::Ui_FrameLessWindow(QWidget *parent) : QWidget(parent)
{
    THEME_NAME(this, "FrameLessWindow")
    custom_window = globalSettings["window"]["custom_window"];
    if (custom_window)
    {
        // 设置无边框窗口
        setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
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

int beiklive::Ui_FrameLessWindow::getMargin()
{
    return m_margin;
}

void beiklive::Ui_FrameLessWindow::setMargin(int margin)
{
    m_margin = margin;
    this->layout()->setContentsMargins(m_margin, m_margin, m_margin, m_margin);
}

void beiklive::Ui_FrameLessWindow::setMargin(int margin_top, int margin_bottom, int margin_left, int margin_right)
{
    this->layout()->setContentsMargins(margin_left, margin_top, margin_right, margin_bottom);
}

void beiklive::Ui_FrameLessWindow::hideGrip(bool top, bool bottom, bool left, bool right, bool topleft, bool topright, bool bottomleft, bool bottomright)
{
    if(top){
        m_top_grop->hide();
    }
    if(bottom){
        m_bottom_grop->hide();
    }
    if(left){
        m_left_grop->hide();
    }
    if(right){
        m_right_grop->hide();
    }
    if(topleft){
        m_topleft_grop->hide();
    }
    if(topright){
        m_topright_grop->hide();
    }
    if(bottomleft){
        m_bottomleft_grop->hide();
    }
    if(bottomright){
        m_bottomright_grop->hide();
    }
}

void beiklive::Ui_FrameLessWindow::resizeEvent(QResizeEvent *event)
{
    updateGrip();

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
    }
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_centralWidget);
    m_centralWidget->setMouseTracking(true);





    spdlog::debug("窗口大小 {} {}", width(), height());
    spdlog::debug("主视图大小 {} {}, pos {} {}", 
        m_centralWidget->width(), m_centralWidget->height(),
        m_centralWidget->x(), m_centralWidget->y());


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
    int gapsize = 3;
    if (custom_window)
    {

        m_top_grop->setGeo(gapsize, 0, width() - gapsize*2, gapsize);
        m_bottom_grop->setGeo(gapsize, height() - gapsize, width() - gapsize*2, gapsize);
        m_left_grop->setGeo(gapsize, gapsize, gapsize, height() - gapsize*2);
        m_right_grop->setGeo(width() - gapsize, gapsize, gapsize, height() - gapsize*2);
        m_topleft_grop->setGeo(0, 0, gapsize*2, gapsize*2);
        m_topright_grop->setGeo(width() - gapsize*2, 0, gapsize*2, gapsize*2);
        m_bottomleft_grop->setGeo(0, height() - gapsize*2, gapsize*2, gapsize*2);
        m_bottomright_grop->setGeo(width() - gapsize*2, height() - gapsize*2, gapsize*2, gapsize*2);
    }
}

