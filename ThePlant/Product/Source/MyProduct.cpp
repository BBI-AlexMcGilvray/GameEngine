#include "Product/Headers/MyProduct.h"

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

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
        DEBUG_PROFILE_SCOPE("MyProduct::Update");
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