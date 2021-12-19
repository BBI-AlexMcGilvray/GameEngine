#include "Pipeline/Rendering/2D/Headers/SimpleShapes.h"

#include "Core/Math/Headers/UtilityFunctions.h"

namespace Application {
namespace Rendering {
    Mesh_NEW CreateBox(const Core::Math::Float2& dimensions)
    {
        auto halfX = dimensions.X * 0.5f;
        auto halfY = dimensions.Y * 0.5f;

        return CreateBox(Core::Math::Float2(-halfX, -halfY), Core::Math::Float2(halfX, halfY));
    }

    Mesh_NEW CreateBox(const Core::Math::Float2& min, const Core::Math::Float2& max)
    {
        std::vector<SimpleVertexData> vertices;

        vertices.push_back({ Core::Math::Float3{ min.X, min.Y, 0.0f }, Core::Math::Float3{ 0.0f } });
        vertices.push_back({ Core::Math::Float3{ min.X, max.Y, 0.0f }, Core::Math::Float3{ 0.0f } });
        vertices.push_back({ Core::Math::Float3{ max.X, max.Y, 0.0f }, Core::Math::Float3{ 0.0f } });

        vertices.push_back({ Core::Math::Float3{ max.X, max.Y, 0.0f }, Core::Math::Float3{ 0.0f } });
        vertices.push_back({ Core::Math::Float3{ max.X, min.Y, 0.0f }, Core::Math::Float3{ 0.0f } });
        vertices.push_back({ Core::Math::Float3{ min.X, min.Y, 0.0f }, Core::Math::Float3{ 0.0f } });

        return CreateMesh(vertices);
    }

    Mesh_NEW CreateCircle(const float& radius)
    {
        std::vector<SimpleVertexData> vertices;

        Core::Math::Float2 center(0.0f);
        float halfStepCount = 50.0f;

        auto createVertices = [radius, &vertices, center, halfStepCount](bool positiveY) {
            float startX = positiveY ? center.X - radius : center.X + radius;
            float endX = positiveY ? center.X + radius : center.X - radius;

            Core::Math::Float3 normal = Core::Math::Float3(0.0f);
            Core::Math::Float3 currentPosition = Core::Math::Float3{ startX, center.Y, 0.0f };
            for (float i = 1.0f; i <= halfStepCount; i++) {
                vertices.push_back({ currentPosition, normal });

                currentPosition.X = Core::Math::Lerp(startX, endX, i / halfStepCount);
                currentPosition.Y = positiveY ? sqrt(Core::Math::sqr(radius) - Core::Math::sqr(currentPosition.X)) : -sqrt(Core::Math::sqr(radius) - Core::Math::sqr(currentPosition.X));

                vertices.push_back({ currentPosition, normal });
                vertices.push_back({ center, normal });
            }
        };

        createVertices(true);
        createVertices(false);

        return CreateMesh(vertices);
    }
} // namespace Rendering
} // namespace Application