#include "Product/Headers/MyProduct.h"

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

#include "Product/Headers/MyState.h"
#include "Product/Headers/RegisterUtils.h"

namespace Product
{
    MyProduct::MyProduct(Application::ApplicationManager& application)
    : _application(application)
    {}

    void MyProduct::initialize()
    {
        _luaManager.initialize();
        _application.StateManager().AddAndGoToState<MyState>();

        RegisterComponents(_application);
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