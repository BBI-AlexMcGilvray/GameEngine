#include "Pipeline/Rendering/3D/Headers/SkinnedMeshBase.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include "Pipeline/Rendering/Shaders/Headers/SkinnedObjectShader.h"
#include "Pipeline/Rendering/3D/Headers/VertexData.h"

using namespace Core;

namespace Application {
namespace Rendering {
  SkinnedMeshBase::SkinnedMeshBase(Core::Ptr<RenderManager> manager, Core::Ptr<Geometric::HierarchyTransform> renderTransform, Data::AssetName<Data::Rendering::AnimatedMeshData> asset)
    : RenderObjectBase(manager, renderTransform), Data(ApplicationManager::AppAssetManager().getAssetData(asset)), _onMaterialDeleted([this] {
        ClearMaterialComponent();

        return false;
      })
  {
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
    return _runtimeData.size();
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

    // if we want to allow for modifying the vertex (or just reading the data), this should be stored in the instance
    _runtimeData = createRuntimeData(*Data);
    CreateRenderData();

    // glBufferData( < type >, < size of data >, < start of data >, < draw type >); // GL_DYNAMIC_DRAW because Skin(...) could be called multiple times, changing indices
    glBufferData(newBuffer.Type, _renderData.size() * sizeof(Application::Rendering::SkinnedVertexData), &(_renderData[0]), GL_DYNAMIC_DRAW);

    // glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
    // position
    glEnableVertexAttribArray(0);// this matches with object shader construction
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::position)));
    // normal
    glEnableVertexAttribArray(1);// this matches with object shader construction
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::normal)));
    // bone weight
    glEnableVertexAttribArray(2);// this matches with object shader construction
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::boneWeight)));
    // bone indices
    glEnableVertexAttribArray(3);// this matches with object shader construction
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::boneIndices)));

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
    for (int i = 0; i < _runtimeData.size(); i++) {
      const AnimatedVertexData& vertexData = _runtimeData[i];
      Application::Rendering::SkinnedVertexData& vertexRenderData = _renderData[i];

      int bonesPerVert = 4;
      for (int j = 0; j < bonesPerVert; j++) {
        if (j < vertexData.boneName.size() && vertexData.boneName[j] != "") {
          // boneIndices needs to be a float because of GPU issues when it was an int (didn't read correctly)
          vertexRenderData.boneIndices[j] = static_cast<float>(skeleton->GetIndexOf(vertexData.boneName[j]));
        } else {
          // unused bone indices should be zeroed out by the weight
          vertexRenderData.boneIndices[j] = 0.0f;
        }
      }
    }

    // Update the data in the opengl buffer
    MappedMesh.Map(GL_WRITE_ONLY);
    MappedMesh.Assign(&(_renderData[0]), _renderData.size() * sizeof(Application::Rendering::SkinnedVertexData));
    MappedMesh.Unmap();
  }

  void SkinnedMeshBase::CreateRenderData()
  {
    for (int i = 0; i < _runtimeData.size(); i++) {
      _renderData.push_back(SkinnedVertexData(_runtimeData[i]));
    }
  }
}// namespace Rendering
}// namespace Application