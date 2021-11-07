#pragma once

#include <string>
#include <vector>

#include "Core/Headers/CoreDefs.h"

#include "Factory/CustomData/Headers/DataExportDefs.h"

using namespace Core;

namespace Data
{
	namespace DataExport
	{
		UniquePtr<DataType> CreateType(std::string sql);
		UniquePtr<DataProperty> CreateProperty(std::string sqlColumn);

		std::string TableName(std::string sql);
		std::string Acronym(std::string tableName);

		std::string FieldName(std::string sqlColumn);
		std::string TypeName(std::string sqlColumn);

		// this is needed for exporting - so we know what to hash/name it
		bool IsPrimaryKey(std::string sqlColumn);

		bool IsForeignKey(std::string sqlColumn);
		std::string GetForeignKeyType(std::string sqlColumn);

		bool IsList(std::string sqlColumn);

		// this is needed for exporting - so we know to make it directly referenceable
		bool IsExported(std::string sqlColumn);

		std::string ClipLeadingWhitespace(std::string str);
	}
}