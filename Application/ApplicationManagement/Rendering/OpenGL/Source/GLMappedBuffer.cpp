#include "ApplicationManagement/Rendering/OpenGL/Headers/GLMappedBuffer.h"

#if _DEBUG
#include "Core/Debugging/Headers/Macros.h"
#endif

namespace Application
{
	namespace Rendering
	{
		GLMappedBuffer::GLMappedBuffer()
		{}

		GLMappedBuffer::GLMappedBuffer(Core::Ptr<GLBuffer> bufferToMap)
			: _buffer(bufferToMap)
		{}

		GLMappedBuffer::~GLMappedBuffer()
		{
			// don't unmap here since map and unmap must be called together
		}

		void GLMappedBuffer::Bind() const
		{
			_buffer->Bind();
		}

		void GLMappedBuffer::Map(GLenum accessType, bool internalHandling)
		{
			if (internalHandling)
			{
				Bind();
			}

			_mappedBuffer = glMapBuffer(_buffer->Type, accessType);
		#if DEBUG
			if (_mappedBuffer == nullptr)
			{
				//LOG("Failed to assign mapped buffer");
				std::cout << "Failed to assign mapped buffer, glError: " << glGetError() << std::endl;
			}
		#endif
		}

		void GLMappedBuffer::Assign(Core::Ptr<void> data, Core::size dataSize, bool internalHandling)
		{
			if (_mappedBuffer != nullptr)
			{
				memcpy(_mappedBuffer, data, dataSize);
			}
		#if DEBUG
			else
			{
				//LOG("No buffer to assign to");
				std::cout << "No buffer to assign to, glError: " << glGetError() << std::endl;
			}
		#endif
		}

		bool GLMappedBuffer::Unmap(bool internalHandling) const
		{
			bool result = glUnmapBuffer(_buffer->Type);

			if (internalHandling)
			{
				Unbind();
			}

			return result;
		}

		void GLMappedBuffer::Unbind() const
		{
			_buffer->Unbind();
		}
	}
}