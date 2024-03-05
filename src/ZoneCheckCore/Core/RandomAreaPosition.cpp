#include "./RandomAreaPosition.h"
#include <cmath>
#include <iostream>
#include <random>


namespace zc::RandomAreaPosition {

/**
 * @brief 生成指定范围内的随机整数
 * @param min 最小值
 * @param max 最大值
 * @return 随机整数
 */
int randomInt(int min, int max) {
    std::random_device rd;                            // 生成随机设备
    std::mt19937       gen(rd());                     // 使用随机设备生成随机数引擎
    std::uniform_int_distribution<int> dis(min, max); // 使用引擎生成[min, max]范围内的均匀分布的随机整数
    return dis(gen);                                  // 返回生成的随机整数
}


/**
 * @brief 在圆形区域内生成随机坐标
 * @param x 圆心的X坐标
 * @param z 圆心的Z坐标
 * @param radius 圆的半径
 * @return 包含随机坐标的unordered_map，键为"x"和"z"
 */
std::unordered_map<std::string, int> getRandomCoordinateInCircle(double x, double z, double radius) {
    std::unordered_map<std::string, int> result;
    double                               minX = x - radius; // 计算圆形区域的最小X坐标
    double                               maxX = x + radius; // 计算圆形区域的最大X坐标
    double                               minZ = z - radius; // 计算圆形区域的最小Z坐标
    double                               maxZ = z + radius; // 计算圆形区域的最大Z坐标
    double newX = randomInt(minX, maxX);                    // 在最小X坐标和最大X坐标之间生成随机X坐标
    double newZ = randomInt(minZ, maxZ);                    // 在最小Z坐标和最大Z坐标之间生成随机Z坐标
    result["x"] = newX;                                     // 将生成的随机X坐标存入结果unordered_map中
    result["z"] = newZ;                                     // 将生成的随机Z坐标存入结果unordered_map中
    return result;                                          // 返回包含随机坐标的unordered_map
}


/**
 * @brief 在矩形区域内生成随机坐标
 * @param topLeftX 矩形左上角的X坐标
 * @param topLeftZ 矩形左上角的Z坐标
 * @param bottomRightX 矩形右下角的X坐标
 * @param bottomRightZ 矩形右下角的Z坐标
 * @return 包含随机坐标的unordered_map，键为"x"和"z"
 */
std::unordered_map<std::string, int>
getRandomCoordinateInRectangle(double topLeftX, double topLeftZ, double bottomRightX, double bottomRightZ) {
    // 创建一个unordered_map来存储结果
    std::unordered_map<std::string, int> result;
    // 如果左上角的X坐标大于右下角的X坐标，交换两者
    if (topLeftX > bottomRightX) std::swap(topLeftX, bottomRightX);
    // 如果左上角的Z坐标大于右下角的Z坐标，交换两者
    if (topLeftZ > bottomRightZ) std::swap(topLeftZ, bottomRightZ);
    // 在左上角和右下角的X坐标之间生成一个随机的X坐标
    double newX = randomInt(topLeftX, bottomRightX);
    // 在左上角和右下角的Z坐标之间生成一个随机的Z坐标
    double newZ = randomInt(topLeftZ, bottomRightZ);
    // 将生成的X坐标存入结果unordered_map中
    result["x"] = newX;
    // 将生成的Z坐标存入结果unordered_map中
    result["z"] = newZ;
    // 返回包含随机坐标的unordered_map
    return result;
}


/**
 * @brief 在正方形区域内生成随机坐标
 * @param centerX 正方形中心点的X坐标
 * @param centerZ 正方形中心点的Z坐标
 * @param halfLength 正方形边长的一半
 * @return 包含随机坐标的unordered_map，键为"x"和"z"
 */
std::unordered_map<std::string, int> getRandomCoordinateInSquare(double centerX, double centerZ, double halfLength) {
    // 创建一个unordered_map来存储结果
    std::unordered_map<std::string, int> result;
    // 计算正方形区域的最小X坐标
    double minX = centerX - halfLength;
    // 计算正方形区域的最大X坐标
    double maxX = centerX + halfLength;
    // 计算正方形区域的最小Z坐标
    double minZ = centerZ - halfLength;
    // 计算正方形区域的最大Z坐标
    double maxZ = centerZ + halfLength;
    // 如果最小X坐标大于最大X坐标，交换两者
    if (minX > maxX) std::swap(minX, maxX);
    // 如果最小Z坐标大于最大Z坐标，交换两者
    if (minZ > maxZ) std::swap(minZ, maxZ);
    // 在最小X坐标和最大X坐标之间生成随机X坐标
    double newX = randomInt(minX, maxX);
    // 在最小Z坐标和最大Z坐标之间生成随机Z坐标
    double newZ = randomInt(minZ, maxZ);
    // 将生成的X坐标存入结果unordered_map中
    result["x"] = newX;
    // 将生成的Z坐标存入结果unordered_map中
    result["z"] = newZ;
    // 返回包含随机坐标的unordered_map
    return result;
}


} // namespace zc::RandomAreaPosition
