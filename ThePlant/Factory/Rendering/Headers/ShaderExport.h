#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/IO/Headers/File.h"

#include "Factory/Headers/Config.h"

namespace Data
{
	namespace DataExport
	{
        void ExportShadersInFolder(Config& config, Core::Ptr<Core::IO::File> directAssets, std::string folder);
	}
}
