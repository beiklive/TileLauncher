#include "ui_window.h"
#include <format>
#include <string>
beiklive::Ui_Window::Ui_Window()
{
    this->resize(800, 600);

    functionsSetup();
    styleSetup();
}

void beiklive::Ui_Window::functionsSetup()
{
    m_window = new QWidget(this);
    m_window->setObjectName("app_ui_window");
    QVBoxLayout *layout = new QVBoxLayout();
    
    
    if (globalSettings["window"]["custom_title_bar"])
    {
        m_helper = new FramelessWindowHelper(this);
        m_helper->setResizable(true);
        layout->setContentsMargins(10, 10, 10, 10);
    }else{
        layout->setContentsMargins(0, 0, 0, 0);

    }
    layout->addWidget(m_window);
    this->setLayout(layout);
    addCloseButton();
}

void beiklive::Ui_Window::styleSetup()
{
    auto bg_color = globalTheme["window"]["bg_color"].get<std::string>();
    int radius = globalTheme["window"]["border_radius"].get<int>();
    int border_width = globalTheme["window"]["border_width"].get<int>();
    auto border_color = globalTheme["window"]["border_color"].get<std::string>();
    auto text_color = globalTheme["window"]["text_color"].get<std::string>();
    auto text_font = globalTheme["window"]["text_font"].get<std::string>();

    std::string styleSheet = std::format(R"(
    #app_ui_window {{
        background-color: {};
        border-radius: {}px;
        border: {}px solid {};
    }}
    QWidget {{
        color: {};
        font: "{}";
    }}
    )",
    bg_color, radius, border_width, border_color, text_color, text_font);
    spdlog::debug("Stylesheet: {}", styleSheet);
    m_window->setStyleSheet(styleSheet.c_str());
}

void beiklive::Ui_Window::addCloseButton()
{
    QPushButton *closeButton = new QPushButton();
    QVBoxLayout *layout = new QVBoxLayout();
    closeButton->setObjectName("close_button");
    closeButton->setFixedSize(80, 80);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(closeButton);
    m_window->setLayout(layout);
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);
}

void beiklive::Ui_Window::resizeEvent(QResizeEvent *event)
{
    if (globalSettings["window"]["custom_title_bar"] && m_helper)
    {
        m_helper->resizeGrips();
    }
}

void beiklive::Ui_Window::mouseMoveEvent(QMouseEvent *event)
{
}