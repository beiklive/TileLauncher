
#include "ui_button.h"
#include <QPainter>
#include <QStyleOption>

Win10MenuButton::Win10MenuButton(QWidget *parent)
    : QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor);
    setFlat(true);
    setStyleSheet("text-align: left; padding-left: 15px; border: none;");
    
    m_colorAnimation = new QPropertyAnimation(this, "backgroundColor");
    m_colorAnimation->setDuration(150);
    m_colorAnimation->setEasingCurve(QEasingCurve::OutQuad);
}

void Win10MenuButton::setActive(bool active)
{
    m_isActive = active;
    if (active) {
        m_colorAnimation->stop();
        setBackgroundColor(m_activeColor);
    } else {
        setBackgroundColor(m_normalColor);
    }
    update();
}

void Win10MenuButton::setExpanded(bool expanded)
{
    m_isExpanded = expanded;
    if (expanded) {
        setText(this->toolTip());
    } else {
        setText("");
    }
    update();
}

QColor Win10MenuButton::backgroundColor() const
{
    return m_currentColor;
}

void Win10MenuButton::setBackgroundColor(const QColor &color)
{
    m_currentColor = color;
    update();
}

void Win10MenuButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    if (!m_isActive) {
        m_colorAnimation->stop();
        m_colorAnimation->setStartValue(m_currentColor);
        m_colorAnimation->setEndValue(m_hoverColor);
        m_colorAnimation->start();
    }
}

void Win10MenuButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    if (!m_isActive) {
        m_colorAnimation->stop();
        m_colorAnimation->setStartValue(m_currentColor);
        m_colorAnimation->setEndValue(m_normalColor);
        m_colorAnimation->start();
    }
}

void Win10MenuButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制背景
    painter.fillRect(rect(), m_currentColor);
    
    // 绘制图标
    if (!icon().isNull()) {
        QRect iconRect(10, (height() - 24) / 2, 24, 24);
        icon().paint(&painter, iconRect);
    }
    
    // 绘制文本（展开状态下）
    if (m_isExpanded && !text().isEmpty()) {
        QRect textRect(45, 0, width() - 50, height());
        painter.setPen(palette().windowText().color());
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
    }
    
    // 绘制选中状态指示器
    if (m_isActive) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0, 120, 215)); // Win10主题色
        painter.drawRect(0, 0, 3, height());
    }
}