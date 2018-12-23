#include "ApplicationManagement\Geometric\Headers\ContentBase.h"

#include "ApplicationManagement/Geometric/Headers/ContainerBase.h"

namespace Application
{
	namespace Geometric
	{
		ContentBase::ContentBase()
			: OnContainerDeleted([this]
		{
			Container = nullptr;
			return false;
		})
		{

		}

		ContentBase::~ContentBase()
		{
			ContentDeleted();
		}

		void ContentBase::Update(Second dt)
		{
			// nothing by default
		}

		void ContentBase::SetContainer(Ptr<ContainerBase> parentContainer)
		{
			Container = parentContainer;

			Container->ContainerDeleted += OnContainerDeleted;
		}

		Ptr<ContainerBase> ContentBase::GetContainer() const
		{
			return Container;
		}
	}
}