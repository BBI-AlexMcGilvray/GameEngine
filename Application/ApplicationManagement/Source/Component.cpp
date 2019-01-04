#include "ApplicationManagement/Headers/Component.h"

#include "ApplicationManagement/Headers/Entity.h"

using namespace Core;

namespace Application
{
	ComponentBase::ComponentBase(Ptr<EntityBase> entity)
		: ParentEntity(entity)
		, OnEntityDestroyed([this]()
	{
		SetActive(false);
		DeleteComponent();

		return false;
	})
	{

	}

	ComponentBase::~ComponentBase()
	{
		Deleted();
	}

	Ptr<EntityBase> ComponentBase::GetEntity() const
	{
		return ParentEntity;
	}

	void ComponentBase::SetActive(bool active)
	{
		Active = active;
	}

	bool ComponentBase::IsActive() const
	{
		return Active;
	}

	void ComponentBase::DeleteComponent()
	{
		Delete = true;
	}

	bool ComponentBase::ShouldBeDeleted() const
	{
		return Delete;
	}

	void ComponentBase::Initialize()
	{
		// nothing by default
	}

	void ComponentBase::Start()
	{
		// nothing by default
	}

	void ComponentBase::Update()
	{
		// nothing by default
	}

	void ComponentBase::End()
	{
		// nothing by default
	}

	void ComponentBase::CleanUp()
	{
		// nothing by default
	}
}