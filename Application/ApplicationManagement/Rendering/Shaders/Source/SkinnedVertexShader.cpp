#include "ApplicationManagement/Rendering/Shaders/Headers/SkinnedVertexShader.h"

#include <string>  

using namespace std::string_literals;

namespace Application
{
	namespace Rendering
	{
		// try the below, but with the 'facingCamera' variable set as the actual camera's facing
		Ptr<const char> SkinnedVertexShader::Shader = R"(
			#version 450 core
			
			// values per vertex
			layout(location = 0) in vec3 vPosition;
			layout(location = 1) in vec3 vNormal;
			layout(location = 2) in vec4 vWeight;
			layout(location = 3) in ivec4 vBoneIndex;
			
			// Values that stay constant for the whole mesh
			uniform mat4 MVP;
			uniform vec4 modColor;
			uniform mat4 boneMatrices[50]; // no more than 50 bones for the moment
			
			// values to return to fragment shader
			out vec4 Color;
			out smooth float CameraFacingRatio;
			
			void main()
			{
				// rotational
				vec3 facingCamera = vec3(0.0, 0.0, -1.0);
				vec3 rotatedNormal = vec3(MVP * vec4(vNormal, 0.0));
				float dotProduct = dot(rotatedNormal, facingCamera);

				// the below can be used to outline characters based on normal
				CameraFacingRatio = (dotProduct * dotProduct) / dot(rotatedNormal, rotatedNormal);

				// colour
				Color = modColor * CameraFacingRatio;

				// positional
				mat4 boneTransform = boneMatrices[vBoneIndex.x] * vWeight.x;
				boneTransform = boneMatrices[vBoneIndex.y] * vWeight.y + boneTransform;
				boneTransform = boneMatrices[vBoneIndex.z] * vWeight.z + boneTransform;
				boneTransform = boneMatrices[vBoneIndex.w] * vWeight.w + boneTransform;

				gl_Position = MVP * vec4((boneTransform * vec4(vPosition, 1.0)).xyz, 1.0);
			}
		)";

		Ptr<const char> SkinnedVertexShader::GetShader() const
		{
			return Shader;
		}


		void SkinnedVertexShader::SetSkinningInformation(const List<Float4x4> boneList)
		{
			BoneList = boneList;
		}

		void SkinnedVertexShader::Prepare(GLuint program, const Float4x4& mvp, const Color& color) const
		{
			// set the required information that needs to be used in the shader
			GLint MVP = glGetUniformLocation(program, "MVP");
			glUniformMatrix4fv(MVP, 1, GL_FALSE, (GLfloat*)&(mvp.Bases[0]));

			// assign color to shader
			GLint modColor = glGetUniformLocation(program, "modColor");
			glUniform4fv(modColor, 1, color.Values);

			// assign bones to shader
			GLint boneMatrices = glGetUniformLocation(program, "boneMatrices");
			glUniformMatrix4fv(boneMatrices, BoneList.size(), GL_FALSE, (GLfloat*)&(BoneList[0].Bases[0]));
		}

		void SkinnedVertexShader::CleanUp() const
		{
			// this may not need to be used
		}
	}
}