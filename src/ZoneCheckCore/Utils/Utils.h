#include <iostream>
#include <string>
#include <unordered_map>


namespace zc {

std::string toJson(const std::unordered_map<std::string, double>& map);

std::string toJson(const std::unordered_map<std::string, int>& map);

} // namespace zc