#include "Pipeline\Rendering\3D\Headers\SimpleMeshBase.h"

#include "Pipeline/Headers/ApplicationManager.h"

namespace Application {
namespace Rendering {
  SimpleMeshBase::SimpleMeshBase(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Data::AssetName<Data::Rendering::SimpleMeshData> asset)
    : RenderObjectBase(manager, renderTransform), Data(ApplicationManager::AppAssetManager().getAssetData(asset)), _onMaterialDeleted([this] {
        ClearMaterialComponent();

        return false;
      })
  {
    Initialize();
  }

  SimpleMeshBase::~SimpleMeshBase()
  {
    Vao.Delete();
    for (int i = 0; i < Vbos.size(); i++) {
      Vbos[i].Delete();
    }
  }

  Core::size SimpleMeshBase::GetVertexCount() const
  {
    return Data->vertexCount;
  }

  void SimpleMeshBase::SetMaterialComponent(ComponentPtr<MaterialComponent> materialComponent)
  {
    _materialComponent = materialComponent;
  }

  void SimpleMeshBase::ClearMaterialComponent()
  {
    _materialComponent = ComponentPtr<MaterialComponent>(nullptr);
  }

  void SimpleMeshBase::Initialize()
  {
    Vao.Generate();
    Vao.Bind();

    auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
    newBuffer.Generate();
    newBuffer.Bind();

    // glBufferData( < type >, < size of data >, < start of data >, < draw type >);
    // the Data->Data would go away with a DataPtr<T>
    glBufferData(newBuffer.Type, Data->vertexCount * sizeof(Data::Rendering::SimpleVertexDataBase), &(Data->vertices[0]), GL_STATIC_DRAW);

    // glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
    // position
    glEnableVertexAttribArray(0);// this matches with object shader construction
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::SimpleVertexDataBase), (void *)(offsetof(Data::Rendering::SimpleVertexDataBase, Data::Rendering::SimpleVertexDataBase::position)));
    // normal
    glEnableVertexAttribArray(1);// this matches with object shader construction
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::SimpleVertexDataBase), (void *)(offsetof(Data::Rendering::SimpleVertexDataBase, Data::Rendering::SimpleVertexDataBase::normal)));

    Vao.Unbind();// must be done first, as it stores the states of the binded vbos
    newBuffer.Unbind();
    glDisableVertexAttribArray(0);

    Push(Vbos, newBuffer);
  }

  void SimpleMeshBase::Prepare(const Core::Math::Float4x4 &mvp, const Core::Math::Color &color) const
  {
    Vao.Bind();

    if ((bool)_materialComponent) {
      _materialComponent->GetMaterial()->Prepare(mvp, color);
    }
  }

  void SimpleMeshBase::CleanUp() const
  {
    Vao.Unbind();

    if ((bool)_materialComponent) {
      _materialComponent->GetMaterial()->CleanUp();
    }
  }
}// namespace Rendering
}// namespace Application