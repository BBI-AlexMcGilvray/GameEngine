#include "Pipeline/Rendering/RenderLayer.h"

namespace Application {
namespace Rendering {

IRenderLayer::IRenderLayer(const std::string& name)
#if DEBUG
: _name(name)
#endif
{}

void IRenderLayer::QueueRender(const Context& context)
{
    SCOPED_MEMORY_CATEGORY("Rendering");
    _contexts.push_back(context);
}

void IRenderLayer::QueueRender(const SkinnedContext& context)
{
    SCOPED_MEMORY_CATEGORY("Rendering");
    _skinnedContexts.push_back(context);
}

void IRenderLayer::Clear()
{
    _contexts.clear();
    _skinnedContexts.clear();
}

} // namespace Rendering
} // namespace Application