#include "Cafe/HW/Latte/Renderer/Metal/MetalLayer.h"

#include "Cafe/HW/Latte/Renderer/MetalView.h"

void* CreateMetalLayer(void* handle, float& scaleX, float& scaleY)
{
	NSView* view = (NSView*)handle;

	MetalView* childView = [[MetalView alloc] initWithFrame:view.bounds];
	childView.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
	childView.wantsLayer = YES;

	[view addSubview:childView];

	const NSRect points = [childView frame];
    const NSRect pixels = [childView convertRectToBacking:points];

	scaleX = (float)(pixels.size.width / points.size.width);
    scaleY = (float)(pixels.size.height / points.size.height);

	// Return the view itself (not its layer) so the owner can later remove it
	// from the hierarchy. We keep the +1 from alloc as the owner's reference;
	// the superview holds its own reference from addSubview. DestroyMetalLayer
	// balances both.
	return childView;
}

void* GetMetalLayerFromView(void* view)
{
	return ((MetalView*)view).layer;
}

void DestroyMetalLayer(void* view)
{
	MetalView* childView = (MetalView*)view;
	// Drop the superview's reference, then the owner's alloc reference. Once both
	// are gone AppKit deallocates the view and, with it, its backing CAMetalLayer.
	[childView removeFromSuperview];
	[childView release];
}
