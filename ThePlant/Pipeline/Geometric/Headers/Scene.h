#pragma once

#include "Pipeline/Geometric/Headers/Node.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

namespace Application {
namespace Geometric {
  // a parent scene. holds a list of nodes (that represent that scene's content - all other content types should inherit from Node)
  struct Scene : Node
  {
    Scene(Core::Ptr<State> parentState);
  };
}// namespace Geometric
}// namespace Application