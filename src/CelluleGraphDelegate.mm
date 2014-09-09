#include "cinder/Cinder.h"
#include "cinder/Rand.h"
#import "CelluleGraphDelegate.h"

@implementation CelluleGraphDelegate

@synthesize window;

- (void)dealloc
{
    [super dealloc];
}
	
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	mApp = new CelluleGraphApp;
	mApp->prepareLaunch();
	mApp->setupCinderView( cinderView, cinder::app::RendererGl::create() );
	mApp->launch();

	[window setAcceptsMouseMovedEvents:YES];
	
//	colorWell.color = [NSColor colorWithCalibratedRed:mApp->mColor.r green:mApp->mColor.g blue:mApp->mColor.b alpha:1.0f]; 
}

- (IBAction)subdivisionSliderChanged:(id)sender
{
	mApp->scale = [sender floatValue];
}

- (IBAction)alphaSliderChanged:(id)sender
{
	mApp->angle = [sender floatValue];
}

- (IBAction)colorChanged:(id)sender
{
	NSColor *color = [sender color];
//	mApp->mColor = ci::Colorf( [color redComponent], [color greenComponent], [color blueComponent] );
}

@end
