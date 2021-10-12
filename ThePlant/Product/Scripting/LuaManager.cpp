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
        // _lua.open_libraries(sol::lib::base);
        // registerFunction("helloWorld", "print('hello world')");
    }

    void LuaManager::update(Core::Second dt)
    {
        // loss of rendering may not be due to lua - seems to be due to not properly handling SDL events (might be focus related)
        // repro:
        /*
            - run
            - click outside of game
            - click back to game
            - breaks + unhandled input error
            - running again with same terminal open will then repro again
        */
        for (auto iter = _scripts.begin(); iter != _scripts.end(); ++iter)
        {
            // this will run what we want, but removing for now to reduce spam until this is used more heavily
            //_lua[*iter]();
        }
    }

    void LuaManager::end()
    {
        
    }

    void LuaManager::cleanUp()
    {

    }
}