#pragma once

#include <vector>

#include "Materials/Core/Headers/TimeDefs.h"

#include "Product/Dependencies/sol2-3.2.3/include/sol/sol.hpp"

namespace Product
{
    using LuaTag = sol::load_result;
    using LuaReturn = sol::protected_function_result;

    // sol2 documentation: https://sol2.readthedocs.io/en/latest/tutorial/all-the-things.html#opening-a-state
    class LuaManager
    {
    public:
        // need methods to pass in a function or a string to register with the lua context
        /*[[nodiscard]] LuaTag&*/ void registerFunction(const std::string& name, const std::string& code);
        // LuaTag& registerScript(const Core::FilePath& file);

        void initialize();
        void start();

        // update all lua scripts (in the order they are registered)
        void update(Core::Second dt);

        void end();
        void cleanUp();

    private:
        sol::state _lua;
        // will need to be more than just 'lua tags' - should be an object that contains state (last result, if it should be executed this tick, ...)
        std::vector<std::string> _scripts;
    };
}