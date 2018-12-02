#include "Data/Rendering/Headers/StaticModelData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		StaticModelData::StaticModelData(String fileName)
		{
			File modelFile = OpenFileI(FilePath{ String("Resources/ExportedAssets/Models/"), fileName });

			MESSAGE(modelFile.FileStream.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

			try
			{
				String line = modelFile.GetLine();

				IOSStreamChar lineStream(line);
				
				lineStream >> Material.Name.H;
				lineStream >> Mesh.Name.H;
				lineStream >> Skeleton.Name.H;
				lineStream >> Texture.Name.H;
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
			}

			modelFile.Close();
		}
	}
}