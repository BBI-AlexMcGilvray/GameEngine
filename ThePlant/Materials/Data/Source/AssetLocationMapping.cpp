#include "Data/Headers/AssetLocationMapping.h"

#include "Core/IO/Headers/IOUtils.h"
#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/SerializationUtils.h"

namespace Data
{
    void AssetLocationMapping::Load(const FilePath& mappingLocation)
    {        
        SCOPED_MEMORY_CATEGORY("Assets");
        Core::IO::File mappingFile = Core::IO::OpenFileI(mappingLocation);

        std::string mappingData = mappingFile.GetFullText();

        Serialization::Format::JSON parsedMapping;
        parsedMapping.Parse(mappingData);

        DeserializeTo(_mapping, parsedMapping, "AssetLocationMapping");
    }

    void AssetLocationMapping::Save(const FilePath& mappingLocation) const
    {
        SCOPED_MEMORY_CATEGORY("Assets");
        Core::IO::File mappingFile = Core::IO::OpenFileO(mappingLocation);

        Serialization::Format::JSON serializedMapping;
        SerializeTo(serializedMapping, _mapping, "AssetLocationMapping");

        mappingFile.Write(serializedMapping.ToString(Serialization::Format::Style::Readable));
    }
} // namesapce Data