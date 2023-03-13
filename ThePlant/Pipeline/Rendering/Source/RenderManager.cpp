#include "Pipeline\Rendering\Headers\RenderManager.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Headers/ApplicationManager.h"

// testing
#include "Pipeline/Rendering/3D/Headers/SimpleShapes.h"
#include "Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"
// \testing

using namespace Core;
using namespace Core::Math;
using namespace Core::Functionality;

namespace Application {
namespace Rendering {
  RenderManager::RenderManager()
  {}

  CameraManager& RenderManager::GetCameraManager()
  {
    return _cameraManager;
  }

  UI::IMGUI::Manager& RenderManager::GetUIManager()
  {
    return *_ui;
  }

  void RenderManager::Initialize(SDL2Manager& sdlManager, Core::Threading::Thread&& renderThread, Color clearColor)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    _sdlManager = &sdlManager;
    _ui = std::make_unique<UI::IMGUI::Manager>(_sdlManager->GetWindowManager(), _sdlManager->GetContextManager());
    _ui->Initialize();

    _initialColor = WHITE;
    _clearColor = clearColor;

    // don't render everything, but set up the default state
    // _RenderStart();
    // _RenderEnd();

    // testing
    _InitialiseFrameBufferTest();
    // \testing

    _renderThread = std::move(renderThread);
  }

  void RenderManager::Start()
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    _ui->Start();

    _rendering = true;
  #ifdef MULTITHREADED_RENDERING
    // NOTE: Apparently opengl context is thread-specific. If we are using threaded rendering, then we need to create the opengl context on that thread
    // https://stackoverflow.com/questions/21048927/initializing-opengl-context-in-another-thread-than-the-rendering
    // https://gmane.comp.lib.sdl.narkive.com/WK0DM9bJ/sdl-opengl-context-and-threads
    // Additional note:
    //    - seems sdl uses vsync automatically. either way it seems that the true frame rate is not being displayed by IMGUI due to using GPU calls
    //        - may want our own timers to know 'render thread' frame rate and 'game logic' frame rate
    SDL_GL_MakeCurrent(_sdlManager->GetWindowManager().GetWindow(), nullptr);
    _renderThread.SetTaskAndRun(std::packaged_task<void()>([this]
    {
      SDL_GL_MakeCurrent(_sdlManager->GetWindowManager().GetWindow(), _sdlManager->GetContextManager().GetContext());
      while (_rendering)
      {
        DEBUG_PROFILE_SCOPE("Render Thread"); // this thread is currently locked at 13ms, apparently by sdl's vsync (see above)
        _RenderStart();
        _RenderMiddle();
        _ui->Render(); // how can we get this to be multithreaded?
        _RenderEnd();
      }
    }));
  #endif
  }

  void RenderManager::Render()
  {
    _mainThreadRenderFrame.OrderLayers();

    RenderFrame movingFrame; // this is just immediately moved below, is temp variable only
    _mainThreadRenderFrame.MoveTo(movingFrame);
    _renderFrames.WriteBuffer(std::move(movingFrame));
    _mainThreadRenderFrame.Clear(); // tidy-up whatever wasn't cleaned by the MoveTo

  #ifndef MULTITHREADED_RENDERING
    SDL_GL_MakeCurrent(_sdlManager->GetWindowManager().GetWindow(), _sdlManager->GetContextManager().GetContext());
    _RenderStart();

    // instead of this, UI and world rendering should be different displays
    // we should have a list of displays, and each display should have a way to check what cameras it needs
    // therefore, _RenderMiddle would become:
    /*
    *   get all cameras needed by each display
    *   loop over all cameras that are used by a display
    *     - render to the cameras as we have it set up now
    *   loop over all displays and tell them to render
    *     ** game layer (default if no layers are specified) renders to the default opengl frame buffer
    *     ** ui layer renders all the ui
    *     ** the 'factory' (editor) would add it's own layer and only add the above 2 when we enter 'play' mode
    */
    _RenderMiddle();
    
    _ui->Render(); // even not rendering any of the camera makes the UI fully black...

    _RenderEnd();
  #endif
  }

  void RenderManager::End(Core::Threading::ThreadManager& threadManager)
  {
    _ui->End();
    _rendering = false;
  #ifdef MULTITHREADED_RENDERING
    _renderThread.Complete();
  #endif
    threadManager.ReturnThread(std::move(_renderThread));
  }

  void RenderManager::CleanUp()
  {
    _ui->CleanUp();

    // testing
    _CleanUpFrameBufferTest();
    // \testing
  }

  void RenderManager::SetOpenGLAttributes()
  {
    // starting with version 3.2 of OpenGL as it is modern and should be runnable by most video cards
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    // we are going to use double buffering (this only sets a 23bit Z buffer)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

    // SDL_GL_CONTEXT_PROFILE_CORE uses only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  }

  void RenderManager::SetOpenGLState()
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // facing and culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
  }

