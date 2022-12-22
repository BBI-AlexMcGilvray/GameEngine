#pragma once

#include "Core/IdTypes/RuntimeId.h"
#include "Core/Headers/TemplateDefs.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Renderer.h"

#include <string>

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
    void AddDependency()
    {
    #if DEBUG
        if (std::find(_dependencies.begin(), _dependencies.end(), Core::GetTypeId<LAYER>()) != _dependencies.end())
        {
            CORE_THROW("RenderLayer", "Adding dependency twice!");
        }
    #endif
        _dependencies.push_back(Core::GetTypeId<LAYER>());
    }

    template <typename LAYER>
    void RemoveDependency()
    {
        if (auto iter = std::find(_dependencies.begin(), _dependencies.end(), Core::GetTypeId<LAYER>()) != _dependencies.end())
        {
            _dependencies.remove(iter);
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

    virtual void Render(Renderer& renderer, const Core::Math::Float4x4& camera) const = 0;

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

    // inside this method is where different layers can apply some custom rendering logic (like different frame buffers or special shader stuff)
    virtual void Render(Renderer& renderer, const Core::Math::Float4x4& camera) const override
    {
        static_cast<const LAYER&>(*this).RenderContexts(renderer, camera);
        static_cast<const LAYER&>(*this).RenderSkinnedContexts(renderer, camera);
    }
};

} // namespace Rendering
} // namespace Application