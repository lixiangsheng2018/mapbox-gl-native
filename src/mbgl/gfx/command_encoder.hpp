#pragma once

namespace mbgl {
namespace gfx {

class CommandEncoder {
protected:
    CommandEncoder() = default;

public:
    virtual ~CommandEncoder() = default;
    CommandEncoder(CommandEncoder&&) = delete;
    CommandEncoder(const CommandEncoder&) = delete;
    CommandEncoder& operator=(CommandEncoder&&) = delete;
    CommandEncoder& operator=(const CommandEncoder&) = delete;
};

} // namespace gfx
} // namespace mbgl
