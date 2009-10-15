// Headers
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGProxyGroup.h>
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGSimpleStatisticsForeground.h>
#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGForeground.h>

#include <OpenSG/OSGStatElemDesc.h>
#include <OpenSG/OSGStatIntElem.h>
#include <OpenSG/OSGSimpleAttachments.h>

// New Headers

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/Toolbox/OSGFCFileHandler.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Animations
#include <OpenSG/Animation/OSGAnimation.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>

//Particle Systems
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

int SelectedRootNode;
int SelectedCamera;
int SelectedBackground;
ElapsedTimeAnimationAdvancerPtr GlobalAnimationAdvancer;

std::vector<NodePtr> GlobalRootNodes;
std::vector<BackgroundPtr> GlobalBackgrounds;
std::vector<ForegroundPtr> GlobalForegrounds;
std::vector<AnimationPtr> GlobalAnimations;
std::vector<ParticleSystemPtr> GlobalParticleSystems;
std::vector<CameraPtr> GlobalCameras;
SimpleStatisticsForegroundPtr RenderStatisticeForeground;

bool IsPaused(false);

// forward declaration so we can have the interesting stuff upfront


void display(void);
void reshape(Vec2f Size);
void Load(std::string FilePath, std::vector<NodePtr>& RootNodes,
                                std::vector<CameraPtr>& Cameras,
                                std::vector<AnimationPtr>& Animations,
                                std::vector<ParticleSystemPtr>& ParticleSystems,
                                std::vector<BackgroundPtr>& Backgrounds,
                                std::vector<ForegroundPtr>& Foregrounds);
void LoadXML(std::string FilePath, std::vector<NodePtr>& RootNodes,
                                std::vector<CameraPtr>& Cameras,
                                std::vector<AnimationPtr>& Animations,
                                std::vector<ParticleSystemPtr>& ParticleSystems,
                                std::vector<BackgroundPtr>& Backgrounds,
                                std::vector<ForegroundPtr>& Foregrounds);
