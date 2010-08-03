// 
// OpenSGToolbox Tutorial: 05TextureAnimation 
//
// Demonstrates a texture animation. 
//

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"

#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGImageFileHandler.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"

#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"

#include "OSGContainerUtils.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Animation
#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

ChunkMaterialUnrecPtr TheBoxMaterial;

// forward declaration so we can have the interesting stuff upfront
void setupAnimation(void);
void display(void);
void reshape(Vec2f Size);

class TutorialAnimationListener : public AnimationListener
{
public:
   virtual void animationStarted(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationStopped(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationPaused(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationUnpaused(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationEnded(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationCycled(const AnimationEventUnrecPtr e)
   {
       std::cout << "Animation Cycled.  Cycle Count: " << dynamic_cast<Animation*>(e->getSource())->getCycles() << std::endl;
   }

};

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

FieldAnimationUnrecPtr TutorialTextureAnimation;
TutorialAnimationListener TutorialTextureAnimationListener;

KeyframeAnimatorUnrecPtr TutorialTextureAnimator;

// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            TutorialWindow->closeWindow();
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

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
	OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();

    //Initialize Window
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

    //Setup the Animation
    setupAnimation();

    //Box Geometry
    GeometryUnrecPtr BoxGeometry = makeBoxGeo(1.0,1.0,1.0,1,1,1);
    BoxGeometry->setMaterial(TheBoxMaterial);
    
    NodeUnrecPtr BoxGeometryNode = Node::create();
    BoxGeometryNode->setCore(BoxGeometry);

    //Make Box Node
    NodeUnrecPtr BoxNode = Node::create();
    TransformUnrecPtr BoxNodeTrans;
    BoxNodeTrans = Transform::create();

    BoxNode->setCore(BoxNodeTrans);
    BoxNode->addChild(BoxGeometryNode);

    //Make Main Scene Node
    NodeUnrecPtr scene = Node::create();
    ComponentTransformUnrecPtr Trans;
    Trans = ComponentTransform::create();
    scene->setCore(Trans);

    // add the torus as a child
    scene->addChild(BoxNode);

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    
    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);

    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "05TextureAnimation");

    //Main Loop
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

std::vector<ImageUnrecPtr> _Images;
void setupAnimation(void)
{
    std::vector<BoostPath> _ImagePaths;
    _ImagePaths.push_back(BoostPath("./Data/Anim001.jpg"));
    _ImagePaths.push_back(BoostPath("./Data/Anim002.jpg"));
    _ImagePaths.push_back(BoostPath("./Data/Anim003.jpg"));
    _ImagePaths.push_back(BoostPath("./Data/Anim004.jpg"));
    _ImagePaths.push_back(BoostPath("./Data/Anim005.jpg"));

    //Make the textures
    for(UInt32 i(0) ; i<_ImagePaths.size(); ++i)
    {
        ImageUnrecPtr AnimFrameImage = ImageFileHandler::the()->read(_ImagePaths[i].string().c_str());
           
        _Images.push_back(AnimFrameImage);
    }
    
    TextureObjChunkUnrecPtr AnimFrameTexture = TextureObjChunk::create();
    AnimFrameTexture->setImage(_Images.front());

    //Box Material
    MaterialChunkUnrecPtr TheMaterialChunk = MaterialChunk::create();
    TheMaterialChunk->setAmbient(Color4f(0.4,0.4,0.4,1.0));
    TheMaterialChunk->setDiffuse(Color4f(0.8,0.8,0.8,1.0));
    TheMaterialChunk->setSpecular(Color4f(1.0,1.0,1.0,1.0));

    TheBoxMaterial = ChunkMaterial::create();
    TheBoxMaterial->addChunk(AnimFrameTexture);

    //Texture Keyframe Sequence
    KeyframeFCPtrSequenceUnrecPtr TextureKeyframes = KeyframeFCPtrSequenceImage::create();
    for(UInt32 i(0) ; i<_Images.size(); ++i)
    {
        TextureKeyframes->addKeyframe(_Images[i],static_cast<Real32>(i)*0.5f);
    }
    
    //Animator
    TutorialTextureAnimator = KeyframeAnimator::create();
    TutorialTextureAnimator->setKeyframeSequence(TextureKeyframes);
    
    //Animation
    TutorialTextureAnimation = FieldAnimation::create();
    TutorialTextureAnimation->setAnimator(TutorialTextureAnimator);
    TutorialTextureAnimation->setInterpolationType(Animator::STEP_INTERPOLATION);
    TutorialTextureAnimation->setCycling(-1);
    TutorialTextureAnimation->setAnimatedField(AnimFrameTexture,TextureObjChunk::ImageFieldId);

    //Animation Listener
    TutorialTextureAnimation->addAnimationListener(&TutorialTextureAnimationListener);

    TutorialTextureAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TutorialTextureAnimation->start();
}
