#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Rendering/Headers/AnimatedMeshData.h"

#include "Pipeline/Rendering/3D/Headers/VertexData.h"

#include "Pipeline/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLMappedBuffer.h"

namespace Application {
namespace Rendering {
    struct Mesh_NEW;
    struct MappedMesh_NEW;

    // should only be called for code-created meshes
    Mesh_NEW CreateMesh(const std::vector<SimpleVertexData>& data);
    Mesh_NEW CreateMesh(const std::vector<VertexData>& data);
    MappedMesh_NEW CreateMesh(const std::vector<SkinnedVertexData>& data);

    struct Mesh_NEW
    {
        size_t vertices; // number of vertices
        GLArrayBuffer buffer; // vao

        // maybe not the AssetData<...>, but AssetName<...>? Because AssetData will hold onto a shared_ptr and could affect lifetime
        // AssetData<MeshData> in debug?

        bool operator==(const Mesh_NEW& other) const
        {
            return (vertices == other.vertices && buffer == other.buffer);
        }

    private:
        friend Mesh_NEW CreateMesh(const std::vector<SimpleVertexData>&);
        friend Mesh_NEW CreateMesh(const std::vector<VertexData>& data);
        friend MappedMesh_NEW CreateMesh(const std::vector<SkinnedVertexData>&);

        GLBuffer _vbo; // should be useful to update only certain data when (if) required. NOTE: We are currently NOT using these correctly
        // ex: have one VBO for each piece of data (position, normal, color, ...), then update the specific VBO when it's held data is changed (ex: change color without changing position)

        // do we need to store the data for readability on cpu?
        // if we do, make that a different component? how else can we remove the potential size overhead?
        // needs investigation when relevant - maybe we just use the mapped mesh, as below, with a different flag to read right from the GPU?
    };

    struct MappedMesh_NEW
    {
        Mesh_NEW mesh;
        GLMappedBuffer skeletonBuffer;

        bool operator==(const MappedMesh_NEW& other) const
        {
            return (skeletonBuffer == other.skeletonBuffer && mesh == other.mesh);
        }

    private:
        friend MappedMesh_NEW CreateMesh(const std::vector<SkinnedVertexData>&);
    };

    // these need to be adjusted in the future to not create the same mesh multiple times for the same asset (would need something like we have for shaders)
    Mesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::SimpleMeshData>& data);
    Mesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::StaticMeshData>& data);
    MappedMesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::AnimatedMeshData>& data);
}// namespace Rendering
}// namespace Application