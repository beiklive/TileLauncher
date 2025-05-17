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

void beiklive::App_MainWindow::_setupUI()
{
    m_centralWidget = this->get_centralWidget();
    QHBoxLayout *layout = new QHBoxLayout(m_centralWidget);
    layout->setContentsMargins(m_margin, m_margin, m_margin, m_margin);
    m_centralWidget->setLayout(layout);


    m_sidebar = new Ui_Sidebar(m_centralWidget);
    layout->addWidget(m_sidebar);
    m_bodywidget = new QWidget(m_centralWidget);
    layout->addWidget(m_bodywidget);


}
