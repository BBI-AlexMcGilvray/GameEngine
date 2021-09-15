#include "Pipeline/Rendering/3D/Headers/VertexData.h"

namespace Application
{
    namespace Rendering
    {
        std::vector<SimpleVertexData> createRuntimeData(const Data::Rendering::SimpleMeshData& meshData)
        {
            std::vector<SimpleVertexData> runtimeData;

            // do we need the field vertexCount? could we not just use indices.size()?
            for(uint i = 0; i < meshData.vertexCount; i++)
            {
                Core::Math::Uint3 indices = meshData.indices[i];

                runtimeData.push_back({ meshData.positions[indices.X], meshData.normals[indices.X] });
                runtimeData.push_back({ meshData.positions[indices.Y], meshData.normals[indices.Y] });
                runtimeData.push_back({ meshData.positions[indices.Z], meshData.normals[indices.Z] });
            }

            return runtimeData;
        }

        std::vector<VertexData> createRuntimeData(const Data::Rendering::StaticMeshData& meshData)
        {
            std::vector<VertexData> runtimeData;

            // do we need the field vertexCount? could we not just use indices.size()?
            for(uint i = 0; i < meshData.vertexCount; i++)
            {
                Core::Math::Uint3 indices = meshData.indices[i];

                runtimeData.push_back({ meshData.positions[indices.X], meshData.normals[indices.X], meshData.uvs[indices.X] });
                runtimeData.push_back({ meshData.positions[indices.Y], meshData.normals[indices.Y], meshData.uvs[indices.Y] });
                runtimeData.push_back({ meshData.positions[indices.Z], meshData.normals[indices.Z], meshData.uvs[indices.Z] });
            }

            return runtimeData;
        }

        std::vector<AnimatedVertexData> createRuntimeData(const Data::Rendering::AnimatedMeshData& meshData)
        {
            std::vector<AnimatedVertexData> runtimeData;

            // do we need the field vertexCount? could we not just use indices.size()?
            for(uint i = 0; i < meshData.indices.size(); i++)
            {
                Core::Math::Uint3 indices = meshData.indices[i];

                runtimeData.push_back({ meshData.positions[indices.X], meshData.normals[indices.X], meshData.uvs[indices.X], meshData.boneNames[indices.X], meshData.boneWeights[indices.X] });
                runtimeData.push_back({ meshData.positions[indices.Y], meshData.normals[indices.Y], meshData.uvs[indices.Y], meshData.boneNames[indices.Y], meshData.boneWeights[indices.Y] });
                runtimeData.push_back({ meshData.positions[indices.Z], meshData.normals[indices.Z], meshData.uvs[indices.Z], meshData.boneNames[indices.Z], meshData.boneWeights[indices.Z] });
            }

            return runtimeData;
        }
    }
}