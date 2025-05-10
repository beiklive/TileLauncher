#pragma once
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneHoverEvent>

class TileButtonItem : public QGraphicsItem
{
public:
    TileButtonItem(const QString &label, const QColor &color, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QString m_label;
    QColor m_baseColor;
    QColor m_currentColor;
    bool m_hovered;
};