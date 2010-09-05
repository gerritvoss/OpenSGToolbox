// OpenSG Tutorial Example: Show an animated texture in hte background
//
// This example shows how to use the TextureBackground to show animated
// pictures behind the 3D graphics, and how to do it as efficiently as 
// possible
//
// Most video is not a power-of-two (POT) size, which makes it interesting.
// OpenSG handles most of that behind the scenes, but you have to set some
// options to make it efficient (see below).



// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGSwitch.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

// For textures
#include "OSGTextureObjChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGChunkMaterial.h"

// To put a texture into the background
#include "OSGVideoManager.h"


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

//Ctrl+q handler
void handleKeyTyped(KeyEventDetails* const details,
              VideoWrapper* const video,
              Switch* const nodeSwitch)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        video->stop();
        video->close();
        getDefaultVideoManager()->exit();
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    Int64 JumpAmount(50000000);
    switch(details->getKey())
    {
    case KeyEventDetails::KEY_P:
    case KeyEventDetails::KEY_SPACE:
		video->pauseToggle();
		break;
    case KeyEventDetails::KEY_S:
    case KeyEventDetails::KEY_ENTER:
        if(video->isPlaying())
        {
		    video->stop();
        }
        else
        {
		    video->play();
        }
		break;
    case KeyEventDetails::KEY_R:
		video->stop();
		video->seek(0);
		video->pause();
		break;
    case KeyEventDetails::KEY_F:
        video->jump(JumpAmount);
        break;
    case KeyEventDetails::KEY_V:
        video->jump(-JumpAmount);
        break;
    /*case KeyEventDetails::KEY_U:
        UpdateImage = !UpdateImage;
        break;*/
    case KeyEventDetails::KEY_W:
        nodeSwitch->setChoice((nodeSwitch->getChoice() + 1) % 
            dynamic_cast<Node*>(nodeSwitch->getParents().front())->getNChildren());
        break;
    }
}

void mousePressed(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
}
void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}
  
void handleVideoPaused(VideoEventDetails* const details)
{
	std::cout << "Paused" << std::endl;
}

void handleVideoUnpaused(VideoEventDetails* const details)
{
	std::cout << "Unpaused" << std::endl;
}

void handleVideoStarted(VideoEventDetails* const details)
{
	std::cout << "Started" << std::endl;
}

void handleVideoStopped(VideoEventDetails* const details)
{
	std::cout << "Stopped" << std::endl;
}

void handleVideoOpened(VideoEventDetails* const details)
{
	std::cout << "Opened" << std::endl;
}

void handleVideoClosed(VideoEventDetails* const details)
{
	std::cout << "Closed" << std::endl;
}

void handleVideoCycled(VideoEventDetails* const details)
{
	std::cout << "Cycled" << std::endl;
}

void handleVideoSeeked(VideoEventDetails* const details)
{
	std::cout << "Seeked" << std::endl;
}

