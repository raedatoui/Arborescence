#include "CelluleGraphApp.h"
#include "cinder/gl/gl.h"
#include "Models.h"
#include "cinder/Xml.h"
#include "cinder/Timeline.h"

void CelluleGraphApp::setup()
{
    scale = 0.3f;
    angle = 0;
    mRoot = Node2DRef( new Node2D() );
    
    std::string path = "cellule_ternaire";
    //loading multiple xml files
    //    vector<string> figs;
    //    figs.push_back("meduses");
    //    figs.push_back("externe");
    //    for( vector<string>::iterator fig = figs.begin(); fig != figs.end(); ++fig ){
	
    try {
		XmlTree doc(loadAsset(path+"/externe.xml")) ;
		XmlTree img = doc.getChild("psd");
		
		FigureData figure;
		figure.file = "";
		figure.numClones = img.getAttributeValue<int>("clones");
		figure.width = img.getAttributeValue<int>("width");
		figure.height = img.getAttributeValue<int>("height");
		figure.scale = img.getAttributeValue<float>("scale");
        figure.name = img.getAttributeValue<string>("name");
		float r = figure.width/2;
        float c = 0.0;
        float total = img.getChildren().size()*1.0f;
        
        mParent = NodeRectangleRef( new NodeRectangle(figure) );
        mParent->setPosition(960, 540); // relative to parent node
        mParent->setSize(figure.width, figure.height);
        mParent->setAnchorPercentage(0.5f, 0.5f);
        
        mParent->setScale(scale);
        mRoot->addChild(mParent);
        
        console() << "Total\t" << total << endl;
		for( XmlTree::Iter track = img.begin("layer"); track != img.end(); ++track ) {
			FigureData imgData;
            imgData.file = path + "/png/" + track->getValue();
            console() << imgData.file << track->getValue() << endl;
			imgData.width = track->getAttributeValue<int>("layerwidth");
			imgData.height = track->getAttributeValue<int>("layerheight");
			imgData.zIndex = track->getAttributeValue<int>("stack");
            imgData.coeff = c/total;
			imgData.name = track->getAttributeValue<string>("name");
			imgData.angle = 360.0/total*c;
            imgData.x = r*cos(imgData.angle*pi/180);
            imgData.y = r*sin(imgData.angle*pi/180);
            c = c+1;
			try {
				imgData.blend = track->getAttributeValue<string>("blend");
                
			}
			catch ( exception& e2 ) {
				//console() << e.what() << endl;
			}
			try {
				imgData.alpha = track->getAttributeValue<float>("alpha");
				console() << imgData.alpha << endl;
			}
			catch ( exception& e3 ) {
			}
            
			console() << imgData.toString() << endl;
            figure.layers.push_back(imgData);
            
            NodeRectangleRef child( new NodeRectangle(imgData) );
            child->setPosition(figure.width/2, figure.height/2); // relative to parent node
            child->setAnchorPercentage(0.0f, 0.0f);
            mParent->addChild(child);
		}
        
	}
	catch( exception& e ) {
		console() << e.what();
	}
    
    timeline().apply(&angleAnim, 360.0f, 100.0f, EaseInCubic());
    

    
//	// create a large rectangle first
//	mParent = NodeRectangleRef( new NodeRectangle("parent", "png/centre-etoile.png") );
//	// specify the position of the anchor point on our canvas
//	mParent->setPosition(400, 300); // relative to parent node
//	// we can easily set the anchor point to its center
//	mParent->setAnchorPercentage(1.0f, 1.0f);
//	// set the size of the node
//	mParent->setSize(600, 450);
//    mParent->setScale(scale);
//	// add it to the root of our scenegraph
//	mRoot->addChild(mParent);
//    
//    // add smaller rectangles to the root node
//	NodeRectangleRef child1( new NodeRectangle("level1a","png/centre-etoile.png") );
//	child1->setPosition(200, 225); // relative to parent node
//	child1->setAnchorPercentage(0.5f, 0.5f);
//	child1->setSize(240, 200);
//	mParent->addChild(child1);
//    
//	NodeRectangleRef child2( new NodeRectangle("level1b","png/deuxieme-strate-1.png") );
//	child2->setPosition(400, 225); // relative to parent node
//	child2->setAnchorPercentage(0.5f, 0.5f);
//	child2->setSize(240, 200);
//	mParent->addChild(child2);
//    
//	// add even smaller rectangles to the child rectangles
//	NodeRectangleRef child( new NodeRectangle("level2a","png/deuxieme-strate-2.png") );
//	child->setPosition(60, 100); // relative to parent node
//	child->setAnchorPercentage(0.5f, 0.5f);
//	child->setSize(100, 100);
//	child1->addChild(child);
//    
//	child.reset( new NodeRectangle("level2b","") );
//	child->setPosition(180, 100); // relative to parent node
//	child->setAnchorPercentage(0.5f, 0.5f);
//	child->setSize(100, 100);
//	child1->addChild(child);
//    
//	child.reset( new NodeRectangle("level2c","") );
//	child->setPosition(60, 100); // relative to parent node
//	child->setAnchorPercentage(0.5f, 0.5f);
//	child->setSize(100, 100);
//	child2->addChild(child);
//    
//	child.reset( new NodeRectangle("level2d","") );
//	child->setPosition(180, 100); // relative to parent node
//	child->setAnchorPercentage(0.5f, 0.5f);
//	child->setSize(100, 100);
//	child2->addChild(child);
    
	// note that we only keep a reference to the root node. The children are
	// not deleted when this function goes out of scope, because they sit happily
	// in the list of children of their parent node. They are not deleted until
	// they are removed from their parent.
}

