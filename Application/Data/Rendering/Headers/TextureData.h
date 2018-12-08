#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Vector2.h"

#include "Data/Headers/AssetName.h"

using namespace Core;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		struct TextureData
		{
			Float2 Size;
			String ImageFile;

			TextureData() = delete;

			TextureData(AssetName<TextureData> asset);
		};
	}

	template <>
	struct AssetType<Rendering::TextureData>
	{
		static Hash ClassHash()
		{
			return HashValue("TextureData");
		}

		static String GetPath()
		{
			return "Resources/Textures/";
		}

		static String GetFileType()
		{
			return ".txt";
		}
	};
}