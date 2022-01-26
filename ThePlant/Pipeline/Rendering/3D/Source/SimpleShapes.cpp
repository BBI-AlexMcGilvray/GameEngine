#include "Pipeline/Rendering/3D/Headers/SimpleShapes.h"

namespace Application {
namespace Rendering {
    Mesh CreateLine(const float& length)
    {
        Core::Math::Float3 normal = 0.0f;
        std::vector<SimpleVertexData> vertices = {
            { Core::Math::Float3(0.0f, 0.0f, 0.0f), normal },
            { Core::Math::Float3(length, 0.0f, 0.0f), normal }
        };

        return CreateMesh(vertices);
    }

    Mesh CreateBox(const Core::Math::Float3& dimensions)
    {
        auto halfX = dimensions.X * 0.5f;
        auto halfY = dimensions.Y * 0.5f;
        auto halfZ = dimensions.Z * 0.5f;

        return CreateBox(Core::Math::Float3(-halfX, -halfY, -halfZ), Core::Math::Float3(halfX, halfY, halfZ));
    }

    Mesh CreateBox(const Core::Math::Float3& min, const Core::Math::Float3& max)
    {
        std::vector<Core::Math::Float3> corners;
        corners.reserve(8);
        corners.push_back(Core::Math::Float3(min.X, min.Y, min.Z));
        corners.push_back(Core::Math::Float3(min.X, max.Y, min.Z));
        corners.push_back(Core::Math::Float3(max.X, max.Y, min.Z));
        corners.push_back(Core::Math::Float3(max.X, min.Y, min.Z));
        corners.push_back(Core::Math::Float3(max.X, min.Y, max.Z));
        corners.push_back(Core::Math::Float3(max.X, max.Y, max.Z));
        corners.push_back(Core::Math::Float3(min.X, max.Y, max.Z));
        corners.push_back(Core::Math::Float3(min.X, min.Y, max.Z));

        // we could set this to be correct for each vert
        Core::Math::Float3 normal = 0.0f;

        std::vector<SimpleVertexData> vertices;

        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[1], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[2], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[2], normal });
        vertices.push_back({ corners[5], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[5], normal });
        vertices.push_back({ corners[4], normal });
        vertices.push_back({ corners[5], normal });
        vertices.push_back({ corners[2], normal });
        vertices.push_back({ corners[1], normal });
        vertices.push_back({ corners[5], normal });
        vertices.push_back({ corners[1], normal });
        vertices.push_back({ corners[6], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[4], normal });
        vertices.push_back({ corners[7], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[7], normal });
        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[7], normal });
        vertices.push_back({ corners[6], normal });
        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[6], normal });
        vertices.push_back({ corners[1], normal });
        vertices.push_back({ corners[4], normal });
        vertices.push_back({ corners[5], normal });
        vertices.push_back({ corners[6], normal });
        vertices.push_back({ corners[4], normal });
        vertices.push_back({ corners[6], normal });
        vertices.push_back({ corners[7], normal });

        return CreateMesh(vertices);
    }

    Mesh CreatePyramid(const float& height, const float& sideLength)
    {
        const float halfSideLength = sideLength * 0.5f;

        std::vector<Core::Math::Float3> corners;
        corners.reserve(5);
        corners.push_back(Core::Math::Float3(-halfSideLength, 0.0f, -halfSideLength));
        corners.push_back(Core::Math::Float3(-halfSideLength, 0.0f, halfSideLength));
        corners.push_back(Core::Math::Float3(halfSideLength, 0.0f, halfSideLength));
        corners.push_back(Core::Math::Float3(halfSideLength, 0.0f, -halfSideLength));
        corners.push_back(Core::Math::Float3(0.0f, height, 0.0f));

        // we could set this to be correct for each vert
        Core::Math::Float3 normal = 0.0f;

        std::vector<SimpleVertexData> vertices;
        // the sides
        vertices.push_back({ corners[4], normal });
        vertices.push_back({ corners[1], normal });
        vertices.push_back({ corners[2], normal });
        vertices.push_back({ corners[4], normal });
        vertices.push_back({ corners[2], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[4], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[4], normal });
        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[1], normal });
        // the bottom (counter clockwise since we want it visible from beneath, not the top)
        vertices.push_back({ corners[1], normal });
        vertices.push_back({ corners[2], normal });
        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[0], normal });
        vertices.push_back({ corners[3], normal });
        vertices.push_back({ corners[2], normal });

        return CreateMesh(vertices);
    }

    Mesh CreateSphere(const float& radius)
    {
        // http://en.wikipedia.org/wiki/Icosahedron
        //(0, +/-1, +/-t)
        //(+/-1, +/-t, 0)
        //(+/-t, 0, +/-1)
        //where t = (1 + sqrt(5)) / 2

        const float t = (1.0f + sqrt(5.0f)) / 2.0f;
        // So each side has a length of sqrt( t*t + 1.0 )
        float rScale = radius / sqrt(t * t + 1.0f);// correct the radius
        std::vector<Core::Math::Float3> edges = std::vector<Core::Math::Float3>(12);

        for (int i = 0; i < 4; i++)
        {
            //v[ i ] = Vector( 0, -(i&2), -(i&1)*t ) ;
            edges[i] = rScale * Core::Math::Float3(0.0f, i & 2 ? -1.0f : 1.0f, i & 1 ? -t : t);
        }

        for (int i = 4; i < 8; i++)
        {
            //v[ i ] = Vector( -(i&2), -(i&1)*t, 0 ) ;
            edges[i] = rScale * Core::Math::Float3(i & 2 ? -1.0f : 1.0f, i & 1 ? -t : t, 0.0f);
        }

        for (int i = 8; i < 12; i++)
        {
            //v[ i ] = Vector( -(i&1)*t, 0, -(i&2) ) ;
            edges[i] = rScale * Core::Math::Float3(i & 1 ? -t : t, 0.0f, i & 2 ? -1.0f : 1.0f);
        }

        // we could set this to be correct for each vert
        Core::Math::Float3 normal = Core::Math::Float3(0.0f);

        std::vector<SimpleVertexData> vertices;

        vertices.push_back({ edges[0], normal });
        vertices.push_back({ edges[2], normal });
        vertices.push_back({ edges[8], normal });
        vertices.push_back({ edges[0], normal });
        vertices.push_back({ edges[8], normal });
        vertices.push_back({ edges[4], normal });
        vertices.push_back({ edges[0], normal });
        vertices.push_back({ edges[4], normal });
        vertices.push_back({ edges[6], normal });
        vertices.push_back({ edges[0], normal });
        vertices.push_back({ edges[6], normal });
        vertices.push_back({ edges[9], normal });
        vertices.push_back({ edges[0], normal });
        vertices.push_back({ edges[9], normal });
        vertices.push_back({ edges[2], normal });

        vertices.push_back({ edges[2], normal });
        vertices.push_back({ edges[7], normal });
        vertices.push_back({ edges[5], normal });
        vertices.push_back({ edges[2], normal });
        vertices.push_back({ edges[5], normal });
        vertices.push_back({ edges[8], normal });
        vertices.push_back({ edges[2], normal });
        vertices.push_back({ edges[9], normal });
        vertices.push_back({ edges[7], normal });

        vertices.push_back({ edges[8], normal });
        vertices.push_back({ edges[5], normal });
        vertices.push_back({ edges[10], normal });
        vertices.push_back({ edges[8], normal });
        vertices.push_back({ edges[10], normal });
        vertices.push_back({ edges[4], normal });

        vertices.push_back({ edges[10], normal });
        vertices.push_back({ edges[5], normal });
        vertices.push_back({ edges[3], normal });
        vertices.push_back({ edges[10], normal });
        vertices.push_back({ edges[3], normal });
        vertices.push_back({ edges[1], normal });
        vertices.push_back({ edges[10], normal });
        vertices.push_back({ edges[1], normal });
        vertices.push_back({ edges[4], normal });

        vertices.push_back({ edges[1], normal });
        vertices.push_back({ edges[6], normal });
        vertices.push_back({ edges[4], normal });
        vertices.push_back({ edges[1], normal });
        vertices.push_back({ edges[3], normal });
        vertices.push_back({ edges[11], normal });
        vertices.push_back({ edges[1], normal });
        vertices.push_back({ edges[11], normal });
        vertices.push_back({ edges[6], normal });

        vertices.push_back({ edges[6], normal });
        vertices.push_back({ edges[11], normal });
        vertices.push_back({ edges[9], normal });

        vertices.push_back({ edges[11], normal });
        vertices.push_back({ edges[3], normal });
        vertices.push_back({ edges[7], normal });
        vertices.push_back({ edges[11], normal });
        vertices.push_back({ edges[7], normal });
        vertices.push_back({ edges[9], normal });

        vertices.push_back({ edges[3], normal });
        vertices.push_back({ edges[5], normal });
        vertices.push_back({ edges[7], normal });

        return CreateMesh(vertices);
    }
} // namespace Rendering
} // namespace Application