#pragma once

#include "Core/Headers/Hash.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"
#include "Core/Geometric/Transform.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Mesh.h"

namespace Application {
struct ColorComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    Core::Math::Color color;

    ColorComponent() = default;
    ColorComponent(const ColorComponent&) = default;
    ColorComponent(ColorComponent&&) = default;
    ColorComponent& operator=(const ColorComponent&) = default;
    ColorComponent& operator=(ColorComponent&&) = default;

    ColorComponent(const Core::Math::Color& color)
    : color(color)
    {}

    bool operator==(const ColorComponent& other) const
    {
        return color == other.color;
    }
    bool operator !=(const ColorComponent& other) const { return !(*this == other); }
};

struct MaterialComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    Rendering::Material material;

    MaterialComponent() = default;
    MaterialComponent(const MaterialComponent&) = default;
    MaterialComponent(MaterialComponent&&) = default;
    MaterialComponent& operator=(const MaterialComponent&) = default;
    MaterialComponent& operator=(MaterialComponent&&) = default;

    MaterialComponent(const Rendering::Material& material)
    : material(material)
    {}

    bool operator==(const MaterialComponent& other) const
    {
        return (material == other.material);
    }
    bool operator !=(const MaterialComponent& other) const { return !(*this == other); }
};

struct MeshComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    Rendering::Mesh mesh;

    MeshComponent() = default;
    MeshComponent(const MeshComponent&) = default;
    MeshComponent(MeshComponent&&) = default;
    MeshComponent& operator=(const MeshComponent&) = default;
    MeshComponent& operator=(MeshComponent&&) = default;

    MeshComponent(const Rendering::Mesh& mesh)
    : mesh(mesh)
    {}

    bool operator==(const MeshComponent& other) const
    {
        return mesh == other.mesh;
    }
    bool operator !=(const MeshComponent& other) const { return !(*this == other); }
};

struct SkinnedMeshComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    Rendering::MappedMesh skinnedMesh;

    SkinnedMeshComponent() = default;
    SkinnedMeshComponent(const SkinnedMeshComponent&) = default;
    SkinnedMeshComponent(SkinnedMeshComponent&&) = default;
    SkinnedMeshComponent& operator=(const SkinnedMeshComponent&) = default;
    SkinnedMeshComponent& operator=(SkinnedMeshComponent&&) = default;

    SkinnedMeshComponent(const Rendering::MappedMesh& skinnedMesh)
    : skinnedMesh(skinnedMesh)
    {}

    bool operator==(const SkinnedMeshComponent& other) const
    {
        return skinnedMesh == other.skinnedMesh;
    }
    bool operator !=(const SkinnedMeshComponent& other) const { return !(*this == other); }
};

struct BoneComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    Core::Geometric::Transform defaultState; // t-pose position (taken when not playing an animation) - local transform, relative to parent
    Core::Math::Float4x4 bindMatrix; // inverse of initial bone position

    BoneComponent() = default;
    BoneComponent(const BoneComponent&) = default;
    BoneComponent(BoneComponent&&) = default;
    BoneComponent& operator=(const BoneComponent&) = default;
    BoneComponent& operator=(BoneComponent&&) = default;

    BoneComponent(const Core::Geometric::Transform& defaultState, const Core::Math::Float4x4& bindMatrix)
    : defaultState(defaultState)
    , bindMatrix(bindMatrix)
    {}

    bool operator==(const BoneComponent& other) const
    {
        return bindMatrix == other.bindMatrix;
    }
    bool operator !=(const BoneComponent& other) const { return !(*this == other); }
};

struct SkeletonComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    EntityId rootBone;
    std::array<std::pair<Core::Hash, Application::EntityId>, 50> nameAndEntities;
    std::array<Core::Math::Float4x4, 50> boneArray;

    SkeletonComponent() = default;
    SkeletonComponent(const SkeletonComponent&) = default;
    SkeletonComponent(SkeletonComponent&&) = default;
    SkeletonComponent& operator=(const SkeletonComponent&) = default;
    SkeletonComponent& operator=(SkeletonComponent&&) = default;

    SkeletonComponent(const EntityId& rootBone, const std::array<std::pair<Core::Hash, Application::EntityId>, 50>& boneInfo)
    : rootBone(rootBone)
    , nameAndEntities(boneInfo)
    {}

    bool operator==(const SkeletonComponent& other) const
    {
        return (rootBone == other.rootBone && nameAndEntities == other.nameAndEntities && boneArray == other.boneArray);
    }
    bool operator !=(const SkeletonComponent& other) const { return !(*this == other); }

    Application::EntityId GetBone(const std::string& name)
    {
        return GetBone(Core::HashValue(name));
    }

    Application::EntityId GetBone(const Core::Hash& name)
    {
        for (size_t index = 0; index < nameAndEntities.size(); ++index)
        {
            if (name == nameAndEntities[index].first)
            {
                return nameAndEntities[index].second;
            }
        }

        throw std::exception("bone does not exist in skeleton");
    }
};

// skinned mesh component

// skeleton component
}// namespace Application