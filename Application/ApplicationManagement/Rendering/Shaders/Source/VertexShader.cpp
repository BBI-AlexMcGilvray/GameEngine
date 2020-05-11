#include "ApplicationManagement/Rendering/Shaders/Headers/VertexShader.h"

#include <string>  

using namespace std::string_literals;

namespace Application
{
	namespace Rendering
	{
		// try the below, but with the 'facingCamera' variable set as the actual camera's facing
		Ptr<const char> VertexShader::Shader = R"(
			#version 450 core
			
			// values per vertex
			layout(location = 0) in vec3 vPosition;
			layout(location = 1) in vec3 vNormal;
			
			// Values that stay constant for the whole mesh
			uniform mat4 MVP;
			uniform vec4 modColor;
			
			// values to return to fragment shader
			out vec4 Color;
			out smooth float CameraFacingRatio;
			
			void main()
			{
				vec3 facingCamera = vec3(0.0, 0.0, -1.0);
				vec3 rotatedNormal = vec3(MVP * vec4(vNormal, 0.0));
				float dotProduct = dot(rotatedNormal, facingCamera);

				// the below can be used to outline characters based on normal
				CameraFacingRatio = (dotProduct * dotProduct) / dot(rotatedNormal, rotatedNormal);

				Color = modColor * CameraFacingRatio;
				
				gl_Position = MVP * vec4(vPosition, 1.0);
			}
		)";

		Ptr<const char> VertexShader::GetShader() const
		{
			return Shader;
		}

		void VertexShader::Prepare(GLuint program, const Float4x4& mvp, const Color& color) const
		{
			// set the required information that needs to be used in the shader
			GLint MVP = glGetUniformLocation(program, "MVP");
			glUniformMatrix4fv(MVP, 1, GL_FALSE, (GLfloat*)&(mvp.Bases[0]));

			// assign color to shader
			GLint modColor = glGetUniformLocation(program, "modColor");
			glUniform4fv(modColor, 1, color.Values);
		}

		void VertexShader::CleanUp() const
		{
			// this may not need to be used
		}
	}
}