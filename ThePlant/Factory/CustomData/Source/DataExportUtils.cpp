#include "Factory/CustomData/Headers/DataExportUtils.h"

#include "Factory/Headers/ExportException.h"

namespace Data
{
	namespace DataExport
	{
		UniquePtr<DataType> CreateType(String sql)
		{
			auto typeName = TableName(sql);
			UniquePtr<DataType> NewType = MakeUnique<DataType>(typeName, Acronym(typeName));

			auto sqlCommands = sql.substr(sql.find("(") + 1, sql.find(")"));

			while (true)
			{
				auto nextCommand = sqlCommands.find(",");
				bool noNextCommand = nextCommand >= sqlCommands.length();

				auto sqlCommand = sqlCommands.substr(0, nextCommand);

				Push(NewType->Properties, CreateProperty(sqlCommand));

				sqlCommands = ClipLeadingWhitespace(sqlCommands.substr(nextCommand + 1));
				if (sqlCommands.length() == 0 || noNextCommand)
				{
					break;
				}
			}

			return NewType;
		}

		UniquePtr<DataProperty> CreateProperty(String sqlColumn)
		{
			if (IsExported(sqlColumn))
			{
				return nullptr;
			}

			String type = TypeName(sqlColumn);
			String name = FieldName(sqlColumn);

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

		String TableName(String sql)
		{
			String header = "CREATE TABLE";
			auto index = sql.find(header);

			auto remaining = sql.substr(index + header.length());
			remaining = ClipLeadingWhitespace(remaining);

			auto name = remaining.substr(0, remaining.find(" "));

			return name;
		}

		String Acronym(String tableName)
		{
			List<char> vowels = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };

			String acronym;

			size index = 0;
			while (acronym.length() < 3 && index < tableName.length())
			{
				if (!InList(vowels, tableName[index]))
				{
					acronym += tableName[index];
				}

				index++;
			}

			return acronym;
		}

		String FieldName(String sqlColumn)
		{
			return sqlColumn.substr(0, sqlColumn.find(" "));
		}

		String TypeName(String sqlColumn)
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
				return "String";
			}
			else if (sqlType == "BIGINT" || sqlType == "DATE" || sqlType == "DATETIME")
			{
				return "uint";
			}

			throw CustomExportException("Uknown sql type field <" + sqlType + ">");
		}

		bool IsPrimaryKey(String sqlColumn)
		{
			return (sqlColumn.find("PRIMARY KEY") < sqlColumn.length());
		}

		bool IsForeignKey(String sqlColumn)
		{
			return (sqlColumn.find("REFERENCES") < sqlColumn.length());
		}

		String GetForeignKeyType(String sqlColumn)
		{
			if (IsForeignKey(sqlColumn))
			{
				auto start = sqlColumn.find("REFERENCES");
				auto remaining = ClipLeadingWhitespace(sqlColumn.substr(start));

				return remaining.substr(0, remaining.find(" "));
			}

			throw CustomExportException("Foreign key type requested for non foreign key type! <" + sqlColumn + ">");
		}

		bool IsList(String sqlColumn)
		{
			return ("List" == sqlColumn.substr(0, 4));
		}

		bool IsExported(String sqlColumn)
		{
			return ("ExportDirectly" == sqlColumn.substr(0, 14));
		}

		String ClipLeadingWhitespace(String str)
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