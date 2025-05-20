#include "ui_list_button.h"
#include <QPainter>
#include <QStyleOption>
#include <QFileIconProvider>
#include <QIcon>

namespace beiklive
{

    Ui_List_Button::Ui_List_Button(QWidget *parent, ButtonMode mode, QString name,
                                   QString file_path, QString icon_path)
        : QPushButton(parent),
          mode_(mode),
          name_(name),
          file_path_(file_path),
          icon_path_(icon_path),
          is_hover_(false),
          is_pressed_(false)
    {
        _init_ui();
    }

    void Ui_List_Button::_init_ui()
    {
        // 根据模式设置不同样式
        switch (mode_)
        {
        case ButtonMode::FILE:
            // 文件模式 - 使用改进的文件图标获取方法
            if (icon_path_.isEmpty() && !file_path_.isEmpty())
            {
                setIcon(getFileIcon(file_path_));
            }
            else if (!icon_path_.isEmpty())
            {
                setIcon(QIcon(icon_path_));
            }
            else
            {
                // 如果既没有文件路径也没有图标路径，使用默认文件图标
                setIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon));
            }
            setText(name_);
            break;

        case ButtonMode::FOLDER:
            // 文件夹模式
            if (icon_path_.isEmpty())
            {
                setIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon));
            }
            else
            {
                setIcon(QIcon(icon_path_));
            }
            setText(name_);
            break;

        case ButtonMode::INDEX:
            // 索引模式 - 显示首字母
            setText(name_.left(1).toUpper());
            break;

        case ButtonMode::NONE:
        default:
            // 普通按钮模式
            setText(name_);
            break;
        }

        // 通用样式设置
        setCursor(Qt::PointingHandCursor);
        setFlat(true);
        setStyleSheet(
            "QPushButton {"
            "   border: none;"
            "   padding: 5px 10px;"
            "   text-align: left;"
            "   spacing: 8px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #e0e0e0;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #d0d0d0;"
            "}");
    }

    QIcon Ui_List_Button::getFileIcon(const QString &filePath)
    {
        // 首先尝试获取系统关联的图标
        QFileInfo fileInfo(filePath);
        QFileIconProvider provider;
        QIcon icon = provider.icon(fileInfo);

        // 如果获取的是通用图标，尝试根据MIME类型获取更具体的图标
        if (icon.availableSizes().isEmpty() ||
            icon.name().contains("unknown") ||
            icon.name().contains("file"))
        {

            QMimeDatabase mimeDb;
            QMimeType mimeType = mimeDb.mimeTypeForFile(filePath);

            // 尝试从主题中获取MIME类型对应的图标
            if (QIcon::hasThemeIcon(mimeType.iconName()))
            {
                icon = QIcon::fromTheme(mimeType.iconName());
            }
            // 如果主题中没有，尝试从MIME类型的通用图标名称获取
            else if (QIcon::hasThemeIcon(mimeType.genericIconName()))
            {
                icon = QIcon::fromTheme(mimeType.genericIconName());
            }
        }

        return icon;
    }

    void Ui_List_Button::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);

        QStyleOptionButton option;
        initStyleOption(&option);

        QPainter painter(this);

        // 绘制背景
        if (is_hover_ || is_pressed_)
        {
            QColor bgColor = is_pressed_ ? QColor("#d0d0d0") : QColor("#e0e0e0");
            painter.fillRect(rect(), bgColor);
        }

        // 绘制图标和文本
        if (mode_ == ButtonMode::INDEX)
        {
            // 索引模式特殊绘制
            painter.setPen(Qt::black);
            QFont font = painter.font();
            font.setBold(true);
            font.setPointSize(16);
            painter.setFont(font);
            painter.drawText(rect(), Qt::AlignCenter, name_.left(1).toUpper());
        }
        else
        {
            // 其他模式使用默认绘制
            style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);
        }
    }

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void Ui_List_Button::enterEvent(QEnterEvent *event)
#else
    void Ui_List_Button::enterEvent(QEvent *event)
#endif
    {
        Q_UNUSED(event);
        is_hover_ = true;
        update();
    }

    void Ui_List_Button::leaveEvent(QEvent *event)
    {
        Q_UNUSED(event);
        is_hover_ = false;
        update();
    }

    void Ui_List_Button::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton)
        {
            is_pressed_ = true;
            update();
        }
        QPushButton::mousePressEvent(event);
    }

} // namespace beiklive