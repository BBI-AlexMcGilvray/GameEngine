#include "Pipeline/Headers/Entity.h"

#include "Core/Debugging/Headers/Macros.h"
#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline//StateSystem/Headers/State.h"
using namespace Core;

namespace Application {
EntityBase::EntityBase(const Ptr<State> owningState)
  : _onwningState(owningState)
{
}

EntityBase::~EntityBase()
{
  OnDestroyed();
}

void EntityBase::Initialize()
{
  // nothing by default
  //	- not initializing components as they are initialized on load
  // child classes will be adding in and initializing components here
}

void EntityBase::Start()
{
  // nothing by default
}

void EntityBase::Update(Second dt)
{
  // nothing by default
}

void EntityBase::End()
{
  // nothing by default
}

void EntityBase::CleanUp()
{
  for (auto const &component : Components) {
    component.second->CleanUp();
  }
}
}// namespace Application