#include "ApplicationManagement/Rendering/Shaders/Headers/FragmentShader.h"

#include <string>  

using namespace std::string_literals;

namespace Application
{
	namespace Rendering
	{
		Ptr<const char> FragmentShader::Shader = R"(
			#version 450 core
			
			layout(location = 0) out vec4 fColor;

			// values passed from vertex shader
			in vec4 Color;
			in smooth float CameraFacingRatio; // DebugVertexShader ALSO uses this
			
			// Values that stay constant for the whole mesh
			
			void main()
			{
				// this is to try and get some shading
				//fColor = vec4(Color.xyz * (1.0 - CameraFacingRatio), Color.w);
				fColor = Color;
			}
		)";

		Ptr<const char> FragmentShader::GetShader() const
		{
			return Shader;
		}

		void FragmentShader::Prepare() const
		{
			// set the required information that needs to be used in the shader
		}

		void FragmentShader::CleanUp() const
		{
			// this may not need to be used
		}
	}
}