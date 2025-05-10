#include "TileButtonContainer.h"
#include "ui_tile_button/TileButtonItem.h"

TileButtonContainer::TileButtonContainer(QGraphicsItem *parent)
    : QGraphicsRectItem(parent), m_layoutDirection(Vertical)
{
    setRect(0, 0, 400, 400);
    setBrush(Qt::transparent);
    setPen(Qt::NoPen);
}

void TileButtonContainer::addButton(TileButtonItem *button)
{
    m_buttons.append(button);
    button->setParentItem(this);
    arrangeButtons();
}

void TileButtonContainer::setLayoutDirection(LayoutDirection dir)
{
    m_layoutDirection = dir;
    arrangeButtons();
}

void TileButtonContainer::arrangeButtons()
{
    const int spacing = 10;
    int x = spacing, y = spacing;
    for (auto *btn : m_buttons)
    {
        btn->setPos(x, y);
        if (m_layoutDirection == Horizontal)
        {
            x += btn->boundingRect().width() + spacing;
        }
        else
        {
            y += btn->boundingRect().height() + spacing;
        }
    }
}