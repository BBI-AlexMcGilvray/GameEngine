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
			ContainerDeleted();
		}

		void ContainerBase::Initialize()
		{

		}

		void ContainerBase::Start()
		{

		}

		void ContainerBase::Update(Second dt)
		{
			for (int i = 0; i < Content.size(); i++)
			{
				Content[i]->Update(dt);
			}
		}

		void ContainerBase::End()
		{

		}

		void ContainerBase::CleanUp()
		{

		}

		Ptr<ContentBase> ContainerBase::AddContent(UniquePtr<ContentBase> newContent)
		{
			Push(Content, move(newContent));

			return Content[Content.size() - 1].get();
		}

		void ContainerBase::RemoveContent(Ptr<ContentBase> content)
		{
			for (int i = 0; i < Content.size(); i++)
			{
				if (Content[i].get() == content)
				{
					RemoveIndex(Content, i);
				}
			}
		}

		bool ContainerBase::HasContent(Ptr<ContentBase> content)
		{
			for (int i = 0; i < Content.size(); i++)
			{
				if (Content[i].get() == content)
				{
					return true;
				}
			}

			return false;
		}
	}
}