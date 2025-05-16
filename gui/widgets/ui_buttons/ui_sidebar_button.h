// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-16
#ifndef _INCLUDE_UI_SIDEBAR_BUTTON_H_
#define _INCLUDE_UI_SIDEBAR_BUTTON_H_

#include "global.hpp"
#include <QLabel>
#include <QPushButton>
namespace beiklive {

class Ui_Sidebar_Button : public QPushButton {
    Q_OBJECT
public:
    Ui_Sidebar_Button(QWidget *parent = nullptr, std::string icon_path = ICON_DEFAULT, std::string text = "");
    ~Ui_Sidebar_Button() = default;

    // Add member functions here
    void hide_text(bool hide);
    void set_icon(std::string icon_path);
    void set_text(std::string text);

private:
    void _setup_ui();
    void _init_icon(std::string icon_path);
    void _init_text(std::string text);

    // Add member variables here
    QLabel *m_icon_label;
    QLabel *m_text_label;

    bool m_hide_text{true};

};

} // namespace beiklive

#endif // _INCLUDE_UI_SIDEBAR_BUTTON_H_