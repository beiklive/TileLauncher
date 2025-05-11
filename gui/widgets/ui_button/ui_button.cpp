#include "ui_button.h"

beiklive::Ui_Button::Ui_Button()
{
    setProperty("style", "ui_button");
    this->setStyleSheet(R"(
        QWidget[style="ui_button"] {
            background-color: rgba(24, 24, 24, 0);
        }
    )");
}

beiklive::Ui_Button::Ui_Button(const QString &text, const QIcon &icon)
{
    layout = new QHBoxLayout(this);
    if(nullptr != text)
    {
        setText(text);
    }else
    {
        setText("");
    }

    if(!icon.isNull())
    {
        setIcon(icon);
    }else
    {
        setIcon(QIcon("assets/icons/default.svg"));
    }
    layout->addWidget(iconLabel);
    layout->addStretch();
    layout->addWidget(textLabel);
    layout->addStretch();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);
    hideText(true);
}

void beiklive::Ui_Button::setIcon(const QIcon &icon)
{
    iconLabel = new QLabel(this);
    int size = globalSettings["button"]["icon_size"].get<int>();
    iconLabel->setPixmap(icon.pixmap(size, size));
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet("background: red;");  // 方法1
    iconLabel->setFixedWidth(globalSettings["button"]["icon_size"].get<int>());  // 方法2
    iconLabel->setFixedHeight(globalSettings["button"]["icon_size"].get<int>());  // 方法2
}

void beiklive::Ui_Button::setText(const QString &text)
{
    textLabel = new QLabel(this);
    textLabel->setText(text);
    textLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    textLabel->setStyleSheet("background: blue;color: white;");  // 方法1
}

void beiklive::Ui_Button::hideText(bool hide)
{
    if (textLabel) {
        if (hide)
        {
            textLabel->setFixedHeight(0);
        }else
        {
            textLabel->setFixedHeight(globalSettings["button"]["button_size"].get<int>());
        }
    }
    
}

void beiklive::Ui_Button::enterEvent(QEvent *)
{
    spdlog::info("enterEvent");
    this->setStyleSheet(R"(
        QWidget[style="ui_button"] {
            background-color: rgba(24, 24, 24, 128);
        }
    )");
}

void beiklive::Ui_Button::leaveEvent(QEvent *)
{
    spdlog::info("leaveEvent");
    this->setStyleSheet(R"(
        QWidget[style="ui_button"] {
            background-color: rgba(24, 24, 24, 0);
        }
    )");
}
