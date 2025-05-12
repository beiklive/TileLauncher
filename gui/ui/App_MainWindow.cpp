#include "App_MainWindow.h"

App_MainWindow::App_MainWindow(QWidget *parent) : beiklive::Ui_Window(parent)
{
    // 是否显示自定义标题栏
    if (!globalSettings["window"]["custom_title_bar"])
    {
        hideTitleBar();
    }
    centralWidget = getWindow();

    // 亚克力背景效果 有bug，暂时不用
    // AcrylicEffect* effect = new AcrylicEffect(centralWidget);
    // effect->apply();

    // 创建侧边栏
    sidebar = new SideBar(centralWidget);
    // // 添加功能按钮
    sidebar->addButton("Home", QIcon("assets/icons/home.svg"), nullptr, nullptr);
    sidebar->addButton("Settings", QIcon("assets/icons/setting.svg"), nullptr, nullptr);
    sidebar->addButton("Help", QIcon("assets/icons/info.svg"), nullptr, nullptr);

    // 主内容区域

    mainWindow = new beiklive::BaseWidget(centralWidget);
    mainWindow->setStyleSheet("background: rgba(193, 132, 1, 0.5); border: 2px solid red;");

    // 主内容区的偏移值
    m_mainwindow_xpos = globalSettings["sidebar"]["sidebar_width"].get<int>();
    flushlayout();
}

void App_MainWindow::resizeEvent(QResizeEvent *event)
{
    beiklive::Ui_Window::resizeEvent(event);
    flushlayout();
}

void App_MainWindow::flushlayout()
{
    
    mainWindow->setGeometry(centralWidget->geometry().x() + m_mainwindow_xpos, 0, centralWidget->width() - m_mainwindow_xpos-10, centralWidget->height());
    sidebar->setGeometry(0,0,  sidebar->curWidth(), centralWidget->height());
    //spdlog打印centralWidget信息
    spdlog::debug("centralWidget {} {} {} {}", centralWidget->geometry().x(), centralWidget->geometry().y(), centralWidget->geometry().width(), centralWidget->geometry().height());
    spdlog::debug("mainWindow    {} {} {} {}", mainWindow->geometry().x(), mainWindow->geometry().y(), mainWindow->geometry().width(), mainWindow->geometry().height());
    spdlog::debug("sidebar       {} {} {} {}", sidebar->geometry().x(), sidebar->geometry().y(), sidebar->geometry().width(), sidebar->geometry().height());
}
