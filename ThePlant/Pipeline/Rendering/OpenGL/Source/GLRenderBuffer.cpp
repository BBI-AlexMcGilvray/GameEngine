#include "Pipeline/Rendering/OpenGL/Headers/GLRenderBuffer.h"

namespace Application {
namespace Rendering {
    GLRenderBuffer::GLRenderBuffer()
    : GLObject(0, GL_RENDERBUFFER)
    {

    }

    GLRenderBuffer::GLRenderBuffer(GLuint object)
    : GLObject(object, GL_RENDERBUFFER)
    {

    }

    GLRenderBuffer::~GLRenderBuffer()
    {

    }

    void GLRenderBuffer::Generate()
    {
        glGenRenderbuffers(1, &Object);
    }

    // could provide a parameter to specify GL_FRAMEBUFFER (read/write), GL_READ_FRAMEBUFFER (read), or GL_DRAW_FRAMEBUFFER (write)
    void GLRenderBuffer::Bind() const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, Object);
    }
    
    void GLRenderBuffer::CreateBufferStorage(const Core::Math::Int2& dimensions, GLenum format)
    {
        glRenderbufferStorage(GL_RENDERBUFFER, format, dimensions.X, dimensions.Y);
    }

    void GLRenderBuffer::AttachToFrameBuffer(GLenum attachmentType)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, Object);
    }

    void GLRenderBuffer::Unbind() const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void GLRenderBuffer::Delete()
    {
        glDeleteRenderbuffers(1, &Object);
    }
}// namespace Rendering
}// namespace Application