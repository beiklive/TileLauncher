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

json get_sorted_directory_structure(const std::string &root_path)
{
    json result = get_directory_structure(root_path);
    PinyinLookup pinyin;
    if (!pinyin.load("assets/file/pinyin.txt")) {
        std::cerr << "Failed to load pinyin data!" << std::endl;
        return 1;
    }

    if (!result.empty())
    {
        json sort_list;
        // 初始化所有字母键，即使为空也保留
        for (char key = 'A'; key <= 'Z'; ++key)
        {
            sort_list[std::string(1, key)] = json::array();
        }
        sort_list["#"] = json::array();

        for (auto &entry : result["list"])
        {
            std::string name = entry["name"];
            char first_letter = getFirstLetter(&pinyin, name)[0];

            if (first_letter >= 'A' && first_letter <= 'Z')
            {
                sort_list[std::string(1, first_letter)].push_back(entry);
            }
            else
            {
                sort_list["#"].push_back(entry);
            }
        }

        return sort_list;
    }

    return json();
}

std::string removeFileExtension(const std::string &fileName)
{
    fs::path p(fileName);
    return p.stem().string(); // 返回不带后缀的文件名
}