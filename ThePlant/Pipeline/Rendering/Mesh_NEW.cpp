#include "Pipeline/Rendering/Mesh_NEW.h"

#include <vector>

#include "Pipeline/Rendering/3D/Headers/VertexData.h"

namespace Application {
namespace Rendering {
    Mesh_NEW CreateMesh(const std::vector<SimpleVertexData>& data)
    {
        Mesh_NEW mesh;
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

        mesh._vbos.push_back(newBuffer);

        return mesh;
    }

    Mesh_NEW CreateMesh(const std::vector<VertexData>& data)
    {
        Mesh_NEW mesh;
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
        // glEnableVertexAttribArray(2);// this matches with object shader construction
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::VertexData), (void *)(offsetof(Application::Rendering::VertexData, Application::Rendering::VertexData::uvs)));

        mesh.buffer.Unbind();// must be done first, as it stores the states of the binded vbos
        newBuffer.Unbind();
        glDisableVertexAttribArray(0);

        mesh._vbos.push_back(newBuffer);

        return mesh;
    }

    MappedMesh_NEW CreateMesh(const std::vector<SkinnedVertexData>& data)
    {
        MappedMesh_NEW mesh;
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

        mesh._vbos.push_back(newBuffer);

        // keep track of mesh data to write to
        mesh.mappedBuffer = GLMappedBuffer(&newBuffer);

        return mesh;
    }

    Mesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::SimpleMeshData>& data)
    {
        std::vector<SimpleVertexData> vertexData = createRuntimeData(*data);
        return CreateMesh(vertexData);
    }

    Mesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::StaticMeshData>& data)
    {
        std::vector<VertexData> vertexData = createRuntimeData(*data);
        return CreateMesh(vertexData);
    }

    MappedMesh_NEW CreateMesh(const Data::AssetData<Data::Rendering::AnimatedMeshData>& data)
    {
        std::vector<SkinnedVertexData> vertexData = createRuntimeData(*data);
        return CreateMesh(vertexData);
    }
} // namespace Rendering
} // namespace Application