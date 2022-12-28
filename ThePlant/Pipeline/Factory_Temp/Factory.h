#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Pipeline/Factory_Temp/FactoryUI.h"

namespace Application
{
    struct ApplicationManager;
} // namespace Application

/*
Notes:
- We should have a registration process for 'editor systems'
    - only these systems are run in 'edit' mode (ex: rendering)
- Factory should have a state that it holds/loads/save
    - there can be a default state when working on smaller assets (meshes, entity prefabs)
    - play mode kicks off the application in that state
        - when the above happens, we should copy the ECS entities to the newly activated ECS system
            - we should be able to specify a 'copy all' vs 'copy entities'
                - the latter is to facilitate copying entities between states in levels
                - the former is for the same, but also to copy things from editor->play mode
*/

namespace Editor {
    class Factory
    {
        public:
            Factory(Application::ApplicationManager& application);

            void Initialize();
            void Start();
            void Update(Core::Second& deltaTime);
            void End();
            void CleanUp();

            Application::ApplicationManager& GetApplication();
            FactoryUI& GetFactoryUI();

            // should this be here? maybe
            void SelectEntity(Application::EntityId entity);

        private:
            Application::ApplicationManager& _application;
            // NOTE: we shouldn't have a 'FactoryUI' thing here.
            // Each editor utility should be a state (or at least the main ones, states can still have additional 'tools' that are just UI windows)
            // We should have:
            //      - FactoryState
            //          - in charge of creating the first UI windows that have: the main header toolbar and the primary dockspace
            //              - the editor should have the ability to open up different tools (profiler, system/memory tracker...)
            //      - Content browser (could be a tool?)
            //      - SceneEditor
            //          - opens up a state and allows for editing/saving a scene asset
            //      - PlayState
            //          - opens an asset up and begins a standard 'play' mode
            //  ** both of SceneEditor and PlayState should probably render within an Imgui window to allow for better docking/control and such
            //      see: https://uysalaltas.github.io/2022/01/09/OpenGL_Imgui.html
            //      and: https://learnopengl.com/Advanced-OpenGL/Framebuffers
            /*
            UPDATE TO THE ABOVE: We do NOT want the different factory/editor UIs to be ties to application States, instead they should manipulate them/work with them
                - ex: we should have an 'Edit' State that works with a subset of systems (i.e. non-gameplay ones) so things are visible/updated but remain as they should
                - we should render these different states to FrameBuffers (see links above) so we can render them to IMGUI windows properly (and facilitate moving/ordering them)
                - We could use the 'Decorator' pattern when we are in a edit-state for a given state (hold a pointer to the static state that we started with and the actual state we are in)
                    - this would let us propagate changes from the play state to the edit state and stuff like that

            ** Things that should get done to support this:
                * Make the rendering pipeline use a FrameBuffer
                    * in non-edit mode, this should still be used for post-process effects
                    * not directly related, but we may want to more concretely lock down how to toggle render 'modes' (wireframe, ...)
                * Implement a Layer system into the rendering pipeline
                    * Layers provide an order in which they are rendered/applied
                    * there should be a default framebuffer used for the full screen, layers can use their own if necessary for additional work
                    * Layers should be able to provide a dependency so they can be ordered properly/automatically
                    * We should display what layers are being used at a given time and have the ability to toggle them on/off
                    * ex: solid, transparent, debug, post processing...
                    * NOTE: need to make sure this works properly with multithreaded rendering (more important as this will make rendering take longer)
                * We should make the render thread handle processing input as well
                    * we already have our own input events, so we can just queue those in a double buffer (once gameplay thread takes the inputs, the other buffer is used)
                * We should probably get a proper 'Factory' build config in place so we can more easily test changes with and without the editor UI 
                    * The Factory can be extracted once we have the ability to specify frame buffers
                    * Maybe we just delete it all and start from scratch, since what we have in there is messy and can just be fixed anyways
            
            ** Other notes:
                * We will likely need a 'Serialization' component (just a UUID?) so we can reference components between save/load and also the network
                    * localy we would just use the entity id (and allow it to be runtime generated) but when saving/loading/sending over network we use the UUIDs instead
                * There may be cases (in a non-editor build) where we want to load up an entity, but do NOT want to load up it's 'Serialization' component to save space and help with archetype efficiency
                * Since the editor will still use our UI (IMGUI) windows, we _can_ still work on their functionality in parallel
                    * like having the content-importer window
            */
            FactoryUI _factoryUI;

            // std::unique_ptr<Application::State> _editingState;
    };
} // namespace Editor