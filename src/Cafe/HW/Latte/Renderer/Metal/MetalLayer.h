#pragma once

/// Creates a MetalView NSView subview and returns an opaque pointer to it.
/// The caller is responsible for calling DestroyMetalLayer when done.
void* CreateMetalLayer(void* handle, float& scaleX, float& scaleY);

/// Returns the CA::MetalLayer* backing the MetalView created by CreateMetalLayer.
void* GetMetalLayerFromView(void* view);

/// Removes the MetalView from its superview, releasing it from the window hierarchy.
void DestroyMetalLayer(void* view);
