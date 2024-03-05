#include <RemoteCallAPI.h>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>

// include files
#include "../../Entry.h"
#include "../../PluginInfo.h"
#include "Remote.h"

// include core files
#include "../Core/BoundaryChecker.h"
#include "../Core/RandomAreaPosition.h"
#include "../Core/RegionChecker2D.h"
#include "../Core/RegionChecker3D.h"
#include "../Utils/Utils.h"

namespace zc {

void startExports() {
    auto& logger    = zoneCheckV3::getSelfPluginInstance().getLogger(); // 获取logger
    auto  startTime = std::chrono::high_resolution_clock::now();        // 记录开始时间

    // export start
#define exportNameSpace PLUGIN_NAME
    using namespace RemoteCall;

    // 2D计算API
    exportAs(
        exportNameSpace,
        "RegionChecker2D::isWithinRadius",
        [&](double centerX, double centerZ, double width, double pointX, double pointZ) -> bool {
            auto s = zc::RegionChecker2D::isWithinRadius(centerX, centerZ, width, pointX, pointZ);
            logger.debug(
                "[RegionChecker2D::isWithinRadius]传入: 中心X: {}, 中心Z: {}，半径：{}, 当前X: {}, 当前Z:{}  => 返回: {}",
                centerX,
                centerZ,
                width,
                pointX,
                pointZ,
                s
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "RegionChecker2D::isWithinRectangle",
        [&](double leftTopX, double leftTopZ, double rightBottomX, double rightBottomZ, double pointX, double pointZ
        ) -> bool {
            auto s =
                zc::RegionChecker2D::isWithinRectangle(leftTopX, leftTopZ, rightBottomX, rightBottomZ, pointX, pointZ);
            logger.debug(
                "[RegionChecker2D::isWithinRectangle]传入: 左上X: {}, 左上Z: {}, 右下X: {}, 右下z: {}, 当前X: {}, 当前Z:{}  => "
                "返回: {}",
                leftTopX,
                leftTopZ,
                rightBottomX,
                rightBottomZ,
                pointX,
                pointZ,
                s
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "RegionChecker2D::isWithinCenteredSquare",
        [&](double centerX, double centerZ, double distance, double x, double z) -> bool {
            auto s = zc::RegionChecker2D::isWithinCenteredSquare(centerX, centerZ, distance, x, z);
            logger.debug(
                "[RegionChecker2D::isWithinCenteredSquare]传入: 中心X: {}, 中心Z: {}，半径：{}, 当前X: {}, 当前Z:{}  => 返回: "
                "{}",
                centerX,
                centerZ,
                distance,
                x,
                z,
                s
            );
            return s;
        }
    );
    // 3D计算API
    exportAs(
        exportNameSpace,
        "RegionChecker3D::isWithinSphere",
        [&](double centerX, double centerY, double centerZ, double width, double pointX, double pointY, double pointZ
        ) -> bool {
            auto s = zc::RegionChecker3D::isWithinSphere(centerX, centerY, centerZ, width, pointX, pointY, pointZ);
            logger.debug(
                "[RegionChecker3D::isWithinSphere]传入: 中心X: {}, 中心Y: {}, 中心Z: {}，半径：{}, 当前X: {}, 当前Y: {}, "
                "当前Z:{}  "
                "=> 返回: {}",
                centerX,
                centerY,
                centerZ,
                width,
                pointX,
                pointY,
                pointZ,
                s
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "RegionChecker3D::isWithinCuboid",
        [&](double leftTopX,
            double leftTopY,
            double leftTopZ,
            double rightBottomX,
            double rightBottomY,
            double rightBottomZ,
            double pointX,
            double pointY,
            double pointZ) -> bool {
            const bool s = zc::RegionChecker3D::isWithinCuboid(
                leftTopX,
                leftTopY,
                leftTopZ,
                rightBottomX,
                rightBottomY,
                rightBottomZ,
                pointX,
                pointY,
                pointZ
            );
            logger.debug(
                "[RegionChecker3D::isWithinCuboid]传入: 左上X: {}, 左上Y: {}, 左上Z: {}, 右下X: {}, 右下Y: {}, 右下Z: {}, "
                "当前X: "
                "{}, 当前Y: {}, 当前Z:{}  => 返回: {}",
                leftTopX,
                leftTopY,
                leftTopZ,
                rightBottomX,
                rightBottomY,
                rightBottomZ,
                pointX,
                pointY,
                pointZ,
                s
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "RegionChecker3D::isWithinCenteredCube",
        [&](double centerX, double centerY, double centerZ, double distance, double x, double y, double z) -> bool {
            auto s = zc::RegionChecker3D::isWithinCenteredCube(centerX, centerY, centerZ, distance, x, y, z);
            logger.debug(
                "[RegionChecker3D::isWithinCenteredCube]传入: 中心X: {}, 中心Y: {}, 中心Z: {}，距离：{}, 当前X: {}, 当前Y: {}, "
                "当前Z:{}  => 返回: {}",
                centerX,
                centerY,
                centerZ,
                distance,
                x,
                y,
                z,
                s
            );
            return s;
        }
    );
    // 边界计算API
    exportAs(
        exportNameSpace,
        "BoundaryChecker::is2D::getExceededBoundaryCircle2D",
        [&](double centerX, double centerZ, double width, double x, double z
        ) -> std::unordered_map<std::string, double> {
            auto s = zc::BoundaryChecker::is2D::getExceededBoundaryCircle2D(centerX, centerZ, width, x, z);
            logger.debug(
                "[BoundaryChecker::is2D::getExceededBoundaryCircle2D]传入: 中心X: {}, 中心Z: {}，半径：{}, 当前X: {}, 当前Z:{}  => "
                "返回: {}",
                centerX,
                centerZ,
                width,
                x,
                z,
                zc::toJson(s)
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "BoundaryChecker::is3D::getExceededBoundaryCircle3D",
        [&](double centerX, double centerY, double centerZ, double width, double x, double y, double z
        ) -> std::unordered_map<std::string, double> {
            auto s = zc::BoundaryChecker::is3D::getExceededBoundaryCircle3D(centerX, centerY, centerZ, width, x, y, z);
            logger.debug(
                "[BoundaryChecker::is3D::getExceededBoundaryCircle3D]传入: 中心X: {}, 中心Y: {}, 中心Z: {}，半径：{}, 当前X: {}, "
                "当前Y: {}, 当前Z:{}  => 返回: {}",
                centerX,
                centerY,
                centerZ,
                width,
                x,
                y,
                z,
                zc::toJson(s)
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "BoundaryChecker::is2D::getExceededBoundaryRectangle2D",
        [&](double minX, double minZ, double maxX, double maxZ, double x, double z
        ) -> std::unordered_map<std::string, double> {
            auto s = zc::BoundaryChecker::is2D::getExceededBoundaryRectangle2D(minX, minZ, maxX, maxZ, x, z);
            logger.debug(
                "[BoundaryChecker::is2D::getExceededBoundaryRectangle2D]传入: 最小X: {}, 最小Z: {}, 最大X: {}, 最大Z: {}, 当前X: "
                "{}, 当前Z:{}  => 返回: {}",
                minX,
                minZ,
                maxX,
                maxZ,
                x,
                z,
                zc::toJson(s)
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "BoundaryChecker::is3D::getExceededBoundaryCube3D",
        [&](double minX, double minY, double minZ, double maxX, double maxY, double maxZ, double x, double y, double z
        ) -> std::unordered_map<std::string, double> {
            auto s = zc::BoundaryChecker::is3D::getExceededBoundaryCube3D(minX, minY, minZ, maxX, maxY, maxZ, x, y, z);
            logger.debug(
                "[BoundaryChecker::is3D::getExceededBoundaryCube3D]传入: 最小X: {}, 最小Y: {}, 最小Z: {}, 最大X: {}, 最大Y: {}, "
                "最大Z: {}, 当前X: {}, 当前Y: {}, 当前Z:{}  => 返回: {}",
                minX,
                minY,
                minZ,
                maxX,
                maxY,
                maxZ,
                x,
                y,
                z,
                zc::toJson(s)
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "BoundaryChecker::is2D::getExceededCenteredBoundary2D",
        [&](double centerX, double centerZ, double width, double x, double z
        ) -> std::unordered_map<std::string, double> {
            auto s = zc::BoundaryChecker::is2D::getExceededCenteredBoundary2D(centerX, centerZ, width, x, z);
            logger.debug(
                "[BoundaryChecker::is2D::getExceededCenteredBoundary2D]传入: 中心X: {}, 中心Z: {}，半径：{}, 当前X: {}, 当前Z:{}  => "
                "返回: {}",
                centerX,
                centerZ,
                width,
                x,
                z,
                zc::toJson(s)
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "BoundaryChecker::is3D::getExceededCenteredBoundary3D",
        [&](double centerX, double centerY, double centerZ, double width, double x, double y, double z
        ) -> std::unordered_map<std::string, double> {
            auto s =
                zc::BoundaryChecker::is3D::getExceededCenteredBoundary3D(centerX, centerY, centerZ, width, x, y, z);
            logger.debug(
                "[BoundaryChecker::is3D::getExceededCenteredBoundary3D]传入: 中心X: {}, 中心Y: {}, 中心Z: {}，半径：{}, 当前X: {}, "
                "当前Y: {}, 当前Z:{}  => 返回: {}",
                centerX,
                centerY,
                centerZ,
                width,
                x,
                y,
                z,
                zc::toJson(s)
            );
            return s;
        }
    );
    // 随机API
    exportAs(
        exportNameSpace,
        "RandomAreaPosition::getRandomCoordinateInCircle",
        [&](double x, double z, double radius) -> std::unordered_map<std::string, int> {
            auto s = zc::RandomAreaPosition::getRandomCoordinateInCircle(x, z, radius);
            logger.debug(
                "[RandomAreaPosition::getRandomCoordinateInCircle]传入: 中心X: {}, 中心Z: {}，半径：{} => 返回: {}",
                x,
                z,
                radius,
                zc::toJson(s)
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "RandomAreaPosition::getRandomCoordinateInRectangle",
        [&](double topLeftX, double topLeftZ, double bottomRightX, double bottomRightZ
        ) -> std::unordered_map<std::string, int> {
            auto s =
                zc::RandomAreaPosition::getRandomCoordinateInRectangle(topLeftX, topLeftZ, bottomRightX, bottomRightZ);
            logger.debug(
                "[RandomAreaPosition::getRandomCoordinateInRectangle]传入: 左上X: {}, 左上Z: {}, 右下X: {}, 右下Z: {} "
                "=> "
                "返回: {}",
                topLeftX,
                topLeftZ,
                bottomRightX,
                bottomRightZ,
                zc::toJson(s)
            );
            return s;
        }
    );
    exportAs(
        exportNameSpace,
        "RandomAreaPosition::getRandomCoordinateInSquare",
        [&](double centerX, double centerZ, double halfLength) -> std::unordered_map<std::string, int> {
            auto s = zc::RandomAreaPosition::getRandomCoordinateInSquare(centerX, centerZ, halfLength);
            logger.debug(
                "[RandomAreaPosition::getRandomCoordinateInSquare]传入: 中心X: {}, 中心Z: {}，半边长：{} => 返回: {}",
                centerX,
                centerZ,
                halfLength,
                zc::toJson(s)
            );
            return s;
        }
    );

    // export end

    auto endTime   = std::chrono::high_resolution_clock::now(); // 记录结束时间
    auto spendTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count(); // 计算耗时
    logger.info("导出API完成，耗时: {}ms", spendTime);
}

} // namespace zc