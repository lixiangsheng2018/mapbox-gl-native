#pragma once

#include <mbgl/util/size.hpp>

namespace mbgl {
namespace gfx {
class RendererBackend;
} // namespace gfx
} // namespace mbgl

class GLFWBackend {
public:
    GLFWBackend() = default;
    GLFWBackend(GLFWBackend&&) = delete;
    GLFWBackend(const GLFWBackend&) = delete;
    GLFWBackend& operator=(GLFWBackend&&) = delete;
    GLFWBackend& operator=(const GLFWBackend&) = delete;
    virtual ~GLFWBackend() = default;

    virtual mbgl::gfx::RendererBackend& getRendererBackend() = 0;
    virtual mbgl::Size getSize() = 0;
    virtual void setSize(mbgl::Size) = 0;
};
