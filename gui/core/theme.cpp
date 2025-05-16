#include "theme.h"

std::string beiklive::WidgetThemeSet(std::string widget_name)
{
    WidgetTheme theme;
    theme.background_color = globalTheme[widget_name]["background-color"].get<std::string>();
    theme.color = globalTheme[widget_name]["color"].get<std::string>();
    theme.border = globalTheme[widget_name]["border"].get<std::string>();
    theme.border_radius = globalTheme[widget_name]["border-radius"].get<int>();
    return _StyleString(widget_name, theme);
}

std::string beiklive::_StyleString(std::string widgetname, WidgetTheme theme)
{
    std::string style_str = 
    "[styleclass=\"" + widgetname + "\"] {"
    "    background-color : " + theme.background_color + ";"
    "    color : " + theme.color + "; "
    "    border : " + theme.border + ";" 
    "    border-radius : " + std::to_string(theme.border_radius) + "px;"
    "}";


    return style_str;
}
