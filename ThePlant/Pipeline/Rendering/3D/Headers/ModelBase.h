#pragma once

#include "Pipeline/Geometric/Headers/ContentBase.h"

#include "Pipeline/Rendering/Shaders/Headers/ObjectShader.h"

#include "Pipeline/Rendering/2D/Headers/MaterialComponent.h"
#include "Pipeline/Rendering/Headers/RenderComponent.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SimpleModelData.h"

namespace Application {
namespace Rendering {
  class SimpleMeshBase;

  // holds the mesh, texture(s), and shader that a model uses
  struct ModelBase : public Geometric::ContentBase
  {
    Data::AssetData<Data::Rendering::SimpleModelData> Data;
    //Material Material;
    //SimpleMeshBase Mesh;

    // this should be loading up the model data instead of the mesh data
    ModelBase(const Core::Ptr<State> owningState, Core::Ptr<Geometric::HierarchyTransform> renderTransform, Data::AssetName<Data::Rendering::SimpleModelData> asset);

    //Core::size GetVertexCount() const override;

    void Initialize() override;
    void Start() override;
    void Update(Core::Second dt) override;
    void End() override;
    void CleanUp() override;

  protected:
    //ObjectShader& Shader;

    //void Prepare(const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const override;
    //void CleanUp() const override;

  private:
    // do we need this?
    Core::Ptr<Geometric::HierarchyTransform> _transform;

    ComponentPtr<MaterialComponent> _materialComponent;
    ComponentPtr<Render> _renderComponent;
  };
}// namespace Rendering
}// namespace Application