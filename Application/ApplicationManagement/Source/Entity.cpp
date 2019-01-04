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
		// child classes will be adding in and initializing components here
	}

	void EntityBase::Start()
	{
		// start all components
	}

	void EntityBase::Update()
	{
		// update all components
	}

	void EntityBase::End()
	{
		// end all components
	}

	void EntityBase::CleanUp()
	{
		// clean up all components
	}
}