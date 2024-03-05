

namespace zc::RegionChecker3D {

bool isWithinSphere(
    double centerX,
    double centerY,
    double centerZ,
    double width,
    double pointX,
    double pointY,
    double pointZ
);

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
);

bool isWithinCenteredCube(
    double centerX,
    double centerY,
    double centerZ,
    double distance,
    double x,
    double y,
    double z
);


} // namespace zc::RegionChecker3D