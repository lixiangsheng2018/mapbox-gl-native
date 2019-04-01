#pragma once

#include <mbgl/gfx/renderable.hpp>

namespace mbgl {
namespace gl {

class RenderableResource : public gfx::RenderableResource {
public:
    RenderableResource() = default;
    virtual void bind() = 0;
};

} // namespace gl
} // namespace mbgl
