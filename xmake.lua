add_rules("mode.debug", "mode.release")
set_defaultmode("debug")
add_requires("spdlog")

target("TileLauncher")
    add_rules("qt.widgetapp")
    set_languages("c99", "c++17")
    add_defines("BEIKLIVE_FRAMELESS=1")


    add_includedirs("gui/widgets/")
    add_files("gui/**.cpp")
    -- add_files("src/mainwindow.ui")
    -- 添加带有 Q_OBJECT 宏的文件（这些是专门给 Qt 的 moc 工具处理的）
    add_files("gui/widgets/ui_window/FramelessWindowHelper.h")
    add_files("gui/widgets/ui_window/ui_window.h")
