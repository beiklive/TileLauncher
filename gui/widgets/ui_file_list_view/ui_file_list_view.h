// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-18
#ifndef _INCLUDE_UI_FILE_LIST_VIEW_H_
#define _INCLUDE_UI_FILE_LIST_VIEW_H_

#include "global.hpp"
#include <QScrollArea>
namespace beiklive {

class Ui_File_List_View : public QFrame {
public:
    Ui_File_List_View(QWidget *parent = nullptr);
    ~Ui_File_List_View() = default;

    // Add member functions here

private:
    void _setup_ui();



    // Add member variables here
    QVBoxLayout *main_layout;
    QScrollArea *scrollArea;

};

} // namespace beiklive

#endif // _INCLUDE_UI_FILE_LIST_VIEW_H_