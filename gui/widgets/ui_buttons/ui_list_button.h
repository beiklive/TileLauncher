// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-20
#ifndef _INCLUDE_UI_LIST_BUTTON_H_
#define _INCLUDE_UI_LIST_BUTTON_H_

#include "global.hpp"
#include <iostream>

#include <QPushButton>
#include <QWidget>
#include <QEnterEvent>
#include <QMouseEvent>
#include <QCursor>
#include <QEvent>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QFileIconProvider> // 获取图标
#include <QLineEdit>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QMimeDatabase>
#include <QMimeType>
#include <QStyle>
#include <QApplication>

namespace beiklive
{


    class Ui_List_Button : public QPushButton
    {
        Q_OBJECT
    public:
        ~Ui_List_Button() = default;
        Ui_List_Button(
            QWidget *parent = nullptr,
            ButtonMode mode = ButtonMode::BM_NONE,
            QString name = "",
            QString file_path = "",
            QString icon_path = "");
        QIcon getFileIcon(const QString &filePath);
        
        void FolderExpand(bool expand);
        // Add member functions here
    protected:
        void paintEvent(QPaintEvent *event) override;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        void enterEvent(QEnterEvent *event) override;
#else
        void enterEvent(QEvent *event) override;
#endif
        void leaveEvent(QEvent *event) override;
        // void mouseReleaseEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        void iconPaint(QPainter *painter, const QIcon &icon, const QRect &rect);

        void _init_ui();
        void _flush_rect();

        // Add member variables here
        ButtonMode mode_;
        QString name_;
        QString file_path_;
        QString icon_path_;
        bool is_hover_;
        bool is_pressed_;
        bool is_folder_expand_;
        //
        int m_height;
        int m_textheight;
        int m_contentHeight;
        QIcon m_icon;
        QRect m_iconRect;
        QRect m_textRect;
        QRect m_indexRect;

        std::string m_TextColor;
        std::string m_NormalColor;
        std::string m_HoverColor;
        std::string m_PressedColor;
    };

} // namespace beiklive

#endif