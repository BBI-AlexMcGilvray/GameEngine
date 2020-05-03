#include "ApplicationManagement/Rendering/Shaders/Headers/SkinnedObjectShader.h"

namespace Application
{
	namespace Rendering
	{
		Ptr<const char> SkinnedObjectShader::Name = "SkinnedObjectShader";

		Ptr<const char> SkinnedObjectShader::GetName()
		{
			return Name;
		}

		Ptr<ShaderBase> SkinnedObjectShader::GetVertexShader()
		{
			return &FShader;
		}

		Ptr<ShaderBase> SkinnedObjectShader::GetFragmentxShader()
		{
			return &VShader;
		}

		void SkinnedObjectShader::Prepare(const Float4x4& mvp, const Color& color) const
		{
			ObjectShaderBase::Prepare();

			VShader.Prepare(Object, mvp, color);
			FShader.Prepare();
		}

		void SkinnedObjectShader::CleanUp() const
		{
			VShader.CleanUp();
			FShader.CleanUp();

			ObjectShaderBase::CleanUp();
		}

		void SkinnedObjectShader::Initialize()
		{
			ObjectShaderBase::Initialize();

			glBindAttribLocation(Object, 0, "vPosition"); // maybe not needed if specified in shader?
			glBindAttribLocation(Object, 1, "vNormal"); // maybe not needed if specified in shader?
		}

		void SkinnedObjectShader::Destroy()
		{
			ObjectShaderBase::Destroy();
		}
	}
}