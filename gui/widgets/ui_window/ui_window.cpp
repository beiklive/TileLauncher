#include "ui_window.h"
#include <format>
#include <string>
beiklive::Ui_Window::Ui_Window(QWidget *parent) : QWidget(parent)
{
    this->resize(800, 600);
    functionsSetup();
    styleSetup();
}

void beiklive::Ui_Window::addTitleBarToWidget(QWidget *widget, const QString &title)
{

    // 创建自定义标题栏（继承自QWidget）
    titleBar = new TitleBar(widget);
    titleBar->setObjectName("titleBar");
    titleBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titleBar->setFixedHeight(globalSettings["window"]["title_bar_height"].get<int>());

    // 标题栏布局
    QHBoxLayout *titleLayout = new QHBoxLayout(titleBar);
    titleLayout->setContentsMargins(5, 0, 5, 0);
    titleLayout->setSpacing(5);

    // 标题标签
    QLabel *titleLabel = new QLabel(title.isEmpty() ? widget->windowTitle() : title, titleBar);
    titleLabel->setObjectName("titleLabel");
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 按钮
    QPushButton *minimizeButton = new QPushButton(titleBar);
    minimizeButton->setObjectName("minimizeButton");
    minimizeButton->setIcon(QIcon("assets/icons/icon_minimize.svg"));
    minimizeButton->setFixedSize(22, 22);
    minimizeButton->setFlat(true);

    QPushButton *maximizeButton = new QPushButton(titleBar);
    maximizeButton->setObjectName("maximizeButton");
    maximizeButton->setIcon(QIcon("assets/icons/icon_maximize.svg"));
    maximizeButton->setFixedSize(22, 22);
    maximizeButton->setFlat(true);

    QPushButton *closeButton = new QPushButton(titleBar);
    closeButton->setObjectName("closeButton");
    closeButton->setIcon(QIcon("assets/icons/icon_close.svg"));
    closeButton->setFixedSize(22, 22);
    closeButton->setFlat(true);

    // 添加控件到布局
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(minimizeButton);
    titleLayout->addWidget(maximizeButton);
    titleLayout->addWidget(closeButton);

    // 将标题栏插入到主布局的顶部
    windowlayout->addWidget(titleBar);

    // 连接按钮信号
    QObject::connect(minimizeButton, &QPushButton::clicked, widget, &QWidget::showMinimized);
    QObject::connect(closeButton, &QPushButton::clicked, widget, &QWidget::close);

    QObject::connect(maximizeButton, &QPushButton::clicked, [widget, this, maximizeButton]()
                     {
        if (widget->isMaximized()) {
            widget->showNormal();
            windowlayout->setContentsMargins(10, 10, 10, 10);
        } else {
            widget->showMaximized();
            windowlayout->setContentsMargins(0, 0, 0, 0);
        } });

    // 设置样式（可选）
    titleBar->setStyleSheet(R"(
        #titleBar {
            background-color: #181818;
            border-top-left-radius: 4px;
            border-top-right-radius: 4px;
        }
        #titleLabel {
            color: white;
            font-weight: bold;
        }
        #closeButton, #minimizeButton, #maximizeButton {
            background: transparent;
            color: white;
        }
        #closeButton:hover, #minimizeButton:hover, #maximizeButton:hover {
            background: #555;
            border-radius: 3px;
        }
            
    )");
}

void beiklive::Ui_Window::functionsSetup()
{
    m_window = new QWidget(this);
    m_window->setObjectName("app_ui_window");
    windowlayout = new QVBoxLayout();
    windowlayout->setSpacing(0);
    if (globalSettings["window"]["custom_window"])
    {
        addTitleBarToWidget(this, "我的窗口标题");
        m_helper = new FramelessWindowHelper(this);
        m_helper->setResizable(true);
        windowlayout->setContentsMargins(10, 10, 10, 10);
    }
    else
    {
        windowlayout->setContentsMargins(0, 0, 0, 0);
    }
    windowlayout->addWidget(m_window);
    this->setLayout(windowlayout);

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
        font-family: {};
    }}
    )",
                                         bg_color, radius, border_width, border_color, text_color, text_font);
    spdlog::debug("Stylesheet: {}", styleSheet);
    m_window->setStyleSheet(styleSheet.c_str());


    // add shadow effect
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setXOffset(0);
    shadow->setYOffset(0);
    shadow->setColor(QColor(0, 0, 0, 160));
    this->setGraphicsEffect(shadow);
}

void beiklive::Ui_Window::hideTitleBar()
{
   titleBar->hide();
}

QWidget *beiklive::Ui_Window::getWindow() const
{
    return m_window;
}

void beiklive::Ui_Window::resizeEvent(QResizeEvent *event)
{
    if (globalSettings["window"]["custom_window"] && m_helper)
    {
        m_helper->resizeGrips();
    }
}

void beiklive::Ui_Window::mouseMoveEvent(QMouseEvent *event)
{
}

void beiklive::Ui_Window::paintEvent(QPaintEvent *event)
{
}

beiklive::TitleBar::TitleBar(QWidget *parent) : QWidget(parent), m_parentWidget(parent)
{
    setMouseTracking(true);
}

void beiklive::TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        m_dragPosition = event->globalPosition().toPoint() - m_parentWidget->frameGeometry().topLeft();
#else
        m_dragPosition = event->globalPos() - m_parentWidget->frameGeometry().topLeft();
#endif
        event->accept();
    }
}
void beiklive::TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (event->buttons() & Qt::LeftButton)
        {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
            m_parentWidget->move(event->globalPosition().toPoint() - m_dragPosition);
#else
            m_parentWidget->move(event->globalPos() - m_dragPosition);
#endif
            event->accept();
        }
    }
}