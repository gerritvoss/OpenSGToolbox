// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"

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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

//Particle System Drawer
PointParticleSystemDrawer* ExamplePointDrawer;
LineParticleSystemDrawer* ExampleLineDrawer;
QuadParticleSystemDrawer* ExampleQuadDrawer;
DiscParticleSystemDrawer* ExampleDiscDrawer;

void keyTyped(KeyEventDetails* const details, SimpleSceneManager *mgr, ParticleSystemCore* const core)
{
    static bool StatisticsOn(false);
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }

    switch(details->getKey())
    {
        case KeyEventDetails::KEY_1: // Use the Point Drawer
            core->setDrawer(ExamplePointDrawer);
            break;

        case KeyEventDetails::KEY_2://Use the Line Drawer for 2
            core->setDrawer(ExampleLineDrawer);
            break;

        case KeyEventDetails::KEY_3://Use the Quad Drawer for 3
            core->setDrawer(ExampleQuadDrawer);
            break;
        case KeyEventDetails::KEY_4://Use the Disc Drawer for 4
            core->setDrawer(ExampleDiscDrawer);
            break;
        case KeyEventDetails::KEY_S://Toggle the statistics
            StatisticsOn = !StatisticsOn;
            mgr->setStatistics(StatisticsOn);
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

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));

        //Particle System Material
        PointChunkRecPtr PSPointChunk = PointChunk::create();
        PSPointChunk->setSize(5.0f);
        PSPointChunk->setSmooth(true);

        BlendChunkRecPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRecPtr PSMaterialChunkChunk = MaterialChunk::create();
        PSMaterialChunkChunk->setAmbient(Color4f(0.5f,0.5f,0.5f,0.3f));
        PSMaterialChunkChunk->setDiffuse(Color4f(0.8f,0.8f,0.8f,0.3f));
        PSMaterialChunkChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,0.3f));
        PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRecPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(PSPointChunk);
        PSMaterial->addChunk(PSMaterialChunkChunk);
        PSMaterial->addChunk(PSBlendChunk);


        //Particle System
        ParticleSystemRecPtr ExampleParticleSystem = ParticleSystem::create();
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
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        //Particle System Drawer
        //Point
        PointParticleSystemDrawerRecPtr ExamplePointParticleSystemDrawer = PointParticleSystemDrawer::create();
        ExamplePointDrawer = ExamplePointParticleSystemDrawer;
        //ExamplePointParticleSystemDrawer->setForcePerParticleSizing(true);

        //Line
        LineParticleSystemDrawerRecPtr ExampleLineParticleSystemDrawer = LineParticleSystemDrawer::create();
        ExampleLineDrawer = ExampleLineParticleSystemDrawer;
        ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_NORMAL);//DIRECTION_VELOCITY_CHANGE);
        ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
        //Quad
        QuadParticleSystemDrawerRecPtr ExampleQuadParticleSystemDrawer = QuadParticleSystemDrawer::create();
        ExampleQuadDrawer = ExampleQuadParticleSystemDrawer;

        //Disc
        DiscParticleSystemDrawerRecPtr ExampleDiscParticleSystemDrawer = DiscParticleSystemDrawer::create();
        ExampleDiscDrawer = ExampleDiscParticleSystemDrawer;
        ExampleDiscParticleSystemDrawer->setSegments(16);
        ExampleDiscParticleSystemDrawer->setCenterAlpha(1.0);
        ExampleDiscParticleSystemDrawer->setEdgeAlpha(0.0);

        //Particle System Node
        ParticleSystemCoreRecPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);

        NodeRecPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);


        // Make Main Scene Node
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(ParticleNode);

        sceneManager.setRoot(scene);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, &sceneManager, ParticleNodeCore.get()));

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01ParticleSystemDrawers");

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

