#pragma once

#include <string>

#include "Core/IO/Headers/File.h"

#include "Factory/SQL/Headers/SQLInstance.h"

#include "Factory/CustomData/Headers/DataExportDefs.h"

using namespace Core;
using namespace Core::IO;

using namespace Data;
using namespace Data::SQL;

namespace Data
{
	namespace DataExport
	{
		void ExportCustomData(Ptr<SQLInstance> db, Ptr<File> directAssets);

		void ExportDataTypeInformation(Ptr<SQLInstance> db, std::string type, Ptr<File> customAssets, Ptr<File> directAssets);

		UniquePtr<DataType> ExportDataType(std::string sql, Ptr<File> customAssets);
		void ExportDataForType(Ptr<SQLInstance> db, UniquePtr<DataType> type, Ptr<File> directAssets);

		void ExportDirectReference_Open(std::string name, Ptr<File> directAssets);
		void ExportDirectReference_Close(std::string name, Ptr<File> directAssets);
		void ExportDataItemForType(MetaAssetData asset, FilePath exportTo, Ptr<File> directAssets);

		void InitializeCustomAssetFile(Ptr<File> customAssets);
		void FinalizeCustomAssetFile(Ptr<File> customAssets);
	}
}