#pragma once

#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/Rendering/Material_NEW.h"
#include "Pipeline/Rendering/Mesh_NEW.h"

namespace Application {
struct ColorComponent
{
    Core::Math::Color color;

    bool operator==(const ColorComponent& other) const
    {
        return color == other.color;
    }
};

struct MaterialComponent
{
    Rendering::Material_NEW material;

    bool operator==(const MaterialComponent& other) const
    {
        return (material == other.material);
    }
};

struct MeshComponent
{
    Rendering::Mesh_NEW mesh;

    bool operator==(const MeshComponent& other) const
    {
        return mesh == other.mesh;
    }
};

struct SkinnedMeshComponent
{
    Rendering::MappedMesh_NEW skinnedMesh;

    bool operator==(const SkinnedMeshComponent& other) const
    {
        return skinnedMesh == other.skinnedMesh;
    }
};

struct BoneComponent
{
    Core::Math::Float4x4 bindMatrix; // inverse of initial bone position

    bool operator==(const BoneComponent& other) const
    {
        return bindMatrix == other.bindMatrix;
    }
};

struct SkeletonComponent
{
    std::array<Application::EntityId, 50> entityArray;
    std::array<Core::Math::Float4x4, 50> boneArray;

    bool operator==(const SkeletonComponent& other) const
    {
        return (entityArray == other.entityArray && boneArray == other.boneArray);
    }
};

// skinned mesh component

// skeleton component
}// namespace Application