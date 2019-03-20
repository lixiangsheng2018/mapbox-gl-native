#pragma once

#include <mbgl/gfx/types.hpp>
#include <mbgl/util/size.hpp>

#include <memory>

namespace mbgl {
namespace gfx {

class RenderbufferResource {
protected:
    RenderbufferResource() = default;
public:
    virtual ~RenderbufferResource() = default;
};

template <RenderbufferPixelType renderbufferType>
class Renderbuffer {
public:
    Renderbuffer(Size size_, std::unique_ptr<const RenderbufferResource>&& resource_)
        : size(std::move(size_)), resource(std::move(resource_)) {
    }

    void shouldClear(bool clear) {
        dirty = clear;
    }
    bool needsClearing() {
        return dirty;
    }

    static constexpr RenderbufferPixelType type = renderbufferType;
    Size size;
    std::unique_ptr<const RenderbufferResource> resource;
    bool dirty;
};

} // namespace gfx
} // namespace mbgl
