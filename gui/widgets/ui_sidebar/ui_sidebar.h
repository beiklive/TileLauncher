// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-16
#ifndef _INCLUDE_UI_SIDEBAR_H_
#define _INCLUDE_UI_SIDEBAR_H_

#include "global.hpp"
#include "widgets/ui_buttons/ui_sidebar_button.h"

#include <QPropertyAnimation>
#include <QVector>
namespace beiklive {

class Ui_Sidebar : public QWidget {
    // Q_OBJECT
public:
    Ui_Sidebar(QWidget *parent = nullptr);
    ~Ui_Sidebar()=default;
    // Add member functions here

    
private:
    void _startAnimation(); // 启动动画的函数
    void _onAnimationFinished(); // 动画完成时的回调槽
    void _init_ui();

    QPropertyAnimation *animation;



    // Add member variables here
    int m_width;
    int m_expand_width;
    int m_normal_width;
    int m_margin;
    bool m_is_expand;
    QVBoxLayout *m_layout;
    QVBoxLayout *m_button_layout;
    QVector<Ui_Sidebar_Button*> m_buttons;
};

} // namespace beiklive

#endif // _INCLUDE_UI_SIDEBAR_H_