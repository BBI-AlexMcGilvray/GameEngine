#include "Pipeline/Rendering/Mesh.h"

#include <vector>

#include "Pipeline/Rendering/3D/Headers/VertexData.h"

namespace Application {
namespace Rendering {
    void CreateMesh(MeshData& mesh, const std::vector<SimpleVertexData>& data)
    {
        mesh.vertices = data.size();

        mesh.buffer.Generate();
        mesh.buffer.Bind();

        auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
        newBuffer.Generate();
        newBuffer.Bind();

        // glBufferData( < type >, < size of data >, < start of data >, < draw type >);
        // the Data->Data would go away with a DataPtr<T>
        glBufferData(newBuffer.Type, data.size() * sizeof(Application::Rendering::SimpleVertexData), &(data[0]), GL_STATIC_DRAW);

        // glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
        // position
        glEnableVertexAttribArray(0);// this matches with object shader construction
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SimpleVertexData), (void *)(offsetof(Application::Rendering::SimpleVertexData, Application::Rendering::SimpleVertexData::position)));
        // normal
        glEnableVertexAttribArray(1);// this matches with object shader construction
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SimpleVertexData), (void *)(offsetof(Application::Rendering::SimpleVertexData, Application::Rendering::SimpleVertexData::normal)));

        mesh.buffer.Unbind();// must be done first, as it stores the states of the binded vbos
        newBuffer.Unbind();
        glDisableVertexAttribArray(0);

        mesh._vbo = newBuffer;
    }

    void CreateMesh(MeshData& mesh, const std::vector<VertexData>& data)
    {
        mesh.vertices = data.size();

        mesh.buffer.Generate();
        mesh.buffer.Bind();

        auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
        newBuffer.Generate();
        newBuffer.Bind();

        // glBufferData( < type >, < size of data >, < start of data >, < draw type >);
        // the Data->Data would go away with a DataPtr<T>
        glBufferData(newBuffer.Type, data.size() * sizeof(Application::Rendering::VertexData), &(data[0]), GL_STATIC_DRAW);

        // glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
        // position
        glEnableVertexAttribArray(0);// this matches with object shader construction
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::VertexData), (void *)(offsetof(Application::Rendering::VertexData, Application::Rendering::VertexData::position)));
        // normal
        glEnableVertexAttribArray(1);// this matches with object shader construction
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::VertexData), (void *)(offsetof(Application::Rendering::VertexData, Application::Rendering::VertexData::normal)));
        // uvs
        glEnableVertexAttribArray(2);// this matches with object shader construction
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::VertexData), (void *)(offsetof(Application::Rendering::VertexData, Application::Rendering::VertexData::uvs)));

        mesh.buffer.Unbind();// must be done first, as it stores the states of the binded vbos
        newBuffer.Unbind();
        glDisableVertexAttribArray(0);

        mesh._vbo = newBuffer;
    }

    void CreateMesh(MappedMeshData& mesh, const std::vector<SkinnedVertexData>& data)
    {
        MappedMesh skinnedMesh;
        Mesh mesh;
        mesh.vertices = data.size();

        mesh.buffer.Generate();
        mesh.buffer.Bind();

        auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
        newBuffer.Generate();
        newBuffer.Bind();

        // glBufferData( < type >, < size of data >, < start of data >, < draw type >); // GL_DYNAMIC_DRAW because Skin(...) could be called multiple times, changing indices
        glBufferData(newBuffer.Type, data.size() * sizeof(Application::Rendering::SkinnedVertexData), &(data[0]), GL_DYNAMIC_DRAW);

        // glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
        // position
        glEnableVertexAttribArray(0);// this matches with object shader construction
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::position)));
        // normal
        glEnableVertexAttribArray(1);// this matches with object shader construction
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::normal)));
        // uvs
        // UVS not used YET: glEnableVertexAttribArray(2);// this matches with object shader construction
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::uvs)));
        // bone weight
        glEnableVertexAttribArray(2);// this matches with object shader construction
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::boneWeight)));
        // bone indices
        glEnableVertexAttribArray(3);// this matches with object shader construction
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::SkinnedVertexData), (void *)(offsetof(Application::Rendering::SkinnedVertexData, Application::Rendering::SkinnedVertexData::boneIndices)));

        mesh.buffer.Unbind();// must be done first, as it stores the states of the binded vbos
        newBuffer.Unbind();
        glDisableVertexAttribArray(0);

        mesh._vbo = newBuffer;

        // mapped buffer just 'mimics' the buffer it is mapping, but this should probably be cleaned up later
        skinnedMesh.skeletonBuffer = GLMappedBuffer(mesh._vbo.Object, mesh._vbo.Type);
        // keep track of mesh data to write to
        skinnedMesh.mesh = mesh;
    }

    void CreateMesh(MeshData& mesh, const Data::AssetData<Data::Rendering::SimpleMeshData>& data)
    {
        std::vector<SimpleVertexData> vertexData = createRuntimeData(*data);
        CreateMesh(mesh, vertexData);
    }

    void CreateMesh(MeshData& mesh, const Data::AssetData<Data::Rendering::StaticMeshData>& data)
    {
        std::vector<VertexData> vertexData = createRuntimeData(*data);
        return CreateMesh(mesh, vertexData);
    }

    void CreateMesh(MappedMeshData& mesh, const Data::AssetData<Data::Rendering::AnimatedMeshData>& data, const Data::AssetData<Data::Rendering::SkeletonData>& skeleton)
    {
        std::vector<SkinnedVertexData> vertexData = createRuntimeData(*data, *skeleton);

        return CreateMesh(mesh, vertexData);
    }
} // namespace Rendering
} // namespace Application