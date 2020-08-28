#pragma once

#include "GLObject.h"
#include "GLBuffer.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/CoreDefs.h"

namespace Application
{
	namespace Rendering
	{
		struct GLMappedBuffer
		{
		private:
			GLBuffer _buffer;
			Core::Ptr<void> _mappedBuffer = nullptr;
			GLenum _accessType = GL_NONE;

		public:
			GLMappedBuffer();
			GLMappedBuffer(GLBuffer bufferToMap);

			~GLMappedBuffer();

			void Bind() const;

			void Map(GLenum accessType, bool internalHandling = true);
			void Assign(Core::Ptr<void> data, Core::size dataSize, bool internalHandling = true);
			bool Unmap(bool internalHandling = true) const;

			void Unbind() const;
		};
	}
}