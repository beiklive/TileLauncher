// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-15
#ifndef _INCLUDE_UI_GRIPITEM_H_
#define _INCLUDE_UI_GRIPITEM_H_

#include "global.hpp"
#include <QSizeGrip>
#include <QCursor>
namespace beiklive {

class Ui_GripItem : public QWidget {
public:
    Ui_GripItem(QWidget *parent = nullptr, WindowParts parts = WindowParts::NONE, bool hideColor = true);
    ~Ui_GripItem() = default;
    // Add member functions here
    void setGeo(int x, int y, int w, int h);
protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void InitUI();

    // Add member variables here
    WindowParts m_parts;
    QSizeGrip *m_grip;
    bool m_hideColor;
    QWidget *m_parent;
};

} // namespace beiklive

#endif // _INCLUDE_UI_GRIPITEM_H_