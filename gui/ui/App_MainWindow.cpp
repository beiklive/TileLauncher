#include "App_MainWindow.h"

App_MainWindow::App_MainWindow(QWidget *parent)
{
    // 是否显示自定义标题栏
    if (!globalSettings["window"]["custom_title_bar"])
    {
        hideTitleBar();
    }
    QWidget *centralWidget = getWindow();

    // 亚克力背景效果 有bug，暂时不用
    // AcrylicEffect* effect = new AcrylicEffect(centralWidget);
    // effect->apply();

        // 创建侧边栏
    SideBar *sidebar = new SideBar();
    // 添加功能按钮
    sidebar->addButton("Home", QIcon("assets/icons/home.svg"), nullptr, nullptr);
    sidebar->addButton("Settings", QIcon("assets/icons/setting.svg"), nullptr, nullptr);
    sidebar->addButton("Help", QIcon("assets/icons/info.svg"), nullptr, nullptr);
    
    // 主内容区域
    QPushButton *textEdit = new QPushButton("Hello World!");

    QHBoxLayout *layout = new QHBoxLayout(centralWidget);
    layout->addWidget(sidebar);
    layout->addWidget(textEdit);
    layout->setContentsMargins(0, 0, 0, 0);
    centralWidget->setLayout(layout);






}