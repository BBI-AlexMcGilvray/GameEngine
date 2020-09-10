#include "ApplicationManagement/Rendering/Shaders/Headers/SkinnedVertexShader.h"

#include "Core/Debugging/Headers/Macros.h"

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
			layout(location = 3) in vec4 vBoneIndex; // for some reason, ints are not being read in correctly
			
			// Values that stay constant for the whole mesh
			uniform mat4 MVP;
			uniform vec4 modColor;
			uniform mat4 boneMatrices[50]; // no more than 50 bones for the moment
			
			// values to return to fragment shader
			out vec4 Color;
			out smooth float CameraFacingRatio;

			// testing
			out mat4 bTransform;
			out mat4 bOne;
			out mat4 bTwo;
			out mat4 bThree;
			out mat4 bFour;
			out vec4 wA;
			//out vec4 iA;
			//out float i1;
			//out int i2;
			//out int i3;
			//out int i4;

			
			void main()
			{
				// rotational
				vec3 facingCamera = vec3(0.0, 0.0, -1.0);
				vec3 rotatedNormal = vec3(MVP * vec4(vNormal, 0.0));
				float dotProduct = dot(rotatedNormal, facingCamera);

				// the below can be used to outline characters based on normal
				CameraFacingRatio = (dotProduct * dotProduct) / dot(rotatedNormal, rotatedNormal);

				// colour
				//Color = modColor * CameraFacingRatio;

				// positional
				vec4 boneWeight = vWeight;
				mat4 boneTransform = (boneMatrices[int(vBoneIndex[0])] * boneWeight[0]);
				boneTransform += (boneMatrices[int(vBoneIndex[1])] * boneWeight[1]);
				boneTransform += (boneMatrices[int(vBoneIndex[2])] * boneWeight[2]);
				boneTransform += (boneMatrices[int(vBoneIndex[3])] * boneWeight[3]);

				// testing
				bTransform = boneTransform;
				bOne = (boneMatrices[int(vBoneIndex[0])]);
				bTwo = (boneMatrices[int(vBoneIndex[1])]);
				bThree = (boneMatrices[int(vBoneIndex[2])]);
				bFour = (boneMatrices[int(vBoneIndex[3])]);
				wA = vWeight;
				//iA = vBoneIndex;
				//i1 = float(vBoneIndex[0]);
				//i2 = int(vBoneIndex.y);
				//i3 = int(vBoneIndex[2]);
				//i4 = 7;

				// testing
				Color = vec4(vec3(1.0) - (vPosition - (boneTransform * vec4(vPosition, 1.0)).xyz), 1.0);

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
			// Should this be using it's own Object field value instead of the passed in program value?
			// Why is modColor returning a value of -1? because it is not currently being used

			// set the required information that needs to be used in the shader
			GLint MVP = glGetUniformLocation(program, "MVP");
			glUniformMatrix4fv(MVP, 1, GL_FALSE, (GLfloat*)&(mvp.E1.X));

			// assign color to shader
			GLint modColor = glGetUniformLocation(program, "modColor");
			glUniform4fv(modColor, 1, color.Values);

			// assign bones to shader
			VERIFY(BoneList.size() <= 50);
			GLint boneMatrices = glGetUniformLocation(program, "boneMatrices");
			glUniformMatrix4fv(boneMatrices, BoneList.size(), GL_FALSE, (GLfloat*)&(BoneList[0].E1.X));
		}

		void SkinnedVertexShader::CleanUp() const
		{
			// this may not need to be used
		}
	}
}