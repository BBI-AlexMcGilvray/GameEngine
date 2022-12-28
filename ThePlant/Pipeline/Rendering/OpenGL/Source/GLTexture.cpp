#include "Pipeline/Rendering/OpenGL/Headers/GLTexture.h"

#include "Pipeline/Rendering/OpenGL/Headers/GLDefs.h"

namespace Application {
namespace Rendering {
    GLTexture::GLTexture()
    : GLObject(0, GL_TEXTURE)
    {

    }

    GLTexture::GLTexture(GLuint object)
    : GLObject(object, GL_TEXTURE)
    {

    }

    GLTexture::~GLTexture()
    {

    }

    void GLTexture::Generate()
    {
        glGenTextures(1, &Object);
    }

    // could provide a parameter to specify GL_FRAMEBUFFER (read/write), GL_READ_FRAMEBUFFER (read), or GL_DRAW_FRAMEBUFFER (write)
    void GLTexture::Bind() const
    {
        // maybe support providing a parameter for the type of texture?
        glBindTexture(GL_TEXTURE_2D, Object);
    }

    void GLTexture::CreateTextureStorage(const Core::Math::Int2& dimensions, GLint format)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, dimensions.X, dimensions.Y, 0, format, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    
    void GLTexture::AttachToFrameBuffer(GLenum attachmentType)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, Object, 0);
    }

    void GLTexture::Unbind() const
    {
        // if variable texture type is supported, used stored type to correctly unbind here
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GLTexture::Delete()
    {
        glDeleteTextures(1, &Object);
    }
}// namespace Rendering
}// namespace Application