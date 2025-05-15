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
    end)

    if is_plat("windows") then
        -- 打印输出到控制台
        add_ldflags("/SUBSYSTEM:CONSOLE")
    end

    add_packages("nlohmann_json")  -- 链接到目标
    add_packages("spdlog")  -- 链接到目标

    add_includedirs("gui/")
    add_includedirs("gui/widgets/")
    add_includedirs("gui/core/")
    add_files("gui/**.cpp")
    -- add_files("src/mainwindow.ui")
    -- 添加带有 Q_OBJECT 宏的文件（这些是专门给 Qt 的 moc 工具处理的）
    add_files(
        "gui/widgets/ui_FrameLessWindow/ui_FrameLessWindow.h"
    )

