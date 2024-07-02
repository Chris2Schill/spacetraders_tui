#pragma once

#include "engine/core/log.h"

#include <sol/sol.hpp>

inline void lua_bind_log_functions(sol::state& lua) {
    lua.set_function("log_trace",    [](const std::string& s){ LOG_TRACE(s);} );
    lua.set_function("log_info",     [](const std::string& s){ LOG_INFO(s);} );
    lua.set_function("log_warn",     [](const std::string& s){ LOG_WARN(s);} );
    lua.set_function("log_error",    [](const std::string& s){ LOG_ERROR(s);} );
    lua.set_function("log_critical", [](const std::string& s){ LOG_CRITICAL(s);} );
}
