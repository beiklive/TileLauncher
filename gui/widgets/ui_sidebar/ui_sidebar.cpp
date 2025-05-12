#include "ui_sidebar.h"

namespace beiklive {

/**
 * @brief 构造函数
 * @param parent 父控件
 */
ui_sidebar::ui_sidebar(QWidget *parent) 
    : BaseWidget(parent),
      m_isExpanded(false),
      m_toggleButton(nullptr),
      m_buttonContainer(nullptr),
      m_mainLayout(nullptr),
      m_buttonLayout(nullptr),
      m_animation(nullptr)
{
    // 从配置加载侧边栏尺寸
    try {
        m_normalWidth = globalSettings["sidebar"]["sidebar_width"].get<int>();
        m_expandedWidth = globalSettings["sidebar"]["sidebar_expand_width"].get<int>();
    } catch (const std::exception &e) {
        spdlog::error("加载侧边栏尺寸失败: {}", e.what());
        m_normalWidth = 40;   // 默认收起宽度
        m_expandedWidth = 100; // 默认展开宽度
    }

    setGeometry(x(), y(), m_normalWidth, height());
    setProperty("style", QVariant("app_sidebar"));
    
    setupUi();
}

/**
 * @brief 获取当前宽度（根据展开状态）
 * @return 当前宽度(像素)
 */
int ui_sidebar::curWidth() const
{
    return m_isExpanded ? m_expandedWidth : m_normalWidth;
}

/**
 * @brief 添加按钮到侧边栏
 */
void ui_sidebar::addButton(const QString &text, const QIcon &icon, 
                       const QObject *receiver, const char *slot)
{
    if (!m_buttonLayout) {
        spdlog::warn("按钮布局未初始化，无法添加按钮");
        return;
    }

    Ui_Button *button = new Ui_Button(text, icon);
    
    try {
        int btnSize = globalSettings["button"]["button_size"].get<int>();
        button->setFixedHeight(btnSize);
    } catch (const std::exception &e) {
        spdlog::warn("加载按钮尺寸失败: {}, 使用默认尺寸40", e.what());
        button->setFixedHeight(40);
    }
    
    // 连接信号槽（如果提供了接收者和槽函数）
    if (receiver && slot) {
        connect(button, SIGNAL(clicked()), receiver, slot);
    }
    
    m_buttonLayout->addWidget(button);
    m_buttons.append(button);
    spdlog::debug("已添加按钮: {}", text.toStdString());
}

/**
 * @brief 切换侧边栏展开/收起状态
 */
void ui_sidebar::toggleSidebar()
{
    m_isExpanded = !m_isExpanded;
    const int targetWidth = curWidth();
    
    raise();  // 确保侧边栏在最上层
    
    // 停止正在进行的动画
    if (m_animation->state() == QPropertyAnimation::Running) {
        m_animation->stop();
    }
    
    // 设置动画参数
    m_animation->setStartValue(geometry());
    m_animation->setEndValue(QRect(x(), y(), targetWidth, height()));
    m_animation->start();
    
    // 展开时立即更新按钮样式
    if (m_isExpanded) {
        updateButtonStyles();
    }
    
    spdlog::debug("切换侧边栏状态: {} -> 宽度:{}", 
                 m_isExpanded ? "展开" : "收起", targetWidth);
}

/**
 * @brief 初始化UI组件
 */
void ui_sidebar::setupUi()
{
    // 初始化切换按钮
    m_toggleButton = new Ui_Button(tr("展开"), QIcon("assets/icons/expands.svg"));
    
    try {
        int btnSize = globalSettings["button"]["button_size"].get<int>();
        m_toggleButton->setFixedHeight(btnSize);
    } catch (const std::exception &e) {
        spdlog::warn("加载按钮尺寸失败: {}, 使用默认尺寸40", e.what());
        m_toggleButton->setFixedHeight(40);
    }
    
    connect(m_toggleButton, SIGNAL(clicked()), this, SLOT(toggleSidebar()));
    m_buttons.append(m_toggleButton);

    // 主布局设置
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);  // 无外边距
    m_mainLayout->setSpacing(0);                   // 无组件间距

    // 按钮容器布局
    m_buttonLayout = new QVBoxLayout();
    m_buttonLayout->setContentsMargins(0, 0, 0, 0);
    m_buttonLayout->setSpacing(0);
    
    m_buttonContainer = new BaseWidget();
    m_buttonContainer->setLayout(m_buttonLayout);

    // 组装布局结构
    m_mainLayout->addWidget(m_toggleButton);  // 顶部添加切换按钮
    m_mainLayout->addStretch();               // 添加伸缩空间
    m_mainLayout->addWidget(m_buttonContainer); // 底部添加按钮容器

    // 动画效果设置
    m_animation = new QPropertyAnimation(this, "geometry");
    m_animation->setDuration(200);  // 200毫秒动画时长
    m_animation->setEasingCurve(QEasingCurve::InOutQuad);  // 平滑曲线
    
    // 动画结束回调
    connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
        if (!m_isExpanded) {
            updateButtonStyles();  // 收起时更新按钮样式
        }
        spdlog::debug("侧边栏动画完成，当前宽度: {}", width());
    });
}

/**
 * @brief 根据展开状态更新按钮样式
 */
void ui_sidebar::updateButtonStyles()
{
    for (auto button : qAsConst(m_buttons)) {
        if (button) {
            button->hideText(!m_isExpanded);  // 收起时隐藏文字
        }
    }
}

} // namespace beiklive