#if DEBUG
  void RenderManager::VerifyOpenGLAttributes()
  {
    // In the future, the attribute values should be stored in a struct so that they are not floating magic numbers
    // Would also enable reading them from a file and such

    int attributeValue = -100;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &attributeValue);
    ASSERT(attributeValue == 4);

    attributeValue = -100;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &attributeValue);
    ASSERT(attributeValue == 5);

    attributeValue = -100;
    SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &attributeValue);
    ASSERT(attributeValue == 1);
  }
#endif

  void RenderManager::QueueCamera(const RenderCamera& camera)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    _mainThreadRenderFrame.QueueCamera(camera);
  }

  void RenderManager::_RenderStart()
  {
    DEBUG_PROFILE_SCOPE("_RenderStart");

    auto& window = _sdlManager->GetWindowManager();
    glViewport(0, 0, window.Width, window.Height);
    glClearColor(_clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A); // probably don't need this anymore since it would be done when we render the main camera
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // same as above
  }

  void RenderManager::_RenderMiddle()
  {
    DEBUG_PROFILE_SCOPE("_RenderMiddle");

    // testing (1)
    // with this (and not rendering main camera or binding the cameras' buffers), the goal is to simplify the process and determine what isn't working
    // the order of this impacts how IMGUI is drawing, and the 'CreateTexture' call FROM THE CAMERA breaks imgui's visuals - but not the one here! so not the call specifically?
    // use renderdoc to see when the texture is actually rendered to - right now things still seem to be rendering directly to the back buffer...
    // _FrameBufferTestBegin();
    // \testing

    const auto& frameData = _renderFrames.ReadBuffer();

    // NOTE: If rendering shadows and the like, we need to DISABLE culling of faces so that they are taken into account for shadows! (I think)
    frameData.Render(_Renderer, _clearColor);
    _Renderer.SetShader(Shader()); // this should be done in the EndFrame call?

    _renderFrames.ReturnBuffer(frameData);

    // should not be needed anymore, this is now handled by displays (current display is being added by MyState.cpp)
    // _RenderMainCamera(frameData.GetMainCamera()); // testing (1)
    
    // testing (1)
    // _FrameBufferTestEnd();
    // \testing

    _displayManager.Render(_Renderer);
  }

  void RenderManager::_RenderEnd()
  {        
    DEBUG_PROFILE_SCOPE("_RenderEnd");

    // here is where we probably go through each 'display' and update them? (how would that work with UI)
    
    SDL_GL_SwapWindow(_sdlManager->GetWindowManager().GetWindow());
  }


