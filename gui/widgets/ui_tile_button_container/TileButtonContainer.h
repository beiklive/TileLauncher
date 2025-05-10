#pragma once
#include <QGraphicsRectItem>
#include <QVector>

class TileButtonItem;

enum LayoutDirection
{
    Vertical,
    Horizontal
};

class TileButtonContainer : public QGraphicsRectItem
{
public:
    TileButtonContainer(QGraphicsItem *parent = nullptr);

    void addButton(TileButtonItem *button);
    void setLayoutDirection(LayoutDirection dir);
    void arrangeButtons();

private:
    QVector<TileButtonItem *> m_buttons;
    LayoutDirection m_layoutDirection;
};