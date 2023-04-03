#include "Pipeline/Rendering/MeshManager.h"

#include "Pipeline/Rendering/Headers/RenderDataCreator.h"

namespace Application {
namespace Rendering {
    MeshManager::MeshManager(Data::AssetManager& assetManager, AssetLoaderFactory& assetLoaderFactory)
    : _assetManager(assetManager)
    , _assetLoaderFactory(assetLoaderFactory)
    {
        _assetLoaderFactory.Register(Core::HashType<Data::Rendering::SimpleMeshData>(), [&](State& state, const Data::AssetName<void>& asset)
        {
            AddMesh(Data::AssetName<Data::Rendering::SimpleMeshData>(asset));
        });
        _assetLoaderFactory.Register(Core::HashType<Data::Rendering::StaticMeshData>(), [&](State& state, const Data::AssetName<void>& asset)
        {
            AddMesh(Data::AssetName<Data::Rendering::StaticMeshData>(asset));
        });
        // need to look into how this can be supported (since we require a skeleton it doesn't seem possible?)
        // probably would need a 'ModelManager' (or just helper class) that registers a function that calls all the requirements for a model
        // _assetLoaderFactory.Register(Core::HashType<Data::Rendering::AnimatedMeshData>(), [&](State& state, const Data::AssetName<void>& asset, const Data::AssetName<Data::Rendering::SkeletonData>& skeleton)
        // {
        //     AddMesh(Data::AssetName<Data::Rendering::AnimatedMeshData>(asset));
        // });
    }

    MeshManager::~MeshManager()
    {
        _assetLoaderFactory.Unregister(Core::HashType<Data::Rendering::SimpleMeshData>());
        _assetLoaderFactory.Unregister(Core::HashType<Data::Rendering::StaticMeshData>());
        // _assetLoaderFactory.Unregister(Core::HashType<Data::Rendering::AnimatedMeshData>()); // see coment on register

        // need to destroy all different types of meshes (with a function ideally)
        // and make sure no handles are valid
    }

    RenderDataHandle MeshManager::AddMesh(const Data::AssetName<Data::Rendering::SimpleMeshData>& meshName)
    {
        MeshData newMesh;
        Core::instanceId<RenderData> newMeshId = newMesh.GetID();

        auto& addedMesh = _meshes.emplace(newMeshId, std::move(newMesh));

        _meshesToCreate.emplace(newMeshId, [this, newMeshId, meshName](MeshData& mesh)
        {            
            auto meshData = _assetManager.getAssetData(meshName);
            RenderDataCreator::InitializeRenderData(mesh, &CreateSimpleMesh, meshData);
        });

        return addedMesh.first->second.GetHandle();
    }

    RenderDataHandle MeshManager::AddMesh(const Data::AssetName<Data::Rendering::StaticMeshData>& meshName)
    {
        MeshData newMesh;
        Core::instanceId<RenderData> newMeshId = newMesh.GetID();

        auto& addedMesh = _meshes.emplace(newMeshId, std::move(newMesh));

        _meshesToCreate.emplace(newMeshId, [this, newMeshId, meshName](MeshData& mesh)
        {            
            auto meshData = _assetManager.getAssetData(meshName);
            RenderDataCreator::InitializeRenderData(mesh, &CreateStaticMesh, meshData);
        });

        return addedMesh.first->second.GetHandle();
    }

    RenderDataHandle MeshManager::AddMesh(const Data::AssetName<Data::Rendering::AnimatedMeshData>& meshName, const Data::AssetName<Data::Rendering::SkeletonData>& skeletonName)
    {
        MeshData newMesh;
        Core::instanceId<RenderData> newMeshId = newMesh.GetID();

        auto& addedMesh = _meshes.emplace(newMeshId, std::move(newMesh));

        _meshesToCreate.emplace(newMeshId, [this, meshName, skeletonName](MeshData& mesh)
        {            
            auto meshData = _assetManager.getAssetData(meshName);
            auto skeletonData = _assetManager.getAssetData(skeletonName);
            RenderDataCreator::InitializeRenderData(mesh, &CreateAnimatedMesh, meshData, skeletonData);
        });

        return addedMesh.first->second.GetHandle();
    }

    RenderDataHandle MeshManager::AddMesh(std::function<void(MeshData&)> meshCreator)
    {
        MeshData newMesh;
        Core::instanceId<RenderData> newMeshId = newMesh.GetID();

        auto& addedMesh = _meshes.emplace(newMeshId, std::move(newMesh));

        _meshesToCreate.emplace(newMeshId, [this, newMeshId, meshCreator](MeshData& mesh)
        {            
            RenderDataCreator::InitializeRenderData(mesh, meshCreator);
        });

        return addedMesh.first->second.GetHandle();
    }

    const MeshData& MeshManager::GetMesh(const RenderDataHandle& handle)
    {
        auto& mesh = _meshes.find(handle.GetRenderDataID());
        if (auto creation = _meshesToCreate.find(handle.GetRenderDataID()); creation != _meshesToCreate.end())
        {
            creation->second(mesh->second);
        }

        return mesh->second;
    }

    // MeshData& MeshManager::_EnsureMeshIsValid(const RenderDataHandle& handle)
    // {

    // }

    // MappedMeshData& MeshManager::_EnsureMappedMeshIsValid(const RenderDataHandle& handle)
    // {

    // }
}// namespace Rendering
}// namespace Application