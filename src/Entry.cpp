#include "Entry.h"
#include "PluginInfo.h"

#include <filesystem>
#include <fmt/format.h>
#include <functional>
#include <ll/api/Config.h>
#include <ll/api/io/FileUtils.h>
#include <ll/api/plugin/NativePlugin.h>
#include <ll/api/plugin/PluginManagerRegistry.h>
#include <ll/api/service/ServerInfo.h>
#include <memory>
#include <stdexcept>


// include all
#include "./ZoneCheckCore/Core/BoundaryChecker.h"
#include "./ZoneCheckCore/Core/RandomAreaPosition.h"
#include "./ZoneCheckCore/Core/RegionChecker2D.h"
#include "./ZoneCheckCore/Core/RegionChecker3D.h"
#include "./ZoneCheckCore/FindPos/FindPos.h"
#include "./ZoneCheckCore/Remote/Remote.h"
#include "./ZoneCheckCore/Utils/Utils.h"


namespace zoneCheckV3 {

namespace {

std::unique_ptr<std::reference_wrapper<ll::plugin::NativePlugin>>
    selfPluginInstance; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

auto disable(ll::plugin::NativePlugin& /*self*/) -> bool {
    auto& logger = getSelfPluginInstance().getLogger();

    logger.info("disabling...");

    // Your code here.

    logger.info("disabled");

    return false;
}

auto enable(ll::plugin::NativePlugin& /*self*/) -> bool {
    auto& logger = getSelfPluginInstance().getLogger();

    logger.info("enabling...");

    logger.info("enabled");

    return true;
}

auto load(ll::plugin::NativePlugin& self) -> bool {
    auto& logger = self.getLogger();
    logger.info("loading...");
    selfPluginInstance = std::make_unique<std::reference_wrapper<ll::plugin::NativePlugin>>(self);


    // Your code here.
    logger.info("Autor: {}", PLUGIN_AUTHOR);
    logger.info(
        "Version: {}.{}.{} for Levilamina and BDS Protocol {}",
        PLUGIN_VERSION_MAJOR,
        PLUGIN_VERSION_MINOR,
        PLUGIN_VERSION_REVISION,
        PLUGIN_TARGET_BDS_PROTOCOL_VERSION
    );
    // 检查配置
    if (std::filesystem::exists("./plugins/PPOUI/debug")) {
        logger.consoleLevel = 5;
        logger.warn("Printing debugging information is enabled");
    }
    if (ll::getServerProtocolVersion() != PLUGIN_TARGET_BDS_PROTOCOL_VERSION) {
        logger.warn("The bedrock server protocol version does not match, which can lead to unexpected errors. ");
        logger.warn(
            "Current protocol version {}  Adaptation protocol version {}",
            ll::getServerProtocolVersion(),
            PLUGIN_TARGET_BDS_PROTOCOL_VERSION
        );
    }
    zc::startExports();
    exportFindPos();

    logger.info("loaded");
    return true;
}

auto unload(ll::plugin::NativePlugin& self) -> bool {
    auto& logger = self.getLogger();

    logger.info("unloading...");

    selfPluginInstance.reset();

    // Your code here.

    logger.info("unloaded");

    return true;
}

} // namespace

auto getSelfPluginInstance() -> ll::plugin::NativePlugin& {
    if (!selfPluginInstance) {
        throw std::runtime_error("selfPluginInstance is null");
    }

    return *selfPluginInstance;
}

} // namespace zoneCheckV3

extern "C" {
_declspec(dllexport) auto ll_plugin_disable(ll::plugin::NativePlugin& self) -> bool {
    return zoneCheckV3::disable(self);
}
_declspec(dllexport) auto ll_plugin_enable(ll::plugin::NativePlugin& self) -> bool { return zoneCheckV3::enable(self); }
_declspec(dllexport) auto ll_plugin_load(ll::plugin::NativePlugin& self) -> bool { return zoneCheckV3::load(self); }
_declspec(dllexport) auto ll_plugin_unload(ll::plugin::NativePlugin& self) -> bool { return zoneCheckV3::unload(self); }
}
