#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"

using namespace Core;

namespace Data
{
	namespace DataExport
	{
		struct DataProperty
		{
			bool IsPrimaryKey = false;

			String Type;
			String Name;

			virtual String GetLine()
			{
				return (Type + " " + Name + ";");
			}

			DataProperty(String type, String name)
				: Type(type), Name(name)
			{}
		};

		struct DataPropertyList : DataProperty
		{
			using DataProperty::DataProperty;

			String GetLine() override
			{
				return ("List<" + Type + "> " + Name + ";");
			}
		};

		struct DataPropertyData : DataProperty
		{
			using DataProperty::DataProperty;

			String GetLine() override
			{
				return ("AssetName<" + Type + "> " + Name + ";");
			}
		};

		struct DataType
		{
			String Name;
			String Acronym;

			List<UniquePtr<DataProperty>> Properties;

			DataType(String name, String acronym)
				: Name(name), Acronym(acronym)
			{}

			String GetDefinition();
			String GetMetaTypeDefinition();
		};

		struct MetaAssetDataProperty
		{
			String variableName;
			String variableValue;
			
			bool IsReference = false;
		};

		struct MetaAssetData
		{
			String typeName;
			String typeAcronym;

			String assetName;
			bool directExport;

			List<MetaAssetDataProperty> variables;
		};
	}
}