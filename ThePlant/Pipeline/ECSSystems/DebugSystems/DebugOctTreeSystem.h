#pragma once

#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/Collision/OctTree.h"
#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/Rendering/3D/Headers/SimpleShapes.h"
#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Mesh.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

namespace Application
{
struct DebugOctTreeSystem : public System<DebugOctTreeSystem>
{
    DebugOctTreeSystem(Collision::CollisionManager& collisionManager, Rendering::RenderManager& renderManager, Rendering::ShaderManager& shaderManager)
    : _collisionManager(collisionManager)
    , _renderManager(renderManager)
    {
        _debugMaterial = Rendering::CreateDefaultMaterial(shaderManager);
        _debugMesh = Rendering::CreateBox(1.0f);
    }

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        const Collision::OctTree& octTree = _collisionManager.GetOctTree();
        _DrawOctTreeNode(octTree);
    }

private:
    Collision::CollisionManager& _collisionManager;
    Rendering::RenderManager& _renderManager;

    // when using these meshes, modify the scale of the transform passed in to be multiplied by the scale of the collider (relative to the default 1.0) being used
    Rendering::Material _debugMaterial;
    Rendering::Mesh _debugMesh;

    void _DrawOctTreeNode(const Collision::OctTreeNode& node) const
    {
        // create render context for node
            // make the color white if it has content, black otherwise
        
        // call _DrawOctTreeNode for each child of node (if they exist)
    }
};
} // namespace Application