bool isFileXML(std::string FilePath);
void printAllStatDescs(void);
void printCommands(void);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            TutorialWindowEventProducer->closeWindow();
        }
        switch(e->getKey())
        {
        case KeyEvent::KEY_F: 
            {  
                mgr->setNavigationMode(Navigator::FLY);
            }
            break;
            
            case KeyEvent::KEY_T:   
            {
                mgr->setNavigationMode(Navigator::TRACKBALL);
            }
            break;
            case KeyEvent::KEY_R:   
            {
			    SelectedRootNode = (SelectedRootNode+1)%GlobalRootNodes.size();
			    if(SelectedRootNode == -1) {SelectedRootNode = 0;}
			    mgr->setRoot  (GlobalRootNodes[SelectedRootNode]);
            }
            break;
            case KeyEvent::KEY_C:   
            {
			    if(GlobalCameras.size() > 0)
			    {
				    SelectedCamera = (SelectedCamera+1)%GlobalCameras.size();
				    if(GlobalCameras[SelectedCamera]->getType().isDerivedFrom(PerspectiveCamera::getClassType()))
				    {
                        Matrix m= GlobalCameras[SelectedCamera]->getBeacon()->getToWorld();
                        mgr->getNavigator()->setCameraTransformation(GlobalCameras[SelectedCamera]->getBeacon());
                        mgr->getNavigator()->set(m);
                        beginEditCP(mgr->getWindow()->getPort(0), Viewport::CameraFieldMask);
                            mgr->getWindow()->getPort(0)->setCamera(GlobalCameras[SelectedCamera]);
                        endEditCP(mgr->getWindow()->getPort(0), Viewport::CameraFieldMask);

                        //beginEditCP(mgr->getHeadlight(), Light::BeaconFieldMask);
                        //    mgr->getHeadlight()->setBeacon(GlobalCameras[SelectedCamera]->getBeacon());
                        //endEditCP(mgr->getHeadlight(), Light::BeaconFieldMask);


					    //mgr->setCamera(PerspectiveCamera::Ptr::dcast(GlobalCameras[SelectedCamera]));
                        const Char8* CameraName(getName(GlobalCameras[SelectedCamera]));
                        if(CameraName != NULL)
                        {
                            std::cout << "Switching to Camera: " << CameraName << std::endl;
                        }
				    }
				    else
				    {
					    std::cout << "Cannont switch to a non-perspective camera.  This needs to be implemented." << std::endl;
				    }
			    }
            }
            break;
            case KeyEvent::KEY_B:   
            {
			    if(GlobalBackgrounds.size() > 0)
			    {
				    SelectedBackground = (SelectedBackground+1)%GlobalBackgrounds.size();

                    beginEditCP(mgr->getWindow()->getPort(0), Viewport::CameraFieldMask);
                        mgr->getWindow()->getPort(0)->setBackground(GlobalBackgrounds[SelectedBackground]);
                    endEditCP(mgr->getWindow()->getPort(0), Viewport::CameraFieldMask);
			    }
            }
            break;

            case KeyEvent::KEY_H:
                if(mgr->getHeadlightState())
                {
                    mgr->turnHeadlightOff();
                }
                else
                {
                    mgr->turnHeadlightOn();
                }
                break;

            case KeyEvent::KEY_F3:
                printAllStatDescs();
                break;

            case KeyEvent::KEY_F4:
                //Toggle the stat foreground
                if(mgr->getWindow()->getPort(0)->getForegrounds().find(RenderStatisticeForeground) == mgr->getWindow()->getPort(0)->getForegrounds().end())
                {
                    beginEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
                        mgr->getWindow()->getPort(0)->getForegrounds().push_back(RenderStatisticeForeground);
                    endEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
                }
                else
                {
                    beginEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
                        mgr->getWindow()->getPort(0)->getForegrounds().erase(mgr->getWindow()->getPort(0)->getForegrounds().find(RenderStatisticeForeground));
                    endEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
                }
                break;

            case KeyEvent::KEY_SPACE:
                //Pause Particle Systems and Animations
                IsPaused = !IsPaused;
                break;
            case KeyEvent::KEY_V:
                //Show All in the scene
                mgr->showAll();
                break;
        }
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventPtr e)
    {
    }
    virtual void mouseExited(const MouseEventPtr e)
    {
    }
    virtual void mousePressed(const MouseEventPtr e)
    {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventPtr e)
    {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEventPtr e)
    {
        static bool WasEmpty(true);
        if(!IsPaused)
        {
            //Update Animations
		    GlobalAnimationAdvancer->update(e->getElapsedTime());

            for(std::vector<AnimationPtr>::iterator Itor(GlobalAnimations.begin()) ; Itor != GlobalAnimations.end(); ++Itor)
            {
                (*Itor)->update(GlobalAnimationAdvancer);
            }
        }
        if(WasEmpty)
        {
            Pnt3f Min,Max;
            mgr->getRoot()->getVolume().getBounds(Min,Max);
            if(Max-Min != Vec3f(0.0f,0.0f,0.0f))
            {
                WasEmpty = false;
                mgr->showAll();
            }
        }
        mgr->idle();
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    printCommands();

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);
	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);


    // load the scene
    std::string WindowFileTitle;
    if(argc < 2)
    {
        FWARNING(("No file given!\n"));
        FWARNING(("Supported file formats:\n"));
        
        std::list<const char*> suffixes;
        SceneFileHandler::the().getSuffixList(suffixes);
        
        for(std::list<const char*>::iterator it  = suffixes.begin();
                                             it != suffixes.end();
                                           ++it)
        {
            FWARNING(("%s\n", *it));
        }

        //std::vector<std::string> suffixesVec;
        //suffixesVec = FCFileHandler::the()->getSuffixList();
        
        //for(std::vector<std::string>::iterator it  = suffixesVec.begin();
                                             //it != suffixesVec.end();
                                           //++it)
        //{
            //FWARNING(("%s\n", *it));
        //}

        GlobalRootNodes.push_back( makeTorus(.5, 2, 16, 16) );
        WindowFileTitle = "No file Loaded";
    }
    else
    {
        WindowFileTitle = argv[1];
        Load(std::string(argv[1]), GlobalRootNodes, GlobalCameras, GlobalAnimations, GlobalParticleSystems, GlobalBackgrounds, GlobalForegrounds);

		if(GlobalRootNodes.size() < 1)
		{
			std::cout << "There are no root nodes defined." << std::endl;
			return 1;
		}
    }

    //Create Statistics Foreground
    RenderStatisticeForeground = SimpleStatisticsForeground::create();
    beginEditCP(RenderStatisticeForeground);
        RenderStatisticeForeground->setSize(25);
        RenderStatisticeForeground->setColor(Color4f(0,1,0,0.7));
        RenderStatisticeForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        RenderStatisticeForeground->addElement(DrawActionBase::statTravTime, "TravTime: %.3f s");
        RenderStatisticeForeground->addElement(RenderAction::statDrawTime, "DrawTime: %.3f s");
        RenderStatisticeForeground->addElement(DrawActionBase::statCullTestedNodes, 
                           "%d Nodes culltested");
        RenderStatisticeForeground->addElement(DrawActionBase::statCulledNodes, 
                           "%d Nodes culled");
        RenderStatisticeForeground->addElement(RenderAction::statNMaterials, 
                           "%d material changes");
        RenderStatisticeForeground->addElement(RenderAction::statNMatrices, 
                           "%d matrix changes");
        RenderStatisticeForeground->addElement(RenderAction::statNGeometries, 
                           "%d Nodes drawn");
        RenderStatisticeForeground->addElement(RenderAction::statNLights, 
                           "%d Lights");
        RenderStatisticeForeground->addElement(RenderAction::statNTransGeometries, 
                           "%d transparent Nodes drawn");
        RenderStatisticeForeground->addElement(Drawable::statNTriangles, 
                           "%d triangles drawn");
        RenderStatisticeForeground->addElement(Drawable::statNLines, 
                           "%d lines drawn");
        RenderStatisticeForeground->addElement(Drawable::statNPoints, 
                           "%d points drawn");
        RenderStatisticeForeground->addElement(Drawable::statNPrimitives,
                            "%d primitive groups drawn");
        RenderStatisticeForeground->addElement(Drawable::statNVertices, 
                           "%d vertices transformed");
        RenderStatisticeForeground->addElement(Drawable::statNGeoBytes, "%d bytes of geometry used");
        RenderStatisticeForeground->addElement(RenderAction::statNTextures, "%d textures used");
        RenderStatisticeForeground->addElement(RenderAction::statNTexBytes, "%d bytes of texture used");
    endEditCP(RenderStatisticeForeground);

    StatCollector *collector = &RenderStatisticeForeground->getCollector();
    
    // add optional elements
    collector->getElem(Drawable::statNTriangles);

	//Set up Selection
	SelectedRootNode = 0;
	SelectedCamera = -1;
	SelectedBackground = -1;

    //Set up animations
    GlobalAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
    beginEditCP(GlobalAnimationAdvancer, ElapsedTimeAnimationAdvancer::StartTimeFieldMask);
        GlobalAnimationAdvancer->setStartTime( 0.0 );
    endEditCP(GlobalAnimationAdvancer, ElapsedTimeAnimationAdvancer::StartTimeFieldMask);

    //Setup Particle Systems
    for(std::vector<ParticleSystemPtr>::iterator Itor(GlobalParticleSystems.begin()) ; Itor != GlobalParticleSystems.end(); ++Itor)
    {
        (*Itor)->attachUpdateListener(TutorialWindowEventProducer);
    }


    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindowEventProducer->getWindow());
    
    // tell the manager what to manage
    mgr->setRoot  (GlobalRootNodes[SelectedRootNode]);
    mgr->turnHeadlightOff();
    
    //Setup Foregrounds
    beginEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
        mgr->getWindow()->getPort(0)->getForegrounds().push_back(RenderStatisticeForeground);
    endEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
    mgr->getAction()->setStatistics(collector);
    

    //Setup Backgrounds
    if(GlobalBackgrounds.size() > 0)
    {
        SelectedBackground = (SelectedBackground+1)%GlobalBackgrounds.size();

        beginEditCP(mgr->getWindow()->getPort(0), Viewport::CameraFieldMask);
            mgr->getWindow()->getPort(0)->setBackground(GlobalBackgrounds[SelectedBackground]);
        endEditCP(mgr->getWindow()->getPort(0), Viewport::CameraFieldMask);
    }

    // show the whole scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        std::string("Advanced XML Scene Viewer - ") + WindowFileTitle);

    //Main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}

