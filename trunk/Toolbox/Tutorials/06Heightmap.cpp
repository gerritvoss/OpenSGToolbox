// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive scene viewer.
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGSimpleMaterial.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGGeoFunctions.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Heightmap Geometry
#include <OpenSG/Toolbox/OSGHeightmapGeometry.h>
#include <OpenSG/Toolbox/OSGPerlinNoise.h>


#include <OpenSG/Toolbox/OSGLambertMaterial.h>
#include <OpenSG/Toolbox/OSGBlinnMaterial.h>
#include <OpenSG/Toolbox/OSGPhong2Material.h>
#include <OpenSG/Toolbox/OSGAnisotropicMaterial.h>
#include <OpenSG/Toolbox/OSGRampMaterial.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;
bool statFlag(false);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }

	   switch(e.getKey())
	   {
	   case KeyEvent::KEY_S:
		   statFlag = !statFlag;
		   mgr->setStatistics(statFlag);
		   break;
	   }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
    }
    virtual void mouseExited(const MouseEvent& e)
    {
    }
    virtual void mousePressed(const MouseEvent& e)
    {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
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

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

	
    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindowEventProducer->getWindow());


    //Lambert Material
    LambertMaterialPtr TheLambertMat = LambertMaterial::create();
    beginEditCP(TheLambertMat, LambertMaterial::ColorFieldMask | LambertMaterial::AmbientColorFieldMask | LambertMaterial::DiffuseFieldMask);
        TheLambertMat->setColor(Color3f(0.0,1.0,0.0));
        TheLambertMat->setAmbientColor(Color3f(0.0,0.0,0.0));
        TheLambertMat->setDiffuse(0.85);
    endEditCP(TheLambertMat, LambertMaterial::ColorFieldMask | LambertMaterial::AmbientColorFieldMask | LambertMaterial::DiffuseFieldMask);
    

    //Blinn Material
    BlinnMaterialPtr TheBlinnMat = BlinnMaterial::create();
    beginEditCP(TheBlinnMat, BlinnMaterial::ColorFieldMask | BlinnMaterial::AmbientColorFieldMask | BlinnMaterial::DiffuseFieldMask
         | BlinnMaterial::SpecularColorFieldMask | BlinnMaterial::SpecularEccentricityFieldMask | BlinnMaterial::SpecularRolloffFieldMask);
        TheBlinnMat->setColor(Color3f(1.0,0.0,0.0));
        TheBlinnMat->setAmbientColor(Color3f(0.0,0.0,0.0));
        TheBlinnMat->setSpecularColor(Color3f(0.0,0.0,1.0));
        TheBlinnMat->setSpecularEccentricity(0.35);
        TheBlinnMat->setSpecularRolloff(0.85);
        TheBlinnMat->setDiffuse(0.65);
    endEditCP(TheBlinnMat, BlinnMaterial::ColorFieldMask | BlinnMaterial::AmbientColorFieldMask | BlinnMaterial::DiffuseFieldMask
         | BlinnMaterial::SpecularColorFieldMask | BlinnMaterial::SpecularEccentricityFieldMask | BlinnMaterial::SpecularRolloffFieldMask);
    
    //Phong Material
    Phong2MaterialPtr ThePhongMat = Phong2Material::create();
    beginEditCP(ThePhongMat, Phong2Material::ColorFieldMask | Phong2Material::AmbientColorFieldMask | Phong2Material::DiffuseFieldMask
         | Phong2Material::SpecularColorFieldMask | Phong2Material::SpecularCosinePowerFieldMask);
        ThePhongMat->setColor(Color3f(1.0,0.0,0.0));
        ThePhongMat->setAmbientColor(Color3f(0.0,0.0,0.0));
        ThePhongMat->setSpecularColor(Color3f(0.0,0.0,1.0));
        ThePhongMat->setSpecularCosinePower(50.0);
        ThePhongMat->setDiffuse(0.65);
    endEditCP(ThePhongMat, Phong2Material::ColorFieldMask | Phong2Material::AmbientColorFieldMask | Phong2Material::DiffuseFieldMask
         | Phong2Material::SpecularColorFieldMask | Phong2Material::SpecularCosinePowerFieldMask);

    //Anisotropic Material
    AnisotropicMaterialPtr TheAnisotropicMat = AnisotropicMaterial::create();
    beginEditCP(TheAnisotropicMat, AnisotropicMaterial::ColorFieldMask | AnisotropicMaterial::AmbientColorFieldMask | AnisotropicMaterial::DiffuseFieldMask
         | AnisotropicMaterial::SpecularColorFieldMask | AnisotropicMaterial::SpecularRoughnessFieldMask | AnisotropicMaterial::SpecularFresnelIndexFieldMask
          | AnisotropicMaterial::SpecularSpreadXFieldMask | AnisotropicMaterial::SpecularSpreadYFieldMask);
        TheAnisotropicMat->setColor(Color3f(1.0,0.0,0.0));
        TheAnisotropicMat->setAmbientColor(Color3f(0.0,0.0,0.0));
        TheAnisotropicMat->setDiffuse(0.65);
        TheAnisotropicMat->setSpecularColor(Color3f(0.0,0.0,1.0));
        TheAnisotropicMat->setSpecularRoughness(32.0);
        TheAnisotropicMat->setSpecularFresnelIndex(0.85);
        TheAnisotropicMat->setSpecularSpreadX(1.0);
        TheAnisotropicMat->setSpecularSpreadY(1.0);
    endEditCP(TheAnisotropicMat, AnisotropicMaterial::ColorFieldMask | AnisotropicMaterial::AmbientColorFieldMask | AnisotropicMaterial::DiffuseFieldMask
         | AnisotropicMaterial::SpecularColorFieldMask | AnisotropicMaterial::SpecularRoughnessFieldMask | AnisotropicMaterial::SpecularFresnelIndexFieldMask
          | AnisotropicMaterial::SpecularSpreadXFieldMask | AnisotropicMaterial::SpecularSpreadYFieldMask);

    //Anisotropic Material
    RampMaterialPtr TheRampMat = RampMaterial::create();
    beginEditCP(TheRampMat);
        ////Color
        //TheRampMat->setRampSource(RampMaterial::RAMP_SOURCE_FACING_ANGLE);
        //TheRampMat->getColors().push_back(Color3f(1.0,0.0,0.0));
        //TheRampMat->getColorPositions().push_back(0.4);
        //TheRampMat->getColorInterpolations().push_back(RampMaterial::RAMP_INTERPOLATION_SMOOTH);
        //TheRampMat->getColors().push_back(Color3f(0.0,1.0,0.0));
        //TheRampMat->getColorPositions().push_back(1.0);
        
        ////Transparency
        //TheRampMat->getTransparencies().push_back(Color3f(0.0,0.0,0.0));
        //TheRampMat->getTransparencyPositions().push_back(0.83);
        //TheRampMat->getTransparencyInterpolations().push_back(RampMaterial::RAMP_INTERPOLATION_SMOOTH);
        //TheRampMat->getTransparencies().push_back(Color3f(1.0,1.0,1.0));
        //TheRampMat->getTransparencyPositions().push_back(1.0);

        //TheRampMat->setAmbientColor(Color3f(0.0,0.0,0.0));
        //TheRampMat->setDiffuse(0.65);
        //TheRampMat->setSpecularity(1.0);
        //TheRampMat->setSpecularEccentricity(0.8);
        //TheRampMat->getSpecularColors().push_back(Color3f(1.0,1.0,1.0));
        //TheRampMat->getSpecularColorPositions().push_back(0.95);
        //TheRampMat->getSpecularColorInterpolations().push_back(RampMaterial::RAMP_INTERPOLATION_SMOOTH);
        //TheRampMat->getSpecularColors().push_back(Color3f(0.0,0.0,1.0));
        //TheRampMat->getSpecularColorPositions().push_back(1.0);
        //TheRampMat->getSpecularRolloffs().push_back(1.0);
    endEditCP(TheRampMat);


	//Load in the Heightmap Image
	ImagePtr PerlinNoiseImage = createPerlinImage(Vec2s(256,256), Vec2f(10.0f,10.0f),0.5f,1.0f,Vec2f(0.0f,0.0f),0.25f,6,PERLIN_INTERPOLATE_COSINE,false,Image::OSG_L_PF, Image::OSG_UINT8_IMAGEDATA);

	//Make the Heightmap Geometry
	HeightmapGeometryPtr TutorialHeightmapGeo = HeightmapGeometry::create();
	beginEditCP(TutorialHeightmapGeo, HeightmapGeometry::HeightImageFieldMask | HeightmapGeometry::DimensionsFieldMask | HeightmapGeometry::SegmentsFieldMask | HeightmapGeometry::ScaleFieldMask | HeightmapGeometry::OffsetFieldMask | HeightmapGeometry::MaterialFieldMask);
		TutorialHeightmapGeo->setHeightImage(PerlinNoiseImage);
		TutorialHeightmapGeo->setDimensions(Vec2f(200.0,200.0));
		TutorialHeightmapGeo->setSegments(Vec2f(150.0,150.0));
		TutorialHeightmapGeo->setScale(20.0);
		TutorialHeightmapGeo->setOffset(0.0);
		TutorialHeightmapGeo->setMaterial( TheRampMat );
	endEditCP(TutorialHeightmapGeo, HeightmapGeometry::HeightImageFieldMask | HeightmapGeometry::DimensionsFieldMask | HeightmapGeometry::SegmentsFieldMask | HeightmapGeometry::ScaleFieldMask | HeightmapGeometry::OffsetFieldMask | HeightmapGeometry::MaterialFieldMask);

    calcVertexTangents(TutorialHeightmapGeo,0,Geometry::TexCoords7FieldId, Geometry::TexCoords6FieldId);

    //Make the Heightmap Node
    NodePtr TutorialHeightmapNode = Node::create();
    beginEditCP(TutorialHeightmapNode, Node::CoreFieldMask);
		TutorialHeightmapNode->setCore(TutorialHeightmapGeo);
    endEditCP  (TutorialHeightmapNode, Node::CoreFieldMask);

    //Make a SphereNode
    GeometryPtr SphereGeo = makeSphereGeo(2,50.0);
    //GeometryPtr SphereGeo = makeCylinderGeo(50,20.0, 16,true,true,true);
    beginEditCP(SphereGeo, Geometry::MaterialFieldMask);
		SphereGeo->setMaterial(TheRampMat);
    endEditCP  (SphereGeo, Geometry::MaterialFieldMask);
    calcVertexTangents(SphereGeo,0,Geometry::TexCoords7FieldId, Geometry::TexCoords6FieldId);

    NodePtr SphereNode = Node::create();
    beginEditCP(SphereNode, Node::CoreFieldMask);
		SphereNode->setCore(SphereGeo);
    endEditCP  (SphereNode, Node::CoreFieldMask);

    //Make Main Scene Node
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
		scene->setCore(Group::create());
 
        // add the torus as a child
        scene->addChild(TutorialHeightmapNode);
        scene->addChild(SphereNode);
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    
    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "06Heightmap");

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

