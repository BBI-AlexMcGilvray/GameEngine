#pragma once

#include "Core/Headers/Exception.h"

using namespace Core;

namespace Data
{
	namespace DataExport
	{
		struct ExportException : Exception
		{
			using Exception::Exception;
		};

		struct CustomExportException : ExportException
		{
			using ExportException::ExportException;
		};
	}
}