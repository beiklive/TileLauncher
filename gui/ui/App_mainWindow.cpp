#include "App_mainWindow.h"


beiklive::App_MainWindow::App_MainWindow(QWidget *parent)
{
    m_sidebarWidth = globalSettings["sidebar"]["sidebar_normal_width"].get<int>();
    _setupUI();

}

void beiklive::App_MainWindow::resizeEvent(QResizeEvent *event)
{
    Ui_FrameLessWindow::resizeEvent(event);
    if(m_sidebar != nullptr) {
        m_sidebar->setGeometry(
            10, 
            10, 
            m_sidebar->width(), 
            height() - 20
        );
    }
}

void beiklive::App_MainWindow::_setupUI()
{
    m_centralWidget = this->get_centralWidget();
    QHBoxLayout *layout = new QHBoxLayout(m_centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    m_centralWidget->setLayout(layout);


    m_sidebar = new Ui_Sidebar(this);
    // layout->addWidget(m_sidebar);

    // Ui_Sidebar *m_sidebar2 = new Ui_Sidebar(this);
    // layout->addWidget(m_sidebar2);
    
    // Ui_Sidebar_Button *button = new Ui_Sidebar_Button(centralWidget, "assets/icons/expands.svg", "展开");
    // layout->addWidget(button);

    // Ui_Sidebar_Button *button2 = new Ui_Sidebar_Button(centralWidget, "assets/icons/expands.svg", "展开");
    // button2->hide_text(true);
    // layout->addWidget(button2);
}
