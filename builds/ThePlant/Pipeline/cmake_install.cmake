# Install script for directory: D:/Coding/VisualStudios/Application/ThePlant/Pipeline

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/the_plant")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Pipeline_Lib" TYPE FILE FILES
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Animation/Headers/Animation.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Animation/Headers/AnimationCurve.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Animation/Headers/AnimationManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Animation/Headers/Animator.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Animation/Headers/Channel.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Animation/Headers/ChannelTypes.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Animation/Headers/Keyframe.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Animation/Headers/SkeletonAnimation.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/AssetHandling/AssetLoaderFactory.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/AssetHandling/EntityFactory.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Collision/Collisions.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Collision/CollisionHandler.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Collision/CollisionManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Collision/CollisionUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Collision/OctTree.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Collision/CollisionHandlers/DebugHandlers/DebugCollisionDisplay.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/Systems/System.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/Systems/SystemManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/Archetype.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/ArchetypeManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/Component.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/ComponentCreator.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/ECS.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/EntityHandler.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/EntitySnapshot.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/IDs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/TemporaryComponentRef.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/DataOriented/TypeCollection.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/ObjectOriented/Headers/Component.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/ObjectOriented/Headers/ComponentPtr.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECS/ObjectOriented/Headers/Entity.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/DebugSystems/DebugCollisionSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/DebugSystems/DebugBoneSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/DebugSystems/DebugWorldTransformSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/DebugSystems/DebugOctTreeSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/AnimationSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/AnimationComponents.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/CameraSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/CameraComponents.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/CollisionComponents.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/CollisionSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/GeneralComponents.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/LifetimeComponent.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/LifetimeSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/ParentSyncSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/RenderingComponents.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/RenderingSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/TransformComponents.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/ECSSystems/TransformSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Factory_Temp/ArchetypesUI.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Factory_Temp/AssetSaverFactory.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Factory_Temp/EntitySnapshotUI.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Factory_Temp/EntitySnapshotUIVisitor.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Factory_Temp/Factory.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Factory_Temp/FactoryUI.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Factory_Temp/UICreator.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Factory_Temp/UIUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/GameSystem/Headers/GameObjectBase.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/GameSystem/Headers/GameObjectManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/GameSystem/Headers/GameSystemManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Headers/ApplicationManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Headers/GLContextManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Headers/SDL2Manager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Headers/ServiceManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Headers/WindowManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Input/Headers/InputController.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Input/Headers/InputDefs.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Input/Headers/InputEvent.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Input/Headers/InputManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Input/Headers/InputReceiverBase.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Input/Headers/InputState.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Input/Headers/InputStateTracker.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Physics/PhysicsCollisionHandler.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Physics/PhysicsComponents.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Physics/PhysicsSettings.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Physics/PhysicsSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Physics/VelocitySystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/2D/Headers/SimpleShapes.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/2D/Headers/Image.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/2D/Headers/Sprite.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/2D/Headers/Texture.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/3D/Headers/AnimatedModel.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/3D/Headers/ModelBase.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/3D/Headers/SimpleShapes.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/3D/Headers/Skeleton.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/3D/Source/VertexData.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Headers/Camera.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Headers/CameraManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Headers/CameraUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Headers/Lights.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Headers/MaterialManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Headers/RenderCamera.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Headers/RenderManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLArrayBuffer.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLBuffer.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLFrameBuffer.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLMappedBuffer.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLObject.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLRenderBuffer.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLShader.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLShaderProgram.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/GLTexture.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/OpenGL/Headers/ShaderUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Shaders/Shader.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Shaders/ShaderManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Material.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Mesh.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/RenderContext.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/Renderer.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/RenderFrame.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/RenderLayer.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Rendering/DefaultRenderLayers.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/StateSystem/Headers/State.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/StateSystem/Headers/StateHelpers.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/StateSystem/Headers/StateManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/StateSystem/Headers/ECSSystemUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Time/Headers/TimeManager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Time/Headers/TimeSettings.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Time/Headers/TimeSystem.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/UI/IMGUI/Manager.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/UI/IMGUI/Window.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/UI/IMGUI/Windows/Examples.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/UI/IMGUI/Windows/MemoryTracker.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/UI/IMGUI/Windows/Profiler.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/UI/IMGUI/Windows/SystemTracker.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Utils/RegisterUtils.h"
    "D:/Coding/VisualStudios/Application/ThePlant/Pipeline/Utils/SerializationUtils.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Coding/VisualStudios/Application/builds/ThePlant/Pipeline/Dependencies/cmake_install.cmake")

endif()

