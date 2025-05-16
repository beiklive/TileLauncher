#include "ui_sidebar_button.h"


beiklive::Ui_Sidebar_Button::Ui_Sidebar_Button(QWidget *parent, std::string icon_path, std::string text):
 m_icon_label(new QLabel(this)),
 m_text_label(new QLabel(this))
{
    THEME_NAME(this, "sidebarButton")

    _init_icon(icon_path);
    _init_text(text);
    _setup_ui();
}

void beiklive::Ui_Sidebar_Button::hide_text(bool hide)
{
    m_hide_text = hide;
    if (hide)
    {
        m_text_label->setFixedHeight(0);
    }
    else
    {
        m_text_label->setFixedHeight(height()-10);
    }
}

void beiklive::Ui_Sidebar_Button::set_icon(std::string icon_path)
{
    _init_icon(icon_path);
}

void beiklive::Ui_Sidebar_Button::set_text(std::string text)
{
    _init_text(text);
}



void beiklive::Ui_Sidebar_Button::_setup_ui()
{
    
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(0);
    layout->addWidget(m_icon_label);
    layout->addWidget(m_text_label);

    hide_text(true);
}

void beiklive::Ui_Sidebar_Button::_init_icon(std::string icon_path)
{
    QIcon icon(icon_path.c_str());
    m_icon_label->setPixmap(icon.pixmap(QSize(24, 24)));
    m_icon_label->setAlignment(Qt::AlignCenter);
    m_icon_label->setFixedSize(QSize(
        globalSettings["sidebar"]["icon_size"].get<int>(),
        globalSettings["sidebar"]["icon_size"].get<int>()
    ));
}

void beiklive::Ui_Sidebar_Button::_init_text(std::string text)
{
    m_text_label->setText(text.c_str());
    m_text_label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

