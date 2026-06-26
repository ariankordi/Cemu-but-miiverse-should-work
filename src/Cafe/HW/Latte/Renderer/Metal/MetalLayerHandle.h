#pragma once

#include <QuartzCore/QuartzCore.hpp>

#include "Cafe/HW/Latte/Renderer/Metal/MetalCommon.h"
#include "util/math/vector2.h"

class MetalLayerHandle
{
public:
    MetalLayerHandle() = default;
    MetalLayerHandle(MTL::Device* device, const Vector2i& size, bool mainWindow);

    ~MetalLayerHandle();

    // This handle uniquely owns the underlying MetalView, so it must not be
    // copied. It is move-only: moving transfers ownership and leaves the source
    // empty so that the moved-from object's destructor is a no-op. Without this,
    // assigning a temporary (e.g. layer = MetalLayerHandle(...)) would let the
    // temporary's destructor remove the view that ownership was just handed to.
    MetalLayerHandle(const MetalLayerHandle&) = delete;
    MetalLayerHandle& operator=(const MetalLayerHandle&) = delete;
    MetalLayerHandle(MetalLayerHandle&& other) noexcept;
    MetalLayerHandle& operator=(MetalLayerHandle&& other) noexcept;

    void Resize(const Vector2i& size);

    bool AcquireDrawable();

    void PresentDrawable(MTL::CommandBuffer* commandBuffer);

    CA::MetalLayer* GetLayer() const { return m_layer; }

    CA::MetalDrawable* GetDrawable() const { return m_drawable; }

private:
    /// Releases the owned MetalView (removing it from the window hierarchy) and resets all members.
    void Reset();

    void* m_view = nullptr; ///< Opaque pointer to the MetalView NSView added as a subview of the canvas.
    CA::MetalLayer* m_layer = nullptr;
    float m_layerScaleX = 1.0f, m_layerScaleY = 1.0f;

    CA::MetalDrawable* m_drawable = nullptr;
};