// --------------- TESTING: this should all be cleaned up/removed/moded...
  void RenderManager::_InitialiseFrameBufferTest()
  {
    auto& window = _sdlManager->GetWindowManager();

    _frameBuffer.Generate();
    _frameBuffer.Bind();

    _frameBufferTexture = CreateTexture(Core::Math::Int2(window.Width, window.Height), Core::Math::Float2(2.0f, 2.0f));
    _frameBufferTexture.actualTexture.Bind(); // may not be needed
    _frameBufferTexture.actualTexture.AttachToFrameBuffer(GL_COLOR_ATTACHMENT0);
    _frameBufferTexture.actualTexture.Unbind(); // may not be needed

    _frameBufferStencilAndDepth.Generate();
    _frameBufferStencilAndDepth.Bind();
    _frameBufferStencilAndDepth.CreateBufferStorage(Core::Math::Int2(window.Width, window.Height), GL_DEPTH24_STENCIL8);
    _frameBufferStencilAndDepth.AttachToFrameBuffer(GL_DEPTH_STENCIL_ATTACHMENT);
    _frameBufferStencilAndDepth.Unbind();

    _frameBuffer.Unbind();
    
    const std::string vShaderCode = R"(
        #version 450 core
			
        layout (location = 0) in vec3 vPos;
        layout (location = 1) in vec3 vNormals;
        layout (location = 2) in vec2 vTexCoords;

        out vec2 fTexCoords;

        void main()
        {
            gl_Position = vec4(vPos.x, vPos.y, 0.0, 1.0); 
            fTexCoords = vTexCoords;
        }  
      )";
    VertexShader vShader = CreateVertexShader(vShaderCode);
    const std::string fShaderCode = R"(
        #version 450 core
			
        layout(location = 0) out vec4 fColor;
  
        in vec2 fTexCoords;

        uniform sampler2D screenTexture;

        void main()
        { 
            vec3 texColour = texture(screenTexture, fTexCoords).xyz;
            fColor = vec4(texColour, 1.0f);
        }
      )";
    FragmentShader fShader = CreateFragmentShader(fShaderCode);
    _frameBufferShader = CreateShader(vShader, fShader);
  }
  
  void RenderManager::_CleanUpFrameBufferTest()
  {
    _frameBuffer.Delete();
    DeleteTexture(_frameBufferTexture);
    _frameBufferStencilAndDepth.Delete();

    DeleteShader(_frameBufferShader);
  }

  void RenderManager::_FrameBufferTestBegin()
  {
    _frameBuffer.Bind();
    glClearColor(_clearColor.R * 0.5f, _clearColor.G * 0.5f, _clearColor.B * 0.5f, _clearColor.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
  }

  void RenderManager::_FrameBufferTestEnd()
  {
    _frameBuffer.Unbind();
    glClearColor(_clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    _Renderer.SetShader(_frameBufferShader);
    _frameBufferTexture.actualTexture.Bind();
    _frameBufferTexture.mesh.buffer.Bind();

    // NOTES: Problem is likely due to the shader needing to have the proper layout structure so that the 'indices' of the different fields (see construction of mesh and default shader) match
    // may also require name changes? this process will definitely require the additional 'context' values to be set at some point (particularly for post process stuff)
    // CURRENTLY: Render doc shows the texture being rendered to properly, but the texture is not then being rendered to the back buffer. Try modifying the shaders to force colours and see what happens

    glDrawArrays(GL_TRIANGLES, 0, GLsizei(_frameBufferTexture.mesh.vertices));

    _frameBufferTexture.actualTexture.Unbind();
    _frameBufferTexture.mesh.buffer.Unbind();
    _Renderer.SetShader(Shader());
  }

  void RenderManager::_RenderMainCamera(const RenderCamera& mainCamera)
  {
    _Renderer.SetShader(_frameBufferShader);
    mainCamera.texture.mesh.buffer.Bind();
    mainCamera.texture.actualTexture.Bind();

    // clearing here breaks, that probably means the texture we're trying to render from isn't working?
    glDisable(GL_DEPTH_TEST);
    glClearColor(_clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, GLsizei(mainCamera.texture.mesh.vertices));

    mainCamera.texture.mesh.buffer.Unbind();
    mainCamera.texture.actualTexture.Unbind();
    _Renderer.SetShader(Shader());
  }
}// namespace Rendering
}// namespace Application