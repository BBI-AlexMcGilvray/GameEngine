#pragma once

#include "Pipeline/Headers/ApplicationManager.h"

namespace Application {
    // should this be a class to support inheritance (and therefore customization for other components)?
    void RegisterComponents(ApplicationManager& application);
} // namespace Editor