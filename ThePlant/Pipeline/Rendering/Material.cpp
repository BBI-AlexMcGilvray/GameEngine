#include "Pipeline/Rendering/Material.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Data/Rendering/Headers/MaterialData.h"

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
        SCOPED_MEMORY_CATEGORY("Rendering");        
        _context.emplace(std::make_pair<std::string, ShaderVariant>(std::string(f.name()), f.get()));
      }

  private:
      ShaderContext& _context;
  };

  Material CreateDefaultMaterial(ShaderManager& shaderManager)
  {
    Material defaultMaterial;
    defaultMaterial.shader = shaderManager.GetDefaultShader();
    
    Data::Rendering::MaterialContext defaultContext = { Core::Math::WHITE, Core::Math::WHITE, Core::Math::WHITE, 0.0 };
    reflector::visit_all(defaultContext, context_creator(defaultMaterial.shaderContext));

    return defaultMaterial;
  }

  Material CreateMaterial(const Data::AssetData<Data::Rendering::MaterialData>& data, ShaderManager& shaderManager)
  {
    Material material;
    material.shader = shaderManager.GetShader(data->shader);

    reflector::visit_all(data->context, context_creator(material.shaderContext));

    return material;
  }
} // namespace Application
} // namespace Rendering