#pragma once

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLDefs.h"

namespace Application
{
	namespace Rendering
	{
		struct GLObject
		{
			GLuint Object;
			GLenum Type;

			GLObject();
			GLObject(GLuint object, GLenum type);

			virtual ~GLObject() = default;

			virtual void SetObject(GLuint object);
			virtual void SetType(GLenum type);
		};
	}
}