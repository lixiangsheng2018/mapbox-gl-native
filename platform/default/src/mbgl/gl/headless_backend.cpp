#include <mbgl/gl/headless_backend.hpp>
#include <mbgl/gl/renderable_resource.hpp>
#include <mbgl/gl/context.hpp>
#include <mbgl/gfx/backend_scope.hpp>

#include <cassert>
#include <stdexcept>
#include <type_traits>

namespace mbgl {
namespace gl {

class HeadlessRenderableResource final : public gl::RenderableResource {
public:
    HeadlessRenderableResource(gl::Context& context_, Size size_)
        : context(context_),
          color(context.createRenderbuffer<gfx::RenderbufferPixelType::RGBA>(size_)),
          depthStencil(context.createRenderbuffer<gfx::RenderbufferPixelType::DepthStencil>(size_)),
          framebuffer(context.createFramebuffer(color, depthStencil)) {
    }

    void bind() override {
        context.bindFramebuffer = framebuffer.framebuffer;
        context.scissorTest = false;
        context.viewport = { 0, 0, framebuffer.size };
    }

    gl::Context& context;
    gfx::Renderbuffer<gfx::RenderbufferPixelType::RGBA> color;
    gfx::Renderbuffer<gfx::RenderbufferPixelType::DepthStencil> depthStencil;
    gl::Framebuffer framebuffer;
};

HeadlessBackend::HeadlessBackend(Size size_)
    : mbgl::gfx::Renderable(size_, nullptr) {
}

HeadlessBackend::~HeadlessBackend() {
    gfx::BackendScope guard { *this };
    resource.reset();
    // Explicitly reset the context so that it is destructed and cleaned up before we destruct
    // the impl object.
    context.reset();
}

gl::ProcAddress HeadlessBackend::getExtensionFunctionPointer(const char* name) {
    assert(impl);
    return impl->getExtensionFunctionPointer(name);
}

void HeadlessBackend::activate() {
    active = true;

    if (!impl) {
        createImpl();
    }

    assert(impl);
    impl->activateContext();
}

void HeadlessBackend::deactivate() {
    assert(impl);
    impl->deactivateContext();
    active = false;
}

gfx::Renderable& HeadlessBackend::getDefaultRenderable() {
    if (!resource) {
        resource = std::make_unique<HeadlessRenderableResource>(static_cast<gl::Context&>(getContext()), size);
    }
    return *this;
}

Size HeadlessBackend::getFramebufferSize() const {
    return size;
}

void HeadlessBackend::updateAssumedState() {
    // no-op
}

void HeadlessBackend::setSize(Size size_) {
    size = size_;
    resource.reset();
}

PremultipliedImage HeadlessBackend::readStillImage() {
    return static_cast<gl::Context&>(getContext()).readFramebuffer<PremultipliedImage>(size);
}

} // namespace gl
} // namespace mbgl
