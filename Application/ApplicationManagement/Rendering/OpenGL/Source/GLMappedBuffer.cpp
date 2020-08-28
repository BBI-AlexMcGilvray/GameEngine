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

		GLMappedBuffer::GLMappedBuffer(GLBuffer bufferToMap)
			: _buffer(bufferToMap)
		{}

		GLMappedBuffer::~GLMappedBuffer()
		{
			Unmap();
		}

		void GLMappedBuffer::Bind() const
		{
			_buffer.Bind();
		}

		void GLMappedBuffer::Map(GLenum accessType)
		{
			if (accessType == _accessType)
			{
				return;
			}

			Unmap();
			_accessType = accessType;

			Bind();
			_mappedBuffer = glMapBuffer(_buffer.Type, _accessType);
		#if DEBUG
			if (_mappedBuffer == nullptr)
			{
				//LOG("Failed to assign mapped buffer");
				std::cout << "Failed to assign mapped buffer" << std::endl;
			}
		#endif
			Unbind();
		}

		void GLMappedBuffer::Assign(Core::Ptr<void> data, Core::size dataSize)
		{
			Bind();
			if (_mappedBuffer != nullptr)
			{
				memcpy(_mappedBuffer, data, dataSize);
			}
		#if DEBUG
			else
			{
				//LOG("No buffer to assign to");
				std::cout << "No buffer to assign to" << std::endl;
			}
		#endif
			Unbind();
		}

		bool GLMappedBuffer::Unmap() const
		{
			Bind();
			bool result = glUnmapBuffer(_buffer.Type);
			Unbind();

			return result;
		}

		void GLMappedBuffer::Unbind() const
		{
			_buffer.Unbind();
		}
	}
}