#include "FindPos.h"
#include "../../Entry.h"
#include "../../PluginInfo.h"
#include "ll/api/service/Bedrock.h"
#include "ll/api/service/ServerInfo.h"
#include "ll/api/service/Service.h"
#include "ll/api/service/ServiceId.h"
#include "ll/api/utils/HashUtils.h"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/BlockSource.h"
#include "mc/world/level/ChunkBlockPos.h"
#include "mc/world/level/Level.h"
#include "mc/world/level/block/Block.h"
#include "mc/world/level/block/actor/BlockActor.h"
#include "mc/world/level/chunk/LevelChunk.h"
#include "mc/world/level/dimension/Dimension.h"
#include <RemoteCallAPI.h>
#include <algorithm>
#include <cstddef>
#include <exception>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>


using string = std::string;

/* jsvascript

findPos(
    {
        x: 0,
        z: 0,
        dimid: 0
    },
    {
        startingValue: 301
        endValue: 0
        stopValue: 10
    },
    [
        "minecraft:lava",
        "minecraft:flowing_lava"
    ], 
    {
        "offset1": 1,
        "offset2": 2
    }
): {
    status: 0 | 1,
    x: int,
    y: int,
    z: int,
    dimid: int
}

*/


#define uMap std::unordered_map<string, int>
#define defaultReturn                                                                                                  \
    uMap def;                                                                                                          \
    def["status"] = 0;                                                                                                 \
    def["x"]      = 0;                                                                                                 \
    def["y"]      = 0;                                                                                                 \
    def["z"]      = 0;                                                                                                 \
    def["dimid"]  = 0;                                                                                                 \
    return def;


struct FindArgs {
    int                 startingValue;   // 遍历开始值
    int                 endValue;        // 结束值
    int                 stopValue;       // 停止值
    std::vector<string> dangerousBlocks; // 危险方块
    int                 x;               // 输入x
    int                 z;               // 输入z
    int                 dimid;           // 输入维度
    int                 offset1 = 1;     // 偏移量1
    int                 offset2 = 2;     // 偏移量2
};


class IntVec4 {
public:
    int             x, y, z;
    int             dim;
    inline BlockPos getBlockPos() { return {x, y, z}; }
    inline int      getDimensionId() { return dim; }
};


// 获取方块封装
Block const& getBlock(BlockPos& bp, int dimid) {
    return ll::service::getLevel()->getDimension(dimid)->getBlockSourceFromMainChunkSource().getBlock(bp);
}
Block const& getBlock(int y, BlockPos bp, int dimid) {
    bp.y = y;
    return getBlock(bp, dimid);
}
// std::optional<Block> getBlock(int x, int y, int z, int dimid) {
//     IntVec4 pos;
//     pos.dim = dimid;
//     pos.x   = x;
//     pos.y   = y;
//     pos.z   = z;
//     auto dimidPtr = ll::service::getLevel()->getDimension(pos.dim).get(); // dimidPtr
//     if (!dimidPtr) return std::nullopt;
//     BlockSource& bs = dimidPtr->getBlockSourceFromMainChunkSource();
//     auto         lc = bs.getChunkAt(pos.getBlockPos());
//     if (!lc) return std::nullopt;
//     short minHeight = dimidPtr->getMinHeight();
//     if (pos.y < minHeight || pos.y > dimidPtr->getHeight()) return {};
//     ChunkBlockPos cbpos = ChunkBlockPos(pos.getBlockPos(), minHeight);
//     auto          block = &const_cast<Block&>(lc->getBlock(cbpos));
//     if (!block) return std::nullopt;
//     BlockPos bp{pos.x, pos.y, pos.z};
//     return getBlock(bp, dimid);
// }


bool findElementInVector(const std::vector<string>& vec, string target) {
    if (vec.empty()) {
        return false;
    }
    return std::find(vec.begin(), vec.end(), target) != vec.end();
}


