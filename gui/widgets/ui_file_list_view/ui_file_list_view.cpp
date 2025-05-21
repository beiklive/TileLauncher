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
    THEME_NAME(scrollArea, "FileListViewScrollArea")
    scrollArea->setWidgetResizable(true); // 允许自动调整大小
    scrollArea->setFrameShape(QFrame::NoFrame);

    QFrame *scrollContent = new QFrame(scrollArea);
    THEME_NAME(scrollContent, "FileListViewContent")
    scroll_layout = new QVBoxLayout(scrollContent);
    scroll_layout->setContentsMargins(0, 0, 0, 0);
    scroll_layout->setSpacing(0);

    // 设置内容控件的最小高度，确保滚动条出现
    
    scrollArea->setWidget(scrollContent);
    
    for (int i = 0; i < 20; i++) {
        createButton("测试按钮" + QString::number(i), "/Users/beiklive/Applications/Balatro.app", ButtonMode::BM_FILE);
    }
    
    scrollContent->setMinimumHeight(heightall); // 例如：2000px
    main_layout->addWidget(scrollArea);
}

void beiklive::Ui_File_List_View::createButton(const QString &name, const QString &path, ButtonMode mode)
    {
        beiklive::Ui_List_Button *btn = new beiklive::Ui_List_Button(
            scrollArea,
            mode,
            name,
            path);
        scroll_layout->addWidget(btn);
        button_count++;
        heightall += btn->height()+5;
    }