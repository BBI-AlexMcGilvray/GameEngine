#pragma once

#include "Core/IdTypes/RuntimeId.h"
#include "Core/Headers/TemplateDefs.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Headers/RenderCamera.h"
#include "Pipeline/Rendering/Renderer.h"

#include <set>

namespace Application {
namespace Rendering {

class IRenderLayer
{
public:
    IRenderLayer(const std::string& name);

#if DEBUG
    const std::string& GetName() const { return _name; };
#endif
    virtual bool IsLayer(const Core::runtimeId_t& id) const = 0;

    template <typename LAYER>
    IRenderLayer& AddDependency()
    {
        SCOPED_MEMORY_CATEGORY("Rendering");

    #if DEBUG
        if (std::find(_dependencies.begin(), _dependencies.end(), Core::GetTypeId<LAYER>()) != _dependencies.end())
        {
            CORE_THROW("RenderLayer", "Adding dependency twice!");
        }
    #endif
        _dependencies.push_back(Core::GetTypeId<LAYER>());
        return *this;
    }

    template <typename LAYER>
    void RemoveDependency()
    {
        if (auto iter = std::find(_dependencies.begin(), _dependencies.end(), Core::GetTypeId<LAYER>()) != _dependencies.end())
        {
            _dependencies.erase(iter);
        }
    #if DEBUG
        else
        {
            CORE_THROW("RenderLayer", "Removing non-existent dependency!");
        }
    #endif
    }

    const std::vector<Core::runtimeId_t>& GetDependencies() { return _dependencies; }

    void QueueRender(const Context& context);
    void QueueRender(const SkinnedContext& context);

    virtual std::unique_ptr<IRenderLayer> CopyAndMoveTo() const = 0;

    virtual void Reset(const Core::Math::Color& clearColor) const = 0;
    virtual void Render(Renderer& renderer, const RenderCamera& camera) const = 0;

    void Clear();

protected:
#if DEBUG
    const std::string _name;
#endif
    // cameras should have a list of the layers that they render, so when we iterate over cameras we render the correct content
    std::vector<Context> _contexts;
    std::vector<SkinnedContext> _skinnedContexts;

    std::vector<Core::runtimeId_t> _dependencies;
};

template <typename LAYER>
class RenderLayer : public IRenderLayer
{
public:
    RenderLayer()
    : IRenderLayer(std::string(Core::TemplateTypeAsString<LAYER>()))
    {}

    virtual bool IsLayer(const Core::runtimeId_t& id) const override
    {
        return (id == Core::GetTypeId<LAYER>());
    }

    // if 'LAYER' wants custom behaviour, they must implement their own, but the basics are covered here
    virtual std::unique_ptr<IRenderLayer> CopyAndMoveTo() const override
    {
        SCOPED_MEMORY_CATEGORY("Rendering");
        
        std::unique_ptr<LAYER> copy = std::make_unique<LAYER>();

        // this and skinned contexts need to be moves (self-imposed, maybe not needed?)
        for (auto& context : _contexts)
        {
            copy->_contexts.push_back(std::move(context));
        }

        for (auto& skinnedContext : _skinnedContexts)
        {
            copy->_skinnedContexts.push_back(std::move(skinnedContext));
        }

        // we may not even need to copy over the dependencies
        copy->_dependencies = _dependencies;

        return copy;
    }

    // inside this method is where layer variables and such should be reset
    virtual void Reset(const Core::Math::Color& clearColor) const override
    {
        static_cast<const LAYER&>(*this).Reset(clearColor);
    }

    // inside this method is where different layers can apply some custom rendering logic (like different frame buffers or special shader stuff)
    virtual void Render(Renderer& renderer, const RenderCamera& camera) const override
    {
        static_cast<const LAYER&>(*this).RenderContexts(renderer, camera);
        static_cast<const LAYER&>(*this).RenderSkinnedContexts(renderer, camera);
    }
};

} // namespace Rendering
} // namespace Application