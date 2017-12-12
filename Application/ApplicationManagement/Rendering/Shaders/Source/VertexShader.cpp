#include "ApplicationManagement/Rendering/Shaders/Headers/VertexShader.h"

#include <string>  

using namespace std::string_literals;

namespace Application
{
	namespace Rendering
	{
		Ptr<const char> VertexShader::Shader = R"(
			#version 450 core
			
			// values per vertex
			layout(location = 0) in vec3 vPosition;
			layout(location = 1) in vec3 vNormal;
			
			// Values that stay constant for the whole mesh
			uniform mat4 MVP;
			uniform vec4 modColor;
			
			// values to return
			out vec4 Color;
			
			void main()
			{
				Color = modColor;
				
				gl_Position = MVP * vec4(vPosition, 1.0);
			}
		)";

		void VertexShader::Prepare(const Float4x4& mvp, const Color& color)
		{
			// set the required information that needs to be used in the shader
			GLint MVP = glGetUniformLocation(Program, "MVP");
			glUniformMatrix4fv(MVP, 1, GL_FALSE, (GLfloat*)&(mvp[0]));

			// assign color to shader
			GLint modColor = glGetUniformLocation(Program, "modColor");
			glUniform4fv(modColor, 1, &(color.Values[0]));
		}

		void VertexShader::CleanUp()
		{
			// this may not need to be used
		}
	}
}