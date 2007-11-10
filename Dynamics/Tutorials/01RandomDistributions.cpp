// OpenSG Tutorial Example: Creating a Button
//
// This tutorial explains how to edit the basic features of
// a button created in the OSG User Interface library.
// 
// Includes: button size, button font and text, button color, button border,
// and adding a button to a scene.


// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGParticles.h>
#include <OpenSG/OSGSimpleMaterial.h>

#include <OpenSG/OSGGeoPropertyBase.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Dynamics Distributions
#include <OpenSG/Dynamics/OSGLineDistribution3D.h>
#include <OpenSG/Dynamics/OSGBoxDistribution3D.h>
#include <OpenSG/Dynamics/OSGDiscDistribution3D.h>
#include <OpenSG/Dynamics/OSGCylinderDistribution3D.h>
#include <OpenSG/Dynamics/OSGSphereDistribution3D.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution3D.h>
#include <OpenSG/Dynamics/OSGTriDistribution3D.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void display(void);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);


    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();


   // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);


    //Make The Distribution
    //Line Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(Pnt3f(-10.0,0.0,0.0));
      TheLineDistribution->setPoint2(Pnt3f(10.0,0.0,0.0));
    endEditCP(TheLineDistribution);
    
    //Box Distribution
    BoxDistribution3DPtr TheBoxDistribution = BoxDistribution3D::create();
    beginEditCP(TheBoxDistribution);
      TheBoxDistribution->setMinPoint(Pnt3f(-10.0,-10.0,-10.0));
      TheBoxDistribution->setMaxPoint(Pnt3f(10.0,10.0,10.0));
      TheBoxDistribution->setSurfaceOrVolume(BoxDistribution3D::SURFACE);
    endEditCP(TheBoxDistribution);

    //Disc Distribution
    DiscDistribution3DPtr TheDiscDistribution = DiscDistribution3D::create();
    beginEditCP(TheDiscDistribution);
      TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheDiscDistribution->setInnerRadius(10.0);
      TheDiscDistribution->setOuterRadius(20.0);
      TheDiscDistribution->setMinTheta(0.0);
      TheDiscDistribution->setMaxTheta(6.283185307);
      TheDiscDistribution->setNormal(Vec3f(0.0,0.0,1.0));
      TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);
    endEditCP(TheDiscDistribution);

    //Cylinder Distribution
    CylinderDistribution3DPtr TheCylinderDistribution = CylinderDistribution3D::create();
    beginEditCP(TheCylinderDistribution);
      TheCylinderDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheCylinderDistribution->setInnerRadius(10.0);
      TheCylinderDistribution->setOuterRadius(20.0);
      TheCylinderDistribution->setMinTheta(0.0);
      TheCylinderDistribution->setMaxTheta(3.14159);
      TheCylinderDistribution->setHeight(40.0);
      TheCylinderDistribution->setNormal(Vec3f(0.0,0.0,1.0));
      TheCylinderDistribution->setSurfaceOrVolume(CylinderDistribution3D::SURFACE);
    endEditCP(TheCylinderDistribution);
    
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(10.0);
      TheSphereDistribution->setOuterRadius(20.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(3.14159);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
      TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);
    endEditCP(TheSphereDistribution);
    
    //Tri Distribution
    TriDistribution3DPtr TheTriDistribution = TriDistribution3D::create();
    beginEditCP(TheTriDistribution);
      TheTriDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
      TheTriDistribution->setPoint2(Pnt3f(-50.0,1000.0,0.0));
      TheTriDistribution->setPoint3(Pnt3f(50.0,1000.0,0.0));
      TheTriDistribution->setPoint3(Pnt3f(50.0,1000.0,0.0));
      TheTriDistribution->setSurfaceOrEdge(TriDistribution3D::SURFACE);
    endEditCP(TheTriDistribution);

    //GaussianNormal Distribution
    GaussianNormalDistribution3DPtr TheGaussianNormalDistribution = GaussianNormalDistribution3D::create();
    beginEditCP(TheGaussianNormalDistribution);
      TheGaussianNormalDistribution->setMean(Pnt3f(0.0,0.0,0.0));
      TheGaussianNormalDistribution->setStandardDeviationX(100.0);
      TheGaussianNormalDistribution->setStandardDeviationY(200.0);
      TheGaussianNormalDistribution->setStandardDeviationZ(100.0);
    endEditCP(TheGaussianNormalDistribution);

    LineDistribution3D::Output0DataType::RawType ReturnValue;

    FunctionPtr TheDistribution = TheTriDistribution;

    //Use the Distribution to generate Positions
    GeoPositionsPtr ParticlePositions = GeoPositions3f::create();
    UInt32 NumParticlesToGenerate(300);
    for(UInt32 i(0) ; i< NumParticlesToGenerate ; ++i)
    {
        ReturnValue = 
            LineDistribution3D::Output0DataType::dcast(
            TheDistribution->evaluate(Function::FunctionIOParameterVector()).front().getDataPtr()
            )->getData();
        ParticlePositions->addValue(ReturnValue);
    }
    
    //Create the particles Material
    SimpleMaterialPtr ParticleMaterial = SimpleMaterial::create();
    beginEditCP(ParticleMaterial);
        ParticleMaterial->setLit(false);
    endEditCP(ParticleMaterial);

    //Create the ParticleCore and set up its properties
    ParticlesPtr ParticlesCore = Particles::create();
    GeoColorsPtr ParticleColors = GeoColors3f::create();
    GeoNormalsPtr ParticleNormals = GeoNormals3f::create();
    beginEditCP(ParticlesCore);
      //Positions
      ParticlesCore->setPositions(ParticlePositions);
      //SecPositions
      ParticlesCore->setSecPositions(ParticlePositions);
      //Color
      ParticlesCore->setColors(ParticleColors);
      ParticleColors->addValue(Color3f(1.0,0.0,0.0));
      //Normal
      ParticlesCore->setNormals(ParticleNormals);
      ParticleNormals->addValue(Vec3f(0.0,0.0,1.0));
      //Sizes
      ParticlesCore->getSizes().addValue(Vec3f(4.0,4.0,4.0));
      //Draw Mode
      ParticlesCore->setMode(Particles::Points);
      //ParticlesCore->setMode(Particles::Lines);
      //ParticlesCore->setMode(Particles::ViewDirQuads);
      //ParticlesCore->setMode(Particles::ViewerQuads);
      //ParticlesCore->setMode(Particles::Arrows);
      //ParticlesCore->setMode(Particles::ViewerArrows);
      //ParticlesCore->setMode(Particles::Rectangles);
      //ParticlesCore->setMode(Particles::ShaderQuads);
      //ParticlesCore->setMode(Particles::ShaderStrips);

      ParticlesCore->setMaterial(ParticleMaterial);
    endEditCP(ParticlesCore);


    // Make Particles Node
    NodePtr ParticlesNode = Node::create();
    beginEditCP(ParticlesNode, Node::CoreFieldMask);
        ParticlesNode->setCore(ParticlesCore);
    endEditCP(ParticlesNode, Node::CoreFieldMask);


    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
        scene->addChild(ParticlesNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin);
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

void idle(void)
{
   glutPostRedisplay();
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:        
        {
            OSG::osgExit();
            exit(0);
        }
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG Dynamics Distributions");
    
    glutPositionWindow(50,50);
    glutReshapeWindow(800,800);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}
