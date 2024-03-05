#include "./BoundaryChecker.h"

namespace zc::BoundaryChecker {

namespace is2D {

/**
 * @brief 获取超出2D圆形边界的信息
 * @param centerX 圆心的X坐标
 * @param centerZ 圆心的Z坐标
 * @param width 圆的宽度
 * @param x 点的X坐标
 * @param z 点的Z坐标
 * @return 返回一个包含超出边界的轴、值和边界的map
 */
std::unordered_map<std::string, double>
getExceededBoundaryCircle2D(double centerX, double centerZ, double width, double x, double z) {
    std::unordered_map<std::string, double> result;
    double                                  dx       = x - centerX;
    double                                  dz       = z - centerZ;
    double                                  distance = std::sqrt(dx * dx + dz * dz);
    if (distance > width) {
        double angle    = std::atan2(dz, dx);
        result["axis"]  = std::abs(dx) > std::abs(dz) ? 'x' : 'z';
        result["value"] = result["axis"] == 'x' ? x : z;
        result["boundary"] =
            result["axis"] == 'x' ? centerX + width * std::cos(angle) : centerZ + width * std::sin(angle);
    }
    return result;
}

/**
 * @brief 获取超出2D矩形边界的信息
 * @param minX 矩形左上角的X坐标
 * @param minZ 矩形左上角的Z坐标
 * @param maxX 矩形右下角的X坐标
 * @param maxZ 矩形右下角的Z坐标
 * @param x 点的X坐标
 * @param z 点的Z坐标
 * @return 返回一个包含超出边界的轴、值和边界的map
 */
std::unordered_map<std::string, double>
getExceededBoundaryRectangle2D(double minX, double minZ, double maxX, double maxZ, double x, double z) {
    std::unordered_map<std::string, double> result;
    if (x < minX || x > maxX) {
        result["axis"]     = 'x';
        result["value"]    = x;
        result["boundary"] = x < minX ? minX : maxX;
    } else if (z < minZ || z > maxZ) {
        result["axis"]     = 'z';
        result["value"]    = z;
        result["boundary"] = z < minZ ? minZ : maxZ;
    }
    return result;
}

/**
 * @brief 获取超出以中心点为中心的2D正方形边界的信息
 * @param centerX 中心点的X坐标
 * @param centerZ 中心点的Z坐标
 * @param width 正方形的宽度
 * @param x 点的X坐标
 * @param z 点的Z坐标
 * @return 返回一个包含超出边界的轴、值和边界的map
 */
std::unordered_map<std::string, double>
getExceededCenteredBoundary2D(double centerX, double centerZ, double width, double x, double z) {
    std::unordered_map<std::string, double> result;
    if (std::abs(x - centerX) > width) {
        result["axis"]     = 'x';
        result["value"]    = x;
        result["boundary"] = x < centerX ? centerX - width : centerX + width;
    } else if (std::abs(z - centerZ) > width) {
        result["axis"]     = 'z';
        result["value"]    = z;
        result["boundary"] = z < centerZ ? centerZ - width : centerZ + width;
    }
    return result;
}

} // namespace is2D


namespace is3D {

/**
 * @brief 获取超出3D圆形边界的信息
 * @param centerX 圆心的X坐标
 * @param centerY 圆心的Y坐标
 * @param centerZ 圆心的Z坐标
 * @param width 圆的半径
 * @param x 点的X坐标
 * @param y 点的Y坐标
 * @param z 点的Z坐标
 * @return 返回一个包含超出边界的轴、值和边界的map
 */
std::unordered_map<std::string, double> getExceededBoundaryCircle3D(
    double centerX,
    double centerY,
    double centerZ,
    double width,
    double x,
    double y,
    double z
) {
    std::unordered_map<std::string, double> result;
    double                                  dx       = x - centerX;
    double                                  dy       = y - centerY;
    double                                  dz       = z - centerZ;
    double                                  distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    if (distance > width) {
        double      ratio  = width / distance;
        std::string axis   = std::abs(dx) > std::abs(dy) ? (std::abs(dx) > std::abs(dz) ? "x" : "z")
                                                         : (std::abs(dy) > std::abs(dz) ? "y" : "z");
        result["axis"]     = axis[0];
        result["value"]    = axis == "x" ? x : (axis == "y" ? y : z);
        result["boundary"] = (axis == "x" ? centerX : (axis == "y" ? centerY : centerZ))
                           + ratio * (axis == "x" ? dx : (axis == "y" ? dy : dz));
    }
    return result;
}

/**
 * @brief 获取超出3D立方体边界的信息
 * @param minX 立方体左上角的X坐标
 * @param minY 立方体左上角的Y坐标
 * @param minZ 立方体左上角的Z坐标
 * @param maxX 立方体右下角的X坐标
 * @param maxY 立方体右下角的Y坐标
 * @param maxZ 立方体右下角的Z坐标
 * @param x 点的X坐标
 * @param y 点的Y坐标
 * @param z 点的Z坐标
 * @return 返回一个包含超出边界的轴、值和边界的map
 */
std::unordered_map<std::string, double> getExceededBoundaryCube3D(
    double minX,
    double minY,
    double minZ,
    double maxX,
    double maxY,
    double maxZ,
    double x,
    double y,
    double z
) {
    std::unordered_map<std::string, double> result;
    if (x < minX || x > maxX) {
        result["axis"]     = 'x';
        result["value"]    = x;
        result["boundary"] = x < minX ? minX : maxX;
    } else if (y < minY || y > maxY) {
        result["axis"]     = 'y';
        result["value"]    = y;
        result["boundary"] = y < minY ? minY : maxY;
    } else if (z < minZ || z > maxZ) {
        result["axis"]     = 'z';
        result["value"]    = z;
        result["boundary"] = z < minZ ? minZ : maxZ;
    }
    return result;
}

/**
 * @brief 获取超出以中心点为中心的3D立方体边界的信息
 * @param centerX 中心点的X坐标
 * @param centerY 中心点的Y坐标
 * @param centerZ 中心点的Z坐标
 * @param width 立方体的宽度
 * @param x 点的X坐标
 * @param y 点的Y坐标
 * @param z 点的Z坐标
 * @return 返回一个包含超出边界的轴、值和边界的map
 */
std::unordered_map<std::string, double> getExceededCenteredBoundary3D(
    double centerX,
    double centerY,
    double centerZ,
    double width,
    double x,
    double y,
    double z
) {
    std::unordered_map<std::string, double> result;
    if (std::abs(x - centerX) > width) {
        result["axis"]     = 'x';
        result["value"]    = x;
        result["boundary"] = x < centerX ? centerX - width : centerX + width;
    } else if (std::abs(y - centerY) > width) {
        result["axis"]     = 'y';
        result["value"]    = y;
        result["boundary"] = y < centerY ? centerY - width : centerY + width;
    } else if (std::abs(z - centerZ) > width) {
        result["axis"]     = 'z';
        result["value"]    = z;
        result["boundary"] = z < centerZ ? centerZ - width : centerZ + width;
    }
    return result;
}

} // namespace is3D

} // namespace zc::BoundaryChecker