#pragma once

/// Creates a MetalView NSView as a subview of the given window and returns an
/// opaque pointer to that view. The caller owns it and must call DestroyMetalLayer.
void* CreateMetalLayer(void* handle, float& scaleX, float& scaleY);

/// Returns the CA::MetalLayer* backing a MetalView created by CreateMetalLayer.
void* GetMetalLayerFromView(void* view);

/// Removes the MetalView from its superview, allowing AppKit to release it and its layer.
void DestroyMetalLayer(void* view);
