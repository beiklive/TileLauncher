#include <QApplication>
#include <QWidget>
#include <fstream>
#include "ui_window/ui_window.h"
#include "global.hpp"

using namespace beiklive;
nlohmann::json globalConfig; // 实际定义


void init(){
    // 配置文件初始化
    std::ifstream file("config/setting.json");
    if (!file.is_open()) {
        spdlog::error("Failed to open config file.");
        return;
    }
    file >> globalConfig;
    file.close();
    spdlog::info("Config loaded. \n{}", globalConfig.dump(4));

    beiklive::set_log_level(globalConfig["log"]["log_level"].get<std::string>());
    spdlog::info("Log level set to {}", globalConfig["log"]["log_level"].get<std::string>());
    




    return;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    init();


    Ui_Window w;
    w.show();
    return a.exec();
}
