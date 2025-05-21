#include "json.h"



json get_directory_structure(const std::string& root_path) {
    json result;
    result["rootPath"] = root_path;
    result["list"] = json::array();
    
    try {
        for (const auto& dir_entry : fs::directory_iterator(root_path)) {
            json entry;
            entry["name"] = dir_entry.path().filename().string();
            entry["path"] = dir_entry.path().string();  // 添加完整路径
            
            if (fs::is_directory(dir_entry)) {
                entry["type"] = "folder";
                // 不再递归搜索子目录
            } else {
                entry["type"] = "file";
            }
            
            result["list"].push_back(entry);
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
    
    return result;
}

