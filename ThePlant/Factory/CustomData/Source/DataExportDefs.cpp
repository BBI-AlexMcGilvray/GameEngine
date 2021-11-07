#include "Factory/CustomData/Headers/DataExportDefs.h"

namespace Data
{
	namespace DataExport
	{
		std::string DataType::GetDefinition()
		{
			std::string definition = "\tstruct " + Name + "\n";
			definition += "\t{\n";
			for (auto& prop : Properties)
			{
				if (prop != nullptr)
				{
					definition += "\t\t" + prop->GetLine() + "\n";
				}
			}
			definition += "\t};\n";

			return definition;
		}

		std::string DataType::GetMetaTypeDefinition()
		{
			std::string definition = "\ttemplate<>\n";
			definition += "\tstruct AssetType<" + Name + ">\n";
			definition += "\t{\n";
			definition += "\t\tHash ClassHash() const\n";
			definition += "\t\t{\n";
			definition += "\t\t\treturn Core::HashValue(\"" + Name + "\");\n";
			definition += "\t\t}\n";
			definition += "\n";
			definition += "\t\tstd::string GetPath() const\n";
			definition += "\t\t{\n";
			definition += "\t\t\treturn \"CustomAssets/" + Name + "/\";\n";
			definition += "\t\t}\n";
			definition += "\n";
			definition += "\t\tstd::string GetFileType() const\n";
			definition += "\t\t{\n";
			definition += "\t\t\treturn \"." + Acronym + "\";\n";
			definition += "\t\t}\n";
			definition += "\t};";

			return definition;
		}
	}
}