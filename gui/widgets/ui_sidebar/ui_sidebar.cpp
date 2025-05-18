#include "ui_sidebar.h"

beiklive::Ui_Sidebar::Ui_Sidebar(QWidget *parent):
    QWidget(parent)
{
    THEME_NAME(this, "Sidebar")

    // 侧边栏展开后宽度
    m_expand_width = globalSettings["sidebar"]["sidebar_expand_width"].get<int>();
    // 侧边栏正常宽度
    m_normal_width = globalSettings["sidebar"]["sidebar_normal_width"].get<int>();
    // 侧边栏是否展开
    m_is_expand = false;
    // 内边距
    m_margin = globalSettings["sidebar"]["margin"].get<int>();
    setMinimumSize(m_normal_width, 0);
    setMaximumSize(m_normal_width, 16777215);

    _init_ui();
}

beiklive::Ui_Sidebar_Button *beiklive::Ui_Sidebar::addButton(std::string name, std::string icon_path, std::function<void()> onClick)
{
    beiklive::Ui_Sidebar_Button *btn = new beiklive::Ui_Sidebar_Button(this, icon_path, name);
    m_buttons.append(btn);
    m_button_layout->addWidget(btn);
    
    if (onClick) {
        connect(btn, &beiklive::Ui_Sidebar_Button::clicked, onClick);
    }
    
    return btn;
}



void beiklive::Ui_Sidebar::_startAnimation()
{

    animation->stop();


    // 设置动画的起始和结束几何属性
    int target_width = m_is_expand? m_normal_width : m_expand_width;
    int startWidth = width();
    int endWidth = target_width;

    animation->setStartValue(startWidth);
    animation->setEndValue(endWidth);

    animation->setEasingCurve(QEasingCurve::InOutQuart);

    // 启动动画
    animation->start();
}

void beiklive::Ui_Sidebar::_onAnimationFinished()
{
    
    for (auto btn : m_buttons) {
        btn->hide_text(m_is_expand);
    }
    m_is_expand =!m_is_expand;
}

void beiklive::Ui_Sidebar::_init_ui()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(m_margin, m_margin, m_margin, m_margin);
    m_layout->setSpacing(0);

    Ui_Sidebar_Button *expand_btn = new Ui_Sidebar_Button(this, "assets/icons/expands.svg", "展开");
    m_buttons.append(expand_btn);
    m_layout->addWidget(expand_btn);
    m_layout->addStretch();

    QWidget* btnBox = new QWidget(this);
    m_button_layout = new QVBoxLayout(btnBox);
    m_button_layout->setContentsMargins(0, 0, 0, 0);
    m_button_layout->setSpacing(0);
    btnBox->setLayout(m_button_layout);

    m_layout->addWidget(btnBox);


    // 连接按钮点击信号到启动动画的槽
    connect(expand_btn, &QPushButton::clicked, this, &Ui_Sidebar::_startAnimation);
    // 初始化动画
    animation = new QPropertyAnimation(this, "minimumWidth");
    animation->setDuration(500); // 动画持续时间，单位毫秒
    // 连接动画完成信号到回调槽
    connect(animation, &QPropertyAnimation::finished, this, &Ui_Sidebar::_onAnimationFinished);
}
