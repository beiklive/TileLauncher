#include "ui_sidebar.h"

beiklive::Ui_Sidebar::Ui_Sidebar(QWidget *parent):
    QWidget(parent)
{
    // 侧边栏展开后宽度
    m_expand_width = globalSettings["sidebar"]["sidebar_expand_width"].get<int>();
    // 侧边栏正常宽度
    m_normal_width = globalSettings["sidebar"]["sidebar_normal_width"].get<int>();

    m_is_expand = false;
    _init_ui();

}


void beiklive::Ui_Sidebar::_startAnimation()
{
    animation->stop();
    // 设置动画的起始和结束几何属性
    int target_width = m_is_expand? m_normal_width : m_expand_width;
    QRect startGeometry = geometry();
    QRect endGeometry = QRect(startGeometry.x(), startGeometry.y(),
                               target_width, startGeometry.height());

    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);

    // 可选：设置缓动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

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
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    Ui_Sidebar_Button *expand_btn = new Ui_Sidebar_Button(this, "assets/icons/expands.svg", "展开");
    m_buttons.append(expand_btn);
    m_layout->addWidget(expand_btn);
    m_layout->addStretch();

    m_button_layout = new QVBoxLayout(this);
    m_button_layout->setContentsMargins(0, 0, 0, 0);
    m_button_layout->setSpacing(0);

    Ui_Sidebar_Button *home_btn = new Ui_Sidebar_Button(this, "assets/icons/home.svg", "主页");
    Ui_Sidebar_Button *setting_btn = new Ui_Sidebar_Button(this, "assets/icons/setting.svg", "设置");
    Ui_Sidebar_Button *info_btn = new Ui_Sidebar_Button(this, "assets/icons/info.svg", "信息");
    m_buttons.append(home_btn);
    m_buttons.append(setting_btn);
    m_buttons.append(info_btn);

    m_button_layout->addWidget(home_btn);
    m_button_layout->addWidget(setting_btn);
    m_button_layout->addWidget(info_btn);
    m_layout->addLayout(m_button_layout);

    // 初始化动画
    animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200); // 动画持续时间，单位毫秒
    // 连接按钮点击信号到启动动画的槽
    connect(expand_btn, &QPushButton::clicked, this, &Ui_Sidebar::_startAnimation);
    // 连接动画完成信号到回调槽
    connect(animation, &QPropertyAnimation::finished, this, &Ui_Sidebar::_onAnimationFinished);

}
