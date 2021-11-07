#pragma once

#include "Factory/SQL/Headers/SQLInstance.h"

#include "Core/Logging/Logger.h"

namespace Data
{
	namespace SQL
	{
		namespace 
		{
			const std::string SQL_INSTANCE = "SQL Instance";
		}

		SQLInstance::SQLInstance()
		{}

		SQLInstance::SQLInstance(FilePath dbPath)
		{
			SetDB(dbPath);
		}

		void SQLInstance::SetDB(FilePath dbPath)
		{
			DBPath = dbPath;
			PathLength = DBPath.GetFullPath().length();
		}

		bool SQLInstance::Open()
		{
			auto fullPath = DBPath.GetFullPath();
			Ptr<const char> path = fullPath.c_str();
			int rc = sqlite3_open(path, &DB);
			CORE_LOG(SQL_INSTANCE, "Opening <" + DBPath.GetFullPath() + ">");

			if (rc != SQLITE_OK)
			{
				CORE_LOG(SQL_INSTANCE, "Failed to open DB <" + DBPath.GetFullPath() + "> - error code: " + std::to_string(rc));
				LatestError = "Unable to open DB <" + DBPath.GetFullPath() + "> - error code: " + std::to_string(rc);
				State = DBState::Errored;
				return false;
			}
			
			State = DBState::Open;
			return true;
		}

		void SQLInstance::Close()
		{
			sqlite3_close(DB);
			CORE_LOG(SQL_INSTANCE, "Closing <" + DBPath.GetFullPath() + ">");

			State = DBState::Closed;
		}

		bool SQLInstance::Query(std::string sqlCall, BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>> rowOperation, Ptr<void> forwardedInfo)
		{
			CORE_LOG(SQL_INSTANCE, "Querying <" + DBPath.GetFullPath() + ">");

			if (State != DBState::Open)
			{
				LatestError = "Tried to query when DB was not in open state.";
				return false;
			}

			// need to wrap the callback, and the user-desired forwarded info so lambda can be called
			// (lambdas cannot be cast to function pointers if they capture objects - since they are _essentially_ structs if they capture)
			struct WrappedInfo
			{
				Ptr<void> ForwardedInfo;
				BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>>& RowOperation;

				// need this constructor as MakeUnique does NOT work on initializer lists
				WrappedInfo(Ptr<void> forwardedInfo, BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>>& rowOperation)
					: ForwardedInfo(forwardedInfo), RowOperation(rowOperation)
				{}
			};
			UniquePtr<WrappedInfo> wrappedInfoObj = MakeUnique<WrappedInfo>(forwardedInfo, rowOperation);

			auto intermediateCallback = [](Ptr<void> wrappedInfo, int columnCount, Ptr<Ptr<char>> columnValues, Ptr<Ptr<char>> columnNames) -> int
			{
				Ptr<WrappedInfo> wrappedInfoObj = static_cast<Ptr<WrappedInfo>>(wrappedInfo);

				std::vector<std::string> columnValueStrings;
				std::vector<std::string> columnNameStrings;

				for (int i = 0; i < columnCount; i++)
				{
					columnValueStrings.push_back(std::string(columnValues[i]));
					columnNameStrings.push_back(std::string(columnNames[i]));
				}

				return wrappedInfoObj->RowOperation(wrappedInfoObj->ForwardedInfo, columnValueStrings, columnNameStrings);
			};

			Ptr<Ptr<char>> errorMessage = nullptr;

			int callResult = sqlite3_exec(DB, sqlCall.c_str(), intermediateCallback, wrappedInfoObj.get(), errorMessage);

			if (callResult != SQLITE_OK)
			{
				Free(*errorMessage);
				return false;
			}

			return true;
		}

		bool SQLInstance::Query(std::vector<std::string> sqlCalls, BoolFunction<Ptr<void>, std::vector<std::string>, std::vector<std::string>> rowOperation, Ptr<void> forwardedInfo)
		{
			for (auto& sqlCall : sqlCalls)
			{
				if (!Query(sqlCall, rowOperation, forwardedInfo))
				{
					return false;
				}
			}

			return true;
		}

		std::string SQLInstance::GetError()
		{
			return LatestError;
		}

		void SQLInstance::Free(char* errorHolder)
		{
			LatestError = errorHolder;
			sqlite3_free(errorHolder);
		}
	}
}