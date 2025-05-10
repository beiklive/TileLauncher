// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-10
#ifndef _INCLUDE_BASEWIDGET_H_
#define _INCLUDE_BASEWIDGET_H_

#include "global.hpp"
#include <QWidget>
namespace beiklive {



class BaseWidget : public QWidget {
public:
    BaseWidget();
    ~BaseWidget() = default;
    // Add member functions here
    void setupStlye();
private:
    // Add member variables here
};

} // namespace beiklive

#endif // _INCLUDE_BASEWIDGET_H_