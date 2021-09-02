#pragma once

// #include "sqlite3.h"
#include "Factory/Workers/SQLiteCpp-3.1.1/sqlite3/sqlite3.h"

#include "Core/Headers/CoreDefs.h"

namespace Data
{
	namespace SQL
	{
		using SQLDB = sqlite3;

		// in the future, we could create a query system with structs
		// ex:
		/*
		struct SQLQueryElement
		{
			virtual String GetText() const = 0;
		}

		struct SQLSelectQuery : SQLQueryElement
		{
			String GetText() const override;
		}

		struct SQLQuery
		{
			List<SQLQueryElement> elements;

			String CreateQuery() const;
		}
		*/
	}
}