#include "json.h"

json get_directory_structure(const std::string &root_path)
{
    json result;
    result["rootPath"] = root_path;
    result["list"] = json::array();

    try
    {
        for (const auto &dir_entry : fs::directory_iterator(root_path))
        {
            json entry;
            entry["name"] = dir_entry.path().filename().string();
            entry["path"] = dir_entry.path().string(); // 添加完整路径

            if (fs::is_directory(dir_entry))
            {
                if (dir_entry.path().extension() == ".app")
                {
                    entry["type"] = "file"; // 特殊标记为 macOS 应用
                }
                else
                {
                    entry["type"] = "folder";
                }
            }
            else
            {
                entry["type"] = "file";
            }

            result["list"].push_back(entry);
        }
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }

    return result;
}


std::string removeFileExtension(const std::string &fileName)
{
    fs::path p(fileName);
    return p.stem().string(); // 返回不带后缀的文件名
}