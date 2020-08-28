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

		void GLMappedBuffer::Map(GLenum accessType, bool internalHandling)
		{
			if (accessType == _accessType)
			{
				return;
			}

			Unmap(internalHandling);
			_accessType = accessType;

			if (internalHandling)
			{
				Bind();
			}

			_mappedBuffer = glMapBuffer(_buffer.Type, _accessType);
		#if DEBUG
			if (_mappedBuffer == nullptr)
			{
				//LOG("Failed to assign mapped buffer");
				std::cout << "Failed to assign mapped buffer" << std::endl;
			}
		#endif

			if (internalHandling)
			{
				Unbind();
			}
		}

		void GLMappedBuffer::Assign(Core::Ptr<void> data, Core::size dataSize, bool internalHandling)
		{
			if (internalHandling)
			{
				Bind();
			}

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

			if (internalHandling)
			{
				Unbind();
			}
		}

		bool GLMappedBuffer::Unmap(bool internalHandling) const
		{
			if (_mappedBuffer == nullptr)
			{
				return true;
			}

			if (internalHandling)
			{
				Bind();
			}

			bool result = glUnmapBuffer(_buffer.Type);

			if (internalHandling)
			{
				Unbind();
			}

			return result;
		}

		void GLMappedBuffer::Unbind() const
		{
			_buffer.Unbind();
		}
	}
}