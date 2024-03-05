#pragma once

#include <ll/api/plugin/NativePlugin.h>

namespace zoneCheckV3 {

[[nodiscard]] auto getSelfPluginInstance() -> ll::plugin::NativePlugin&;

} // namespace zoneCheckV3
