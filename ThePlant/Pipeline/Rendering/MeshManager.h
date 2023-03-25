#pragma once

#include <unordered_map>

#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Headers/AssetManager.h"

#include "Pipeline/AssetHandling/AssetLoaderFactory.h"
#include "Pipeline/Rendering/Shaders/Shader.h"

namespace Application {
namespace Rendering {
  // holds list of ALL shaders that can be used, handles construction, retrieval and deletion of the shaders
  class MeshManager
  {
  public:
    MeshManager(Data::AssetManager& assetManager, AssetLoaderFactory& assetLoaderFactory);
    ~MeshManager();

    // games should loop through all meshes and add them at game-creation time (once games get big enough, this would get done on level-switch?)
    RenderDataHandle AddMesh(const Data::AssetName<Data::Rendering::SimpleMeshData>& shader);
    RenderDataHandle AddMesh(const Data::AssetName<Data::Rendering::StaticMeshData>& shader);
    RenderDataHandle AddMesh(const Data::AssetName<Data::Rendering::AnimatedMeshData>& shader);

    const MeshData& GetMesh(const RenderDataHandle& handle);
    const MappedMeshData& GetMesh(const RenderDataHandle& handle);
    // NOTE:
    /*
      we have nothing that removes a mesh, if we add one we will need to look at how we will handle using mesh in a threaded context!
    */

  private:
    Data::AssetManager& _assetManager;
    AssetLoaderFactory& _assetLoaderFactory;
    
    std::unordered_map<Data::AssetName<Data::Rendering::SimpleMeshData>, MeshData, Data::AssetNameHasher<Data::Rendering::SimpleMeshData>> _simpleMeshes;
    std::unordered_map<Data::AssetName<Data::Rendering::StaticMeshData>, MeshData, Data::AssetNameHasher<Data::Rendering::StaticMeshData>> _staticMeshes;
    std::unordered_map<Data::AssetName<Data::Rendering::AnimatedMeshData>, MappedMeshData, Data::AssetNameHasher<Data::Rendering::AnimatedMeshData>> _mappedMeshes;

    const MeshData& _EnsureSimpleMeshIsValid(Data::AssetName<Data::Rendering::SimpleMeshData> meshAssetName, MeshData& shader);
    const MeshData& _EnsureStaticMeshIsValid(Data::AssetName<Data::Rendering::StaticMeshData> meshAssetName, MeshData& shader);
    const MeshData& _EnsureMappedMeshIsValid(Data::AssetName<Data::Rendering::AnimatedMeshData> meshAssetName, MappedMeshData& shader);
  };
}// namespace Rendering
}// namespace Application