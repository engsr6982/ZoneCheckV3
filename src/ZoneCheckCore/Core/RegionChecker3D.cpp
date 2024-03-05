#include "./RegionChecker3D.h"
#include <cmath>

namespace zc::RegionChecker3D {

/**
 * @brief 检查一个点是否在给定的球体内
 * @param centerX 球心的X坐标
 * @param centerY 球心的Y坐标
 * @param centerZ 球心的Z坐标
 * @param width 球的半径
 * @param pointX 点的X坐标
 * @param pointY 点的Y坐标
 * @param pointZ 点的Z坐标
 * @return 如果点在球体内，返回true，否则返回false
 */
bool isWithinSphere(
    double centerX,
    double centerY,
    double centerZ,
    double width,
    double pointX,
    double pointY,
    double pointZ
) {
    double distance =
        std::sqrt(std::pow(centerX - pointX, 2) + std::pow(centerY - pointY, 2) + std::pow(centerZ - pointZ, 2));
    return distance <= width;
}

/**
 * @brief 检查一个点是否在给定的立方体内
 * @param leftTopX 左上角的X坐标
 * @param leftTopY 左上角的Y坐标
 * @param leftTopZ 左上角的Z坐标
 * @param rightBottomX 右下角的X坐标
 * @param rightBottomY 右下角的Y坐标
 * @param rightBottomZ 右下角的Z坐标
 * @param pointX 点的X坐标
 * @param pointY 点的Y坐标
 * @param pointZ 点的Z坐标
 * @return 如果点在长方体内，返回true，否则返回false
 */
bool isWithinCuboid(
    double leftTopX,
    double leftTopY,
    double leftTopZ,
    double rightBottomX,
    double rightBottomY,
    double rightBottomZ,
    double pointX,
    double pointY,
    double pointZ
) {
    // 确定X轴的最小和最大值
    double minX = std::min(leftTopX, rightBottomX);
    double maxX = std::max(leftTopX, rightBottomX);

    // 确定Y轴的最小和最大值
    double minY = std::max(leftTopY, rightBottomY); // 注意这里交换了min和max
    double maxY = std::min(leftTopY, rightBottomY); // 注意这里交换了min和max

    // 确定Z轴的最小和最大值
    double minZ = std::min(leftTopZ, rightBottomZ);
    double maxZ = std::max(leftTopZ, rightBottomZ);

    // 检查点的X坐标是否在立方体的X轴范围内
    if (pointX < minX || pointX > maxX) {
        return false;
    }

    // 检查点的Y坐标是否在立方体的Y轴范围内
    if (pointY > minY || pointY < maxY) { // 注意这里交换了比较方向
        return false;
    }

    // 检查点的Z坐标是否在立方体的Z轴范围内
    if (pointZ < minZ || pointZ > maxZ) {
        return false;
    }
    // 如果点的所有坐标都在立方体内，返回true
    return true;
}

/**
 * @brief 检查一个点是否在给定的以中心点为中心的立方体内
 * @param centerX 中心点的X坐标
 * @param centerY 中心点的Y坐标
 * @param centerZ 中心点的Z坐标
 * @param distance 到立方体边的距离
 * @param x 点的X坐标
 * @param y 点的Y坐标
 * @param z 点的Z坐标
 * @return 如果点在立方体内，返回true，否则返回false
 */
bool isWithinCenteredCube(
    double centerX,
    double centerY,
    double centerZ,
    double distance,
    double x,
    double y,
    double z
) {
    double minX = centerX - distance;
    double maxX = centerX + distance;
    double minY = centerY - distance;
    double maxY = centerY + distance;
    double minZ = centerZ - distance;
    double maxZ = centerZ + distance;
    return x >= minX && x <= maxX && y >= minY && y <= maxY && z >= minZ && z <= maxZ;
}


} // namespace zc::RegionChecker3D