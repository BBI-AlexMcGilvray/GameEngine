#pragma once

#include <string>
#include <vector>

#include "Factory/SQL/Headers/SQLDefs.h"

#include "Core/Headers/PtrDefs.h"

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

			// Callback function definition: bool rowOperation(void* forwardedInfo, int columnCount, std::vector<std::string> columnValues, std::vector<std::string> columnNames);
			// rowOperation return value is if the query should stop
			bool Query(std::string sqlCall, BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>> rowOperation, Ptr<void> forwardedInfo);
			bool Query(std::vector<std::string> sqlCalls, BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>> rowOperation, Ptr<void> forwardedInfo);

			std::string GetError();

		private:
			FilePath DBPath;
			int PathLength = 0;
			Ptr<SQLDB> DB;

			DBState State = DBState::Closed;

			std::string LatestError = "";

			void Free(char* errorHolder);
		};
	}
}