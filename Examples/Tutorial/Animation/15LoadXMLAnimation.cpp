// 
// OpenSGToolbox Tutorial: 15LoadXMLAnimation 
//
// Loads a skeleton and a skeleton animation from an
// XML file.
//


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"

// Input
#include "OSGKeyListener.h"


#include "OSGSimpleMaterial.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"


#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"

#include "OSGFieldContainerUtils.h"

#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"

#include "OSGFCFileHandler.h"


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

AnimationUnrecPtr TheAnimation;
MaterialUnrecPtr TheTorusMaterial;
GeometryUnrecPtr TorusGeometry;

bool animationPaused = false;

// forward declaration so we can have the interesting stuff upfront
void setupAnimation(void);
void display(void);
void reshape(Vec2f Size);


// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
	   //Exit
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindow->closeWindow();
       }

	   //Toggle animation
	   if(e->getKey() == KeyEvent::KEY_SPACE)
	   {
		   if(animationPaused)
			   animationPaused = false;
		   else
			   animationPaused = true;
	   }
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
public:
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseExited(const MouseEventUnrecPtr e)
    {
    }
    virtual void mousePressed(const MouseEventUnrecPtr e)
    {
        mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
        mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
public:
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};


KeyframeAnimatorUnrecPtr TheAnimator;
KeyframeTransformationSequenceUnrecPtr TransformationKeyframes;
KeyframeColorSequenceUnrecPtr ColorKeyframes;
KeyframeVectorSequenceUnrecPtr VectorKeyframes;
KeyframeRotationSequenceUnrecPtr RotationKeyframes;

// Initialize OpenSG and set up the scene
int main(int argc, char **argv)
{
	//Print key command info
	std::cout << "\n\nKEY COMMANDS:" << std::endl;
	std::cout << "space   Play/Pause the animation" << std::endl;
	std::cout << "CTRL-Q  Exit\n\n" << std::endl;

    // OSG init
    osgInit(argc,argv);


    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);

    //Torus Geometry
    TorusGeometry = makeTorusGeo(.5, 2, 16, 16);
    
    NodeUnrecPtr TorusGeometryNode = Node::create();
    TorusGeometryNode->setCore(TorusGeometry);

    //Make Torus Node
    NodeUnrecPtr TorusNode = Node::create();
    TransformUnrecPtr TorusNodeTrans;
    TorusNodeTrans = Transform::create();
    setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));

    TorusNode->setCore(TorusNodeTrans);
    TorusNode->addChild(TorusGeometryNode);

    //Make Main Scene Node
    NodeUnrecPtr scene = Node::create();
    //ComponentTransformUnrecPtr Trans;
    //Trans = ComponentTransform::create();
    //setName(Trans, std::string("MainTransformationCore"));
    scene->setCore(Group::create());

    // add the torus as a child
    scene->addChild(TorusNode);


	setupAnimation();
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();


    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                        WinSize,
                                        "15LoadXMLAnimation");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();


    return 0;
}

// Redraw the window
void display(void)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}

void setupAnimation(void)
{
	//Read animation data from XML file
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("./Data/15TestAnimations.xml"));

	FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
		if( (*Itor)->getType().isDerivedFrom(Animation::getClassType()))
		{
			//Set the animation to the one we just read in
			TheAnimation = (dynamic_pointer_cast<Animation>(*Itor));
		}
		else if( (*Itor)->getType() == (SimpleMaterial::getClassType()))
		{
			//Set torus material
			TheTorusMaterial = (dynamic_pointer_cast<SimpleMaterial>(*Itor));
			
			//Attach torus material to torus geometry
				TorusGeometry->setMaterial(TheTorusMaterial);
		}
    }

    TheAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TheAnimation->start();
}
