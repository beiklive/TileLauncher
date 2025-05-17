#include "App_mainWindow.h"

beiklive::App_MainWindow::App_MainWindow(QWidget *parent)
{
    m_margin = globalSettings["window"]["margin"].get<int>();
    _setupUI();
}

void beiklive::App_MainWindow::resizeEvent(QResizeEvent *event)
{
    Ui_FrameLessWindow::resizeEvent(event);
}
void beiklive::App_MainWindow::window_maximize()
{
    if (globalSettings["titlebar"]["custom_title_bar"])
    {
        this->layout()->setContentsMargins(0, 0, 0, 0);
        shadow->setBlurRadius(0);
        setGraphicsEffect(shadow);
        hideGrips(true);
        spdlog::info("maximize");
    }
    
}
void beiklive::App_MainWindow::window_restore()
{
    if (globalSettings["titlebar"]["custom_title_bar"])
    {
        this->layout()->setContentsMargins(10, 10, 10, 10);
        shadow->setBlurRadius(20);
        setGraphicsEffect(shadow);
        hideGrips(false);
        spdlog::info("restore");
    }
    resize(width()+1, height()+1);
}

void beiklive::App_MainWindow::_setupUI()
{
    m_centralWidget = this->get_centralWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(m_margin, m_margin, m_margin, m_margin);
    m_centralWidget->setLayout(layout);

    
    m_sidebar = new Ui_Sidebar(m_centralWidget);
    layout->addWidget(m_sidebar);
    m_bodywidget = new QWidget(m_centralWidget);
    
    if (globalSettings["titlebar"]["custom_title_bar"])
    {
        std::string title_name = globalSettings["titlebar"]["title"].get<std::string>();
        titleBar = new Ui_Title_Bar(m_centralWidget, this, title_name);
        QVBoxLayout *vlayout = new QVBoxLayout();
        vlayout->setContentsMargins(0, 0, 0, 0);
        vlayout->addWidget(titleBar);
        vlayout->addWidget(m_bodywidget);
        connect(titleBar, &Ui_Title_Bar::maximize_window, this, &App_MainWindow::window_maximize);
        connect(titleBar, &Ui_Title_Bar::restore_window, this, &App_MainWindow::window_restore);
        layout->addLayout(vlayout);
    }
    else
    {
        layout->addWidget(m_bodywidget);
    }

    // 添加阴影
    shadow = new QGraphicsDropShadowEffect(m_centralWidget);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(0);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);
}
