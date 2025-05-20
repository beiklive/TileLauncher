// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-20
#ifndef _INCLUDE_UI_LIST_BUTTON_H_
#define _INCLUDE_UI_LIST_BUTTON_H_

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
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QInputDialog>
#include <QFileIconProvider>
#include <QMimeDatabase>
#include <QMimeType>
#include <QStyle>
#include <QApplication>
/*
列表按钮， 
1. 按钮模式
2. 文件夹模式  点开展开按钮，显示文件按钮
3. 图标模式  显示图标，显示文件名
4. 索引模式  显示拼音首字母

*/




namespace beiklive {
    enum ButtonMode {
        NONE,
        FILE,
        FOLDER,
        INDEX
    };
    
class Ui_List_Button : public QPushButton {
    Q_OBJECT
public:
    ~Ui_List_Button() = default;
    Ui_List_Button(
        QWidget *parent = nullptr, 
        ButtonMode mode = ButtonMode::NONE, 
        QString name = "", 
        QString file_path = "",  
        QString icon_path = ""
    );
QIcon getFileIcon(const QString &filePath);
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

private:
    void _init_ui();


    // Add member variables here
    ButtonMode mode_;
    QString name_;
    QString file_path_;
    QString icon_path_;
    bool is_hover_;
    bool is_pressed_;
};

} // namespace beiklive



class FileSelectorWindow : public QWidget {
    Q_OBJECT
public:
    FileSelectorWindow(QWidget *parent = nullptr) : QWidget(parent) {
        // 主布局
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        
        // 添加文件按钮
        QPushButton *addFileBtn = new QPushButton("添加文件", this);
        connect(addFileBtn, &QPushButton::clicked, this, &FileSelectorWindow::addFile);
        
        // 添加文件夹按钮
        QPushButton *addFolderBtn = new QPushButton("添加文件夹", this);
        connect(addFolderBtn, &QPushButton::clicked, this, &FileSelectorWindow::addFolder);
        
        // 添加索引按钮
        QPushButton *addIndexBtn = new QPushButton("添加索引项", this);
        connect(addIndexBtn, &QPushButton::clicked, this, &FileSelectorWindow::addIndexItem);
        
        // 按钮容器布局
        buttonsLayout = new QVBoxLayout();
        
        // 添加到主布局
        mainLayout->addWidget(addFileBtn);
        mainLayout->addWidget(addFolderBtn);
        mainLayout->addWidget(addIndexBtn);
        mainLayout->addLayout(buttonsLayout);
        
        // 添加一个拉伸因子，使按钮保持在顶部
        mainLayout->addStretch();
    }

private slots:
    void addFile() {
        QString filePath = QFileDialog::getOpenFileName(
            this, 
            "选择文件", 
            QDir::homePath(),
            "所有文件 (*.*)"
        );
        
        if (!filePath.isEmpty()) {
            QFileInfo fileInfo(filePath);
            createButton(fileInfo.fileName(), filePath, beiklive::ButtonMode::FILE);
        }
    }
    
    void addFolder() {
        QString dirPath = QFileDialog::getExistingDirectory(
            this,
            "选择文件夹",
            QDir::homePath()
        );
        
        if (!dirPath.isEmpty()) {
            QFileInfo dirInfo(dirPath);
            createButton(dirInfo.fileName(), dirPath, beiklive::ButtonMode::FOLDER);
        }
    }
    
    void addIndexItem() {
        bool ok;
        QString text = QInputDialog::getText(
            this,
            "添加索引项",
            "输入名称:",
            QLineEdit::Normal,
            "",
            &ok
        );
        
        if (ok && !text.isEmpty()) {
            createButton(text, "", beiklive::ButtonMode::INDEX);
        }
    }
    
private:
    void createButton(const QString &name, const QString &path, beiklive::ButtonMode mode) {
        beiklive::Ui_List_Button *btn = new beiklive::Ui_List_Button(
            this, 
            mode, 
            name, 
            path
        );
        
        // 连接点击信号
        connect(btn, &QPushButton::clicked, [btn, mode]() {
            QString message;
            switch(mode) {
                case beiklive::ButtonMode::FILE:
                    message = QString("打开文件: %1").arg(btn->property("file_path").toString());
                    break;
                case beiklive::ButtonMode::FOLDER:
                    message = QString("打开文件夹: %1").arg(btn->property("file_path").toString());
                    break;
                case beiklive::ButtonMode::INDEX:
                    message = QString("索引项: %1").arg(btn->text());
                    break;
                default:
                    message = QString("按钮: %1").arg(btn->text());
            }
            QMessageBox::information(nullptr, "信息", message);
        });
        
        // 添加到布局
        buttonsLayout->addWidget(btn);
    }

private:
    QVBoxLayout *buttonsLayout;
};




#endif // _INCLUDE_UI_LIST_BUTTON_H_