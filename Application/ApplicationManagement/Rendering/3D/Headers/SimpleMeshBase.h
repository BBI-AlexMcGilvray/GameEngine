#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"

#include "ApplicationManagement/Rendering/2D/Headers/Material.h"
#include "ApplicationManagement/Rendering/2D/Headers/MaterialComponent.h"

using namespace Core;

namespace Application {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  class SimpleMeshBase : public RenderObjectBase
  {
  public:
    Data::AssetData<Data::Rendering::SimpleMeshData> Data;

    SimpleMeshBase(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Data::AssetName<Data::Rendering::SimpleMeshData> asset);
    ~SimpleMeshBase();

    Core::size GetVertexCount() const override;

    void SetMaterialComponent(ComponentPtr<MaterialComponent> materialComponent);
    void ClearMaterialComponent();

    virtual void Initialize();

  protected:
    void Prepare(const Core::Math::Float4x4 &mvp, const Core::Math::Color &color) const override;
    void CleanUp() const override;

  private:
    GLArrayBuffer Vao;
    List<GLBuffer> Vbos;

    Core::Functionality::Delegate<> _onMaterialDeleted;
    ComponentPtr<MaterialComponent> _materialComponent;
  };
}// namespace Rendering
}// namespace Application