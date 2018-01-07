#include "ApplicationManagement/Geometric/Headers/Container.h"

#include "ApplicationManagement/Geometric/Headers/Content.h"

namespace Application
{
	namespace Geometric
	{
		Container::Container()
		{

		}

		Container::~Container()
		{
			// tell each content that it's node was deleted
			for (auto& content : ContainerContents)
			{
				content->OnContainerDeletion();
			}
		}

		void Container::Update(Second dt)
		{
			// update contents as it may affect children
			for (auto& content : ContainerContents)
			{
				content->Update(dt);
			}
		}

		void Container::Render(Renderer& renderer, Float4x4 transformationMatrix)
		{
			// render contents with the passed in positional information
			for (auto& content : ContainerContents)
			{
				content->Render(renderer, transformationMatrix);
			}
		}

		void Container::AddContent(SharedPtr<Content> newContent)
		{
			for (auto& content : ContainerContents)
			{
				if (content == newContent)
				{
					return;
				}
			}

			newContent->OnContainerSet(this);
			Push(ContainerContents, move(newContent));
		}

		void Container::RemoveContent(SharedPtr<Content> oldContent)
		{
			for (auto& content : ContainerContents)
			{
				if (content == oldContent)
				{
					Remove(ContainerContents, oldContent);
					return;
				}
			}
		}
	}
}