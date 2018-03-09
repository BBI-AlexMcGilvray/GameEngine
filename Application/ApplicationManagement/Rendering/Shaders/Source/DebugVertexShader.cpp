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
				// normal ratio for outlining
				vec3 facingCamera = vec3(0, 0, 1);
				vec3 rotatedNormal = (MVP * vec4(vNormal, 0.0)).xyz;
				float dot = dot(rotatedNormal, facingCamera);
				float normalRatio = (dot * dot) / dot(rotatedNormal, rotatedNormal);

				Color = modColor * (1.0 - normalRatio);
				
				gl_Position = vec4(vPosition, 1.0);
			}
		)";

		Ptr<const char> DebugVertexShader::GetShader() const
		{
			return Shader;
		}

		void DebugVertexShader::Prepare(GLuint program, const Color& color) const
		{
			// assign color to shader
			GLint modColor = glGetUniformLocation(program, "modColor");
			glUniform4fv(modColor, 1, &(color.R));
		}

		void DebugVertexShader::CleanUp() const
		{
			// this may not need to be used
		}
	}
}