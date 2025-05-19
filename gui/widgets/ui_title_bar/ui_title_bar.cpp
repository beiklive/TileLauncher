#include "ui_title_bar.h"

beiklive::Ui_Title_Bar::Ui_Title_Bar(QWidget *parent, QWidget *app_parent, std::string title_text)
{
    THEME_NAME(this, "TitleBar")

    m_parent = parent;
    m_app_parent = app_parent;
    m_title_text = title_text;
    m_height = globalSettings["titlebar"]["title_bar_height"].get<int>();
    m_margin = globalSettings["titlebar"]["margin"].get<int>();
    // setAttribute(Qt::WA_StyledBackground, true);
    setFixedHeight(m_height);
    _init_ui();
}

void beiklive::Ui_Title_Bar::set_title_text(std::string text)
{
    m_title_text = text;
    title_label->setText(m_title_text.c_str());
}

void beiklive::Ui_Title_Bar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        maximize_restore();
    }
}

void beiklive::Ui_Title_Bar::_init_ui()
{
    title_label = new QLabel(m_title_text.c_str());

    m_btn_close = new Ui_Title_Button(this, ICON_WINDOW_CLOSE);
    m_btn_min = new Ui_Title_Button(this, ICON_WINDOW_MINIMIZE);
    m_btn_max = new Ui_Title_Button(this, ICON_WINDOW_MAXIMIZE);

    connect(m_btn_close, &Ui_Title_Button::clicked, this, [this]() {
        m_app_parent->close();
    });
    connect(m_btn_min, &Ui_Title_Button::clicked, this, [this]{
        m_app_parent->showMinimized();
    });
    connect(m_btn_max, &Ui_Title_Button::clicked, this, [this]()
    {
        maximize_restore();
    });


    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(title_label);
    title_layout->addStretch();
    title_layout->addWidget(m_btn_min);
    title_layout->addWidget(m_btn_max);
    title_layout->addWidget(m_btn_close);
    title_layout->setContentsMargins(m_margin,m_margin,m_margin,m_margin);
    title_layout->setSpacing(1);

    setLayout(title_layout);

}


void beiklive::Ui_Title_Bar::maximize_restore()
{
    if (m_app_parent->isMaximized()) {
        m_is_maximized = false;
        m_app_parent->showNormal();
        emit restore_window();
    } else {
        m_is_maximized = true;
        m_old_size = QSize(m_app_parent->width(), m_app_parent->height());
        m_app_parent->showMaximized();
        emit maximize_window();
    }
    update_maximize_icon();
}

void beiklive::Ui_Title_Bar::update_maximize_icon()
{
    m_btn_max->setIconPath(m_is_maximized? ICON_WINDOW_RESTORE : ICON_WINDOW_MAXIMIZE);
}
