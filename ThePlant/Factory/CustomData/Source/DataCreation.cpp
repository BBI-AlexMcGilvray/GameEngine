#include "Factory/CustomData/Headers/DataCreation.h"

#include "Core/Logging/LogFunctions.h"

#include "Core/Headers/Hash.h"
#include "Core/IO/Headers/IOUtils.h"

#include "Factory/Headers/ExportException.h"

#include "Factory/CustomData/Headers/DataExportUtils.h"

using namespace std::string_literals;

namespace Data
{
	namespace DataExport
	{
		namespace 
		{
			const std::string CUSTOM_DATA = "Custom Data";
		}

		void ExportCustomData(Ptr<SQLInstance> db, Ptr<File> directAssets)
		{
			CORE_LOG(CUSTOM_DATA, "Starting to export custom data");

			File customAssets(FilePath{ GetCWD() + "Resources/ExportedAssets/", "CustomAssets.h" }, std::ios::out);
			customAssets.Open();
			InitializeCustomAssetFile(&customAssets);

			BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>> forEachType = [db, &customAssets, directAssets](void* forwardedInfo, std::vector<std::string> columnValues, std::vector<std::string> columnNames)
			{
				// due to query, there will only ever be one column value (the table name)
				ExportDataTypeInformation(db, columnValues[0], &customAssets, directAssets);

				return false;
			};

			std::string allTypeQuery = "SELECT name FROM sqlite_master WHERE type='table'";

			ExportDirectReference_Open("CustomAssets", directAssets);
			if (!db->Query(allTypeQuery, forEachType, nullptr))
			{
				throw CustomExportException("Query to get tables failed");
			}
			ExportDirectReference_Close("CustomAssets", directAssets);

			FinalizeCustomAssetFile(&customAssets);

			CORE_LOG(CUSTOM_DATA, "Finished exporting custom data");
		}

		void ExportDataTypeInformation(Ptr<SQLInstance> db, std::string type, Ptr<File> customAssets, Ptr<File> directAssets)
		{
			CORE_LOG(CUSTOM_DATA, "Starting to export data type: " + type);

			BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>> formatConstruction = [db, type, customAssets, directAssets](void* forwardedInfo, std::vector<std::string> columnValues, std::vector<std::string> columnNames)
			{
				// due to query, there will only even be one column value (the sql statement)
				auto type = ExportDataType(columnValues[0], customAssets);
				ExportDataForType(db, move(type), directAssets);

				return false;
			};

			std::string typeFormatQuery = "Select sql from sqlite_master WHERE name = '" + type + "'";
			if (!db->Query(typeFormatQuery, formatConstruction, nullptr))
			{
				throw CustomExportException("Query to get format failed");
			}

			CORE_LOG(CUSTOM_DATA, "Finished exporting data type: " + type);
		}

		UniquePtr<DataType> ExportDataType(std::string sql, Ptr<File> customAssets)
		{
			CORE_LOG(CUSTOM_DATA, "Starting to export data type: " + sql);

			auto dataType = CreateType(sql);

			customAssets->CreateNewLine();
			customAssets->Write("// " + dataType->Name);
			customAssets->CreateNewLine();
			customAssets->Write(dataType->GetDefinition());
			customAssets->CreateNewLine();
			customAssets->Write(dataType->GetMetaTypeDefinition());
			customAssets->CreateNewLine();

			return dataType;

			CORE_LOG(CUSTOM_DATA, "Finished exporting data type: " + sql);
		}

