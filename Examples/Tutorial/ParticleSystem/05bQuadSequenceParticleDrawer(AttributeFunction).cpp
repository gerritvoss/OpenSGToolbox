// NOTE: If the images are not loading correctly, make sure the working 
// directory is set to the location of the .cpp file for this tutorial.

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGSimpleGeometry.h"
#include "OSGWindowUtils.h"

// Input
#include "OSGKeyListener.h"

#include "OSGBlendChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGImageFileHandler.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGRateParticleGenerator.h"

#include "OSGQuadSequenceParticleSystemDrawer.h"
#include "OSGAttributeParticleFunction.h"

#include "OSGGaussianNormalDistribution1D.h"
#include "OSGCylinderDistribution3D.h"
#include "OSGLineDistribution3D.h"
#include "OSGSphereDistribution3D.h"


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void ClickToGenerate(const MouseEventUnrecPtr e);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);
Distribution3DRefPtr createAccelerationDistribution(void);
Distribution3DRefPtr createSizeDistribution(void);

ParticleSystemRefPtr ExampleParticleSystem;
QuadSequenceParticleSystemDrawerRefPtr ExampleParticleSystemDrawer;
RateParticleGeneratorRefPtr ExampleParticleGenerator;

// Function that figues out which image in the sequence to use.
AttributeParticleFunctionRefPtr AttributeFunc;

// Create a class to allow for the use of the Ctrl+q
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
    {	// changes the sequence ordering
        if (e->getKey() == KeyEvent::KEY_1)
		{
			AttributeFunc->setSequenceOrder(AttributeParticleFunction::DIRECT);
		}		
		else if (e->getKey() == KeyEvent::KEY_3)
		{
			AttributeFunc->setSequenceOrder(AttributeParticleFunction::CUSTOM);
		}
		else return;
    }
};


class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
        if(e->getButton()== MouseEvent::BUTTON1)
        {
        }

        if(e->getButton()== MouseEvent::BUTTON3)
        {
        }
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
int main(int argc, char **argv)
{
    OSG::preloadSharedObject("OSGImageFileIO");
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

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

    // Creating the Particle System Material
	// Here, the image is loaded.  The entire image sequence is conatined in one image,
	// which reduces texture memory overhead and runs faster.
    TextureObjChunkRefPtr QuadTextureChunk = TextureObjChunk::create();
    ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/SpriteExplode.png");    
    QuadTextureChunk->setImage(LoadedImage);

    TextureEnvChunkRefPtr QuadTextureEnvChunk = TextureEnvChunk::create();
    QuadTextureEnvChunk->setEnvMode(GL_MODULATE);

    BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
    PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    MaterialChunkRefPtr PSMaterialChunk = MaterialChunk::create();
    PSMaterialChunk->setAmbient(Color4f(0.3f,0.0f,0.0f,1.0f));
    PSMaterialChunk->setDiffuse(Color4f(0.7f,0.0f,0.0f,1.0f));
    PSMaterialChunk->setSpecular(Color4f(0.9f,0.0f,0.0f,1.0f));
    PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

    ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
    PSMaterial->addChunk(QuadTextureChunk);
    PSMaterial->addChunk(QuadTextureEnvChunk);
    PSMaterial->addChunk(PSMaterialChunk);
    PSMaterial->addChunk(PSBlendChunk);

    //Particle System
    ExampleParticleSystem = OSG::ParticleSystem::create();
    ExampleParticleSystem->attachUpdateListener(TutorialWindow);

	//Attribute Particle Function.  Controls which image is shown when, based on the attribute of a particle.
	AttributeFunc = OSG::AttributeParticleFunction::create();
	AttributeFunc->setSequenceOrder(AttributeParticleFunction::DIRECT); 
	AttributeFunc->setAttribute("seq");
	/*
		Here, a custom sequence for the image ordering is assembled.  The image sequence will be shown in 
		the order specified here.  Once the end of the sequence is reached, the sequence repeats.
	*/
	AttributeFunc->editMFCustomSequence()->push_back(0);
	AttributeFunc->editMFCustomSequence()->push_back(1);
	AttributeFunc->editMFCustomSequence()->push_back(2);
	AttributeFunc->editMFCustomSequence()->push_back(3);
	AttributeFunc->editMFCustomSequence()->push_back(4);
	AttributeFunc->editMFCustomSequence()->push_back(5);
	AttributeFunc->editMFCustomSequence()->push_back(4);
	AttributeFunc->editMFCustomSequence()->push_back(3);
	AttributeFunc->editMFCustomSequence()->push_back(2);
	AttributeFunc->editMFCustomSequence()->push_back(1);

	//Particle System Drawer - 
    ExampleParticleSystemDrawer = OSG::QuadSequenceParticleSystemDrawer::create();
	// image dimensions (in pixels) are required if there is a border on the images.
	ExampleParticleSystemDrawer->setImageDimensions(OSG::Vec2us(780,520));
	// The "dimensions" of the sequence contained in the image.  For this image,
	// there are 3 images in the "x" direction, and two in the "y" direction, for a 
	// total of 6.
	ExampleParticleSystemDrawer->setSequenceDimensions(OSG::Vec2b(3,2));
	// width of the border on each side of the image, in pixels.
	ExampleParticleSystemDrawer->setBorderOffsets(OSG::Vec2b(0,0));
	// this is the age function we just created above.
	ExampleParticleSystemDrawer->setSequenceFunction(AttributeFunc);

    ExampleParticleGenerator = OSG::RateParticleGenerator::create();
    //Attach the function objects to the Generator
    ExampleParticleGenerator->setPositionDistribution(createPositionDistribution());
    ExampleParticleGenerator->setLifespanDistribution(createLifespanDistribution());
    ExampleParticleGenerator->setVelocityDistribution(createVelocityDistribution());
    ExampleParticleGenerator->setAccelerationDistribution(createAccelerationDistribution());
    ExampleParticleGenerator->setSizeDistribution(createSizeDistribution());
	ExampleParticleGenerator->setGenerationRate(2.0f);

    //Particle System Node
    ParticleSystemCoreRefPtr ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);
	ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);
	
    NodeRefPtr ParticleNode = OSG::Node::create();
    ParticleNode->setCore(ParticleNodeCore);

	for(UInt32 i(0); i < 6; i++)
	{
	// adding some particles, and setting their attributes.
		ExampleParticleSystem->addParticle(Pnt3f(2*i,0.0,0.0),
									   Vec3f(0.0,1.0,0.0),
									   Color4f(1.0,1.0,1.0,1.0),
									   Vec3f(1.0,1.0,1.0),
									   -1,
									   Vec3f(0.0,0.0,0.0),
									   Vec3f(0.0,0.0,0.0));

		ExampleParticleSystem->setAttribute("seq",i,i);
	}


    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(ParticleNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "05b - QuadSequenceParticleDrawer");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}


// Callback functions

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

Distribution3DRefPtr createPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(0.0);
    TheSphereDistribution->setOuterRadius(3.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution3DRefPtr createVelocityDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(2.0);
    TheSphereDistribution->setOuterRadius(5.0);
    TheSphereDistribution->setMinTheta(-1.5);
    TheSphereDistribution->setMaxTheta(1.5);
    TheSphereDistribution->setMinZ(0.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution1DRefPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(10.0f);
    TheLifespanDistribution->setStandardDeviation(2.0);

    return TheLifespanDistribution;
}

Distribution3DRefPtr createAccelerationDistribution(void)
{

    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,0.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createSizeDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.2,0.2,1.0));
    TheLineDistribution->setPoint2(Pnt3f(1.0,1.0,1.0));

    return TheLineDistribution;
}
