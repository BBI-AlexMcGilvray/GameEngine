#include "Pipeline/Rendering/Headers/Material_NEW.h"

#include "Pipeline/Rendering/Shaders/Headers/ShaderManager.h"

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
          if (f.get() == f.self.shader) // maybe there is a nicer way to do this, probably by having MaterialData split into 'ShaderData' and 'ShaderValues' - but we can deal with that later
          {
              return;
          }
          
          _context.insert(std::make_pair(f.name(), f.get()));
          _json->AddElement(f.name(), object_writer_visitor<raw_type_t<decltype(f.get())>>().Write(f.get()));
      }

  private:
      ShaderContext& _context;
  };

  Material_NEW CreateMaterial(const Data::Rendering::MaterialData& data, ShaderManager& shaderManager)
  {
    Material_NEW material(shaderManager.GetShader(data.shader));

    reflector::visit_all(data, context_creator(material.shaderContext));

    return material;
  }
} // namespace Application
} // namespace Rendering