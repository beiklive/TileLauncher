#pragma once
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QApplication>
#include <QGraphicsView>
#include <spdlog/spdlog.h>
#include "GraphicsMenuItem.h"
class LiveTile : public QGraphicsObject {
    Q_OBJECT
public:
    LiveTile(qreal x, qreal y, qreal size, const QColor& color, int id, QGraphicsItem* parent = nullptr);
    
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    int getID();
    void setColor(const QColor& color); // 新增方法
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

    void handleMenuAction(const QString& action);
private:
    void showContextMenu(const QPointF& pos);
private:
    qreal m_size;
    QColor m_color;
    QRectF m_rect;
    int m_id;
};