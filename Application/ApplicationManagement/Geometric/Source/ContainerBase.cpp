#include "ApplicationManagement/Geometric/Headers/ContainerBase.h"

#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

namespace Application
{
	namespace Geometric
	{
		ContainerBase::ContainerBase()
		{

		}

		ContainerBase::~ContainerBase()
		{
			// tell content that it's node was deleted
			if (Content != nullptr)
			{
				Content->OnContainerDeletion();
			}
		}

		void ContainerBase::Update(Second dt)
		{
			// update content as it may affect children
			if (Content != nullptr)
			{
				Content->Update(dt);
			}
		}

		void ContainerBase::Render(Renderer& renderer, Float4x4 transformationMatrix) const
		{
			// render content with the passed in positional information
			if (Content != nullptr)
			{
				Content->Render(renderer, transformationMatrix);
			}
		}

		void ContainerBase::SetContent(UniquePtr<ContentBase> newContent)
		{
			if (newContent != nullptr)
			{
				newContent->OnContainerSet(this);
				RemoveContent();
				Content = move(newContent);
			}
		}

		void ContainerBase::RemoveContent()
		{
			if (Content != nullptr)
			{
				Content->OnContainerDeletion();
			}
			Content = nullptr;
		}
	}
}