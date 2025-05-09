#include <QApplication>
#include <QWidget>
#include <fstream>
#include "ui_window/ui_window.h"
#include "global.hpp"

using namespace beiklive;
nlohmann::json globalSettings; // 实际定义
nlohmann::json globalTheme;    // 实际定义

void init()
{
    //==============================================================
    // 配置文件初始化
    std::ifstream file("config/setting.json");
    if (!file.is_open())
    {
        spdlog::error("Failed to open config file.");
        return;
    }
    file >> globalSettings;
    file.close();
    beiklive::set_log_level(globalSettings["log"]["log_level"].get<std::string>());
    spdlog::debug("Config loaded. \n{}", globalSettings.dump(4));

    spdlog::info("Log level set to [{}]", globalSettings["log"]["log_level"].get<std::string>());
    //==============================================================


    //==============================================================
    // 主题文件初始化
    auto theme_name = globalSettings["window"]["theme"].get<std::string>();
    std::string theme_file = "config/" + theme_name;
    std::ifstream theme_stream(theme_file.c_str()); 
    if (!theme_stream.is_open())
    {
        spdlog::error("Failed to open theme file.");
        return;
    }
    theme_stream >> globalTheme;
    theme_stream.close();
    spdlog::debug("theme loaded. \n{}", globalTheme.dump(4));
    //==============================================================



    return;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init();

    Ui_Window w;
    w.show();
    return a.exec();
}
