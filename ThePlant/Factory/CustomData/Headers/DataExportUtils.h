#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Factory/CustomData/Headers/DataExportDefs.h"

using namespace Core;

namespace Data
{
	namespace DataExport
	{
		UniquePtr<DataType> CreateType(String sql);
		UniquePtr<DataProperty> CreateProperty(String sqlColumn);

		String TableName(String sql);
		String Acronym(String tableName);

		String FieldName(String sqlColumn);
		String TypeName(String sqlColumn);

		// this is needed for exporting - so we know what to hash/name it
		bool IsPrimaryKey(String sqlColumn);

		bool IsForeignKey(String sqlColumn);
		String GetForeignKeyType(String sqlColumn);

		bool IsList(String sqlColumn);

		// this is needed for exporting - so we know to make it directly referenceable
		bool IsExported(String sqlColumn);

		String ClipLeadingWhitespace(String str);
	}
}