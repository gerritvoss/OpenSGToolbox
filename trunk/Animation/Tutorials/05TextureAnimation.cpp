// 
// OpenSGToolbox Tutorial: 05TextureAnimation 
//
// Demonstrates a texture animation. 
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImageFileHandler.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldFactory.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Animation
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

ChunkMaterialPtr TheBoxMaterial;

// forward declaration so we can have the interesting stuff upfront
void setupAnimation(void);
void display(void);
void reshape(Vec2f Size);

class TutorialAnimationListener : public AnimationListener
{
public:
   virtual void animationStarted(const AnimationEventPtr e)
   {
   }

   virtual void animationStopped(const AnimationEventPtr e)
   {
   }

   virtual void animationPaused(const AnimationEventPtr e)
   {
   }

   virtual void animationUnpaused(const AnimationEventPtr e)
   {
   }

   virtual void animationEnded(const AnimationEventPtr e)
   {
   }

   virtual void animationCycled(const AnimationEventPtr e)
   {
       std::cout << "Animation Cycled.  Cycle Count: " << AnimationPtr::dcast(e)->getCycles() << std::endl;
   }

};

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

Time TimeLastIdle;
FieldAnimationPtr TutorialTextureAnimation;
TutorialAnimationListener TutorialTextureAnimationListener;
AnimationAdvancerPtr TutorialTextureAnimationAdvancer;

KeyframeAnimatorPtr TutorialTextureAnimator;

// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
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
		ElapsedTimeAnimationAdvancer::Ptr::dcast(TutorialTextureAnimationAdvancer)->update(e->getElapsedTime());

		TutorialTextureAnimation->update(TutorialTextureAnimationAdvancer);
    }
};

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

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

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

	

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindowEventProducer->getWindow());

    //Setup the Animation
    setupAnimation();

    //Box Geometry
    GeometryPtr BoxGeometry = makeBoxGeo(1.0,1.0,1.0,1,1,1);
    beginEditCP(BoxGeometry);
        BoxGeometry->setMaterial(TheBoxMaterial);
    endEditCP  (BoxGeometry);
    
    NodePtr BoxGeometryNode = Node::create();
    beginEditCP(BoxGeometryNode, Node::CoreFieldMask);
        BoxGeometryNode->setCore(BoxGeometry);
    endEditCP  (BoxGeometryNode, Node::CoreFieldMask);

    //Make Box Node
    NodePtr BoxNode = Node::create();
    TransformPtr BoxNodeTrans;
    BoxNodeTrans = Transform::create();

    beginEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        BoxNode->setCore(BoxNodeTrans);
        BoxNode->addChild(BoxGeometryNode);
    endEditCP  (BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Make Main Scene Node
    NodePtr scene = Node::create();
    ComponentTransformPtr Trans;
    Trans = ComponentTransform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Trans);
 
        // add the torus as a child
        scene->addChild(BoxNode);
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    TutorialTextureAnimationAdvancer->start();
    
    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "05TextureAnimation");

    //Main Loop
    TutorialWindowEventProducer->mainLoop();

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
    std::vector<Path> _ImagePaths;
    _ImagePaths.push_back(Path("./Data/Anim001.jpg"));
    _ImagePaths.push_back(Path("./Data/Anim002.jpg"));
    _ImagePaths.push_back(Path("./Data/Anim003.jpg"));
    _ImagePaths.push_back(Path("./Data/Anim004.jpg"));
    _ImagePaths.push_back(Path("./Data/Anim005.jpg"));

    std::vector<TextureChunkPtr> _Textures;
    //Make the textures
    for(UInt32 i(0) ; i<_ImagePaths.size(); ++i)
    {
        ImagePtr AnimFrameImage = ImageFileHandler::the().read(_ImagePaths[i].string().c_str());
           
        TextureChunkPtr AnimFrameTexture = TextureChunk::create();
        beginEditCP(AnimFrameTexture, TextureChunk::ImageFieldMask | TextureChunk::EnvModeFieldMask);
            AnimFrameTexture->setImage(AnimFrameImage);
		    AnimFrameTexture->setEnvMode(GL_REPLACE);
        endEditCP(AnimFrameTexture, TextureChunk::ImageFieldMask | TextureChunk::EnvModeFieldMask);

        _Textures.push_back(AnimFrameTexture);
        addRefCP(AnimFrameTexture);
    }
    
    //Box Material
    MaterialChunkPtr TheMaterialChunk = MaterialChunk::create();
    beginEditCP(TheMaterialChunk);
    TheMaterialChunk->setAmbient(Color4f(0.4,0.4,0.4,1.0));
    TheMaterialChunk->setDiffuse(Color4f(0.8,0.8,0.8,1.0));
    TheMaterialChunk->setSpecular(Color4f(1.0,1.0,1.0,1.0));
    endEditCP(TheMaterialChunk);

    TheBoxMaterial = ChunkMaterial::create();
    beginEditCP(TheBoxMaterial);
        TheBoxMaterial->addChunk(_Textures.front());
    endEditCP(TheBoxMaterial);

    //Texture Keyframe Sequence
    KeyframeFCPtrsSequencePtr TextureKeyframes = KeyframeFCPtrsSequenceStateChunk::create();
    for(UInt32 i(0) ; i<_Textures.size(); ++i)
    {
        TextureKeyframes->addKeyframe(_Textures[i],static_cast<Real32>(i)*0.5f);
    }
    
    //Animator
    TutorialTextureAnimator = KeyframeAnimator::create();
    beginEditCP(TutorialTextureAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
        TutorialTextureAnimator->setKeyframeSequence(TextureKeyframes);
    endEditCP(TutorialTextureAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
    
    //Animation
    TutorialTextureAnimation = FieldAnimation::create();
    beginEditCP(TutorialTextureAnimation);
        TutorialTextureAnimation->setAnimator(TutorialTextureAnimator);
        TutorialTextureAnimation->setInterpolationType(STEP_INTERPOLATION);
        TutorialTextureAnimation->setCycling(-1);
    endEditCP(TutorialTextureAnimation);
    TutorialTextureAnimation->setAnimatedMultiField(TheBoxMaterial,ChunkMaterial::ChunksFieldId,0);
	//TutorialTextureAnimation->setAnimatedField(getFieldContainer("Transform",std::string("BoxNodeTransformationCore")), std::string("matrix"));

    //Animation Listener
    TutorialTextureAnimation->addAnimationListener(&TutorialTextureAnimationListener);

    //Animation Advancer
    TutorialTextureAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
    beginEditCP(TutorialTextureAnimationAdvancer);
    ElapsedTimeAnimationAdvancer::Ptr::dcast(TutorialTextureAnimationAdvancer)->setStartTime( 0.0 );
    beginEditCP(TutorialTextureAnimationAdvancer);
}
