#include "Factory/CustomData/Headers/DataExportUtils.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Factory/Headers/ExportException.h"

namespace Data
{
	namespace DataExport
	{
		UniquePtr<DataType> CreateType(std::string sql)
		{
			SCOPED_MEMORY_CATEGORY("DataExport");
			auto typeName = TableName(sql);
			UniquePtr<DataType> NewType = MakeUnique<DataType>(typeName, Acronym(typeName));

			auto sqlCommands = sql.substr(sql.find("(") + 1, sql.find(")"));

			while (true)
			{
				auto nextCommand = sqlCommands.find(",");
				bool noNextCommand = nextCommand >= sqlCommands.length();

				auto sqlCommand = sqlCommands.substr(0, nextCommand);

				NewType->Properties.push_back(CreateProperty(sqlCommand));

				sqlCommands = ClipLeadingWhitespace(sqlCommands.substr(nextCommand + 1));
				if (sqlCommands.length() == 0 || noNextCommand)
				{
					break;
				}
			}

			return NewType;
		}

		UniquePtr<DataProperty> CreateProperty(std::string sqlColumn)
		{
			if (IsExported(sqlColumn))
			{
				return nullptr;
			}

			std::string type = TypeName(sqlColumn);
			std::string name = FieldName(sqlColumn);

			UniquePtr<DataProperty> newProperty;

			if (IsList(sqlColumn))
			{
				newProperty = MakeUnique<DataPropertyList>(type, name);
			}
			else if (IsForeignKey(sqlColumn))
			{
				newProperty = MakeUnique<DataPropertyData>(type, name);
			}
			else
			{
				newProperty = MakeUnique<DataProperty>(type, name);
			}

			if (IsPrimaryKey(sqlColumn))
			{
				newProperty->IsPrimaryKey = true;
			}

			return move(newProperty);
		}

		std::string TableName(std::string sql)
		{
			std::string header = "CREATE TABLE";
			auto index = sql.find(header);

			auto remaining = sql.substr(index + header.length());
			remaining = ClipLeadingWhitespace(remaining);

			auto name = remaining.substr(0, remaining.find(" "));

			return name;
		}

		std::string Acronym(std::string tableName)
		{
			std::vector<char> vowels = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };

			std::string acronym;

			size index = 0;
			while (acronym.length() < 3 && index < tableName.length())
			{
				if (std::find(vowels.begin(), vowels.end(), tableName[index]) != vowels.end())
				{
					acronym += tableName[index];
				}

				index++;
			}

			return acronym;
		}

		std::string FieldName(std::string sqlColumn)
		{
			return sqlColumn.substr(0, sqlColumn.find(" "));
		}

		std::string TypeName(std::string sqlColumn)
		{
			auto firstSpace = sqlColumn.find(" ") + 1;
			auto secondSpace = sqlColumn.find(" ", firstSpace);
			auto sqlType = sqlColumn.substr(firstSpace, secondSpace - firstSpace);

			if (sqlType == "BOOLEAN")
			{
				return "bool";
			}
			if (sqlType == "CHAR")
			{
				return "char";
			}
			else if (sqlType == "DOUBLE")
			{
				return "double";
			}
			else if (sqlType == "FLOAT" || sqlType == "DECIMAL" || sqlType == "REAL")
			{
				return "float";
			}
			else if (sqlType == "INT" || sqlType == "INTEGER")
			{
				return "int";
			}
			else if (sqlType == "STRING" || sqlType == "BLOB" || sqlType == "TEXT" || sqlType == "VARCHAR")
			{
				return "std::string";
			}
			else if (sqlType == "BIGINT" || sqlType == "DATE" || sqlType == "DATETIME")
			{
				return "uint";
			}

			throw CustomExportException("Uknown sql type field <" + sqlType + ">");
		}

		bool IsPrimaryKey(std::string sqlColumn)
		{
			return (sqlColumn.find("PRIMARY KEY") < sqlColumn.length());
		}

		bool IsForeignKey(std::string sqlColumn)
		{
			return (sqlColumn.find("REFERENCES") < sqlColumn.length());
		}

		std::string GetForeignKeyType(std::string sqlColumn)
		{
			if (IsForeignKey(sqlColumn))
			{
				auto start = sqlColumn.find("REFERENCES");
				auto remaining = ClipLeadingWhitespace(sqlColumn.substr(start));

				return remaining.substr(0, remaining.find(" "));
			}

			throw CustomExportException("Foreign key type requested for non foreign key type! <" + sqlColumn + ">");
		}

		bool IsList(std::string sqlColumn)
		{
			return ("List" == sqlColumn.substr(0, 4));
		}

		bool IsExported(std::string sqlColumn)
		{
			return ("ExportDirectly" == sqlColumn.substr(0, 14));
		}

		std::string ClipLeadingWhitespace(std::string str)
		{
			auto index = str.find(" ");

			if (index == 0)
			{
				return str.substr(1);
			}

			return str;
		}
	}
}