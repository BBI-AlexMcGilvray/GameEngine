#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Data/Headers/AssetName.h"
#include "Data/Rendering/Headers/MaterialData.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShaderBase.h"

using namespace Core;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		// holds shader information in terms of how it is affected by light, shadows, ...
		// maybe should contain the data, not BE the data?
		struct Material
		{
			Data::Rendering::MaterialData Data;
			Core::Ptr<ObjectShaderBase> Shader;

			Material();
			Material(Data::AssetName<Data::Rendering::MaterialData> asset);

			void SetShader(Core::Ptr<ObjectShaderBase> shader);

			void Update(Core::Second dt);

			void Prepare(const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const;
			void CleanUp() const;

			// NOT Initialize or Destroy, those are called by the ShaderManager
		};
	}
}