#include "App_mainWindow.h"
#include <QShortcut>

beiklive::App_MainWindow::App_MainWindow(QWidget *parent)
{
    m_margin = globalSettings["window"]["margin"].get<int>();

    setWindowIcon(QIcon(ICON_LOGO));   // 使用文件系统中的图标

    _setupUI();
    menuMode(true);
    createTrayIcon();

}

void beiklive::App_MainWindow::menuMode(bool enable)
{
    if (enable)
    {
        setMargin(0,0,0,0);
        hideGrip(
            false,
            true,
            true,
            false,
            true,
            false,
            true,
            false
        );
        moveWindowToBottomLeft(this);
        m_windowFlags = this->windowFlags();
        // this->setWindowFlags( m_windowFlags |Qt::Popup);

    }
}

void beiklive::App_MainWindow::animaShow()
{
    spdlog::debug("animaShow");
    this->setWindowFlags( m_windowFlags);
    show();
    QPoint geo = geometry().topLeft();
    animation->setStartValue(QPoint(geo.x(), geo.y()+geometry().height()));
    animation->setEndValue(QPoint(geo.x(), geo.y()));
    animation->start();

}


void beiklive::App_MainWindow::resizeEvent(QResizeEvent *event)
{
    Ui_FrameLessWindow::resizeEvent(event);
}
void beiklive::App_MainWindow::mousePressEvent(QMouseEvent *event)
{

    Ui_FrameLessWindow::mousePressEvent(event);
}

void beiklive::App_MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    Ui_FrameLessWindow::mouseMoveEvent(event);
}
void beiklive::App_MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Ui_FrameLessWindow::mouseReleaseEvent(event);
    
}
void beiklive::App_MainWindow::window_maximize()
{
    if (globalSettings["window"]["custom_window"])
    {
        this->setMargin(0);
        shadow->setBlurRadius(20);
        setGraphicsEffect(shadow);
        hideGrips(true);
        spdlog::info("maximize");
    }
    
}

void beiklive::App_MainWindow::window_restore()
{
    if (globalSettings["window"]["custom_window"])
    {
        this->setMargin(0);
        shadow->setBlurRadius(20);
        setGraphicsEffect(shadow);
        hideGrips(false);
        spdlog::info("restore");
    }
    // resize(width()+1, height()+1);
}
void beiklive::App_MainWindow::_onAnimationFinished()
{
    // this->setWindowFlags( m_windowFlags |Qt::Popup);
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
    shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(0);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);



    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(200); // 动画持续时间，单位毫秒
    connect(animation, &QPropertyAnimation::finished, this, &App_MainWindow::_onAnimationFinished);

}

void beiklive::App_MainWindow::moveWindowToBottomLeft(QWidget *window)
{
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect availableGeometry = screen->availableGeometry();  // 获取可用区域
    
    window->move(
        availableGeometry.left(), 
        availableGeometry.bottom() - window->height()
    );
}

void beiklive::App_MainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(ICON_LOGO));
    trayIcon->setToolTip("My Application");
    
    QMenu *trayMenu = new QMenu(this);
    QAction *showAction = trayMenu->addAction("Show");
    QAction *quitAction = trayMenu->addAction("Quit");
    
    connect(showAction, &QAction::triggered, this, &App_MainWindow::animaShow);
    connect(quitAction, &QAction::triggered, this, &App_MainWindow::close);
    // connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::onTrayIconActivated);
    
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}
