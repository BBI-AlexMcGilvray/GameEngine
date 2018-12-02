#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Vector2.h"

#include "Data/Headers/AssetType.h"

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

			TextureData(String file);
		};
	}

	/*
	template <>
	struct AssetType<Rendering::TextureData>
	{
		Hash ClassHash() const
		{
			return HashValue("TextureData");
		}

		String GetPath() const
		{
			return "Resources/ExportedAssets/Textures/";
		}

		String GetFileType() const
		{
			return ".Txt";
		}
	};
	*/
}