#include <QApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QWidget>
#include <fstream>
#include "ui/App_mainWindow.h"

#include "global.hpp"
using namespace beiklive;
nlohmann::json globalSettings;


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

    std::string theme_name = "theme/" + globalSettings["window"]["theme"].get<std::string>();
    QFile qssFile(theme_name.c_str());  // 可以是资源文件或本地文件
        if (qssFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString qss = QLatin1String(qssFile.readAll());
            a.setStyleSheet(qss);  // 应用到整个应用
            qssFile.close();
            spdlog::debug("主题{}加载成功", theme_name);
        } else {
            spdlog::error("读取主题文件{}失败", theme_name);
        }

    App_MainWindow w;
    
    w.animaShow();



    return a.exec();
}