void CelluleGraphApp::shutdown()
{
}

void CelluleGraphApp::update()
{
	// update all nodes
	mRoot->treeUpdate();
    mParent->setScale(scale);
    mParent->setRotation(angle);
}

void CelluleGraphApp::draw()
{
	// clear the window
	gl::clear(Color(1.0f,1.0f,1.0f));
	gl::setMatricesWindow( getWindowSize(), true );
	// draw all nodes, starting with the root node
    angle = angleAnim;
	mRoot->treeDraw();
    
	// example of coordinate conversion:
	// convert big rectangle's origin to screen coordinates and draw a red circle there
//	gl::color( Color(1, 0, 0) );
	gl::drawSolidCircle( mParent->objectToScreen( Vec2f::zero() ), 5.0f );
}

void CelluleGraphApp::mouseMove( MouseEvent event )
{
	// pass the mouseMove event to all nodes. Important: this can easily bring your
	// frame rate down if you have a lot of nodes and none of them does anything with
	// this event. Only use it if you have just a few nodes, like in this sample,
	// or catch it as soon as possible by returning TRUE in your mouseMove() method.
	mRoot->treeMouseMove(event);
}

void CelluleGraphApp::mouseDown( MouseEvent event )
{
	// pass the mouseDown event to all nodes. This is usually very quick because
	// it starts at the top nodes and they often catch the event.
	mRoot->treeMouseDown(event);
}

void CelluleGraphApp::mouseDrag( MouseEvent event )
{
	// pass the mouseDrag event to all nodes. This is usually very quick.
	mRoot->treeMouseDrag(event);
}

void CelluleGraphApp::mouseUp( MouseEvent event )
{
	// pass the mouseUp event to all nodes. This is usually very quick.
	mRoot->treeMouseUp(event);
}

void CelluleGraphApp::keyDown( KeyEvent event )
{
	// let nodes handle keys first
	if(! mRoot->treeKeyDown(event) ) {
		switch( event.getCode() ) {
            case KeyEvent::KEY_ESCAPE:
                quit();
                break;
            case KeyEvent::KEY_RETURN:
                if(event.isAltDown()) {
                    setFullScreen( !isFullScreen() );
                }
                break;
		}
	}
}

void CelluleGraphApp::keyUp( KeyEvent event )
{
	mRoot->treeKeyUp(event);
}

void CelluleGraphApp::resize()
{
	mRoot->treeResize();
}

void CelluleGraphApp::prepareSettings( CelluleGraphApp::Settings *settings)
{
	settings->setFrameRate( 60.0f );
	//settings->setWindowSize(18898/2, 21260/2);
}
