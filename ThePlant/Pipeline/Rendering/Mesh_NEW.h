#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Data/Rendering/Headers/SimpleMeshData.h"
#include "Data/Rendering/Headers/StaticMeshData.h"
#include "Data/Rendering/Headers/AnimatedMeshData.h"

#include "Pipeline/Rendering/3D/Headers/VertexData.h"

#include "Pipeline/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLMappedBuffer.h"

namespace Application {
namespace Rendering {
    struct Mesh_NEW
    {
        uint vertices; // number of vertices
        GLArrayBuffer buffer; // vao

    private:
        friend Mesh_NEW CreateMesh(const std::vector<SimpleVertexData>&);
        friend MappedMesh_NEW CreateMesh(const std::vector<SkinnedVertexData>&);

        std::vector<GLBuffer> _vbos; // should be useful to update only certain data when (if) required. NOTE: We are currently NOT using these correctly
        // ex: have one VBO for each piece of data (position, normal, color, ...), then update the specific VBO when it's held data is changed (ex: change color without changing position)

        // do we need to store the data for readability on cpu?
        // if we do, make that a different component? how else can we remove the potential size overhead?
        // needs investigation when relevant - maybe we just use the mapped mesh, as below, with a different flag to read right from the GPU?
    };

    struct MappedMesh_NEW : public Mesh_NEW
    {
        GLMappedBuffer mappedBuffer;
    };

    // should only be called for code-created meshes
    Mesh_NEW CreateMesh(const std::vector<SimpleVertexData>& data);
    MappedMesh_NEW CreateMesh(const std::vector<SkinnedVertexData>& data);

    // these need to be adjusted in the future to not create the same mesh multiple times for the same asset (would need something like we have for shaders)
    Mesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::SimpleMeshData>& data);
    Mesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::StaticMeshData>& data);
    MappedMesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::AnimatedMeshData>& data);
}// namespace Rendering
}// namespace Application