void Load(std::string FilePath, std::vector<NodePtr>& RootNodes,
                                std::vector<CameraPtr>& Cameras,
                                std::vector<AnimationPtr>& Animations,
                                std::vector<ParticleSystemPtr>& ParticleSystems,
                                std::vector<BackgroundPtr>& Backgrounds,
                                std::vector<ForegroundPtr>& Foregrounds)
{
    /*
        All scene file loading is handled via the SceneFileHandler.
    */
    NodePtr LoadedScene;

    Time start = getSystemTime();
    
    if(isFileXML(FilePath))
    {
        LoadXML(FilePath, RootNodes, Cameras, Animations, ParticleSystems, Backgrounds,Foregrounds);
    }
    else
    {
        NodePtr TheNode = Node::create();
        ProxyGroupPtr TheProxyGroup = ProxyGroup::create();
        beginEditCP(TheProxyGroup, ProxyGroup::UrlFieldMask | ProxyGroup::EnabledFieldMask | ProxyGroup::ConcurrentLoadFieldMask);
            TheProxyGroup->setUrl(FilePath.c_str());
            TheProxyGroup->setEnabled(true);
            TheProxyGroup->setConcurrentLoad(true);
        endEditCP(TheProxyGroup, ProxyGroup::UrlFieldMask | ProxyGroup::EnabledFieldMask | ProxyGroup::ConcurrentLoadFieldMask);
		
        TheNode->setCore(TheProxyGroup);

        RootNodes.push_back(TheNode);
		//RootNodes.push_back(SceneFileHandler::the().read(FilePath.c_str(),NULL));
    }
    
    Time end = getSystemTime();

    std::cerr << "Took " << end-start << " to load" << std::endl;
}

