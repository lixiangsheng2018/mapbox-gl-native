#pragma once

#include <mbgl/gfx/renderbuffer.hpp>
#include <mbgl/gl/object.hpp>

namespace mbgl {
namespace gl {

class RenderbufferResource : public gfx::RenderbufferResource {
public:
    RenderbufferResource(UniqueRenderbuffer&& renderbuffer_) : renderbuffer(std::move(renderbuffer_)) {
    }

    UniqueRenderbuffer renderbuffer;
};

} // namespace gl
} // namespace mbgl
