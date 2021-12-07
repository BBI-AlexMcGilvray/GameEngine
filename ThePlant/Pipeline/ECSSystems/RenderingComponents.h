#pragma once

#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/Material_NEW.h"
#include "Pipeline/Rendering/Mesh_NEW.h"

namespace Application {
struct ColorComponent
{
    Core::Math::Color color;
};

struct MaterialComponent
{
    Rendering::Material_NEW material;
};

struct MeshComponent
{
    Rendering::Mesh_NEW mesh;
};

struct SkinnedMeshComponent
{
    Rendering::MappedMesh_NEW mesh;
};

struct SkeletonComponent
{
    std::array<Core::Math::Float4x4, 50> boneArray;
};

// skinned mesh component

// skeleton component
}// namespace Application