#pragma once

#include "Materials/Core/Headers/PtrDefs.h"
#include "Materials/Core/Headers/TimeDefs.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include "Product/Scripting/LuaManager.h"

namespace Product
{
    class MyProduct
    {
    public:
        MyProduct(Application::ApplicationManager& application);

        void initialize();
        void start();
        void update(Core::Second dt);
        void end();
        void cleanUp();

    private:
        Application::ApplicationManager& _application;
        LuaManager _luaManager;
    };
}