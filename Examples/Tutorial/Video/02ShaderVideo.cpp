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
#include "OSGSimpleSHLChunk.h"

// To put a texture into the background
#include "OSGVideoManager.h"

#include <boost/filesystem/convenience.hpp>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

std::string createSHLVertexProg(void);
std::string createSHLFragProg(void);

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
    Real64 JumpAmount(1.0f);
    switch(details->getKey())
    {
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
    case KeyEventDetails::KEY_N:
        video->setRate(video->getRate() + 0.1f);
        break;
    case KeyEventDetails::KEY_M:
        video->setRate(video->getRate() - 0.1f);
        break;
    case KeyEventDetails::KEY_MINUS:
        video->setAudioVolume(video->getAudioVolume() - 0.1f);
        std::cout << "Volume: " << video->getAudioVolume() <<  std::endl;
        break;
    case KeyEventDetails::KEY_EQUALS:
        video->setAudioVolume(video->getAudioVolume() + 0.1f);
        std::cout << "Volume: " << video->getAudioVolume() <<  std::endl;
        break;
    case KeyEventDetails::KEY_I:
        std::cout << "Dimensions: " << video->getWidth()
                  << "x"            << video->getHeight()
                  << std::endl;
        std::cout << "Duration: " << video->getDuration()
                  << std::endl;
        std::cout << "Position: " << video->getPosition()
                  << std::endl;
        std::cout << "Rate: " << video->getRate()
                  << std::endl;
        break;
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

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseWheelMoved(MouseWheelEventDetails* const details, SimpleSceneManager *mgr)
{
    if(details->getUnitsToScroll() > 0)
    {
        for(UInt32 i(0) ; i<details->getUnitsToScroll() ;++i)
        {
            mgr->mouseButtonPress(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
    else if(details->getUnitsToScroll() < 0)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            mgr->mouseButtonPress(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
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
	//dynamic_cast<VideoWrapper*>(details->getSource())->pause();
	dynamic_cast<VideoWrapper*>(details->getSource())->stop();
	//dynamic_cast<VideoWrapper*>(details->getSource())->seek(0);
	dynamic_cast<VideoWrapper*>(details->getSource())->play();
	//dynamic_cast<VideoWrapper*>(details->getSource())->unpause();
}

std::string createSHLVertexProg(void)
{
    std::ostringstream FragCodeStream;

    FragCodeStream
        << "attribute vec4 Position;//Position\n"
        << "attribute vec3 Normal;//Normal\n"
        << "attribute vec2 TexCoord;//TexCoord\n"

        //<< "varying vec3 temp;\n"
        << "void main() {\n"

        << "gl_TexCoord[0] = vec4(TexCoord.s,TexCoord.t,0.0,0.0);\n"
        //<< "pos    = ftransform();\n"
        //<< "gl_Position    = ftransform();\n"
        //<< "temp = Normal;\n"
        << "gl_Position    = gl_ModelViewProjectionMatrix * Position;\n"
        << "} \n";


    return FragCodeStream.str();
}

std::string createSHLFragProg(void)
{
    std::ostringstream FragCodeStream;

    FragCodeStream
        << "//Fragment Shader\n"
        //<< "varying vec3 temp;\n"
        << "uniform sampler2D VideoTexture;\n"

        << "void main()\n"
        << "{\n"
        //<< "    gl_FragColor = vec4( gl_TexCoord[0].r, gl_TexCoord[0].g, 1.0,1.0);\n"
        //<< "    vec3 Color = texture2D(VideoTexture,pos.st*0.1).rgb;\n"
        << "    vec3 Color = texture2D(VideoTexture,gl_TexCoord[0].st).rgb;\n"
        << "    //Invert\n"
        << "    gl_FragColor = vec4( 1.0 - Color.r,1.0 - Color.g,1.0 - Color.b,1.0);\n"
        //<< "    //grayscale\n"
        //<< "    float intensity = 0.3*Color.r + 0.59*Color.g + 0.11*Color.b;\n"
        //<< "    gl_FragColor = vec4( intensity,intensity,intensity,1.0);\n"
        << "}\n";


    return FragCodeStream.str();
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
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

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
        
        BoostPath VideoFilePath("./Data/ExampleVideo.avi");
        if(argc >= 2)
        {
            VideoFilePath = BoostPath(argv[1]);
            if(!boost::filesystem::exists(VideoFilePath))
            {
                std::cerr << "Could not load file: "<< VideoFilePath.string()
                          << ", because no such files exists."<< std::endl;
                VideoFilePath = BoostPath("./Data/ExampleVideo.avi");
            }
        }

        TheVideo->open(VideoFilePath, TutorialWindow);
	    TheVideo->pause();
        if(TheVideo->hasAudio())
        {
	        TheVideo->enableAudio();
	        TheVideo->setAudioVolume(0.5f);
        }

        //Wait for the video to initialize
        std::cout << "Dimensions: " << TheVideo->getWidth()
                  << "x"            << TheVideo->getHeight()
                  << std::endl;
        Real32 AspectRatio(static_cast<Real32>(TheVideo->getWidth())/static_cast<Real32>(TheVideo->getHeight()));
        //Real32 AspectRatio(4.0f/3.0f);

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

        SimpleSHLChunkUnrecPtr TheSHLChunk = SimpleSHLChunk::create();
        TheSHLChunk->setVertexProgram(createSHLVertexProg());
        TheSHLChunk->setFragmentProgram(createSHLFragProg());
        TheSHLChunk->addUniformVariable("VideoTexture",0);

	    ChunkMaterialUnrecPtr VideoMaterial = ChunkMaterial::create();

	    VideoMaterial->addChunk(TheVideo);
        StateChunkUnrecPtr pMChunk = MaterialChunk::create();
		//VideoMaterial->addChunk(pMChunk);
		VideoMaterial->addChunk(TheSHLChunk);

        // create the scene
        //Plane Geometry
	    GeometryRecPtr PlaneGeometry = makePlaneGeo(10.0*AspectRatio,10.0,1,1);
        PlaneGeometry->setMaterial(VideoMaterial);
        PlaneGeometry->setDlistCache(false);
    	
        NodeRecPtr PlaneGeometryNode = Node::create();
        PlaneGeometryNode->setCore(PlaneGeometry);

        //Box Geometry
	    GeometryRecPtr BoxGeometry = makeBoxGeo(10.0*AspectRatio,10.0,10.0,2,2,2);
        BoxGeometry->setMaterial(VideoMaterial);
        BoxGeometry->setDlistCache(false);
    	
        NodeRecPtr BoxGeometryNode = Node::create();
        BoxGeometryNode->setCore(BoxGeometry);

        //Sphere Geometry
	    GeometryRecPtr SphereGeometry = makeSphereGeo(2,5.0);
        SphereGeometry->setMaterial(VideoMaterial);
        SphereGeometry->setDlistCache(false);
    	
        NodeRecPtr SphereGeometryNode = Node::create();
        SphereGeometryNode->setCore(SphereGeometry);
        

        //Torus Geometry
	    GeometryRecPtr TorusGeometry = makeTorusGeo(2.0,5.0,32,32);
        TorusGeometry->setMaterial(VideoMaterial);
        TorusGeometry->setDlistCache(true);
    	
        NodeRecPtr TorusGeometryNode = Node::create();
        TorusGeometryNode->setCore(TorusGeometry);

        //Switch Node
        SwitchRecPtr GeometryNodeSwitch = Switch::create();
        GeometryNodeSwitch->setChoice(3);

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
