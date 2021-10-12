#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/AnimatedMeshData.h"

#include "Pipeline/Rendering/Headers/RenderObjectBase.h"

#include "Pipeline/Rendering/3D/Headers/Skeleton.h"
#include "Pipeline/Rendering/3D/Headers/VertexData.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLMappedBuffer.h"

#include "Pipeline/Rendering/2D/Headers/MaterialComponent.h"

using namespace Core;

namespace Application {
namespace Rendering {
  // holds the information about the mesh of a 3D object
  struct SkinnedMeshBase : public RenderObjectBase
  {
    Data::AssetData<Data::Rendering::AnimatedMeshData> Data;

    SkinnedMeshBase(Core::Ptr<RenderManager> manager, Core::Ptr<Geometric::HierarchyTransform> renderTransform, Data::AssetName<Data::Rendering::AnimatedMeshData> asset);
    ~SkinnedMeshBase();

    Core::size GetVertexCount() const override;

    // should these be a part of render object base?
    void SetMaterialComponent(ComponentPtr<MaterialComponent> materialComponent);
    void ClearMaterialComponent();

    virtual void Initialize();

    void Skin(const Ptr<Skeleton> skeleton);

  protected:
    virtual void Prepare(const Core::Math::Float4x4 &mvp, const Core::Math::Color &color) const;
    virtual void CleanUp() const;

  private:
    // this should be optional so that it is only stored if desired (for reading the data that was passed to the GPU)
    // it could just be cleared after being used
    std::vector<AnimatedVertexData> _runtimeData;
    std::vector<SkinnedVertexData> _renderData;
    GLArrayBuffer Vao;
    List<GLBuffer> Vbos;
    GLMappedBuffer MappedMesh;

    Core::Functionality::Delegate<> _onMaterialDeleted;
    ComponentPtr<MaterialComponent> _materialComponent;
    Core::Ptr<Skeleton> _skeleton;// should be a skeleton component in the future

    void CreateRenderData();
  };
}// namespace Rendering
}// namespace Application