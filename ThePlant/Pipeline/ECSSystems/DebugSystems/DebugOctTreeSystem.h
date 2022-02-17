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
    bool drawOccupiedOnly = true;

    DebugOctTreeSystem(Collision::CollisionManager& collisionManager, Rendering::RenderManager& renderManager, Rendering::ShaderManager& shaderManager)
    : System<DebugOctTreeSystem>("DebugOctTreeSystem")
    , _collisionManager(collisionManager)
    , _renderManager(renderManager)
    {
        _debugMaterial = Rendering::CreateDefaultMaterial(shaderManager);
        _debugMesh = Rendering::CreateBox(1.0f);
    }

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

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
        const auto nodeShapeOrientation = node.DEBUG_GetBounds();
        Core::Geometric::Transform nodeTransform = nodeShapeOrientation.orientation;
        nodeTransform.AdjustScale(nodeShapeOrientation.shape.dimensions);

        bool hasContent = node.DEBUG_GetAllContent().size() > 0;

        Core::Math::Color nodeColor = Core::Math::BLACK;
        if (hasContent)
        {
            nodeColor = Core::Math::WHITE;
        }

        if (!drawOccupiedOnly || hasContent)
        {
            Rendering::Context context = {
                _debugMaterial,
                nodeTransform.GetTransformationMatrix(),
                nodeColor,
                _debugMesh,
                Rendering::DrawMode::LINE
            };
            _renderManager.QueueRender(context);
        }
        
        for (const auto& child : node.DEBUG_GetAllChildren())
        {
            if (child == nullptr)
            { // if one is null, they all are
                break;
            }

            _DrawOctTreeNode(*child);
        }
    }
};
} // namespace Application