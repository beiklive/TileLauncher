add_rules("mode.debug", "mode.release")
set_defaultmode("debug")
add_requires("spdlog")
add_requires("nlohmann_json")  -- 自动下载并集成
target("TileLauncher")
    add_rules("qt.widgetapp")
    set_languages("c99", "c++17")
    
    set_targetdir("$(projectdir)/output/")
    set_installdir("$(projectdir)/output")
    add_installfiles("$(projectdir)/gui/config")  -- ​**表示递归匹配
    after_build(function (target)
        print("Target dir: " .. target:targetdir())
        -- 将生成的文件拷贝到指定目录
        -- os.cp("$(targetdir)/TileLauncher", "$(projectdir)/output/bin")
        os.cp("$(projectdir)/gui/config", "$(projectdir)/output")
    end)

    add_defines("BEIKLIVE_FRAMELESS=1")

    add_packages("nlohmann_json")  -- 链接到目标
    add_packages("spdlog")  -- 链接到目标

    add_includedirs("gui/widgets/")
    add_includedirs("gui/")
    add_files("gui/**.cpp")
    -- add_files("src/mainwindow.ui")
    -- 添加带有 Q_OBJECT 宏的文件（这些是专门给 Qt 的 moc 工具处理的）
    add_files("gui/widgets/ui_window/FramelessWindowHelper.h")
    add_files("gui/widgets/ui_window/ui_window.h")
