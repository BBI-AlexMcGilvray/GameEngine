#pragma once

#include "Data/SQL/Headers/SQLDefs.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/Functionality/Headers/Function.h"

#include "Core/IO/Headers/IODefs.h"

using namespace Core;
using namespace Core::Functionality;
using namespace Core::IO;

namespace Data
{
	namespace SQL
	{
		struct SQLInstance
		{
			// Reference: https://www.sqlite.org/c3ref/exec.html

			/*
				Once read/write has been modified, it may be possible to have this be a specialized SQL reader/writer?
			*/

			enum class DBState
			{
				Closed,
				Open,
				Errored
			};

			SQLInstance();
			SQLInstance(FilePath dbPath);

			void SetDB(FilePath dbPath);

			bool Open();
			void Close();

			// Callback function definition: bool rowOperation(void* forwardedInfo, int columnCount, List<String> columnValues, List<String> columnNames);
			// rowOperation return value is if the query should stop
			bool Query(String sqlCall, Function<bool, Ptr<void>, List<String>, List<String>> rowOperation, Ptr<void> forwardedInfo);
			bool Query(List<String> sqlCalls, Function<bool, Ptr<void>, List<String>, List<String>> rowOperation, Ptr<void> forwardedInfo);

			String GetError();

		private:
			FilePath DBPath;
			int PathLength = 0;
			Ptr<SQLDB> DB;

			DBState State = DBState::Closed;

			String LatestError = "";

			void Free(char* errorHolder);
		};
	}
}