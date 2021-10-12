#include "Pipeline/Rendering/2D/Headers/BoxRenderObject.h"

#include "Pipeline/Rendering/Headers/RenderManager.h"

using namespace Core;
using namespace Core::Math;

using namespace Application::Geometric;

namespace Application {
namespace Rendering {
  BoxRenderObject::BoxRenderObject(Core::Ptr<RenderManager> manager, Ptr<HierarchyTransform> renderTransform, Color color)
    : BoxRenderObject(manager, renderTransform, color, Float2(1.0f))
  {}

  BoxRenderObject::BoxRenderObject(Core::Ptr<RenderManager> manager, Ptr<HierarchyTransform> renderTransform, Color color, float width, float height)
    : BoxRenderObject(manager, renderTransform, color, Float2(width, height))
  {}

  BoxRenderObject::BoxRenderObject(Core::Ptr<RenderManager> manager, Ptr<HierarchyTransform> renderTransform, Color color, Float2 scale)
    : RenderObjectBase(manager, renderTransform, color), Scale(scale), Shader(manager->ObjectShaderManager.DefaultShader)
  {
    Initialize();
  }

  BoxRenderObject::~BoxRenderObject()
  {
    Vao.Delete();
    for (int i = 0; i < Vbos.size(); i++) {
      Vbos[i].Delete();
    }
  }

  void BoxRenderObject::Initialize()
  {
    Float3 center = 0.0f;// want box to be centered on transform

    _vertices.push_back({ Float3{ center.X - Scale.X, center.Y - Scale.Y, 0.0f }, Float3{ 0.0f } });
    _vertices.push_back({ Float3{ center.X - Scale.X, center.Y + Scale.Y, 0.0f }, Float3{ 0.0f } });
    _vertices.push_back({ Float3{ center.X + Scale.X, center.Y + Scale.Y, 0.0f }, Float3{ 0.0f } });

    _vertices.push_back({ Float3{ center.X + Scale.X, center.Y + Scale.Y, 0.0f }, Float3{ 0.0f } });
    _vertices.push_back({ Float3{ center.X + Scale.X, center.Y - Scale.Y, 0.0f }, Float3{ 0.0f } });
    _vertices.push_back({ Float3{ center.X - Scale.X, center.Y - Scale.Y, 0.0f }, Float3{ 0.0f } });

    Vao.Generate();
    Vao.Bind();

    auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
    newBuffer.Generate();
    newBuffer.Bind();

    // glBufferData( < type >, < size of data >, < start of data >, < draw type >);
    glBufferData(newBuffer.Type, _vertices.size() * sizeof(SimpleVertexData), &_vertices[0], GL_STATIC_DRAW);

    // glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
    // position
    glEnableVertexAttribArray(0);// this matches with object shader construction
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertexData), (void *)(0));
    // normal
    glEnableVertexAttribArray(1);// this matches with object shader construction
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertexData), (void *)(offsetof(SimpleVertexData, SimpleVertexData::position)));

    Vao.Unbind();// must be done first, as it stores the states of the binded vbos
    newBuffer.Unbind();
    glDisableVertexAttribArray(0);

    Vbos.push_back(newBuffer);
  }

  void BoxRenderObject::Prepare(const Float4x4 &mvp, const Color &color) const
  {
    Vao.Bind();
    Shader.Prepare(mvp, color);
  }

  void BoxRenderObject::CleanUp() const
  {
    Vao.Unbind();
    Shader.CleanUp();
  }
}// namespace Rendering
}// namespace Application