#include "ApplicationManagement/Geometric/Headers/ContainerBase.h"

#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

namespace Application {
namespace Geometric {
  ContainerBase::ContainerBase()
  {
  }

  ContainerBase::~ContainerBase()
  {
    ContainerDeleted();
  }

  void ContainerBase::Initialize()
  {
    for (int i = 0; i < Content.size(); i++) {
      Content[i]->Initialize();
    }
  }

  void ContainerBase::Start()
  {
    for (int i = 0; i < Content.size(); i++) {
      Content[i]->Start();
    }
  }

  void ContainerBase::Update(Second dt)
  {
    for (int i = 0; i < Content.size(); i++) {
      Content[i]->Update(dt);
    }
  }

  void ContainerBase::End()
  {
    for (int i = 0; i < Content.size(); i++) {
      Content[i]->End();
    }
  }

  void ContainerBase::CleanUp()
  {
    for (int i = 0; i < Content.size(); i++) {
      Content[i]->CleanUp();
    }
  }

  Ptr<ContentBase> ContainerBase::AddContent(UniquePtr<ContentBase> newContent)
  {
    Push(Content, move(newContent));

    return Content[Content.size() - 1].get();
  }

  void ContainerBase::RemoveContent(Ptr<ContentBase> content)
  {
    for (int i = 0; i < Content.size(); i++) {
      if (Content[i].get() == content) {
        RemoveIndex(Content, i);
      }
    }
  }

  bool ContainerBase::HasContent(Ptr<ContentBase> content)
  {
    for (int i = 0; i < Content.size(); i++) {
      if (Content[i].get() == content) {
        return true;
      }
    }

    return false;
  }
}// namespace Geometric
}// namespace Application