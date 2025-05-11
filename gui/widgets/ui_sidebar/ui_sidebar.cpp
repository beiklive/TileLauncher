#include "ui_sidebar.h"
#include <QPainter>
#include <QStyleOption>

SideBar::SideBar(QWidget *parent) :
    beiklive::BaseWidget(parent),
    m_isExpanded(false)
{
    m_normalWidth = globalSettings["sidebar"]["sidebar_width"].get<int>();
    m_expandedWidth = globalSettings["sidebar"]["sidebar_expand_width"].get<int>();
    this->setGeometry(this->x(), this->y(), m_normalWidth, this->height());
    this->setMaximumWidth(m_expandedWidth);
    this->setMinimumWidth(m_normalWidth);
    this->setProperty("style", QVariant("app_sidebar"));
    this->setStyleSheet("QWidget[style='app_sidebar'] {background-color: red;border : 5px solid white;}");

    setupUi();
}

int SideBar::curWidth() const
{
    return m_isExpanded ? m_expandedWidth : m_normalWidth;
}

void SideBar::addButton(const QString &text, const QIcon &icon, const QObject *receiver, const char *slot)
{
    beiklive::Ui_Button *button = new beiklive::Ui_Button(text, icon);

    int btnsize = globalSettings["button"]["button_size"].get<int>();
    button->setFixedHeight(btnsize);
    
    if (receiver && slot) {
        connect(button, SIGNAL(clicked()), receiver, slot);
    }
    
    m_button_layout->addWidget(button);
    m_buttons.append(button);
}
void SideBar::resizeEvent(QResizeEvent *event)
{
    // QWidget::resizeEvent(event);
}
void SideBar::toggleSidebar()
{
    m_isExpanded = !m_isExpanded;
    int targetWidth = m_isExpanded ? m_expandedWidth : m_normalWidth;
    this->raise();
    m_animation->stop();
    m_animation->setStartValue(QRect(this->x(), this->y(), !m_isExpanded ? m_expandedWidth : m_normalWidth, this->height()));
    m_animation->setEndValue(QRect(this->x(), this->y(), targetWidth, this->height()));
    m_animation->start();
    if(m_isExpanded) {
        updateButtonStyles();
    }
    spdlog::debug("toggleSidebar: width:{} -> {}", this->width(), targetWidth);
}

void SideBar::setupUi()
{
    m_toggleButton = new beiklive::Ui_Button("展开", QIcon("assets/icons/expands.svg"));
    m_buttons.append(m_toggleButton);

    int btnsize = globalSettings["button"]["button_size"].get<int>();
    m_toggleButton->setFixedHeight(btnsize);
    connect(m_toggleButton, SIGNAL(clicked()), this, SLOT(toggleSidebar()));

    m_main_layout = new QVBoxLayout(this);
    m_main_layout->setContentsMargins(0, 0, 0, 0);
    m_main_layout->setSpacing(0);

    m_button_layout = new QVBoxLayout();
    m_button_layout->setContentsMargins(0, 0, 0, 0);
    m_button_layout->setSpacing(0);
    m_buttonContainer = new beiklive::BaseWidget();
    // m_buttonContainer->setStyleSheet(R"(
    //     background-color: black;
    // )");
    m_buttonContainer->setLayout(m_button_layout);


    m_main_layout->addWidget(m_toggleButton);
    m_main_layout->addStretch();
    m_main_layout->addWidget(m_buttonContainer);

    this->setLayout(m_main_layout);

    m_animation = new QPropertyAnimation(this, "geometry");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);
    QObject::connect(m_animation, &QPropertyAnimation::finished, [this]() {
        if(!m_isExpanded) {
            updateButtonStyles();
        }
        spdlog::debug("toggleSidebar finished: width:{}", this->width());

    });
}

void SideBar::updateButtonStyles()
{
    for (auto button : m_buttons) {
        button->hideText(!m_isExpanded);
    }
}
