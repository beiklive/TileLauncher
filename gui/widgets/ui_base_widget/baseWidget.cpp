#include "baseWidget.h"

beiklive::BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent)
{
    setProperty("style", QVariant("BaseWidget"));
    setupStlye();
}

void beiklive::BaseWidget::setupStlye()
{
    setStyleSheet(R"(
        QWidget[style="BaseWidget"] 
        {
        background-color: transparent;
    }
        )");
}