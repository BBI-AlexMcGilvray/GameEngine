#pragma once

#include "Pipeline/Rendering/Material_NEW.h"
#include "Pipeline/Rendering/Mesh_NEW.h"

namespace Application {
struct MaterialComponent
{
    Rendering::Material_NEW material;
};

struct MeshComponent
{
    Rendering::Mesh_NEW mesh;
};

// skinned mesh component

// skeleton component
}// namespace Application