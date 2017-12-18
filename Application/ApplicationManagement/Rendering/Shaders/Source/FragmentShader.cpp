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
			
			in vec2 UV;
			in vec4 Color;
			
			// Values that stay constant for the whole mesh
			
			
			void main()
			{
				fColor = Color;
			}
		)";

		Ptr<const char> FragmentShader::GetShader() const
		{
			return Shader;
		}

		void FragmentShader::Prepare()
		{
			// set the required information that needs to be used in the shader
		}

		void FragmentShader::CleanUp()
		{
			// this may not need to be used
		}
	}
}