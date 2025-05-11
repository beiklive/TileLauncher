// GraphicsMenuItem.h
#pragma once
#include <QGraphicsObject>
#include <QPropertyAnimation>

class GraphicsMenuItem : public QGraphicsObject {
    Q_OBJECT
public:
    explicit GraphicsMenuItem(const QString& text, QGraphicsItem* parent = nullptr);
    
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    
signals:
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    QString m_text;
    bool m_hovered = false;
};