#include "Product/Headers/MyProduct.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include "Product/Headers/MyState.h"

namespace Product
{
    void MyProduct::initialize()
    {
        _luaManager.initialize();

        auto application = Application::ApplicationManager::Application();
        application->AppStateManager().AddAndGoToState<MyState>();
    }

    void MyProduct::start()
    {
        _luaManager.start();
    }

    void MyProduct::update(Core::Second dt)
    {
        _luaManager.update(dt);
    }

    void MyProduct::end()
    {
        _luaManager.end();
    }

    void MyProduct::cleanUp()
    {
        _luaManager.cleanUp();
    }
}