		void ExportDataForType(Ptr<SQLInstance> db, UniquePtr<DataType> type, Ptr<File> directAssets)
		{
			SCOPED_MEMORY_CATEGORY("DataExport");
			CORE_LOG(CUSTOM_DATA, "Starting to export data with type: " + type->Name);

			FilePath exportTo = { GetCWD() + "Resources/ExportedAssets/CustomData/", "" };

			BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>> exportData = [dataType = type.get(), directAssets, exportTo](void* forwardedInfo, std::vector<std::string> columnValues, std::vector<std::string> columnNames)
			{
				MetaAssetData assetData;
				assetData.typeName = dataType->Name;
				assetData.typeAcronym = dataType->Acronym;

				std::string assetName;

				for (auto& prop : dataType->Properties)
				{
					if (prop != nullptr && prop->IsPrimaryKey)
					{
						assetName = prop->Name;
						break;
					}
				}

				auto IsReference = [dataType](std::string variableName)
				{
					if (variableName == "ExportDirectly")
					{
						CORE_LOG(CUSTOM_DATA, "Variable is 'ExportDirectly' - so is ignored");
						return false;
					}

					for (auto& prop : dataType->Properties)
					{
						if (prop != nullptr)
						{
							if (prop->Name == variableName)
							{
								auto line = prop->GetLine();
								return (line.find("AssetType<") < line.size());
							}
						}
					}

					return false;
				};

				for (uint i = 0; i < columnNames.size(); i++)
				{
					if (columnNames[i] == "ExportDirectly")
					{
						assetData.directExport = true;
						continue;
					}

					if (columnNames[i] == assetName)
					{
						assetData.assetName = columnValues[i];
					}

					MetaAssetDataProperty newVariable;
					newVariable.IsReference = IsReference(columnNames[i]);
					newVariable.variableName = columnNames[i];
					newVariable.variableValue = columnValues[i];

					assetData.variables.push_back(newVariable);
				}

				ExportDataItemForType(assetData, exportTo, directAssets);

				return false;
			};

			std::string elementQuery = "Select * from " + type->Name;

			ExportDirectReference_Open(type->Name, directAssets);
			if (!db->Query(elementQuery, exportData, nullptr))
			{
				throw CustomExportException("Query to get assets failed");
			}
			ExportDirectReference_Close(type->Name, directAssets);

			CORE_LOG(CUSTOM_DATA, "Finished exporting data with type: " + type->Name);
		}

		void ExportDirectReference_Open(std::string name, Ptr<File> directAssets)
		{
			directAssets->Write("\t\tstruct " + name);
			directAssets->CreateNewLine();
			directAssets->Write("\t\t{");
			directAssets->CreateNewLine();
		}

		void ExportDirectReference_Close(std::string name, Ptr<File> directAssets)
		{
			auto acronym = Acronym(name);

			directAssets->Write("\t\t};");
			directAssets->CreateNewLine();
			directAssets->Write("\t\tconst " + name + " " + acronym + ";");
			directAssets->CreateNewLine();
		}

		void ExportDataItemForType(MetaAssetData asset, FilePath exportTo, Ptr<File> directAssets)
		{
			exportTo.File = to_string(HashValue(asset.assetName)) + "." + asset.typeAcronym;
			CORE_LOG(CUSTOM_DATA, exportTo.GetFullPath());
			File assetFile = File(exportTo, std::ios::out);
			assetFile.Open();
			assetFile.Clear();

			for (auto& variable : asset.variables)
			{
				auto value = (variable.IsReference ? to_string(HashValue(variable.variableValue)) : variable.variableValue);
				assetFile.Write(variable.variableName + " " + value);
				assetFile.CreateNewLine();
			}

			if (asset.directExport)
			{
				std::string assetName = "AssetName<" + asset.typeName + ">";
				directAssets->Write("\t\t\tconst " + assetName + " " + asset.assetName + " = " + assetName + "(" + to_string(HashValue(asset.assetName)) + ");");
				directAssets->CreateNewLine();
			}

			assetFile.Close();
		}

		void InitializeCustomAssetFile(Ptr<File> customAssets)
		{
			customAssets->Clear();

			std::string header = R"(#pragma once

#include "Data/Headers/AssetType.h"

/*
This file is auto-generated.

DO NOT MODIFY
*/

namespace Data
{
)";
			customAssets->Write(header);
		}

		void FinalizeCustomAssetFile(Ptr<File> customAssets)
		{
			std::string footer = R"(
}
)";
			customAssets->Write(footer);
		}
	}
}