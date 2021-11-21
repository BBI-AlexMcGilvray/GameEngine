#include "Pipeline/Rendering/3D/Headers/SphereRenderObject.h"

#include "Pipeline/Rendering/Headers/RenderManager.h"

#include "Core/Math/Headers/UtilityFunctions.h"

using namespace Core;
using namespace Core::Math;

using namespace Application::Geometric;

namespace Application {
namespace Rendering {
  SphereRenderObject::SphereRenderObject(Core::Ptr<RenderManager> manager, Ptr<HierarchyTransform> renderTransform, Color color)
    : SphereRenderObject(manager, renderTransform, color, 1.0f)
  {}

  SphereRenderObject::SphereRenderObject(Core::Ptr<RenderManager> manager, Ptr<HierarchyTransform> renderTransform, Color color, float radius)
    : RenderObjectBase(manager, renderTransform, color), Radius(radius), Shader(manager->ObjectShaderManager.DefaultShader)
  {
    Initialize();
  }

  SphereRenderObject::~SphereRenderObject()
  {
    Vao.Delete();
    for (int i = 0; i < Vbos.size(); i++) {
      Vbos[i].Delete();
    }
  }

  void SphereRenderObject::Initialize()
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

    Vbos.push_back(newBuffer);
  }

  void SphereRenderObject::Prepare(const Float4x4 &mvp, const Color &color) const
  {
    Vao.Bind();
    Shader.Prepare(mvp, color);
  }

  void SphereRenderObject::CleanUp() const
  {
    Vao.Unbind();
    Shader.CleanUp();
  }

  void SphereRenderObject::CreateMesh()
  {
    // http://en.wikipedia.org/wiki/Icosahedron
    //(0, +/-1, +/-t)
    //(+/-1, +/-t, 0)
    //(+/-t, 0, +/-1)
    //where t = (1 + sqrt(5)) / 2

    const float t = (1.0f + sqrt(5.0f)) / 2.0f;
    // So each side has a length of sqrt( t*t + 1.0 )
    float rScale = Radius / sqrt(t * t + 1.0f);// correct the radius
    std::vector<Float3> vertices = std::vector<Float3>(12);

    for (int i = 0; i < 4; i++)
      //v[ i ] = Vector( 0, -(i&2), -(i&1)*t ) ;
      vertices[i] = rScale * Float3(0.0f, i & 2 ? -1.0f : 1.0f, i & 1 ? -t : t);

    for (int i = 4; i < 8; i++)
      //v[ i ] = Vector( -(i&2), -(i&1)*t, 0 ) ;
      vertices[i] = rScale * Float3(i & 2 ? -1.0f : 1.0f, i & 1 ? -t : t, 0.0f);

    for (int i = 8; i < 12; i++)
      //v[ i ] = Vector( -(i&1)*t, 0, -(i&2) ) ;
      vertices[i] = rScale * Float3(i & 1 ? -t : t, 0.0f, i & 2 ? -1.0f : 1.0f);

    Float3 normal = Float3(0.0f);
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[2], normal });
    _vertices.push_back({ vertices[8], normal });
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[8], normal });
    _vertices.push_back({ vertices[4], normal });
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[4], normal });
    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[9], normal });
    _vertices.push_back({ vertices[0], normal });
    _vertices.push_back({ vertices[9], normal });
    _vertices.push_back({ vertices[2], normal });

    _vertices.push_back({ vertices[2], normal });
    _vertices.push_back({ vertices[7], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[2], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[8], normal });
    _vertices.push_back({ vertices[2], normal });
    _vertices.push_back({ vertices[9], normal });
    _vertices.push_back({ vertices[7], normal });

    _vertices.push_back({ vertices[8], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[10], normal });
    _vertices.push_back({ vertices[8], normal });
    _vertices.push_back({ vertices[10], normal });
    _vertices.push_back({ vertices[4], normal });

    _vertices.push_back({ vertices[10], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[10], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[10], normal });
    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[4], normal });

    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[4], normal });
    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[11], normal });
    _vertices.push_back({ vertices[1], normal });
    _vertices.push_back({ vertices[11], normal });
    _vertices.push_back({ vertices[6], normal });

    _vertices.push_back({ vertices[6], normal });
    _vertices.push_back({ vertices[11], normal });
    _vertices.push_back({ vertices[9], normal });

    _vertices.push_back({ vertices[11], normal });
    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[7], normal });
    _vertices.push_back({ vertices[11], normal });
    _vertices.push_back({ vertices[7], normal });
    _vertices.push_back({ vertices[9], normal });

    _vertices.push_back({ vertices[3], normal });
    _vertices.push_back({ vertices[5], normal });
    _vertices.push_back({ vertices[7], normal });
  }
}// namespace Rendering
}// namespace Application