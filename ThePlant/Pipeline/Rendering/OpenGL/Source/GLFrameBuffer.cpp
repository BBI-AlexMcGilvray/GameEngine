#include "Pipeline/Rendering/OpenGL/Headers/GLFrameBuffer.h"

namespace Application {
namespace Rendering {
    GLFrameBuffer::GLFrameBuffer()
    : GLObject(0, GL_FRAMEBUFFER)
    {

    }

    GLFrameBuffer::GLFrameBuffer(GLuint object)
    : GLObject(object, GL_FRAMEBUFFER)
    {

    }

    GLFrameBuffer::~GLFrameBuffer()
    {

    }

    void GLFrameBuffer::Generate()
    {
        glGenFramebuffers(1, &Object);
    }

    // could provide a parameter to specify GL_FRAMEBUFFER (read/write), GL_READ_FRAMEBUFFER (read), or GL_DRAW_FRAMEBUFFER (write)
    void GLFrameBuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, Object);
    }

    void GLFrameBuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // binds back to the original framebuffer
    }

    void GLFrameBuffer::Delete()
    {
        glDeleteFramebuffers(1, &Object);
    }
}// namespace Rendering
}// namespace Application