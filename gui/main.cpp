#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QWidget>
#include <fstream>
#include "ui/App_MainWindow.h"

#include "global.hpp"
using namespace beiklive;
nlohmann::json globalSettings;
nlohmann::json globalTheme;


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

  // 遍历所有屏幕并打印信息
    for (const QScreen* screen : QGuiApplication::screens()) {
        spdlog::debug(
            "Screen: {}, Geometry: (x={}, y={}, w={}, h={}), DPI: {:.1f}",
            screen->name().toStdString(),  // QString → std::string
            screen->geometry().x(),
            screen->geometry().y(),
            screen->geometry().width(),
            screen->geometry().height(),
            screen->logicalDotsPerInch()
        );
    }

    return;
}

int main(int argc, char *argv[])
{
    // 启用Qt的高DPI支持（推荐）
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication a(argc, argv);
    init();
    App_MainWindow w;
    
    w.show();



    return a.exec();
}
