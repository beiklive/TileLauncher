#include "ui_window.h"
beiklive::Ui_Window::Ui_Window()
{
    resize(800, 600);

    #if BEIKLIVE_FRAMELESS
    setFrameless();
    #endif

}
void beiklive::Ui_Window::setFrameless()
{
    m_helper = new FramelessWindowHelper(this);
    m_helper->setResizable(true);

}
void beiklive::Ui_Window::resizeEvent(QResizeEvent *event)
{
    if(m_helper)
    {
        m_helper->resizeGrips();
    }
}
