#include "ui_window.h"
beiklive::Ui_Window::Ui_Window()
{
    resize(800, 600);
    functionsSetup();





}


void beiklive::Ui_Window::functionsSetup()
{


    if (globalConfig["window"]["custom_title_bar"])
    {
        setFrameless();
    }
}
void beiklive::Ui_Window::setFrameless()
{
    m_helper = new FramelessWindowHelper(this);
    m_helper->setResizable(true);

}
void beiklive::Ui_Window::resizeEvent(QResizeEvent *event)
{

    if(globalConfig["window"]["custom_title_bar"] && m_helper)
    {
        m_helper->resizeGrips();
    }
}

void beiklive::Ui_Window::mouseMoveEvent(QMouseEvent *event)
{
    
}