#include "Pipeline/Rendering/Material_NEW.h"

#include "Pipeline/Rendering/Shaders/ShaderManager.h"

namespace Application {
namespace Rendering {
  struct context_creator
  {
      context_creator(ShaderContext& context)
      : _context(context)
      {}

      template<typename FieldData>
      void operator()(FieldData f)
      {          
        _context.emplace(std::make_pair<std::string, ShaderVariant>(std::string(f.name()), f.get()));
      }

  private:
      ShaderContext& _context;
  };

  Material_NEW CreateMaterial(const Data::AssetData<Data::Rendering::MaterialData>& data, ShaderManager& shaderManager)
  {
    Material_NEW material;
    material.shader = shaderManager.GetShader(data->shader);

    reflector::visit_all(data->context, context_creator(material.shaderContext));

    return material;
  }
} // namespace Application
} // namespace Rendering