// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"

// Input
#include "OSGKeyListener.h"

#include "OSGBlendChunk.h"
#include "OSGPointChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGLineParticleSystemDrawer.h"
#include "OSGQuadParticleSystemDrawer.h"
#include "OSGDiscParticleSystemDrawer.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

//Particle System Drawer
ParticleSystemCoreRefPtr ParticleNodeCore;
PointParticleSystemDrawerRefPtr ExamplePointParticleSystemDrawer;
LineParticleSystemDrawerRefPtr ExampleLineParticleSystemDrawer;
QuadParticleSystemDrawerRefPtr ExampleQuadParticleSystemDrawer;
DiscParticleSystemDrawerRefPtr ExampleDiscParticleSystemDrawer;

bool StatisticsOn(false);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            TutorialWindow->closeWindow();
        }
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
        switch(e->getKey())
        {
            case KeyEvent::KEY_1: // Use the Point Drawer
                ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
                break;

            case KeyEvent::KEY_2://Use the Line Drawer for 2
                ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
                break;

            case KeyEvent::KEY_3://Use the Quad Drawer for 3
                ParticleNodeCore->setDrawer(ExampleQuadParticleSystemDrawer);
                break;
            case KeyEvent::KEY_4://Use the Disc Drawer for 4
                ParticleNodeCore->setDrawer(ExampleDiscParticleSystemDrawer);
                break;
            case KeyEvent::KEY_S://Toggle the statistics
                StatisticsOn = !StatisticsOn;
                mgr->setStatistics(StatisticsOn);
                break;
        }
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

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    //Add Key Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);
    //Add Mouse Listeners
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);

    //Particle System Material
    PointChunkRefPtr PSPointChunk = PointChunk::create();
    PSPointChunk->setSize(5.0f);
    PSPointChunk->setSmooth(true);

    BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
    PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
    PSMaterialChunkChunk->setAmbient(Color4f(0.5f,0.5f,0.5f,0.3f));
    PSMaterialChunkChunk->setDiffuse(Color4f(0.8f,0.8f,0.8f,0.3f));
    PSMaterialChunkChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,0.3f));
    PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

    ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
    PSMaterial->addChunk(PSPointChunk);
    PSMaterial->addChunk(PSMaterialChunkChunk);
    PSMaterial->addChunk(PSBlendChunk);


    //Particle System
    ParticleSystemRefPtr ExampleParticleSystem = ParticleSystem::create();
    for(UInt32 i(0) ; i<10 ; ++i)
    {
        ExampleParticleSystem->addParticle(Pnt3f(i,i,i),
                                           Vec3f(0.0,0.0f,1.0f),
                                           Color4f(1.0,0.0,0.0,0.5), 
                                           Vec3f(1.0,1.0,1.0), 
                                           -1.0, 
                                           Vec3f(0.0f,0.0f,0.0f), //Velocity
                                           Vec3f(0.0f,0.0f,0.0f)
                                          );
    }
    ExampleParticleSystem->attachUpdateListener(TutorialWindow);

    //Particle System Drawer
    //Point
    ExamplePointParticleSystemDrawer = PointParticleSystemDrawer::create();
    //ExamplePointParticleSystemDrawer->setForcePerParticleSizing(true);

    //Line
    ExampleLineParticleSystemDrawer = LineParticleSystemDrawer::create();
    ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_NORMAL);//DIRECTION_VELOCITY_CHANGE);
    ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
    //Quad
    ExampleQuadParticleSystemDrawer = QuadParticleSystemDrawer::create();

    //Disc
    ExampleDiscParticleSystemDrawer = DiscParticleSystemDrawer::create();
    ExampleDiscParticleSystemDrawer->setSegments(16);
    ExampleDiscParticleSystemDrawer->setCenterAlpha(1.0);
    ExampleDiscParticleSystemDrawer->setEdgeAlpha(0.0);

    //Particle System Node
    ParticleNodeCore = ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);

    NodeRefPtr ParticleNode = Node::create();
    ParticleNode->setCore(ParticleNodeCore);


    // Make Main Scene Node
    NodeRefPtr scene = Node::create();
    scene->setCore(Group::create());
    scene->addChild(ParticleNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "01ParticleSystemDrawers");

    commitChanges();

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

