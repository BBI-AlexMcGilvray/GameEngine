#pragma once

#include <string>

#include "Core/IO/Headers/File.h"
#include "Core/Headers/PtrDefs.h"

#include "Factory/Headers/Config.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace DataExport
	{
		void ExportData();

		void ExportCustomData(Ptr<File> directAssets, Config& config);
		void ExportRenderingData(Ptr<File> directAssets, Config& config);

		void InitializeAssetsFile(Ptr<File> directAssets);
		void FinalizeAssetsFile(Ptr<File> directAssets);

		// none of the below should be here, but for the sake of getting this running without re-configuring
		// the whole mesh/mat export data sequence
		void ExportDirectReference_Open(std::string name, std::string acronym, Ptr<File> directAssets);
		void ExportDirectReference_Close(std::string name, std::string acronym, Ptr<File> directAssets);
	}
}