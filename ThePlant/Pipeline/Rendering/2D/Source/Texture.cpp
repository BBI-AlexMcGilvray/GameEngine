#include "Pipeline/Rendering/2D/Headers/Texture.h"

namespace Application {
namespace Rendering {
void _CreateNewMesh(Texture& texture, const Core::Math::Float2& dimensions)
{
    std::vector<VertexData> meshVertices;
    meshVertices.reserve(6);

    const Core::Math::Float2 min = dimensions * -0.5f;
    const Core::Math::Float2 max = dimensions * 0.5f;

    VertexData bottomLeft = { Core::Math::Float3(min.X, min.Y, 0.0f), Core::Math::Float3(0.0f), Core::Math::Float2(0.0f, 0.0f) };
    VertexData topLeft = { Core::Math::Float3(min.X, max.Y, 0.0f), Core::Math::Float3(0.0f), Core::Math::Float2(0.0f, 1.0f) };
    VertexData topRight = { Core::Math::Float3(max.X, max.Y, 0.0f), Core::Math::Float3(0.0), Core::Math::Float2(1.0f, 1.0f) };
    VertexData bottomRight = { Core::Math::Float3(max.X, min.Y), Core::Math::Float3(0.0f), Core::Math::Float2(1.0f, 0.0f) };

    meshVertices.push_back(bottomLeft);
    meshVertices.push_back(topLeft);
    meshVertices.push_back(topRight);

    meshVertices.push_back(topRight);
    meshVertices.push_back(bottomRight);
    meshVertices.push_back(bottomLeft);

    texture.mesh = CreateMesh(meshVertices);
}

Texture CreateTexture(const Core::Math::Int2& textureDimensions, const Core::Math::Float2& meshDimensions)
{
    Texture texture;

    texture.actualTexture.Generate();
    ResizeTexture(texture, textureDimensions);
    _CreateNewMesh(texture, meshDimensions);

    return texture;
}

void DeleteTexture(Texture& texture)
{
    texture.actualTexture.Delete();
    texture.mesh.buffer.Delete();
}

void ResizeTexture(Texture& texture, const Core::Math::Int2& newDimensions)
{
    texture.actualTexture.Bind();
    texture.actualTexture.CreateTextureStorage(newDimensions, GL_RGB);
    texture.actualTexture.Unbind();
}

void ResizeMesh(Texture& texture, const Core::Math::Float2& newDimensions)
{
    texture.mesh.buffer.Delete();
    _CreateNewMesh(texture, newDimensions);
}
}
}// namespace Application