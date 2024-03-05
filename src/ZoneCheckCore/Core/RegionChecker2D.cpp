#include "./RegionChecker2D.h"
#include <cmath>


namespace zc::RegionChecker2D {


/**
 * @brief 检查一个点是否在给定的圆内
 * @param centerX 圆心的X坐标
 * @param centerZ 圆心的Z坐标
 * @param width 圆的半径
 * @param pointX 点的X坐标
 * @param pointZ 点的Z坐标
 * @return 如果点在圆内，返回true，否则返回false
 */
bool isWithinRadius(double centerX, double centerZ, double width, double pointX, double pointZ) {
    double distance = std::sqrt(std::pow(centerX - pointX, 2) + std::pow(centerZ - pointZ, 2));
    return distance <= width;
}

/**
 * @brief 检查一个点是否在给定的矩形内
 * @param leftTopX 左上角的X坐标
 * @param leftTopZ 左上角的Z坐标
 * @param rightBottomX 右下角的X坐标
 * @param rightBottomZ 右下角的Z坐标
 * @param pointX 点的X坐标
 * @param pointZ 点的Z坐标
 * @return 如果点在矩形内，返回true，否则返回false
 */
bool isWithinRectangle(
    double leftTopX,
    double leftTopZ,
    double rightBottomX,
    double rightBottomZ,
    double pointX,
    double pointZ
) {
    // 确定X轴的最小和最大值
    double minX = std::min(leftTopX, rightBottomX);
    double maxX = std::max(leftTopX, rightBottomX);

    // 确定Z轴的最小和最大值
    double minZ = std::max(leftTopZ, rightBottomZ); // 注意这里交换了min和max
    double maxZ = std::min(leftTopZ, rightBottomZ); // 注意这里交换了min和max

    // 检查点的X坐标是否在矩形的X轴范围内
    if (pointX < minX || pointX > maxX) {
        return false;
    }

    // 检查点的Z坐标是否在矩形的Z轴范围内
    if (pointZ > minZ || pointZ < maxZ) // 注意这里交换了比较方向
    {
        return false;
    }

    // 如果点的所有坐标都在矩形内，返回true
    return true;
}

/**
 * @brief 检查一个点是否在给定的以中心点为中心的正方形内
 * @param centerX 中心点的X坐标
 * @param centerZ 中心点的Z坐标
 * @param distance 到正方形边的距离
 * @param x 点的X坐标
 * @param z 点的Z坐标
 * @return 如果点在正方形内，返回true，否则返回false
 */
bool isWithinCenteredSquare(double centerX, double centerZ, double distance, double x, double z) {
    double minX = centerX - distance;
    double maxX = centerX + distance;
    double minZ = centerZ - distance;
    double maxZ = centerZ + distance;
    return x >= minX && x <= maxX && z >= minZ && z <= maxZ;
}

} // namespace zc::RegionChecker2D