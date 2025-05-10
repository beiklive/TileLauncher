#include "TileButtonItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

TileButtonItem::TileButtonItem(const QString &label, const QColor &color, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_label(label),
      m_baseColor(color),
      m_currentColor(color),
      m_hovered(false)
{
    setAcceptHoverEvents(true);
}

QRectF TileButtonItem::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void TileButtonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);

    QColor fillColor = m_currentColor;
    if (m_hovered)
    {
        fillColor = fillColor.lighter(130); // hover effect
    }

    painter->setBrush(fillColor);
    painter->drawRoundedRect(boundingRect(), 10, 10);

    painter->setPen(Qt::white);
    painter->setFont(QFont("Segoe UI", 12, QFont::Bold));
    painter->drawText(boundingRect(), Qt::AlignCenter, m_label);
}

void TileButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Button clicked:" << m_label;
}

void TileButtonItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = true;
    update();
}

void TileButtonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    m_hovered = false;
    update();
}