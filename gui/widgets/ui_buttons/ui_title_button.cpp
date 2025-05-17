#include "ui_title_button.h"

beiklive::Ui_Title_Button::Ui_Title_Button(QWidget *parent, std::string icon_path)
{
    THEME_NAME(this, "TitleButton")

    m_button_size = globalSettings["titlebar"]["button_size"].get<int>();
    m_icon_size = globalSettings["titlebar"]["icon_size"].get<int>();
    m_set_icon_color = QColor(globalSettings["titlebar"]["icon_color"].get<std::string>().c_str());
    m_icon_path = icon_path;

    // setFixedSize(m_button_size, m_button_size);
    setCursor(Qt::PointingHandCursor);
}

void beiklive::Ui_Title_Button::setIconPath(std::string icon_path)
{
    m_icon_path = icon_path;
}

void beiklive::Ui_Title_Button::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
painter.setRenderHint(QPainter::Antialiasing, true);  // 开启抗锯齿
painter.setRenderHint(QPainter::SmoothPixmapTransform, true);  // 平滑缩放

    QRect rect(2, 2, m_button_size-4, m_button_size-4);
    QRect rect_icon(0, 0, m_button_size, m_button_size);
    painter.setBrush(QBrush(m_is_hover? QColor("#438c8c8c") : QColor(0, 0, 0, 0)));
    painter.drawRoundedRect(rect, 3, 3);
    iconPaint(&painter, m_icon_path.c_str(), rect_icon, m_set_icon_color);
    painter.end();
}

void beiklive::Ui_Title_Button::enterEvent(QEvent *event)
{
    m_is_hover = true;
    update();
}

void beiklive::Ui_Title_Button::leaveEvent(QEvent *event)
{
    m_is_hover = false;
    update();

}

void beiklive::Ui_Title_Button::iconPaint(QPainter *qp, const QString &imagePath, const QRect &rect, const QColor &color)
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
        (rect.width() - m_icon_size) / 2,
        (rect.height() - m_icon_size) / 2,
        m_icon_size,
        m_icon_size,
        icon
    );
}