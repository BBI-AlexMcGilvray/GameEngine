#pragma once

#include <string>
#include <vector>

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"

using namespace Core;

namespace Data
{
	namespace DataExport
	{
		struct DataProperty
		{
			virtual ~DataProperty() = default;

			bool IsPrimaryKey = false;

			std::string Type;
			std::string Name;

			virtual std::string GetLine()
			{
				return (Type + " " + Name + ";");
			}

			DataProperty(std::string type, std::string name)
				: Type(type), Name(name)
			{}
		};

		struct DataPropertyList : DataProperty
		{
			using DataProperty::DataProperty;

			std::string GetLine() override
			{
				return ("std::vector<" + Type + "> " + Name + ";");
			}
		};

		struct DataPropertyData : DataProperty
		{
			using DataProperty::DataProperty;

			std::string GetLine() override
			{
				return ("AssetName<" + Type + "> " + Name + ";");
			}
		};

		struct DataType
		{
			std::string Name;
			std::string Acronym;

			std::vector<UniquePtr<DataProperty>> Properties;

			DataType(std::string name, std::string acronym)
				: Name(name), Acronym(acronym)
			{}

			std::string GetDefinition();
			std::string GetMetaTypeDefinition();
		};

		struct MetaAssetDataProperty
		{
			std::string variableName;
			std::string variableValue;
			
			bool IsReference = false;
		};

		struct MetaAssetData
		{
			std::string typeName;
			std::string typeAcronym;

			std::string assetName;
			bool directExport;

			std::vector<MetaAssetDataProperty> variables;
		};
	}
}