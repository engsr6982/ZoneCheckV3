


namespace zc::RegionChecker2D {

bool isWithinRadius(double centerX, double centerZ, double width, double pointX, double pointZ);

bool isWithinRectangle(
    double leftTopX,
    double leftTopZ,
    double rightBottomX,
    double rightBottomZ,
    double pointX,
    double pointZ
);

bool isWithinCenteredSquare(double centerX, double centerZ, double distance, double x, double z);


} // namespace zc::RegionChecker2D