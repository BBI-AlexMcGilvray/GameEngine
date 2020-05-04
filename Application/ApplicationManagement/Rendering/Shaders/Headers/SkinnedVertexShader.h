#pragma once
#pragma once

#include "ShaderBase.h"

#include "Core/Headers/PtrDefs.h"

#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Dependencies\Includes\GLEW\glew.h"

using namespace Core;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		// holds onto vertex shader information
		struct SkinnedVertexShader : ShaderBase
		{
			SkinnedVertexShader()
				: ShaderBase("SkinnedVertexShader", GL_VERTEX_SHADER)
			{}

			Ptr<const char> GetShader() const override;

			void SetSkinningInformation(const List<Float4x4> boneList);

			virtual void Prepare(GLuint program, const Float4x4& mvp, const Color& color) const;
			virtual void CleanUp() const;

		protected:
			static Ptr<const char> Shader;

			// skinning information
			List<Float4x4> BoneList;
		};
	}
}