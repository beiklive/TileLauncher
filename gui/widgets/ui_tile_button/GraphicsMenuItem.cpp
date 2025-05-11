// GraphicsMenuItem.cpp
#include "GraphicsMenuItem.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

GraphicsMenuItem::GraphicsMenuItem(const QString& text, QGraphicsItem* parent) 
    : QGraphicsObject(parent), m_text(text) {
    setAcceptHoverEvents(true);
}

QRectF GraphicsMenuItem::boundingRect() const {
    return QRectF(0, 0, 120, 30);
}

void GraphicsMenuItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(m_hovered ? QColor(70, 130, 200) : QColor(240, 240, 240));
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(boundingRect(), 5, 5);
    
    painter->setPen(m_hovered ? Qt::white : Qt::black);
    painter->drawText(boundingRect(), Qt::AlignCenter, m_text);
}

void GraphicsMenuItem::mousePressEvent(QGraphicsSceneMouseEvent*) {
    emit clicked();
}

void GraphicsMenuItem::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
    m_hovered = true;
    update();
}

void GraphicsMenuItem::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
    m_hovered = false;
    update();
}