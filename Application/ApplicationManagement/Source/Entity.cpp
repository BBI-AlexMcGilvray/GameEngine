#include "ApplicationManagement/Headers/Entity.h"

namespace Application
{
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
		for (auto const& component : Components)
		{
			component.second->Start();
		}
	}

	void EntityBase::Update()
	{
		for (auto const& component : Components)
		{
			component.second->Update();
		}
	}

	void EntityBase::End()
	{
		for (auto const& component : Components)
		{
			component.second->End();
		}
	}

	void EntityBase::CleanUp()
	{
		for (auto const& component : Components)
		{
			component.second->CleanUp();
		}
	}
}