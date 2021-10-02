#include "Product/Scripting/LuaManager.h"

namespace Product
{
    /*LuaTag&*/ void LuaManager::registerFunction(const std::string& name, const std::string& code)
    {
        _lua.script("function " + name + " () " + code + " end");
        _scripts.push_back(std::move(name));
    }

    void LuaManager::initialize()
    {

    }

    void LuaManager::start()
    {
        _lua.open_libraries(sol::lib::base);
        registerFunction("helloWorld", "print('hello world')");
    }

    void LuaManager::update(Core::Second dt)
    {
        for (auto iter = _scripts.begin(); iter != _scripts.end(); ++iter)
        {
            // _lua[*iter]();
        }
    }

    void LuaManager::end()
    {
        
    }

    void LuaManager::cleanUp()
    {

    }
}