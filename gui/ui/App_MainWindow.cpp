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

    // 主内容区域

    mainWindow = new beiklive::BaseWidget(centralWidget);
    mainWindow->setStyleSheet("background: rgba(193, 132, 1, 1); border: 2px solid red;");


    // 创建侧边栏
    sidebar = new beiklive::ui_sidebar(centralWidget);
    sidebar->setStyleSheet("background: rgb(22, 255, 53); border: 2px solid red;");
    // sidebar->setStyleSheet("QWidget[style='app_sidebar'] {background: yellow; border : 5px solid white;}");

    // // 添加功能按钮
    sidebar->addButton("主页", QIcon("assets/icons/home.svg"), nullptr, nullptr);
    sidebar->addButton("设置", QIcon("assets/icons/setting.svg"), nullptr, nullptr);
    sidebar->addButton("帮助", QIcon("assets/icons/info.svg"), nullptr, nullptr);


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
    
    mainWindow->setGeometry(m_mainwindow_xpos, 0, centralWidget->width() - m_mainwindow_xpos, centralWidget->height());
    // sidebar->setGeometry(0,0,  40, centralWidget->height());
    sidebar->setGeometry(0,0,  sidebar->curWidth(), centralWidget->height());
    //spdlog打印centralWidget信息
    spdlog::debug("centralWidget {} {} {} {}", centralWidget->geometry().x(), centralWidget->geometry().y(), centralWidget->geometry().width(), centralWidget->geometry().height());
    spdlog::debug("mainWindow    {} {} {} {}", mainWindow->geometry().x(), mainWindow->geometry().y(), mainWindow->geometry().width(), mainWindow->geometry().height());
    spdlog::debug("sidebar       {} {} {} {}", sidebar->geometry().x(), sidebar->geometry().y(), sidebar->geometry().width(), sidebar->geometry().height());
}
