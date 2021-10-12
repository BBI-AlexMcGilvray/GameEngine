#include "Pipeline/Rendering/3D/Headers/CubeRenderObject.h"

#include "Pipeline/Rendering/Headers/RenderManager.h"

using namespace Core;
using namespace Core::Math;

using namespace Application::Geometric;

namespace Application {
namespace Rendering {
  CubeRenderObject::CubeRenderObject(Core::Ptr<RenderManager> manager, Ptr<HierarchyTransform> renderTransform, Color color)
    : CubeRenderObject(manager, renderTransform, color, Float3(1.0f))
  {}

  CubeRenderObject::CubeRenderObject(Core::Ptr<RenderManager> manager, Ptr<HierarchyTransform> renderTransform, Color color, float width, float height, float depth)
    : CubeRenderObject(manager, renderTransform, color, Float3(width, height, depth))
  {}

  CubeRenderObject::CubeRenderObject(Core::Ptr<RenderManager> manager, Ptr<HierarchyTransform> renderTransform, Color color, Float3 scale)
    : RenderObjectBase(manager, renderTransform, color), Scale(scale), Shader(manager->ObjectShaderManager.DefaultShader)
  {
    Initialize();
  }

  CubeRenderObject::~CubeRenderObject()
  {
    Vao.Delete();
    for (int i = 0; i < Vbos.size(); i++) {
      Vbos[i].Delete();
    }
  }

  void CubeRenderObject::Initialize()
  {
    CreateMesh();

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

    Push(Vbos, newBuffer);
  }

  void CubeRenderObject::Prepare(const Float4x4 &mvp, const Color &color) const
  {
    Vao.Bind();
    Shader.Prepare(mvp, color);
  }

  void CubeRenderObject::CleanUp() const
  {
    Vao.Unbind();
    Shader.CleanUp();
  }

  void CubeRenderObject::CreateMesh()
  {
    std::vector<Float3> vertices = List<Float3>(8);
    vertices.push_back(Float3(-Scale.X, -Scale.Y, -Scale.Z));
    vertices.push_back(Float3(-Scale.X, Scale.Y, -Scale.Z));
    vertices.push_back(Float3(Scale.X, Scale.Y, -Scale.Z));
    vertices.push_back(Float3(Scale.X, -Scale.Y, -Scale.Z));
    vertices.push_back(Float3(Scale.X, -Scale.Y, Scale.Z));
    vertices.push_back(Float3(Scale.X, Scale.Y, Scale.Z));
    vertices.push_back(Float3(-Scale.X, Scale.Y, Scale.Z));
    vertices.push_back(Float3(-Scale.X, -Scale.Y, Scale.Z));

    Float3 normal = 0.0f;

    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[2], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[2], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[4], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[2], normal });
    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[4], normal });
    _vertices.push_back({ vertices[7], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[7], normal });
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[7], normal });
    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[4], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[4], normal });
    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[7], normal });
  }
}// namespace Rendering
}// namespace Application