void LoadXML(std::string FilePath, std::vector<NodePtr>& RootNodes,
                                std::vector<CameraPtr>& Cameras,
                                std::vector<AnimationPtr>& Animations,
                                std::vector<ParticleSystemPtr>& ParticleSystems,
                                std::vector<BackgroundPtr>& Backgrounds,
                                std::vector<ForegroundPtr>& Foregrounds)
{
	RootNodes.clear();
	Cameras.clear();
	Animations.clear();
	ParticleSystems.clear();
	Backgrounds.clear();
	Foregrounds.clear();
    std::cout << "Loading xml File: " << FilePath << std::endl;

	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path(FilePath));

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
        //Get Root Nodes
        if( (*Itor)->getType() == Node::getClassType() &&
            Node::Ptr::dcast(*Itor)->getParent() == NullFC)
        {
            RootNodes.push_back(Node::Ptr::dcast(*Itor));
            addRefCP(*Itor);
        }
        //Get Cameras
		else if( (*Itor)->getType().isDerivedFrom( Camera::getClassType() ))
		{
            Cameras.push_back(Camera::Ptr::dcast(*Itor));
            addRefCP(*Itor);
		}
        //Get Animations
		else if( (*Itor)->getType().isDerivedFrom( Animation::getClassType() ))
		{
            Animations.push_back(Animation::Ptr::dcast(*Itor));
            addRefCP(*Itor);
		}
        //Get Particle Systems
		else if( (*Itor)->getType().isDerivedFrom( ParticleSystem::getClassType() ))
		{
            ParticleSystems.push_back(ParticleSystem::Ptr::dcast(*Itor));
            addRefCP(*Itor);
		}
        //Get Backgrounds
		else if( (*Itor)->getType().isDerivedFrom( Background::getClassType() ))
		{
            Backgrounds.push_back(Background::Ptr::dcast(*Itor));
            addRefCP(*Itor);
		}
        //Get Foregrounds
		else if( (*Itor)->getType().isDerivedFrom( Foreground::getClassType() ))
		{
            Foregrounds.push_back(Foreground::Ptr::dcast(*Itor));
            addRefCP(*Itor);
		}
    }
}

bool isFileXML(std::string FilePath)
{
    std::string::size_type LastDotPos = FilePath.find_last_of(".");
    ++LastDotPos;
    std::string Extension(FilePath.substr(LastDotPos, FilePath.length() - LastDotPos));

    return Extension.compare("xml") == 0;
}

void printAllStatDescs(void)
{
    UInt32 NumOfStatDescs(StatElemDesc<StatIntElem>::getNumOfDescs());
    std::cout << "Number of StatIntElem Stat Descriptions: "<< NumOfStatDescs << std::endl;

    for(UInt32 i(0) ; i<NumOfStatDescs ; ++i)
    {
        std::cout << i << " : " << StatElemDesc<StatIntElem>::getDesc(i)->getName() << std::endl;
    }
}

void printCommands(void)
{
    std::cout << "Keyboard Commands: " << std::endl;
    std::cout << "    Ctrl+q: Exit the Application" << std::endl;
    std::cout << "    f: Switch navigation mode to fly" << std::endl;
    std::cout << "    t: Switch navigation mode to trackball" << std::endl;
    std::cout << "    r: Cycle through all root nodes" << std::endl;
    std::cout << "    c: Cycle through all cameras" << std::endl;
    std::cout << "    b: Cycle through all backgrounds" << std::endl;
    std::cout << "    h: Toggle a headlight on and off" << std::endl;
    std::cout << "    F4: Toggle the Statistic forground on/off" << std::endl;
    std::cout << "    F3: Print description of all stat elements available" << std::endl;
}
