#include "ApplicationManagement/Rendering/Shaders/Headers/DebugVertexShader.h"

#include <string>  

using namespace std::string_literals;

namespace Application
{
	namespace Rendering
	{
		Ptr<const char> DebugVertexShader::Shader = R"(
			#version 450 core
			
			// values per vertex
			layout(location = 0) in vec3 vPosition;
			
			// Values that stay constant for the whole mesh
			uniform vec4 modColor;
			
			// values to return
			out vec4 Color;
			
			void main()
			{
				Color = modColor;
				
				gl_Position = vec4(vPosition, 1.0);
			}
		)";

		Ptr<const char> DebugVertexShader::GetShader() const
		{
			return Shader;
		}

		void DebugVertexShader::Prepare(GLuint program, const Color& color)
		{
			// assign color to shader
			GLint modColor = glGetUniformLocation(program, "modColor");
			glUniform4fv(modColor, 1, &(color.Values[0]));
		}

		void DebugVertexShader::CleanUp()
		{
			// this may not need to be used
		}
	}
}