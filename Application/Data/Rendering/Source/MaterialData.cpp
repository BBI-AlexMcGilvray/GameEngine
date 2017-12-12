#include "Data/Rendering/Headers/MaterialData.h"

#include "Data/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Data::IO;
using namespace Core;

namespace Data
{
	namespace Rendering
	{
		MaterialData::MaterialData(String fileName)
		{
			IFStreamChar materialFile = OpenFileI(fileName);

			MESSAGE(materialFile.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

			String line;
			while (std::getline(materialFile, line))
			{
				IOSStreamChar lineStream(line);

				String word;
				lineStream >> word;

				String comma;
				lineStream >> comma;
				if (word == "spec")
				{
					lineStream >> Specular.R;
					lineStream >> comma;
					lineStream >> Specular.G;
					lineStream >> comma;
					lineStream >> Specular.B;
					lineStream >> comma;
					lineStream >> Specular.A;
				}
				else if (word == "diff")
				{
					lineStream >> Diffuse.R;
					lineStream >> comma;
					lineStream >> Diffuse.G;
					lineStream >> comma;
					lineStream >> Diffuse.B;
					lineStream >> comma;
					lineStream >> Diffuse.A;
					lineStream >> comma;
				}
				else if (word == "amb")
				{
					lineStream >> Ambient.R;
					lineStream >> comma;
					lineStream >> Ambient.G;
					lineStream >> comma;
					lineStream >> Ambient.B;
					lineStream >> comma;
					lineStream >> Ambient.A;
					lineStream >> comma;
				}
				else if (word == "shin")
				{
					lineStream >> Shininess;
				}
				else
				{
					cout << "Unsuppoerted specifier read in material file <<" + fileName + ">>" << endl;
				}
			}
		}
	}
}