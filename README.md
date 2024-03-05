# ZoneCheck 区域检查/计算边界

一个前置插件，用于计算各种区域、边界

## API接口

> 注意：  
>
> 1. 命名空间为：`ZoneCheckV3`
> 2. 使用以下接口请参照[远程调用参数类型对照](https://lse.liteldev.com/zh/apis/ScriptAPI/Ll/#_6)
>
> 导入示例：
>
> ```javascript
> ll.imports("ZoneCheckV3", "Region2D_isWithinRadius");      
> ```

### 2D类

`RegionChecker2D::isWithinRadius`  
检查一个点是否在给定的圆内

- 参数:  
  - centerX : `number`  
  圆心的X坐标
  - centerZ : `number`  
  圆心的Z坐标
  - width: `number`  
   圆的半径
  - pointX: `number`  
  点的X坐标
  - pointZ: `number`  
  点的Z坐标
- 返回值：`boolean`

`RegionChecker2D::isWithinRectangle`  
检查一个点是否在给定的矩形内

- 参数:  
  - leftTopX : `number`  
  左上角的X坐标
  - leftTopZ : `number`  
  左上角的Z坐标
  - rightBottomX: `number`  
  右下角的X坐标
  - rightBottomZ: `number`  
  右下角的Z坐标
  - pointX : `number`  
  点的X坐标
  - pointZ : `number`  
  点的Z坐标
- 返回值：`boolean`

`RegionChecker2D::isWithinCenteredSquare`  
检查一个点是否在给定的以中心点为中心的正方形内

- 参数:  
  - centerX : `number`  
  中心点的X坐标
  - centerZ : `number`  
  中心点的Z坐标
  - distance : `number`  
  到正方形边的距离
  - x : `number`  
  点的X坐标
  - z : `number`  
  点的Z坐标
- 返回值：`boolean`

### 3D类

`RegionChecker3D::isWithinSphere`  
检查一个点是否在给定的球体内

- 参数:  
  - centerX : `number`  
  球心的X坐标
  - centerY : `number`  
  球心的Y坐标
  - centerZ : `number`  
  球心的Z坐标
  - width : `number`  
  球的半径
  - pointX : `number`  
  点的X坐标
  - pointY : `number`  
  点的Y坐标
  - pointZ : `number`  
  点的Z坐标
- 返回值：`boolean`

`RegionChecker3D::isWithinCuboid`  
检查一个点是否在给定的立方体内

- 参数:  
  - leftTopX : `number`  
  左上角的X坐标
  - leftTopY : `number`  
  左上角的Y坐标
  - leftTopZ : `number`  
  左上角的Z坐标
  - rightBottomX : `number`  
  右下角的X坐标
  - rightBottomY : `number`  
  右下角的Y坐标
  - rightBottomZ : `number`  
  右下角的Z坐标
  - pointX : `number`  
  点的X坐标
  - pointY : `number`  
  点的Y坐标
  - pointZ : `number`  
  点的Z坐标
- 返回值：`boolean`

`RegionChecker3D::isWithinCenteredCube`  
检查一个点是否在给定的以中心点为中心的立方体内

- 参数:  
  - centerX : `number`  
  中心点的X坐标
  - centerY : `number`  
  中心点的Y坐标
  - centerZ : `number`  
  中心点的Z坐标
  - distance : `number`  
  到立方体边的距离
  - x : `number`  
  点的X坐标
  - y : `number`  
  点的Y坐标
  - z : `number`  
  点的Z坐标
- 返回值：`boolean`

### 边界

`BoundaryChecker::is2D::getExceededBoundaryCircle2D`  
获取超出2D圆形边界的信息

- 参数:  
  - centerX: `number`  
  圆心的X坐标
  - centerZ: `number`  
  圆心的Z坐标
  - width: `number`  
   圆的宽度
  - x : `number`  
  点的X坐标
  - z : `number`  
  点的Z坐标
- 返回值：`object`

```json
{
  "axis": 0,
  "value": 0,
  "boundary": 0
}
```

`BoundaryChecker::is2D::getExceededBoundaryRectangle2D`  
获取超出2D矩形边界的信息

- 参数:  
  - minX : `number`  
  矩形左上角的X坐标
  - minZ : `number`  
  矩形左上角的Z坐标
  - maxX : `number`  
  矩形右下角的X坐标
  - maxZ : `number`  
  矩形右下角的Z坐标
  - x : `number`  
  点的X坐标
  - z : `number`  
  点的Z坐标
- 返回值：`object`

```json
{
  "axis": 0,
  "value": 0,
  "boundary": 0
}
```

`BoundaryChecker::is2D::getExceededCenteredBoundary2D`  
获取超出以中心点为中心的2D正方形边界的信息

- 参数:  
  - centerX: `number`  
   中心点的X坐标
  - centerZ: `number`  
   中心点的Z坐标
  - width : `number`  
  正方形的宽度
  - x : `number`  
  点的X坐标
  - z : `number`  
  点的Z坐标
- 返回值：`object`

```json
{
  "axis": 0,
  "value": 0,
  "boundary": 0
}
```

`BoundaryChecker::is3D::getExceededBoundaryCircle3D`  
获取超出3D圆形边界的信息

- 参数:  
  - centerX  : `number`  
  圆心的X坐标
  - centerY  : `number`  
  圆心的Y坐标
  - centerZ  : `number`  
  圆心的Z坐标
  - width  : `number`  
  圆的半径
  - x : `number`  
  点的X坐标
  - y : `number`  
  点的Y坐标
  - z : `number`  
  点的Z坐标
- 返回值：`object`

```json
{
  "axis": 0,
  "value": 0,
  "boundary": 0
}
```

`BoundaryChecker::is3D::getExceededBoundaryCube3D`  
获取超出3D立方体边界的信息

- 参数:  
  - minX : `number`  
  立方体左上角的X坐标
  - minY : `number`  
  立方体左上角的Y坐标
  - minZ : `number`  
  立方体左上角的Z坐标
  - maxX : `number`  
  立方体右下角的X坐标
  - maxY : `number`  
  立方体右下角的Y坐标
  - maxZ : `number`  
  立方体右下角的Z坐标
  - x  : `number`  
  点的X坐标
  - y  : `number`  
  点的Y坐标
  - z  : `number`  
  点的Z坐标
- 返回值：`object`

```json
{
  "axis": 0,
  "value": 0,
  "boundary": 0
}
```

`BoundaryChecker::is3D::getExceededCenteredBoundary3D`  
获取超出以中心点为中心的3D立方体边界的信息

- 参数:  
  - centerX : `number`  
  中心点的X坐标
  - centerY : `number`  
  中心点的Y坐标
  - centerZ : `number`  
  中心点的Z坐标
  - width: `number`  
  立方体的宽度
  - x : `number`  
  点的X坐标
  - y : `number`  
  点的Y坐标
  - z : `number`  
  点的Z坐标
- 返回值：`object`

```json
{
  "axis": 0,
  "value": 0,
  "boundary": 0
}
```

### 随机

`RandomAreaPosition::getRandomCoordinateInCircle`  
在圆形区域内生成随机坐标

- 参数:  
  - x: `number`  
    圆心x轴坐标
  - z: `number`  
    圆心y轴坐标
  - radius: `number`  
    圆半径
- 返回值：`object`

```json
{ "x": 0, "z": 0 }
```

`RandomAreaPosition::getRandomCoordinateInRectangle`  
在矩形区域内生成随机坐标

- 参数:  
  - topLeftX: `number`  
    矩形左上角的X坐标
  - topLeftZ: `number`  
    矩形左上角的Z坐标
  - bottomRightX: `number`  
    矩形右下角的X坐标
  - bottomRightZ: `number`  
    矩形右下角的Z坐标
- 返回值：`object`

```json
{ "x": 0, "z": 0 }
```

`RandomAreaPosition::getRandomCoordinateInSquare`  
在正方形区域内生成随机坐标

- 参数:  
  - centerX : `number`  
    正方形中心点的X坐标
  - centerZ : `number`  
    正方形中心点的Z坐标
  - halfLength : `number`  
    半边长
- 返回值：`object`

```json
{ "x": 0, "z": 0 }
```
