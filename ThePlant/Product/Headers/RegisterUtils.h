#pragma once

#include "Pipeline/Headers/ApplicationManager.h"

namespace Product {
    // should this be a class to support inheritance (and therefore customization for other components)?
    void RegisterComponents(Application::ApplicationManager& application);
} // namespace Editor