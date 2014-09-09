
#include "cinder/app/CinderView.h"
#include "CelluleGraphApp.h"
#import <Cocoa/Cocoa.h>

@interface CelluleGraphDelegate : NSObject <NSApplicationDelegate>
{
	IBOutlet CinderView		*cinderView;
	IBOutlet NSWindow		*window;
	IBOutlet NSColorWell	*colorWell;
	
	CelluleGraphApp		*mApp;
}

@property (assign) IBOutlet NSWindow *window;

- (IBAction)subdivisionSliderChanged:(id)sender;
- (IBAction)colorChanged:(id)sender;

@end
