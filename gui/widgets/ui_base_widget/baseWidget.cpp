#include "baseWidget.h"

beiklive::BaseWidget::BaseWidget()
{
    setupStlye();
}

void beiklive::BaseWidget::setupStlye()
{
    std::string styleSheet = std::format(R"(
        background-color: transparent;
    )");
}