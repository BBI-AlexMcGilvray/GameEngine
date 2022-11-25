#pragma once

#include "Core/Headers/PtrDefs.h"

#include "Pipeline/UI/IMGUI/Window.h"

#include "Pipeline/Factory_Temp/ComponentRefUIFactory.h"

namespace Editor {
    class Factory;

namespace UI {
// this serves as the base level stuff for factory ui (aka an editor window)
//      -> the 'details' ui will be an instance/part of this that shows what is currently selected
namespace IMGUI {
    class ArchetypesUI : public Application::UI::IMGUI::Window
    {
    public:
        ArchetypesUI(Factory& factory);

        void Draw() override;

        // ComponentRefUIFactory& GetComponentRefUIFactory();

    private:
        Factory& _factory;
        // ComponentRefUIFactory _uiFactory;
    };
} // namespace IMGUI
} // namespace UI
} // namespace Editor