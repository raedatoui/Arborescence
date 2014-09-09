#pragma once

#include "cinder/app/AppCocoaView.h"
#include "NodeRectangle.h"
#include "cinder/Timeline.h"

using namespace ph::nodes;
using namespace ci;
using namespace ci::app;
using namespace std;

class CelluleGraphApp : public cinder::app::AppCocoaView {

public:
	//void prepareSettings( Settings *settings );
    
	void setup();
	void shutdown();
	void update();
	void draw();
    
	void mouseMove( MouseEvent event );
	void mouseDown( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void mouseUp( MouseEvent event );
    
	void keyDown( KeyEvent event );
	void keyUp( KeyEvent event );
    
	void resize();
    
    float				scale;
    float				angle;
    Anim<float>         angleAnim;

    void prepareSettings(Settings *settings);
    void loadFigure();
	
protected:
	//! The root node
	Node2DRef			mRoot;
	//! The big rectangle that acts as a parent for the smaller ones
	NodeRectangleRef	mParent;
};
