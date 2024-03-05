#include "Utils.h"

namespace zc {

std::string toJson(const std::unordered_map<std::string, double>& map) {
    std::string json = "{";
    for (const auto& pair : map) {
        json += "\"" + pair.first + "\":" + std::to_string(pair.second) + ",";
    }
    json[json.size() - 1] = '}'; // 替换最后一个逗号为闭合括号
    return json;
}

std::string toJson(const std::unordered_map<std::string, int>& map) {
    std::string json = "{";
    for (const auto& pair : map) {
        json += "\"" + pair.first + "\":" + std::to_string(pair.second) + ",";
    }
    json[json.size() - 1] = '}'; // 替换最后一个逗号为闭合括号
    return json;
}

} // namespace zc