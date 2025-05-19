#include "ui_sidebar_button.h"


beiklive::Ui_Sidebar_Button::Ui_Sidebar_Button(QWidget *parent, std::string icon_path, std::string text)
{
    THEME_NAME(this, "sidebarButton")
    m_expand_width = globalSettings["sidebar"]["sidebar_expand_width"].get<int>();
    m_normal_width = globalSettings["sidebar"]["sidebar_normal_width"].get<int>();
    m_set_icon_color = QColor(globalSettings["sidebar"]["icon_color"].get<std::string>().c_str());
    m_set_text_color = QColor(globalSettings["sidebar"]["text_color"].get<std::string>().c_str());

    m_icon_width = globalSettings["sidebar"]["icon_size"].get<int>();

    _init_icon(icon_path);
    _init_text(text);
    _setup_ui();
}

void beiklive::Ui_Sidebar_Button::hide_text(bool hide)
{
    m_hide_text = hide;

    update();
}

void beiklive::Ui_Sidebar_Button::set_icon(std::string icon_path)
{
    _init_icon(icon_path);
}

void beiklive::Ui_Sidebar_Button::set_text(std::string text)
{
    _init_text(text);
}

void beiklive::Ui_Sidebar_Button::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(this->font());

    QRect rect(4, 4, width()-8, height()-8);
    QRect rect_icon(0, 0, m_normal_width, height());
    QRect rect_text(m_normal_width, 0, m_expand_width - m_normal_width, height());
    if(m_is_hover)
    {
        painter.setBrush(QBrush(QColor("#438c8c8c")));

    }
    else
    {
        painter.setBrush(QBrush(QColor(0, 0, 0, 0)));
    }
    // 绘制透明背景
    painter.drawRoundedRect(rect, 3, 3);
    iconPaint(&painter, m_icon_path.c_str(), rect_icon, m_set_icon_color);
    painter.setPen(m_set_text_color);
    painter.drawText(rect_text, Qt::AlignVCenter, m_text.c_str());
    painter.end();
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
void beiklive::Ui_Sidebar_Button::enterEvent(QEnterEvent *event)
#else
void beiklive::Ui_Sidebar_Button::enterEvent(QEvent *event)
#endif
{
    m_is_hover = true;
    update();
}
void beiklive::Ui_Sidebar_Button::leaveEvent(QEvent *event)
{
    m_is_hover = false;
    update();
}
void beiklive::Ui_Sidebar_Button::mousePressEvent(QMouseEvent *event)
{
    emit clickedAtPosition(event->pos());  // 传递点击坐标（相对按钮）
    QPushButton::mousePressEvent(event);
}
void beiklive::Ui_Sidebar_Button::iconPaint(QPainter *qp, const QString &imagePath, const QRect &rect, const QColor &color)
{
    // 加载图标
    QPixmap icon(imagePath);
    
    // 创建临时 QPainter 来修改图标颜色
    QPainter painter(&icon);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(icon.rect(), color);
    painter.end();  // 结束对图标的绘制
    
    // 在主 QPainter 上绘制图标（居中）
    qp->drawPixmap(
        (rect.width() - m_icon_width) / 2,
        (rect.height() - m_icon_width) / 2,
        m_icon_width,
        m_icon_width,
        icon
    );
}
void beiklive::Ui_Sidebar_Button::_setup_ui()
{
    setCursor(Qt::PointingHandCursor);
    hide_text(true);
}

void beiklive::Ui_Sidebar_Button::_init_icon(std::string icon_path)
{
    m_icon_path = icon_path;
    update();
}

void beiklive::Ui_Sidebar_Button::_init_text(std::string text)
{
    m_text = text;
    update();
}

