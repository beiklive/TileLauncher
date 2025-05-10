#include "ui_sidebar.h"
#include <QPainter>
#include <QStyleOption>

SideBar::SideBar()
{
    m_normalWidth = globalSettings["sidebar"]["sidebar_width"].get<int>();
    m_expandedWidth = globalSettings["sidebar"]["sidebar_expand_width"].get<int>();
    this->setMaximumWidth(m_isExpanded ? m_expandedWidth : m_normalWidth);
    std::string styleSheet = std::format(R"(
        background-color: rgba(24, 24, 24);
    )");
    setupUi();
}

void SideBar::addButton(const QString &text, const QIcon &icon, const QObject *receiver, const char *slot)
{
    QPushButton *button = new QPushButton(m_buttonContainer);
    button->setIcon(icon);
    button->setText(text);
    button->setToolTip(text);
    button->setIconSize(QSize(24, 24));
    int btnsize = globalSettings["button"]["button_size"].get<int>();
    button->setFixedHeight(btnsize);
    
    // if (receiver && slot) {
    //     connect(button, SIGNAL(clicked()), receiver, slot);
    // }
    
    m_button_layout->addWidget(button);
}

void SideBar::toggleSidebar()
{
    m_isExpanded = !m_isExpanded;
    m_animation->stop();
    this->setMaximumWidth(m_isExpanded ? m_expandedWidth : m_normalWidth);
    m_animation->setStartValue(width());
    m_animation->setEndValue(m_isExpanded ? m_expandedWidth : m_normalWidth);
    m_animation->start();
    
}

void SideBar::setupUi()
{
    m_toggleButton = new QPushButton("this");
    int btnsize = globalSettings["button"]["button_size"].get<int>();
    m_toggleButton->setFixedSize(btnsize, btnsize);
    connect(m_toggleButton, SIGNAL(clicked()), this, SLOT(toggleSidebar()));

    m_main_layout = new QVBoxLayout(this);
    m_main_layout->setContentsMargins(0, 0, 0, 0);
    m_main_layout->setSpacing(0);

    m_buttonContainer = new beiklive::BaseWidget();
    m_buttonContainer->setLayout(m_button_layout);

    // 弹簧
    m_spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    m_main_layout->addWidget(m_toggleButton);
    m_main_layout->addItem(m_spacer);
    m_main_layout->addWidget(m_buttonContainer);

    this->setLayout(m_main_layout);

    // 动画
    m_animation = new QPropertyAnimation(this, "minimumWidth");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);
}
