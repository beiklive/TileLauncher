#include "ui_file_list_view.h"

beiklive::Ui_File_List_View::Ui_File_List_View(QWidget *parent)
{
    THEME_NAME(this, "FileListView")

    setFixedWidth(200);
    _setup_ui();
    spdlog::info("FileListView created");
}

void beiklive::Ui_File_List_View::_setup_ui()
{
    main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);
    setLayout(main_layout);

    scrollArea = new QScrollArea(this);

    // 插入按钮到滚动区域
    // scrollArea->setWidgetResizable(true);
    // scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));
    scrollArea->setWidget(new QPushButton(scrollArea));


    main_layout->addWidget(scrollArea);
}