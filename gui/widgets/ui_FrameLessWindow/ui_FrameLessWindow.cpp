#include "ui_FrameLessWindow.h"
#include "ui_frameLessWindow.h"

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

QWidget *beiklive::Ui_FrameLessWindow::centralWidget() const
{
    return m_centralWidget;
}

void beiklive::Ui_FrameLessWindow::mouseMoveEvent(QMouseEvent *event)
{

    QWidget::mouseMoveEvent(event);
}

void beiklive::Ui_FrameLessWindow::mousePressEvent(QMouseEvent *event)
{

    QWidget::mousePressEvent(event);
}

void beiklive::Ui_FrameLessWindow::mouseReleaseEvent(QMouseEvent *event)
{

    QWidget::mouseReleaseEvent(event);
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
    m_centralWidget->setProperty("styleclass", "centralWidget");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    
    if (custom_window)
    {
        initGrip();
        mainLayout->setContentsMargins(10, 10, 10, 10);
        if(globalSettings["window"]["custom_title_bar"])
        {
            titleBar = new QWidget(m_centralWidget);
            titleBar->setProperty("styleclass", "titleBar");
            QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
            titleLayout->setContentsMargins(5, 0, 5, 0);
            titleLayout->setSpacing(0);
            
            QLabel *m_titleLabel = new QLabel(titleBar);
            m_titleLabel->setText(globalSettings["window"]["title"].get<std::string>().c_str());
            m_titleLabel->setProperty("styleclass", "titleLabel");
            titleLayout->addWidget(m_titleLabel);
            titleLayout->addStretch();

            QPushButton *m_closeButton = new QPushButton(titleBar);
            m_closeButton->setProperty("styleclass", "windowButton");
            // 设置图标
            m_closeButton->setIcon(QIcon(ICON_WINDOW_CLOSE));
            titleLayout->addWidget(m_closeButton);
            connect(m_closeButton, &QPushButton::clicked, this, &QWidget::close);
            
        }
    }
    else
    {
        mainLayout->setContentsMargins(0, 0, 0, 0);
    }
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_centralWidget);
    m_centralWidget->setMouseTracking(true);


    // 添加阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(m_centralWidget);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(0);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);


    spdlog::info("窗口大小 {} {}", width(), height());
    spdlog::info("主视图大小 {} {}, pos {} {}", 
        m_centralWidget->width(), m_centralWidget->height(),
        m_centralWidget->x(), m_centralWidget->y());
    if(titleBar){
        spdlog::info("标题栏大小 {} {}, pos {} {}", 
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

