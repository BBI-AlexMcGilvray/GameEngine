#include "ApplicationManagement/Rendering/3D/Headers/SkinnedMeshBase.h"
#include "ApplicationManagement/Rendering/Shaders/Headers/SkinnedObjectShader.h"

// testing
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Debugging/Headers/Macros.h"

using namespace Core;

namespace Application {
namespace Rendering {
  SkinnedMeshBase::SkinnedMeshBase(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Data::AssetName<Data::Rendering::AnimatedMeshData> asset)
    : RenderObjectBase(manager, renderTransform), Data(asset), _onMaterialDeleted([this] {
        ClearMaterialComponent();

        return false;
      })
  {
    CreateRenderData();
    Initialize();
  }

  SkinnedMeshBase::~SkinnedMeshBase()
  {
    Vao.Delete();
    for (int i = 0; i < Vbos.size(); i++) {
      Vbos[i].Delete();
    }

    // do we need to delete MappedMesh?
  }

  Core::size SkinnedMeshBase::GetVertexCount() const
  {
    return Data.Data.VertexCount;
  }

  void SkinnedMeshBase::SetMaterialComponent(ComponentPtr<MaterialComponent> materialComponent)
  {
    _materialComponent = materialComponent;
  }

  void SkinnedMeshBase::ClearMaterialComponent()
  {
    _materialComponent = ComponentPtr<MaterialComponent>(nullptr);
  }

  void SkinnedMeshBase::Initialize()
  {
    Vao.Generate();
    Vao.Bind();

    auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
    newBuffer.Generate();
    newBuffer.Bind();

    // glBufferData( < type >, < size of data >, < start of data >, < draw type >); // GL_DYNAMIC_DRAW because Skin(...) could be called multiple times, changing indices
    glBufferData(newBuffer.Type, RenderData.size() * sizeof(Application::Rendering::AnimatedVertexRenderDataBase), &(RenderData[0]), GL_DYNAMIC_DRAW);

    // glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
    // position
    glEnableVertexAttribArray(0);// this matches with object shader construction
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::AnimatedVertexRenderDataBase), (void *)(offsetof(Application::Rendering::AnimatedVertexRenderDataBase, Application::Rendering::AnimatedVertexRenderDataBase::Position)));
    // normal
    glEnableVertexAttribArray(1);// this matches with object shader construction
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::AnimatedVertexRenderDataBase), (void *)(offsetof(Application::Rendering::AnimatedVertexRenderDataBase, Application::Rendering::AnimatedVertexRenderDataBase::Normal)));
    // bone weight
    glEnableVertexAttribArray(2);// this matches with object shader construction
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::AnimatedVertexRenderDataBase), (void *)(offsetof(Application::Rendering::AnimatedVertexRenderDataBase, Application::Rendering::AnimatedVertexRenderDataBase::BoneWeight)));
    // bone indices
    glEnableVertexAttribArray(3);// this matches with object shader construction
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::AnimatedVertexRenderDataBase), (void *)(offsetof(Application::Rendering::AnimatedVertexRenderDataBase, Application::Rendering::AnimatedVertexRenderDataBase::BoneIndices)));

    Vao.Unbind();// must be done first, as it stores the states of the binded vbos
    newBuffer.Unbind();
    glDisableVertexAttribArray(0);

    Push(Vbos, newBuffer);

    // keep track of mesh data to write to
    MappedMesh = GLMappedBuffer(&Vbos[0]);
  }

  void SkinnedMeshBase::Prepare(const Core::Math::Float4x4 &mvp, const Core::Math::Color &color) const
  {
    Vao.Bind();

    if ((bool)_materialComponent) {
      // need a better way to do this that doesn't involve static casting (or casting it here at least)
      static_cast<Ptr<SkinnedObjectShader>>(_materialComponent->GetMaterial()->Shader)->SetSkinningInformation(_skeleton->GetBoneMatrices());
      _materialComponent->GetMaterial()->Prepare(mvp, color);
    }
  }

  void SkinnedMeshBase::CleanUp() const
  {
    Vao.Unbind();

    if ((bool)_materialComponent) {
      _materialComponent->GetMaterial()->CleanUp();
    }
  }

  void SkinnedMeshBase::Skin(const Ptr<Skeleton> skeleton)
  {
    _skeleton = skeleton;
    for (int i = 0; i < Data.Data.Vertices.size(); i++) {
      Data::Rendering::AnimatedVertexDataBase vertexData = Data.Data.Vertices[i];
      Application::Rendering::AnimatedVertexRenderDataBase vertexRenderData = RenderData[i];

      int bonesPerVert = 4;
      for (int j = 0; j < bonesPerVert; j++) {
        if (j < vertexData.BoneName.size() && vertexData.BoneName[j] != "") {
          // BoneIndices needs to be a float because of GPU issues when it was an int (didn't read correctly)
          vertexRenderData.BoneIndices[j] = static_cast<float>(skeleton->GetIndexOf(vertexData.BoneName[j]));
        } else {
          // unused bone indices should be zeroed out by the weight
          vertexRenderData.BoneIndices[j] = 0.0f;
        }
      }

      RenderData[i] = vertexRenderData;
    }

    // Update the data in the opengl buffer
    MappedMesh.Map(GL_WRITE_ONLY);
    MappedMesh.Assign(&(RenderData[0]), RenderData.size() * sizeof(Application::Rendering::AnimatedVertexRenderDataBase));
    MappedMesh.Unmap();
  }

  void SkinnedMeshBase::CreateRenderData()
  {
    for (int i = 0; i < Data.Data.Vertices.size(); i++) {
      Push(RenderData, AnimatedVertexRenderDataBase(Data.Data.Vertices[i]));
    }
  }
}// namespace Rendering
}// namespace Application