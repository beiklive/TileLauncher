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
          is_pressed_(false),
          is_folder_expand_(false)
    {
        m_height = 36;
        m_contentHeight = 30;

        m_NormalColor = "#00ffffff";
        m_HoverColor = "#7d9e9e9e";
        m_PressedColor = "#7d565656";
        m_TextColor = "#1f1f1f";

        setFixedHeight(m_height);
        _flush_rect();
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
                m_icon = getFileIcon(file_path_);
            }
            else if (!icon_path_.isEmpty())
            {
                m_icon = QIcon(icon_path_);
            }
            else
            {
                // 如果既没有文件路径也没有图标路径，使用默认文件图标
                m_icon = QApplication::style()->standardIcon(QStyle::SP_FileIcon);
            }
            break;

        case ButtonMode::FOLDER:
            // 文件夹模式
            if (icon_path_.isEmpty())
            {
                m_icon = QApplication::style()->standardIcon(QStyle::SP_DirIcon);
            }
            else
            {
                m_icon = QIcon(icon_path_);
            }
            break;

        case ButtonMode::INDEX:
            // 索引模式 - 显示首字母
            name_ = name_.left(1).toUpper();
            break;

        case ButtonMode::NONE:
        default:
            break;
        }

        // 通用样式设置
        setCursor(Qt::PointingHandCursor);
    }

    void Ui_List_Button::_flush_rect()
    {
        int margin = (m_height - m_contentHeight) / 2;
        m_iconRect = QRect(margin, margin, m_contentHeight, m_contentHeight);
        m_textRect = QRect(m_height + margin, margin, width() - m_height - margin*2, m_contentHeight);
        m_indexRect = m_iconRect;
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

    void Ui_List_Button::FolderExpand(bool expand)
    {
        is_folder_expand_ = expand;
        update();
    }

    void Ui_List_Button::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);

        _flush_rect();

        // QStyleOptionButton option;
        // initStyleOption(&option);

        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制背景
        if (is_hover_ || is_pressed_)
        {
            QColor bgColor = is_pressed_ ? QColor(m_PressedColor.c_str()) : QColor(m_HoverColor.c_str());
            painter.setBrush(QBrush(bgColor));
        }else
        {
            QColor bgColor = QColor(m_NormalColor.c_str());
            painter.setBrush(QBrush(bgColor));
        }
        painter.drawRoundedRect(rect(), 3, 3);


        // 绘制图标和文本
        switch (mode_)
        {
        case ButtonMode::FILE:
            // 文件模式
            if (!m_icon.isNull())
            {
                // 绘制图标
                iconPaint(&painter, m_icon, m_iconRect);
                // 绘制文本
                painter.setPen(QColor(m_TextColor.c_str()));
                painter.drawText(m_textRect, Qt::AlignLeft | Qt::AlignVCenter, name_);
            }
            /* code */
            break;
        case ButtonMode::FOLDER:
            // 文件夹模式
            if (!m_icon.isNull())
            {
                // 绘制图标
                iconPaint(&painter, m_icon, m_iconRect);
                // 绘制文本
                painter.setPen(QColor(m_TextColor.c_str()));
                painter.drawText(m_textRect, Qt::AlignLeft | Qt::AlignVCenter, name_);
            }
            /* code */
            break;
        case ButtonMode::INDEX:
            // 索引模式
            {
                // 创建字体对象
                QFont font = painter.font(); // 获取当前字体
                
                // 设置字体大小（两种方式任选其一）
                // font.setPointSize(20);       // 使用逻辑点(pt)为单位
                font.setPixelSize(m_contentHeight);    // 使用像素(px)为单位
                
                // 应用字体到painter
                painter.setFont(font);
                // 绘制文本
                painter.setPen(QColor(m_TextColor.c_str()));
                painter.drawText(m_indexRect, Qt::AlignCenter, name_);
            }
            break;
        case ButtonMode::NONE:
        default:
            break;
        }
        painter.end();
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
    void Ui_List_Button::mouseReleaseEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton)
        {
            is_pressed_ = false;
            update();
        }
        QPushButton::mouseReleaseEvent(event);
    }
    void Ui_List_Button::iconPaint(QPainter* painter, const QIcon& icon, const QRect& rect)
    {
        QPixmap pixmap = icon.pixmap(rect.size());
        
        // 如果是SVG图标（QT5.6+支持）
        if (!pixmap.isNull()) {
            painter->drawPixmap(rect, pixmap);
        } 
        else {
            // 回退方案
            icon.paint(painter, rect);
        }
    }






} // namespace beiklive