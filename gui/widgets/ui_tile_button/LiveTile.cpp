#include "LiveTile.h"
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QDebug>

LiveTile::LiveTile(qreal x, qreal y, qreal size, const QColor& color, int id, QGraphicsItem* parent)
    : QGraphicsObject(parent), m_size(size), m_color(color), m_rect(0, 0, size, size), m_id(id) {
    
    // 设置初始位置（通过setPos而非rect坐标）
    setPos(x, y);
    
    // 启用悬停和点击事件
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    
    // 配置阴影效果（无偏移+大模糊半径）
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(20);
    shadow->setOffset(0, 0);  // 关键修复：取消偏移
    shadow->setColor(QColor(0, 0, 0, 100));
    setGraphicsEffect(shadow);
    
    // 默认缩放锚点设为图形中心
    setTransformOriginPoint(m_rect.center());
}

QRectF LiveTile::boundingRect() const {
    // 扩大边界以包含阴影
    const qreal shadowPadding = 20;
    return m_rect.adjusted(-shadowPadding, -shadowPadding, 
                          shadowPadding, shadowPadding);
}

void LiveTile::paint(QPainter* painter, 
                    const QStyleOptionGraphicsItem*, 
                    QWidget*) {
    painter->setBrush(m_color);
    painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}
// 新增颜色设置方法
void LiveTile::setColor(const QColor& color) {
  m_color = color;
  update(); // 触发重绘
}
int LiveTile::getID()
{
    return m_id;
}

void LiveTile::hoverEnterEvent(QGraphicsSceneHoverEvent*) {
    // 仅当未放大时触发动画
    if (qFuzzyCompare(scale(), 1.0)) {
        QPropertyAnimation* anim = new QPropertyAnimation(this, "scale");
        anim->setDuration(200);
        anim->setEasingCurve(QEasingCurve::OutBack);
        anim->setStartValue(1.0);
        anim->setEndValue(0.7);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        // spdlog::info("Tile hovered id = {}",getID());
    }
}

void LiveTile::hoverLeaveEvent(QGraphicsSceneHoverEvent*) {
    QPropertyAnimation* anim = new QPropertyAnimation(this, "scale");
    anim->setDuration(200);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->setStartValue(scale());
    anim->setEndValue(1.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void LiveTile::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // 点击下沉效果
    QPropertyAnimation* pressAnim = new QPropertyAnimation(this, "scale");
    pressAnim->setDuration(100);
    pressAnim->setEasingCurve(QEasingCurve::OutQuad);
    pressAnim->setStartValue(scale());
    pressAnim->setEndValue(0.95);
    pressAnim->start(QAbstractAnimation::DeleteWhenStopped);

    QGraphicsObject::mousePressEvent(event);
}

void LiveTile::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    // 释放时恢复悬停状态
    QPropertyAnimation* releaseAnim = new QPropertyAnimation(this, "scale");
    releaseAnim->setDuration(100);
    releaseAnim->setEasingCurve(QEasingCurve::OutBack);
    releaseAnim->setStartValue(scale());
    releaseAnim->setEndValue(1.1);
    releaseAnim->start(QAbstractAnimation::DeleteWhenStopped);

    qDebug() << "Tile clicked at:" << event->pos();
    QGraphicsObject::mouseReleaseEvent(event);
}

void LiveTile::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
  showContextMenu(event->scenePos());
    event->accept();
}

void LiveTile::showContextMenu(const QPointF& pos) {
  QGraphicsRectItem* menuContainer = new QGraphicsRectItem(0, 0, 140, 120);
  menuContainer->setPos(pos);
  scene()->addItem(menuContainer);

  QStringList actions = {"复制颜色", "粘贴颜色", "删除", "更改颜色"};
  for (int i = 0; i < actions.size(); ++i) {
      GraphicsMenuItem* item = new GraphicsMenuItem(actions[i], menuContainer);
      item->setPos(10, 10 + i * 35);
      
      connect(item, &GraphicsMenuItem::clicked, 
             [this, action = actions[i], item]() {  // 显式捕获item
          handleMenuAction(action);
          item->scene()->removeItem(item->parentItem());
      });
  }
}

void LiveTile::handleMenuAction(const QString& action) {
  if (action == "删除") {
    scene()->removeItem(this);
  }
  if (action == "更改颜色") {
      setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
  }
  qDebug() << "Action:" << action;
}