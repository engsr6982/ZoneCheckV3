#include <iostream>
#include <string>
#include <unordered_map>


namespace zc::BoundaryChecker {

namespace is2D {

std::unordered_map<std::string, double>
getExceededBoundaryCircle2D(double centerX, double centerZ, double width, double x, double z);

std::unordered_map<std::string, double>
getExceededBoundaryRectangle2D(double minX, double minZ, double maxX, double maxZ, double x, double z);


std::unordered_map<std::string, double>
getExceededCenteredBoundary2D(double centerX, double centerZ, double width, double x, double z);

} // namespace is2D

namespace is3D {

std::unordered_map<std::string, double>
getExceededBoundaryCircle3D(double centerX, double centerY, double centerZ, double width, double x, double y, double z);

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
);

std::unordered_map<std::string, double> getExceededCenteredBoundary3D(
    double centerX,
    double centerY,
    double centerZ,
    double width,
    double x,
    double y,
    double z
);

} // namespace is3D


} // namespace zc::BoundaryChecker