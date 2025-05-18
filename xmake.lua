add_rules("mode.debug", "mode.release")
set_defaultmode("release")
add_requires("spdlog")
add_requires("nlohmann_json")  -- 自动下载并集成





target("TileLauncher")
    add_rules("qt.widgetapp")
    set_languages("c99", "c++20")
    
    set_targetdir("$(projectdir)/output/")
    set_installdir("$(projectdir)/output")
    after_build(function (target)
    
        -- 将生成的文件拷贝到指定目录
        os.cp("$(projectdir)/gui/config", "$(projectdir)/output")
        print(">> Copy config files to " .. target:targetdir())
        os.cp("$(projectdir)/gui/assets", "$(projectdir)/output")
        print(">> Copy assets files to " .. target:targetdir())
        os.cp("$(projectdir)/gui/theme", "$(projectdir)/output")
        print(">> Copy theme files to " .. target:targetdir())
    end)

    before_run(function (target)
        os.cp("$(projectdir)/gui/config", "$(projectdir)/output")
        print(">> Copy config files")
        os.cp("$(projectdir)/gui/assets", "$(projectdir)/output")
        print(">> Copy assets files")
        os.cp("$(projectdir)/gui/theme", "$(projectdir)/output")
        print(">> Copy theme files")
    end)

    if is_plat("windows") then
        -- 打印输出到控制台
        add_ldflags("/SUBSYSTEM:CONSOLE")
    end

    add_packages("nlohmann_json")
    add_packages("spdlog") 

    add_includedirs("gui/")
    add_includedirs("gui/widgets/")
    add_includedirs("gui/ui/")
    add_includedirs("gui/core/")
    add_files("gui/**.cpp")
    -- 添加带有 Q_OBJECT 宏的文件（这些是专门给 Qt 的 moc 工具处理的）
    add_files(
        "gui/widgets/ui_FrameLessWindow/ui_FrameLessWindow.h",
        "gui/ui/App_mainWindow.h",
        "gui/widgets/ui_buttons/ui_sidebar_button.h",
        "gui/widgets/ui_buttons/ui_title_button.h",
        "gui/widgets/ui_title_bar/ui_title_bar.h",
        "gui/widgets/ui_sidebar/ui_sidebar.h"
    )

