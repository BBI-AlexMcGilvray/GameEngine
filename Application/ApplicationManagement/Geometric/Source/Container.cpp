#include "ApplicationManagement/Geometric/Headers/Container.h"

#include "ApplicationManagement/Geometric/Headers/Content.h"

namespace Application
{
	namespace Geometric
	{
		Container::Container()
		{

		}

		Container::Container(Float3 position, FQuaternion rotation, Float3 scale)
			: Transform(position, rotation, scale)
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

		void Container::Render(const Renderer& renderer, Float4x4 transformationMatrix)
		{
			// pass down modified transformation matrix
			auto modifiedTransformationMatrix = GetTransformationMatrix() * transformationMatrix;

			// render contents for above reason
			for (auto& content : ContainerContents)
			{
				content->Render(renderer, modifiedTransformationMatrix);
			}
		}

		void Container::AddContent(Ptr<Content> newContent)
		{
			for (auto& content : ContainerContents)
			{
				if (content == newContent)
				{
					return;
				}
			}

			Push(ContainerContents, newContent);
			newContent->OnContainerSet(this);
		}

		void Container::RemoveContent(Ptr<Content> oldContent)
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