#pragma once

#include <string>
#include <vector>

#include "Core/Headers/PtrDefs.h"

#include "Core/IO/Headers/File.h"

#include "ASSIMP/scene.h"

namespace Data
{
	namespace DataExport
	{
		struct ExportNode : aiNode
		{
			bool exportNode = false;

			// created bone from existing node (deep copy)
			ExportNode(Core::Ptr<const aiNode> initialNode);

			// marks node as include if names match
			void IncludeNode(std::string name);

			// marks all nodes with an included child node as export
			// then removes any nodes not marked as export
			void CleanStructure();

		private:
			int initialChildCount = 0;
			bool IncludeIfContainsName(std::string name);

			void ExportIfChildren();
			void RemoveNonExportChildren();
			void CleanUpChildren();
		};
	}
}
