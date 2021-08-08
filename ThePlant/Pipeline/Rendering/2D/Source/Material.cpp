#include "Pipeline/Rendering/2D/Headers/Material.h"

namespace Application {
namespace Rendering {
  Material::Material()
  {}

  Material::Material(Data::AssetName<Data::Rendering::MaterialData> asset)
    : Data(asset)
  {
    // shader should be part of material data in the future so that it can be saved
  }

  void Material::SetShader(Core::Ptr<ObjectShaderBase> shader)
  {
    Shader = shader;
  }

  void Material::Prepare(const Core::Math::Float4x4 &mvp, const Core::Math::Color &color) const
  {
    Shader->Prepare(mvp, color);
  }

  void Material::CleanUp() const
  {
    Shader->CleanUp();
  }

  void Material::Update(Core::Second dt)
  {
    // used for animated materials later? tbd
  }
}// namespace Rendering
}// namespace Application