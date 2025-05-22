// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-18
#ifndef _INCLUDE_UI_FILE_LIST_VIEW_H_
#define _INCLUDE_UI_FILE_LIST_VIEW_H_

#include "global.hpp"
#include "widgets/ui_buttons/ui_list_button.h"
#include <QScrollArea>
#include <QVector>
namespace beiklive
{

    class Ui_File_List_View : public QFrame
    {
    public:
        Ui_File_List_View(QWidget *parent = nullptr);
        ~Ui_File_List_View() = default;

        // Add member functions here
        void createButton(QVBoxLayout *layout, const QString &name, const QString &path, ButtonMode mode);

    private:
        void _setup_ui();
        void _init_root_list();

        ButtonMode BtnType(std::string type);
        QString typeName(ButtonMode mode);

        bool show_suffixed = true;
        int button_count = 0;
        int heightall = 0;
        // Add member variables here
        QVBoxLayout *main_layout;
        QScrollArea *scrollArea;
        QVBoxLayout *scroll_layout;
        QFrame *scrollContent;

        // 存储所有按钮
        QList<beiklive::Ui_List_Button *> buttons;
        QList<QVBoxLayout *> layout_list;
    };

} // namespace beiklive

#endif // _INCLUDE_UI_FILE_LIST_VIEW_H_