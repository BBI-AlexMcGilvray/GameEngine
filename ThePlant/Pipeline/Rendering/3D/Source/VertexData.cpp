#include "Pipeline/Rendering/3D/Headers/VertexData.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Pipeline/Rendering/3D/Headers/Skeleton.h"

namespace Application
{
    namespace Rendering
    {
        std::vector<SimpleVertexData> createRuntimeData(const Data::Rendering::SimpleMeshData& meshData)
        {
            SCOPED_MEMORY_CATEGORY("Rendering");

            std::vector<SimpleVertexData> runtimeData;
            runtimeData.reserve(meshData.vertexCount);

            // do we need the field vertexCount? could we not just use indices.size()?
            for(uint i = 0; i < meshData.indices.size(); i++)
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
            SCOPED_MEMORY_CATEGORY("Rendering");

            std::vector<VertexData> runtimeData;
            runtimeData.reserve(meshData.vertexCount);

            // do we need the field vertexCount? could we not just use indices.size()?
            for(uint i = 0; i < meshData.indices.size(); i++)
            {
                Core::Math::Uint3 indices = meshData.indices[i];

                runtimeData.push_back({ meshData.positions[indices.X], meshData.normals[indices.X], meshData.uvs[indices.X] });
                runtimeData.push_back({ meshData.positions[indices.Y], meshData.normals[indices.Y], meshData.uvs[indices.Y] });
                runtimeData.push_back({ meshData.positions[indices.Z], meshData.normals[indices.Z], meshData.uvs[indices.Z] });
            }

            return runtimeData;
        }

        std::vector<AnimatedVertexData> createExplicitRuntimeData(const Data::Rendering::AnimatedMeshData& meshData)
        {
            SCOPED_MEMORY_CATEGORY("Rendering");
            
            std::vector<AnimatedVertexData> runtimeData;
            runtimeData.reserve(meshData.vertexCount);

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

        SkinnedVertexData SkinToSkeleton(const AnimatedVertexData& vertexData, const Data::Rendering::SkeletonData& skeleton)
        {
            SCOPED_MEMORY_CATEGORY("Rendering");

            SkinnedVertexData result(vertexData);
            for (size_t index = 0; index < vertexData.boneName.size(); ++index)
            {
                const auto& boneName = vertexData.boneName[index];
                if (!boneName.empty())
                {
                    result.boneIndices[index] = static_cast<int>(GetBoneIndex(skeleton, boneName));
                }
            }
            return result;
        }

        std::vector<SkinnedVertexData> createRuntimeData(const std::vector<AnimatedVertexData>& animatedData, const Data::Rendering::SkeletonData& skeleton)
        {
            SCOPED_MEMORY_CATEGORY("Rendering");

            std::vector<SkinnedVertexData> runtimeData;
            runtimeData.reserve(animatedData.size());

            for (int i = 0; i < animatedData.size(); i++) {
                runtimeData.push_back(SkinToSkeleton(animatedData[i], skeleton));
            }

            return runtimeData;
        }

        std::vector<SkinnedVertexData> createRuntimeData(const Data::Rendering::AnimatedMeshData& meshData, const Data::Rendering::SkeletonData& skeleton)
        {
            return createRuntimeData(createExplicitRuntimeData(meshData), skeleton);
        }
    }
}