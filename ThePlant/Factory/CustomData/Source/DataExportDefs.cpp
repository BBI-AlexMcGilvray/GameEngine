#include "Factory/CustomData/Headers/DataExportDefs.h"

namespace Data
{
	namespace DataExport
	{
		String DataType::GetDefinition()
		{
			String definition = "\tstruct " + Name + "\n";
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

		String DataType::GetMetaTypeDefinition()
		{
			String definition = "\ttemplate<>\n";
			definition += "\tstruct AssetType<" + Name + ">\n";
			definition += "\t{\n";
			definition += "\t\tHash ClassHash() const\n";
			definition += "\t\t{\n";
			definition += "\t\t\treturn Core::HashValue(\"" + Name + "\");\n";
			definition += "\t\t}\n";
			definition += "\n";
			definition += "\t\tString GetPath() const\n";
			definition += "\t\t{\n";
			definition += "\t\t\treturn \"CustomAssets/" + Name + "/\";\n";
			definition += "\t\t}\n";
			definition += "\n";
			definition += "\t\tString GetFileType() const\n";
			definition += "\t\t{\n";
			definition += "\t\t\treturn \"." + Acronym + "\";\n";
			definition += "\t\t}\n";
			definition += "\t};";

			return definition;
		}
	}
}