#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"

#include <iostream>

using namespace std;

namespace Application {
namespace Rendering {
  void CreateProgram(Ptr<ObjectShaderBase> objectShader)
  {
    if (!CreateShader(objectShader->GetVertexShader()))// create a vertex shader
    {
      cout << "Failed to create VERTEX shader!" << endl;
      return;
    }

    if (!CreateShader(objectShader->GetFragmentxShader()))// create a fragment shader
    {
      cout << "Failed to create FRAGMENT shader!" << endl;
      return;
    }

    GLuint vertexProgram = objectShader->GetVertexShader()->Object;// create a vertex shader
    GLuint fragmentProgram = objectShader->GetFragmentxShader()->Object;// create a fragment shader

    int linkResult = 0;
    // create the program handle, attach the shader and link it
    GLuint program = glCreateProgram();// creates empty program handle
    glAttachShader(program, vertexProgram);// attach vertex shader to program
    glAttachShader(program, fragmentProgram);// attach fragment shader to program
    glLinkProgram(program);// link the program
    glGetProgramiv(program, GL_LINK_STATUS, &linkResult);// make sure program was linked properly

    // check for link errors
    if (linkResult != GL_TRUE) {
      int infoLogLength = 0;
      int maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
      std::vector<GLchar> programLog(maxLength);
      glGetProgramInfoLog(program, maxLength, &infoLogLength, &programLog[0]);
      cout << "Shader Loader: LINK ERROR <<" << objectShader->GetName() << ">>" << endl
           << &programLog[0] << endl;

      return;
    }

    objectShader->SetShaderProgram(program);

    // free up memory that is no longer needed...
    glDetachShader(program, vertexProgram);
    glDetachShader(program, fragmentProgram);
    glDeleteShader(vertexProgram);
    glDeleteShader(fragmentProgram);
    // above courtesy of: https://gamedev.stackexchange.com/questions/47910/after-a-succesful-gllinkprogram-should-i-delete-detach-my-shaders
    // essentiall, the shaders have been set up already - so we can clear out the memory reserved for them
  }

  // encapsulates all relevant operations to create a shader
  bool CreateShader(Ptr<ShaderBase> shader)
  {
    int compileResult = 0;

    shader->SetShaderProgram(glCreateShader(shader->Type));// create shader creates an empty shader object (handle) of desired type
    const char *shaderCodePtr = shader->GetShader();
    //const int shaderCodeSize = source.size(); // we can create a StringRef class that holds a const char*, and also the size of the array (by reading null character) to fill this in

    glShaderSource(shader->Object, 1, &shaderCodePtr, nullptr);//, &shaderCodeSize); // loads the shader object with given code.
      // count is usually set to 1 because you normally have one character array
      // shaderCode is the array of code (array of size one in this case) and length is normally set to NULL (reads until NULL), but here we set it to the actual length
    glCompileShader(shader->Object);// compiles the code
    glGetShaderiv(shader->Object, GL_COMPILE_STATUS, &compileResult);// check for errors and output them to console
      // the above set of operations is done for any shaders that we have to create their objects

    // check for errors
    if (compileResult != GL_TRUE) {
      int infoLogLength = 0;
      glGetShaderiv(shader->Object, GL_INFO_LOG_LENGTH, &infoLogLength);
      List<char> shaderLog(infoLogLength);
      glGetShaderInfoLog(shader->Object, infoLogLength, nullptr, &shaderLog[0]);
      cout << "ERROR compiling shader: " << shader->ShaderName << endl
           << &shaderLog[0] << endl;

      return false;
    }

    return true;
  }
}// namespace Rendering
}// namespace Application