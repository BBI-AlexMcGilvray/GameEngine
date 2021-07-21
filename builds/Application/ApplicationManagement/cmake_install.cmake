# Install script for directory: D:/Coding/VisualStudios/Application/Application/ApplicationManagement

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/application")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/ApplicationManagement" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/FieldAnimation/Headers/FloatAnimationTrack.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/Headers/Animatable.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/Headers/Animation.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/Headers/AnimationCurve.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/Headers/AnimationManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/Headers/AnimationMixer.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/Headers/Animator.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/Headers/AnimatorComponent.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/Headers/Keyframe.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimatable.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimation.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimationMixer.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimationTrack.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Animation/TransformAnimation/Headers/TransformAnimationTrack.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Collision/Headers/BoxCollider.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Collision/Headers/ColliderBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Collision/Headers/CollisionBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Collision/Headers/CollisionCheck.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Collision/Headers/CollisionManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Collision/Headers/SphericalCollider.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Debugging/Headers/Declarations.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Debugging/Headers/Logging.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Debugging/Headers/Macros.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/GameSystem/Headers/GameObjectBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/GameSystem/Headers/GameObjectManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/GameSystem/Headers/GameSystemManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Geometric/Headers/CameraNode.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Geometric/Headers/ContainerBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Geometric/Headers/ContentBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Geometric/Headers/HierarchyComponent.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Geometric/Headers/Node.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Geometric/Headers/Scene.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Geometric/Headers/World.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Headers/ApplicationManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Headers/Component.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Headers/Entity.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Headers/GLContextManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Headers/SDL2Manager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Headers/WindowManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Input/Headers/InputController.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Input/Headers/InputDefs.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Input/Headers/InputEvent.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Input/Headers/InputManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Input/Headers/InputReceiverBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/2D/Headers/BoxRenderObject.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/2D/Headers/Image.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/2D/Headers/Material.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/2D/Headers/MaterialComponent.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/2D/Headers/Sprite.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/2D/Headers/Texture.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/AnimatedModel.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/Bone.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/CubeRenderObject.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/ModelBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/RenderVertexBaseData.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/SimpleMeshBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/Skeleton.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/SkeletonComponent.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/SkinnedMeshBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/3D/Headers/SphereRenderObject.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Animation/Headers/KeyFrame.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Animation/Headers/Timeline.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/Camera.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/CameraComponent.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/CameraManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/CameraUtils.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/Lights.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/MaterialManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/RenderComponent.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/Renderer.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/RenderManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/RenderObjectBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/RenderObjectManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Headers/SingleCameraManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/OpenGL/Headers/GLDefs.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/OpenGL/Headers/GLMappedBuffer.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/OpenGL/Headers/GLObject.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/OpenGL/Headers/GLShader.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/OpenGL/Headers/GLShaderProgram.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/OpenGL/Headers/ShaderUtils.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/DebugObjectShader.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/DebugVertexShader.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/FragmentShader.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/ObjectShader.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/ObjectShaderBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/ShaderBase.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/ShaderManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/SkinnedObjectShader.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/SkinnedVertexShader.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Rendering/Shaders/Headers/VertexShader.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/StateSystem/Headers/State.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/StateSystem/Headers/StateManager.h"
    "D:/Coding/VisualStudios/Application/Application/ApplicationManagement/Time/Headers/TimeManager.h"
    )
endif()

