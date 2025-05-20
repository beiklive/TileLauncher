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
            true
        );
        moveWindowToBottomLeft(this);
        m_windowFlags = this->windowFlags();
        // this->setWindowFlags( m_windowFlags |Qt::Popup);

    }
}

void beiklive::App_MainWindow::animaShow()
{
    spdlog::debug("animaShow");
    // this->setWindowFlags( m_windowFlags);
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
        spdlog::info("窗口最大化");
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
        spdlog::info("窗口恢复");
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
    layout = new QHBoxLayout();
    layout->setContentsMargins(m_margin, m_margin, m_margin, m_margin);
    layout->setSpacing(0);
    m_centralWidget->setLayout(layout);

    _initSidebar();
    _initFileListView();
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

void beiklive::App_MainWindow::_initSidebar()
{
    m_sidebar = new Ui_Sidebar(m_centralWidget);
    layout->addWidget(m_sidebar);

    // beiklive::Ui_Sidebar_Button *btn = m_sidebar->addButton("亮色主题", "assets/icons/sun.svg");
    // btn->setProperty("theme", "light");
    // connect(btn, &beiklive::Ui_Sidebar_Button::clickedAtPosition, this, [this, btn](const QPoint &pos) {
    //     QPoint globalPos = btn->mapTo(this, pos);
    //     drawBackground(btn, globalPos);
    // });

    m_sidebar->addButton("主页", "assets/icons/home.svg", [this]() {
        spdlog::info("主页");
    });
    m_sidebar->addButton("设置", "assets/icons/setting.svg",  [this]() {
        spdlog::info("设置");
    });
    m_sidebar->addButton("关于", "assets/icons/info.svg",  [this]() {
        spdlog::info("关于");
    });
}

void beiklive::App_MainWindow::_initFileListView()
{
    m_filelistview = new Ui_File_List_View(m_centralWidget);
    layout->addWidget(m_filelistview);
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

void beiklive::App_MainWindow::drawBackground(beiklive::Ui_Sidebar_Button *btn, const QPoint &center)
{
    beiklive::Ui_Sidebar_Button *sender = qobject_cast<beiklive::Ui_Sidebar_Button*>(QObject::sender());
    if (sender != nullptr)
    {
        QVariant theme_name = sender->property("theme");
        std::string theme_name_str = theme_name.toString().toStdString();
        bool is_light{false};
        if (theme_name_str == "light")
        {
            sender->setProperty("theme", "dark");
            sender->set_icon("assets/icons/moon.svg");
            sender->set_text("暗黑主题");
            is_light = false;
        }else if (theme_name_str == "dark")
        {
            sender->setProperty("theme", "light");
            sender->set_icon("assets/icons/sun.svg");
            sender->set_text("亮色主题");
            is_light = true;
        }
        spdlog::info("theme changed to {}", sender->property("theme").toString().toStdString());


        // m_centralWidget->startAnimation(center, width()+height(), is_light);



    }
}

