#include "Data/Rendering/Headers/MaterialData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;

namespace Data
{
	namespace Rendering
	{
		MaterialData::MaterialData(AssetName<MaterialData> asset)
		{
			File materialFile = OpenFileI(asset.GetFilePath());

			MESSAGE(materialFile.FileStream.is_open(), "FAILED TO READ FILE <<" + asset.GetFilePath().GetFullPath() + ">>");

			try
			{
				while (true)
				{
					String line = materialFile.GetLine();

					IOSStreamChar lineStream(line);

					String word;
					lineStream >> word;

					if (word == "spec")
					{
						lineStream >> Specular.R;
						lineStream >> Specular.G;
						lineStream >> Specular.B;
						lineStream >> Specular.A;
					}
					else if (word == "diff")
					{
						lineStream >> Diffuse.R;
						lineStream >> Diffuse.G;
						lineStream >> Diffuse.B;
						lineStream >> Diffuse.A;
					}
					else if (word == "amb")
					{
						lineStream >> Ambient.R;
						lineStream >> Ambient.G;
						lineStream >> Ambient.B;
						lineStream >> Ambient.A;
					}
					else if (word == "shin")
					{
						lineStream >> Shininess;
					}
					else
					{
						cout << "Unsuppoerted specifier read in material file <<" + asset.GetFilePath().GetFullPath() + ">>" << endl;
					}
				}
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
			}

			materialFile.Close();
		}
	}
}