void handleVideoEnded(VideoEventDetails* const details)
{
	std::cout << "Reached End" << std::endl;
	dynamic_cast<VideoWrapper*>(details->getSource())->pause();
	dynamic_cast<VideoWrapper*>(details->getSource())->seek(0);
	dynamic_cast<VideoWrapper*>(details->getSource())->play();
	dynamic_cast<VideoWrapper*>(details->getSource())->unpause();
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        VideoWrapperRecPtr TheVideo  = getDefaultVideoManager()->createVideoWrapper();
	    TheVideo->attachUpdateProducer(TutorialWindow);

	    TheVideo->connectStarted(boost::bind(handleVideoStarted, _1));
	    TheVideo->connectPaused(boost::bind(handleVideoPaused, _1));
	    TheVideo->connectUnpaused(boost::bind(handleVideoUnpaused, _1));
	    TheVideo->connectStopped(boost::bind(handleVideoStopped, _1));
	    TheVideo->connectClosed(boost::bind(handleVideoClosed, _1));
	    TheVideo->connectSeeked(boost::bind(handleVideoSeeked, _1));
	    TheVideo->connectCycled(boost::bind(handleVideoCycled, _1));
	    TheVideo->connectOpened(boost::bind(handleVideoOpened, _1));
	    TheVideo->connectEnded(boost::bind(handleVideoEnded, _1));
        
        TheVideo->open(BoostPath("./Data/Wildlife.wmv"), TutorialWindow);
	    TheVideo->pause();
        if(TheVideo->hasAudio())
        {
	        TheVideo->enableAudio();
	        TheVideo->setAudioVolume(1.0f);
        }

        // create the scene
	    TheVideo->updateImage();
        Real32 AspectRatio(static_cast<Real32>(TheVideo->getWidth())/static_cast<Real32>(TheVideo->getHeight()));

        // Set filtering modes. LINEAR is cheap and good if the image size
        // changes very little (i.e. the window is about the same size as 
        // the images).
        //TheVideo->setMinFilter(GL_LINEAR);
        TheVideo->setMinFilter(GL_NEAREST);
        TheVideo->setMagFilter(GL_LINEAR);
        //TheVideo->setMagFilter(GL_NEAREST);        
        
        // Set the wrapping modes. We don't need repetition, it might actually
        // introduce artifactes at the borders, so switch it off.
        TheVideo->setWrapS(GL_CLAMP_TO_EDGE);
        TheVideo->setWrapT(GL_CLAMP_TO_EDGE);   
        
        TheVideo->setScale(false);            

	    ChunkMaterialUnrecPtr VideoMaterial = ChunkMaterial::create();

	    VideoMaterial->addChunk(TheVideo);
        StateChunkUnrecPtr pMChunk = MaterialChunk::create();
	    VideoMaterial->addChunk(pMChunk);

        //Plane Geometry
	    GeometryRecPtr PlaneGeometry = makePlaneGeo(10.0*AspectRatio,10.0,10,10);
        PlaneGeometry->setMaterial(VideoMaterial);
    	
        NodeRecPtr PlaneGeometryNode = Node::create();
        PlaneGeometryNode->setCore(PlaneGeometry);

        //Box Geometry
	    GeometryRecPtr BoxGeometry = makeBoxGeo(10.0*AspectRatio,10.0,10.0,2,2,2);
        BoxGeometry->setMaterial(VideoMaterial);
    	
        NodeRecPtr BoxGeometryNode = Node::create();
        BoxGeometryNode->setCore(BoxGeometry);

        //Sphere Geometry
	    GeometryRecPtr SphereGeometry = makeSphereGeo(2,5.0);
        SphereGeometry->setMaterial(VideoMaterial);
    	
        NodeRecPtr SphereGeometryNode = Node::create();
        SphereGeometryNode->setCore(SphereGeometry);
        

        //Torus Geometry
	    GeometryRecPtr TorusGeometry = makeTorusGeo(2.0,5.0,32,32);
        TorusGeometry->setMaterial(VideoMaterial);
    	
        NodeRecPtr TorusGeometryNode = Node::create();
        TorusGeometryNode->setCore(TorusGeometry);

        //Switch Node
        SwitchRecPtr GeometryNodeSwitch = Switch::create();
        GeometryNodeSwitch->setChoice(0);

        NodeRecPtr SwitchNode = Node::create();
        SwitchNode->setCore(GeometryNodeSwitch);
        SwitchNode->addChild(PlaneGeometryNode);
        SwitchNode->addChild(BoxGeometryNode);
        SwitchNode->addChild(SphereGeometryNode);
        SwitchNode->addChild(TorusGeometryNode);


        NodeRecPtr scene = Node::create();
        TransformRecPtr trans = Transform::create();
        scene->setCore(trans);
	    scene->addChild(SwitchNode);

        TutorialWindow->connectKeyTyped(boost::bind(handleKeyTyped, _1, TheVideo.get(), GeometryNodeSwitch.get()));
        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01PlayVideo");

        commitChanges();

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}


// Callback functions


// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}
