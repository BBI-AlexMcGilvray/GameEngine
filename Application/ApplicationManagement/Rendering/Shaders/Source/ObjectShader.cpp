#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShader.h"

namespace Application
{
	namespace Rendering
	{
		Ptr<const char> ObjectShader::Name = "ObjectShader";

		Ptr<const char> ObjectShader::GetName()
		{
			return Name;
		}

		Ptr<ShaderBase> ObjectShader::GetVertexShader()
		{
			return &FShader;
		}

		Ptr<ShaderBase> ObjectShader::GetFragmentxShader()
		{
			return &VShader;
		}

		void ObjectShader::Prepare(const Float4x4& mvp, const Color& color) const
		{
			ObjectShaderBase::Prepare();

			VShader.Prepare(Object, mvp, color);
			FShader.Prepare();
		}

		void ObjectShader::CleanUp() const
		{
			VShader.CleanUp();
			FShader.CleanUp();

			ObjectShaderBase::CleanUp();
		}

		void ObjectShader::Initialize()
		{
			ObjectShaderBase::Initialize();

			glBindAttribLocation(Object, 0, "vPosition"); // maybe not needed if specified in shader?
			glBindAttribLocation(Object, 1, "vNormal"); // maybe not needed if specified in shader?
		}

		void ObjectShader::Destroy()
		{
			ObjectShaderBase::Destroy();
		}
	}
}