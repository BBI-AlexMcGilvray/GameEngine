#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShader.h"

namespace Application
{
	namespace Rendering
	{
		Ptr<const char> ObjectShader::Name = "ObjectShader";

		void ObjectShader::Prepare(const Float4x4& mvp, const Color& color)
		{
			ObjectShaderBase::Prepare();

			VShader.Prepare(Object, mvp, color);
			FShader.Prepare();
		}

		void ObjectShader::CleanUp()
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
			glDetachShader(Object, VShader.Object);
			glDetachShader(Object, FShader.Object);

			ObjectShaderBase::Destroy();
		}
	}
}