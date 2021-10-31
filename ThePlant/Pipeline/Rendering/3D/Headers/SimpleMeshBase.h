#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"

#include "Pipeline/ECS/ObjectOriented/Headers/ComponentPtr.h"
#include "Pipeline/Rendering/Headers/RenderObjectBase.h"

#include "Pipeline/Rendering/3D/Headers/VertexData.h"

#include "Pipeline/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLBuffer.h"

#include "Pipeline/Rendering/2D/Headers/Material.h"
#include "Pipeline/Rendering/2D/Headers/MaterialComponent.h"

using namespace Core;

namespace Application {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  class SimpleMeshBase : public RenderObjectBase
  {
  public:
    Data::AssetData<Data::Rendering::SimpleMeshData> Data;

    SimpleMeshBase(Core::Ptr<RenderManager> manager, Core::Ptr<Geometric::HierarchyTransform> renderTransform, Data::AssetName<Data::Rendering::SimpleMeshData> asset);
    ~SimpleMeshBase();

    Core::size GetVertexCount() const override;

    void SetMaterialComponent(ComponentPtr<MaterialComponent> materialComponent);
    void ClearMaterialComponent();

    virtual void Initialize();

  protected:
    void Prepare(const Core::Math::Float4x4 &mvp, const Core::Math::Color &color) const override;
    void CleanUp() const override;

  private:
    // this should be optional so that it is only stored if desired (for reading the data that was passed to the GPU)
    // it could just be cleared after being used
    std::vector<SimpleVertexData> _runtimeData;
    GLArrayBuffer Vao;
    List<GLBuffer> Vbos;

    Core::Functionality::Delegate<> _onMaterialDeleted;
    ComponentPtr<MaterialComponent> _materialComponent;
  };
}// namespace Rendering
}// namespace Application