uMap findPos(const FindArgs& arg) {
    auto& logger = zoneCheckV3::getSelfPluginInstance().getLogger();
    try {
        uMap backValue;
        backValue["x"]      = arg.x;
        backValue["z"]      = arg.z;
        backValue["dimid"]  = arg.dimid;
        backValue["y"]      = 0;
        backValue["status"] = 0;

        if (arg.startingValue < arg.endValue) {
            defaultReturn
        }

        BlockPos bp;
        bp.x = arg.x;
        bp.y = arg.startingValue;
        bp.z = arg.z;

        int currentTraversalY = arg.startingValue;
        while (currentTraversalY > arg.endValue) {
            try {
                bp.y           = currentTraversalY; // 更新BlockPos对象的y值以匹配当前的currentTraversalY
                auto const& bl = getBlock(bp, arg.dimid); // 获取方块对象引用

                logger.debug(
                    "[Finding] Y: {}    Block: {}    BlockType: {}    Vec4: {}, {}, {}, {}",
                    currentTraversalY,
                    bl.getName().c_str(),
                    bl.getTypeName().c_str(),
                    bp.x,
                    bp.y,
                    bp.z,
                    arg.dimid
                );

                if (bl.getTypeName() == "minecraft:air") {
                    // 空气方块跳过
                    currentTraversalY--;
                    continue;
                } else if (currentTraversalY <= arg.stopValue || findElementInVector(arg.dangerousBlocks, bl.getTypeName())) {
                    logger.debug("[Stop] 到达结束位置 / 有危险方块");
                    // 到达结束位置 / 脚下岩浆方块
                    break;
                } else if (
                    bl.getTypeName() != "minecraft:air" && // 落脚方块
                    getBlock(currentTraversalY + arg.offset1, bp, arg.dimid).getTypeName()
                        == "minecraft:air" // 玩家身体 下半
                    && getBlock(currentTraversalY + arg.offset2, bp, arg.dimid).getTypeName()
                           == "minecraft:air" // 玩家身体 上半
                ) {
                    // 安全位置   落脚点安全、上两格是空气
                    backValue["y"]      = currentTraversalY;
                    backValue["status"] = 1;
                    logger.debug("[Finded] 找到安全坐标");
                    break;
                }
                currentTraversalY--; // 递减currentTraversalY以进行下一次迭代
            } catch (const std::exception& e) {
                logger.debug("Fail in findPos, Chunk is not load! \n {}", e.what());
                defaultReturn
            } catch (...) {
                logger.fatal("An unknown exception occurred in findPos! (while)");
                defaultReturn
            }
        }

        if (backValue["status"] != 1) {
            logger.debug("[Failed] 未找到安全坐标");
            defaultReturn
        } else {
            logger.debug(
                "[Success] status: {}, x: {}, y: {}, z: {}, dimid: {}",
                backValue["status"],
                backValue["z"],
                backValue["y"],
                backValue["z"],
                backValue["dimid"]
            );
            return backValue;
        }
    } catch (const std::exception& e) {
        logger.fatal("Fail to findPos \n {}", e.what());
        defaultReturn
    } catch (...) {
        logger.fatal("An unknown exception occurred in findPos");
        defaultReturn
    }
}


void exportFindPos() {
    auto& logger        = zoneCheckV3::getSelfPluginInstance().getLogger();
    // logger.consoleLevel = 5;
    RemoteCall::exportAs(
        PLUGIN_NAME,
        "findPos",
        [&](uMap vec2, uMap inputForInfo, std::vector<string> inputDangerousBlocks, uMap inputOffSet) -> uMap {
            try {
                FindArgs args;
                // 判空
                if (vec2.empty() || inputForInfo.empty()) {
                    logger.debug("arg1 or arg2 is empty");
                    defaultReturn
                }
                if (!vec2.count("x") || !vec2.count("z") || !vec2.count("dimid")) {
                    logger.debug("arg1 {x,z,dimid} have empty");
                    defaultReturn
                }
                if (!inputForInfo.count("startingValue") || !inputForInfo.count("endValue")
                    || !inputForInfo.count("stopValue")) {
                    logger.debug("arg2 {startingValue, endValue, stopValue} have empty");
                    defaultReturn
                }
                // 基本信息
                args.x     = vec2["x"];
                args.z     = vec2["z"];
                args.dimid = vec2["dimid"];
                // 遍历信息
                args.startingValue = inputForInfo["startingValue"];
                args.endValue      = inputForInfo["endValue"];
                args.stopValue     = inputForInfo["stopValue"];
                // 危险方块
                args.dangerousBlocks = inputDangerousBlocks;

                // 偏移量
                if (inputOffSet.empty() != true) {
                    if (inputOffSet.count("offset1")) args.offset1 = inputOffSet["offset1"];
                    if (inputOffSet.count("offset2")) args.offset2 = inputOffSet["offset2"];
                }

                logger.debug(
                    // clang-format off
                    "[Args]: Arg1 => x: {}, z: {}, dimid: {}  |  Arg2 => start: {}, end: {}, stop: {}  |  Arg3 => {}  |  Arg4: {}, {}",
                    // clang-format on
                    args.x,
                    args.z,
                    args.dimid,
                    args.startingValue,
                    args.endValue,
                    args.stopValue,
                    args.dangerousBlocks.size(),
                    args.offset1,
                    args.offset2
                );

                return findPos(args);
            } catch (const std::exception& e) {
                logger.fatal("Fail to findPos, Please check your input args\n {}", e.what());
                defaultReturn
            }
        }
    );
}