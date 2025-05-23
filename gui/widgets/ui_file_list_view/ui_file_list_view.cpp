#include "ui_file_list_view.h"

beiklive::Ui_File_List_View::Ui_File_List_View(QWidget *parent)
{
    THEME_NAME(this, "FileListView")
    show_suffixed = globalSettings["listmenu"]["showsuffix"].get<bool>();
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
    scroll_layout->setProperty("uuid", QVariant(generateUuid()));
    layout_list.append(scroll_layout);

    _init_root_list();
    scroll_layout->addStretch();
    main_layout->addWidget(scrollArea);
}

void beiklive::Ui_File_List_View::_init_root_list()
{
    if (IS_WINDOWS) {
        // Windows 特有实现
        std::string root_path = globalSettings["listmenu"]["winPath"].get<std::string>();
        _init_file_list(scroll_layout, root_path, true);
    } 
    else if (IS_MACOS) {
        // macOS 特有实现
        std::string root_path = globalSettings["listmenu"]["macPath"].get<std::string>();
        _init_file_list(scroll_layout, root_path, true);
    }
}

void beiklive::Ui_File_List_View::_init_file_list(QVBoxLayout *layout, std::string path, bool is_root)
{
    std::string root_path = path;
    json _root_list = get_sorted_directory_structure(root_path);

    for (auto &[key, value] : _root_list.items())
    {
        if (value.size() > 0)
        {
            if (is_root)
            {
                createButton(
                    layout,
                    key.c_str(),
                    "",
                    ButtonMode::BM_INDEX);
            }

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
                    layout,
                    name.c_str(),
                    item["path"].get<std::string>().c_str(),
                    BtnType(item["type"].get<std::string>()));
            }
        }
    }
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
    // 创建按钮并检查是否成功
    beiklive::Ui_List_Button *btn = new beiklive::Ui_List_Button(
        scrollArea,
        mode,
        name,
        path);
    
    if (!btn) {
        spdlog::error("Failed to create button: {}", name.toStdString());
        return;
    }

    // 添加按钮到布局
    layout->addWidget(btn);

    // 更新按钮计数和高度
    button_count++;
    buttons.append(btn);
    heightall = btn->height() * buttons.size();
    scrollContent->setMinimumHeight(heightall);
    scrollContent->setMaximumHeight(heightall);

    // 设置按钮属性
    btn->setProperty("path", QVariant(path));
    btn->setProperty("type", QVariant(static_cast<int>(mode)));
    btn->setProperty("uuid", QVariant(generateUuid()));
    btn->setProperty("parentlayoutuid", QVariant(layout->property("uuid")));

    // 非索引按钮设置点击事件
    if (mode != ButtonMode::BM_INDEX)
    {
        connect(btn, &QPushButton::clicked, [=, btn = btn]() {
            QString path = btn->property("path").toString();
            ButtonMode mode = ButtonMode(btn->property("type").toInt());
            QString uuid = btn->property("uuid").toString();
            
            spdlog::debug("Button clicked: {} {} {}",
                          path.toStdString(),
                          typeName(mode).toStdString(),
                          uuid.toStdString());

            if (mode == ButtonMode::BM_FILE)
            {
                // 文件按钮点击处理
                // QDesktopServices::openUrl(QUrl::fromLocalFile(path));

                openFileWithDefaultProgram(path);
            }
            else if (mode == ButtonMode::BM_FOLDER)
            {
                // 文件夹按钮点击处理
                bool is_expanded = btn->isFolderExpanded();
                btn->FolderExpand(!is_expanded);

                QVariant parent_layout_uid = btn->property("parentlayoutuid");
                spdlog::debug("parent_layout_uid: {}", parent_layout_uid.toString().toStdString());

                // 查找父布局
                QVBoxLayout *parent_layout = nullptr;
                for (QVBoxLayout *layout : layout_list)
                {
                    if (layout->property("uuid") == parent_layout_uid)
                    {
                        parent_layout = layout;
                        break;
                    }
                }

                if (!parent_layout)
                {
                    spdlog::error("parent_layout is null");
                    return;
                }

                if (is_expanded)
                {
                    // 折叠动画
                    QVariant son_layout_uid = btn->property("sonlayoutuid");
                    if (son_layout_uid.isValid())
                    {
                        // 查找包含子布局的容器widget
                        QWidget* container = nullptr;
                        for (int i = 0; i < parent_layout->count(); ++i)
                        {
                            QLayoutItem* item = parent_layout->itemAt(i);
                            if (item && item->widget())
                            {
                                QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(item->widget()->layout());
                                if (layout && layout->property("uuid") == son_layout_uid)
                                {
                                    container = item->widget();
                                    break;
                                }
                            }
                        }

                        if (container)
                        {
                            QVBoxLayout* son_layout = qobject_cast<QVBoxLayout*>(container->layout());
                            if (son_layout)
                            {
                                // 删除子布局中的按钮
                                for (auto btnIt = buttons.begin(); btnIt != buttons.end(); )
                                {
                                    if ((*btnIt)->property("parentlayoutuid") == son_layout_uid)
                                    {
                                        (*btnIt)->deleteLater();
                                        btnIt = buttons.erase(btnIt);
                                    }
                                    else
                                    {
                                        ++btnIt;
                                    }
                                }
                                
                                // 清理布局项
                                QLayoutItem *item;
                                while ((item = son_layout->takeAt(0)) != nullptr)
                                {
                                    if (QWidget *widget = item->widget())
                                    {
                                        widget->deleteLater();
                                    }
                                    delete item;
                                }
                                
                                parent_layout->removeWidget(container);
                                layout_list.removeOne(son_layout);
                                container->deleteLater();
                            }
                            
                            // 更新总高度
                            heightall = buttons.empty() ? 0 : buttons[0]->height() * buttons.size();
                            scrollContent->setMinimumHeight(heightall);
                            scrollContent->setMaximumHeight(heightall);
                        }
                    }
                }
                else
                {
                    // 展开动画
                    QVBoxLayout *new_layout = new QVBoxLayout();
                    new_layout->setProperty("uuid", QVariant(generateUuid()));
                    new_layout->setContentsMargins(5, 0, 0, 0);
                    new_layout->setSpacing(0);
                    
                    // 创建一个容器widget来包含新布局，便于动画
                    QWidget* container = new QWidget();
                    container->setLayout(new_layout);
                    container->setMaximumHeight(0); // 初始高度为0
                    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
                    
                    int index = parent_layout->indexOf(btn);
                    parent_layout->insertWidget(index + 1, container); // 插入widget而不是直接插入布局
                    layout_list.append(new_layout);
                    
                    // 初始化子目录
                    _init_file_list(new_layout, path.toStdString(), false);
                    
                    // 保存子布局引用
                    btn->setProperty("sonlayoutuid", QVariant(new_layout->property("uuid")));
                    
                    // 计算子布局的理想高度
                    container->show(); // 必须先显示才能计算正确高度
                    int targetHeight = container->sizeHint().height();
                    
                    // 创建展开动画
                    QPropertyAnimation* animation = new QPropertyAnimation(container, "maximumHeight");
                    animation->setDuration(300); // 动画持续时间300ms
                    animation->setStartValue(0);
                    animation->setEndValue(targetHeight);
                    animation->setEasingCurve(QEasingCurve::OutQuad); // 平滑的缓动曲线
                    
                    // 动画完成后设置固定高度
                    connect(animation, &QPropertyAnimation::finished, [container, targetHeight]() {
                        container->setMaximumHeight(QWIDGETSIZE_MAX); // 恢复最大高度限制
                        container->setMinimumHeight(targetHeight); // 设置最小高度
                    });
                    
                    animation->start(QAbstractAnimation::DeleteWhenStopped); // 动画完成后自动删除
                }
            }
        });
    }
}