// Copyright (c) 2025. All rights reserved.
// Author: beiklive
// Date: 2025-05-15
#ifndef _INCLUDE_THEME_H_
#define _INCLUDE_THEME_H_

#include "json.h"
#include <iostream>
namespace beiklive
{
    struct WidgetTheme
    {
        std::string background_color;
        std::string color;
        std::string border;
        int border_radius;
    };

    std::string WidgetThemeSet(
        std::string widget_name);

    std::string _StyleString(std::string widgetname, WidgetTheme theme);

} // namespace beiklive

#endif // _INCLUDE_THEME_H_