#pragma once

#include <unordered_map>

#include "Data/Rendering/Headers/AnimatedMeshData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Headers/AssetManager.h"

#include "Pipeline/AssetHandling/AssetLoaderFactory.h"
#include "Pipeline/Rendering/Mesh.h"
#include "Pipeline/Rendering/Shaders/Shader.h"

namespace Application {
namespace Rendering {
  // holds list of ALL meshes that can be used, handles construction, retrieval and deletion of the meshes
  class MeshManager
  {
  public:
    MeshManager(Data::AssetManager& assetManager, AssetLoaderFactory& assetLoaderFactory);
    ~MeshManager();

    // games should loop through all meshes and add them at game-creation time (once games get big enough, this would get done on level-switch?)

    // the below are helper methods to make things easier
    RenderDataHandle AddMesh(const Data::AssetName<Data::Rendering::SimpleMeshData>& meshName);
    RenderDataHandle AddMesh(const Data::AssetName<Data::Rendering::StaticMeshData>& meshName);
    RenderDataHandle AddMesh(const Data::AssetName<Data::Rendering::AnimatedMeshData>& meshName, const Data::AssetName<Data::Rendering::SkeletonData>& skeletonName);
    // this is the runtime version
    RenderDataHandle AddMesh(std::function<void(MeshData&)> meshCreator);

    const MeshData& GetMesh(const RenderDataHandle& handle);
    // NOTE:
    /*
      we have nothing that removes a mesh, if we add one we will need to look at how we will handle using mesh in a threaded context!
    */

  private:
    Data::AssetManager& _assetManager;
    AssetLoaderFactory& _assetLoaderFactory;
    
    // trying _not_ storing these by asset name (meshes can be created at runtime)
    // => if we want to save them later, their asset names must be tracked separately
    std::unordered_map<Core::instanceId<RenderData>, MeshData, Core::instanceIdHasher<RenderData>> _meshes;

    std::unordered_map<Core::instanceId<RenderData>, std::function<void(MeshData&)>, Core::instanceIdHasher<RenderData>> _meshesToCreate;

    // MeshData& _EnsureMeshIsValid(const RenderDataHandle& handle);
    // MappedMeshData& _EnsureMappedMeshIsValid(const RenderDataHandle& handle);
  };
}// namespace Rendering
}// namespace Application