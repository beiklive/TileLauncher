// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-17
#ifndef _INCLUDE_UI_TITLE_BAR_H_
#define _INCLUDE_UI_TITLE_BAR_H_

#include "global.hpp"
#include "widgets/ui_buttons/ui_title_button.h"
#include <QEnterEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QEvent>
#include <QLabel>
namespace beiklive {

class Ui_Title_Bar : public QWidget{
    Q_OBJECT
public:
    Ui_Title_Bar(QWidget *parent = nullptr, QWidget* app_parent=nullptr, std::string title_text = "Title Bar");
    ~Ui_Title_Bar() = default;
    // Add member functions here

    void set_title_text(std::string text);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void maximize_window();
    void restore_window();

private:
    void _init_ui();

    void maximize_restore();
    void update_maximize_icon();
    // Add member variables here

    int m_height;
    int m_margin;
    bool m_is_maximized = false;
    QSize m_old_size;

    std::string m_title_text;
    QWidget* m_parent;
    QWidget* m_app_parent;

    QLabel *title_label;
    Ui_Title_Button* m_btn_min;
    Ui_Title_Button* m_btn_max;
    Ui_Title_Button* m_btn_close;
};

} // namespace beiklive

#endif // _INCLUDE_UI_TITLE_BAR_H_