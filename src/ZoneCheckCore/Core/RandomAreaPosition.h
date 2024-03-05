#include <iostream>
#include <string>
#include <unordered_map>


namespace zc::RandomAreaPosition {


std::unordered_map<std::string, int> getRandomCoordinateInCircle(double x, double z, double radius);


std::unordered_map<std::string, int>
getRandomCoordinateInRectangle(double topLeftX, double topLeftZ, double bottomRightX, double bottomRightZ);


std::unordered_map<std::string, int> getRandomCoordinateInSquare(double centerX, double centerZ, double halfLength);


} // namespace zc::RandomAreaPosition