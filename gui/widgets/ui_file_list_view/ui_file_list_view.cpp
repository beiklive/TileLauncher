#include "ui_file_list_view.h"

beiklive::Ui_File_List_View::Ui_File_List_View(QWidget *parent)
{
    THEME_NAME(this, "FileListView")

    setFixedWidth(250);
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

    scrollContent = new QFrame(scrollArea);
    THEME_NAME(scrollContent, "FileListViewContent")
    scroll_layout = new QVBoxLayout(scrollContent);
    scroll_layout->setContentsMargins(0, 0, 0, 0);
    scroll_layout->setSpacing(0);

    // 设置内容控件的最小高度，确保滚动条出现

    scrollArea->setWidget(scrollContent);

    // for (int i = 0; i < 20; i++) {
    //     createButton("测试按钮" + QString::number(i), "/Users/beiklive/Applications/Balatro.app", ButtonMode::BM_FILE);
    // }
    _init_root_list();
    main_layout->addWidget(scrollArea);
}

void beiklive::Ui_File_List_View::_init_root_list()
{
    std::string root_path = globalSettings["listmenu"]["listPath"].get<std::string>();
    // json _root_list = get_directory_structure(root_path);
    json _root_list = get_sorted_directory_structure(root_path);

    show_suffixed = globalSettings["listmenu"]["showsuffix"].get<bool>();

    for (auto &[key, value] : _root_list.items())
    {
        if (value.size() > 0)
        {
            createButton(
                    scroll_layout,
                    key.c_str(),
                    "",
                    ButtonMode::BM_INDEX);
            // 遍历当前键对应的数组
            for (auto &item : value)
            {
                std::string name = item["name"].get<std::string>();
                if (item["type"].get<std::string>() == "file")
                {
                    if (!show_suffixed)
                    {
                        name = removeFileExtension(name);
                    }
                }
                createButton(
                    scroll_layout,
                    name.c_str(),
                    item["path"].get<std::string>().c_str(),
                    BtnType(item["type"].get<std::string>()));
            }
        }
    }

    // for (auto& item : _root_list["list"]) {
    //     std::string name = item["name"].get<std::string>();
    //     if (item["type"].get<std::string>() == "file") {
    //         if(!show_suffixed)
    //         {
    //             name = removeFileExtension(name);
    //         }
    //     }
    //         createButton(
    //             scroll_layout,
    //             name.c_str(),
    //         item["path"].get<std::string>().c_str(),
    //         BtnType(item["type"].get<std::string>()));
    // }
}

ButtonMode beiklive::Ui_File_List_View::BtnType(std::string type)
{
    if (type == "file")
    {
        return ButtonMode::BM_FILE;
    }
    else if (type == "folder")
    {
        return ButtonMode::BM_FOLDER;
    }
    else if (type == "index")
    {
        return ButtonMode::BM_INDEX;
    }
    return ButtonMode::BM_NONE;
}

QString beiklive::Ui_File_List_View::typeName(ButtonMode mode)
{
    switch (mode)
    {
    case ButtonMode::BM_FILE:
        return "file";
    case ButtonMode::BM_FOLDER:
        return "folder";
    case ButtonMode::BM_INDEX:
        return "index";
    default:
        return "none";
    }
}

void beiklive::Ui_File_List_View::createButton(QVBoxLayout *layout, const QString &name, const QString &path, ButtonMode mode)
{
    beiklive::Ui_List_Button *btn = new beiklive::Ui_List_Button(
        scrollArea,
        mode,
        name,
        path);
    layout->addWidget(btn);
    // if(mode == ButtonMode::BM_FOLDER)
    // {
    //     QVBoxLayout *btn_layout = new QVBoxLayout(layout->parentWidget());
    //     layout->addLayout(btn_layout);
    // }
    /*
    TODO:
    1. 按钮点击事件, 打开文件或文件夹 打开文件就调用默认程序打开 打开文件夹就创建新的列表放到样式中
    2. 修改addButton函数，增加参数，传入布局指针 done
    3. 修改创建逻辑，先生成索引表再分类生成，


    */

    button_count++;
    heightall += btn->height() + 5;
    scrollContent->setMinimumHeight(heightall);
    scrollContent->setMaximumHeight(heightall);
    buttons.append(btn);
    btn->setProperty("path", QVariant(path));
    btn->setProperty("type", QVariant(mode));
    btn->setProperty("uuid", generateUuid());
}