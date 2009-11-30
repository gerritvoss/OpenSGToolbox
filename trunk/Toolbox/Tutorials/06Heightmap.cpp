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
#include <OpenSG/OSGPointChunk.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSpotLight.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTextureChunk.h>

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
TransformPtr ThePointLightBeaconTransform;
RampMaterialPtr TheRampMat;
BlinnMaterialPtr TheBlinnMat;

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }

	   switch(e->getKey())
	   {
	   case KeyEvent::KEY_S:
		   statFlag = !statFlag;
		   mgr->setStatistics(statFlag);
		   break;
       case KeyEvent::KEY_EQUALS:
           {
               Vec3f Translation;
               Quaternion Rotation;
               Vec3f Scale;
               Quaternion ScaleOrient;
               Matrix ThePointLightMat = ThePointLightBeaconTransform->getMatrix();
               ThePointLightMat.getTransform(Translation,Rotation,Scale,ScaleOrient);
               Translation = Translation + Vec3f(0.0,10.0,0.0);
               ThePointLightMat.setTranslate(Translation);
               beginEditCP(ThePointLightBeaconTransform);
                   ThePointLightBeaconTransform->setMatrix(ThePointLightMat);
               endEditCP(ThePointLightBeaconTransform);
           }
           break;
       case KeyEvent::KEY_MINUS:
           {
               Vec3f Translation;
               Quaternion Rotation;
               Vec3f Scale;
               Quaternion ScaleOrient;
               Matrix ThePointLightMat = ThePointLightBeaconTransform->getMatrix();
               ThePointLightMat.getTransform(Translation,Rotation,Scale,ScaleOrient);
               Translation = Translation + Vec3f(0.0,-10.0,0.0);
               ThePointLightMat.setTranslate(Translation);
               beginEditCP(ThePointLightBeaconTransform);
                   ThePointLightBeaconTransform->setMatrix(ThePointLightMat);
               endEditCP(ThePointLightBeaconTransform);
           }
           break;
       case KeyEvent::KEY_T:
            beginEditCP(TheBlinnMat, BlinnMaterial::DiffuseTextureFieldMask);
            endEditCP(TheBlinnMat, BlinnMaterial::DiffuseTextureFieldMask);
           break;
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

    //Make a SphereNode for the point light
    LambertMaterialPtr TheLightMat = LambertMaterial::create();
    beginEditCP(TheLightMat, LambertMaterial::IncandescenceFieldMask);
        TheLightMat->setIncandescence(Color3f(1.0,1.0,1.0));
    endEditCP(TheLightMat, LambertMaterial::IncandescenceFieldMask);

    GeometryPtr LightSphereGeo = makeSphereGeo(2,2.0);
    beginEditCP(LightSphereGeo, Geometry::MaterialFieldMask);
        LightSphereGeo->setMaterial(TheLightMat);
    endEditCP  (LightSphereGeo, Geometry::MaterialFieldMask);

    NodePtr LightSphereNode = Node::create();
    beginEditCP(LightSphereNode, Node::CoreFieldMask);
		LightSphereNode->setCore(LightSphereGeo);
    endEditCP  (LightSphereNode, Node::CoreFieldMask);

    //Create the beacon for the Point Light
    Matrix ThePointLightMat;
    ThePointLightMat.setTranslate(Vec3f(0.0,100.0,0.0));
    
    ThePointLightBeaconTransform = Transform::create();
    beginEditCP(ThePointLightBeaconTransform);
        ThePointLightBeaconTransform->setMatrix(ThePointLightMat);
    endEditCP(ThePointLightBeaconTransform);

    NodePtr ThePointLightBeaconNode = Node::create();
    beginEditCP(ThePointLightBeaconNode);
        ThePointLightBeaconNode->setCore(ThePointLightBeaconTransform);
        ThePointLightBeaconNode->addChild(LightSphereNode);
    endEditCP(ThePointLightBeaconNode);

    //Set the light properties desired
    PointLightPtr ThePointLight = PointLight::create();
    beginEditCP(ThePointLight);
        ThePointLight->setAmbient(0.3,0.3,0.3,0.3);
        ThePointLight->setDiffuse(1.0,1.0,1.0,1.0);
        ThePointLight->setSpecular(1.0,1.0,1.0,1.0);
        ThePointLight->setBeacon(ThePointLightBeaconNode);
    endEditCP(ThePointLight);

    NodePtr ThePointLightNode = Node::create();
    beginEditCP(ThePointLightNode);
        ThePointLightNode->setCore(ThePointLight);
    endEditCP(ThePointLightNode);
    
    //Set the light properties desired
    SpotLightPtr TheSpotLight = SpotLight::create();
    beginEditCP(TheSpotLight);
        TheSpotLight->setAmbient(0.3,0.3,0.3,0.3);
        TheSpotLight->setDiffuse(1.0,1.0,1.0,1.0);
        TheSpotLight->setSpecular(1.0,1.0,1.0,1.0);
        TheSpotLight->setBeacon(ThePointLightBeaconNode);
        TheSpotLight->setDirection(Vec3f(0.0,-1.0,0.0));
        TheSpotLight->setSpotExponent(5.0);
        TheSpotLight->setSpotCutOff(1.1);
    endEditCP(TheSpotLight);

    NodePtr TheSpotLightNode = Node::create();
    beginEditCP(TheSpotLightNode);
        TheSpotLightNode->setCore(TheSpotLight);
    endEditCP(TheSpotLightNode);

	//Load in the Heightmap Image
	ImagePtr PerlinNoiseImage = createPerlinImage(Vec2s(256,256), Vec2f(10.0f,10.0f),0.5f,1.0f,Vec2f(0.0f,0.0f),0.25f,6,PERLIN_INTERPOLATE_COSINE,false,Image::OSG_L_PF, Image::OSG_UINT8_IMAGEDATA);

    TextureChunkPtr TheTextureChunk = TextureChunk::create();
    beginEditCP(TheTextureChunk);
        TheTextureChunk->setImage(PerlinNoiseImage);
    endEditCP(TheTextureChunk);

    //Lambert Material
    LambertMaterialPtr TheLambertMat = LambertMaterial::create();
    beginEditCP(TheLambertMat, LambertMaterial::ColorFieldMask | LambertMaterial::AmbientColorFieldMask | LambertMaterial::DiffuseFieldMask
                              | LambertMaterial::NumLightsFieldMask | LambertMaterial::DiffuseTextureFieldMask);
        TheLambertMat->setColor(Color3f(0.0,1.0,0.0));
        TheLambertMat->setAmbientColor(Color3f(1.0,0.0,0.0));
        TheLambertMat->setDiffuse(0.5);
        TheLambertMat->setNumLights(1);
    endEditCP(TheLambertMat, LambertMaterial::ColorFieldMask | LambertMaterial::AmbientColorFieldMask | LambertMaterial::DiffuseFieldMask
                              | LambertMaterial::NumLightsFieldMask | LambertMaterial::DiffuseTextureFieldMask);
    

    //Blinn Material
    TheBlinnMat = BlinnMaterial::create();
    beginEditCP(TheBlinnMat, BlinnMaterial::ColorFieldMask | BlinnMaterial::AmbientColorFieldMask | BlinnMaterial::DiffuseFieldMask
         | BlinnMaterial::SpecularColorFieldMask | BlinnMaterial::SpecularEccentricityFieldMask | BlinnMaterial::SpecularRolloffFieldMask | BlinnMaterial::DiffuseTextureFieldMask);
        TheBlinnMat->setColor(Color3f(1.0,0.0,0.0));
        TheBlinnMat->setAmbientColor(Color3f(0.0,0.0,0.0));
        TheBlinnMat->setSpecularColor(Color3f(0.0,0.0,1.0));
        TheBlinnMat->setSpecularEccentricity(0.35);
        TheBlinnMat->setSpecularRolloff(0.85);
        TheBlinnMat->setDiffuse(0.65);
        TheBlinnMat->setDiffuseTexture(TheTextureChunk);
    endEditCP(TheBlinnMat, BlinnMaterial::ColorFieldMask | BlinnMaterial::AmbientColorFieldMask | BlinnMaterial::DiffuseFieldMask
         | BlinnMaterial::SpecularColorFieldMask | BlinnMaterial::SpecularEccentricityFieldMask | BlinnMaterial::SpecularRolloffFieldMask | BlinnMaterial::DiffuseTextureFieldMask);
    
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

    PointChunkPtr TempChunk = PointChunk::create();
    //addRefCP(TempChunk);

    //Anisotropic Material
    TheRampMat = RampMaterial::create();
    beginEditCP(TheRampMat);
        //Color
        TheRampMat->setRampSource(RampMaterial::RAMP_SOURCE_FACING_ANGLE);
        TheRampMat->getColors().push_back(Color3f(1.0,0.0,0.0));
        TheRampMat->getColorPositions().push_back(0.4);
        TheRampMat->getColorInterpolations().push_back(RampMaterial::RAMP_INTERPOLATION_SMOOTH);
        TheRampMat->getColors().push_back(Color3f(0.0,1.0,0.0));
        TheRampMat->getColorPositions().push_back(1.0);
        
        //Transparency
        TheRampMat->getTransparencies().push_back(Color3f(0.0,0.0,0.0));
        TheRampMat->getTransparencyPositions().push_back(0.83);
        TheRampMat->getTransparencyInterpolations().push_back(RampMaterial::RAMP_INTERPOLATION_SMOOTH);
        TheRampMat->getTransparencies().push_back(Color3f(1.0,1.0,1.0));
        TheRampMat->getTransparencyPositions().push_back(1.0);

        TheRampMat->setAmbientColor(Color3f(0.0,0.0,0.0));
        TheRampMat->setSpecularity(1.0);
        TheRampMat->setSpecularEccentricity(0.8);
        TheRampMat->getSpecularColors().push_back(Color3f(1.0,1.0,1.0));
        TheRampMat->getSpecularColorPositions().push_back(0.95);
        TheRampMat->getSpecularColorInterpolations().push_back(RampMaterial::RAMP_INTERPOLATION_SMOOTH);
        TheRampMat->getSpecularColors().push_back(Color3f(0.0,0.0,1.0));
        TheRampMat->getSpecularColorPositions().push_back(1.0);
        TheRampMat->getSpecularRolloffs().push_back(1.0);
        TheRampMat->getExtraChunks().push_back(TempChunk);
    endEditCP(TheRampMat);



	//Make the Heightmap Geometry
	HeightmapGeometryPtr TutorialHeightmapGeo = HeightmapGeometry::create();
	beginEditCP(TutorialHeightmapGeo, HeightmapGeometry::HeightImageFieldMask | HeightmapGeometry::DimensionsFieldMask | HeightmapGeometry::SegmentsFieldMask | HeightmapGeometry::ScaleFieldMask | HeightmapGeometry::OffsetFieldMask | HeightmapGeometry::MaterialFieldMask);
		TutorialHeightmapGeo->setHeightImage(PerlinNoiseImage);
		TutorialHeightmapGeo->setDimensions(Vec2f(200.0,200.0));
		TutorialHeightmapGeo->setSegments(Vec2f(150.0,150.0));
		TutorialHeightmapGeo->setScale(30.0);
		TutorialHeightmapGeo->setOffset(0.0);
		TutorialHeightmapGeo->setMaterial( TheBlinnMat );
	endEditCP(TutorialHeightmapGeo, HeightmapGeometry::HeightImageFieldMask | HeightmapGeometry::DimensionsFieldMask | HeightmapGeometry::SegmentsFieldMask | HeightmapGeometry::ScaleFieldMask | HeightmapGeometry::OffsetFieldMask | HeightmapGeometry::MaterialFieldMask);

    calcVertexNormals(TutorialHeightmapGeo);
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
		SphereGeo->setMaterial(TheLambertMat);
    endEditCP  (SphereGeo, Geometry::MaterialFieldMask);
    calcVertexNormals(SphereGeo);
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
        //scene->addChild(SphereNode);
        scene->addChild(ThePointLightBeaconNode);
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Add the scene to the Light Nodes
    //beginEditCP(ThePointLightNode, Node::ChildrenFieldMask);
        //ThePointLightNode->addChild(scene);
    //endEditCP(ThePointLightNode, Node::ChildrenFieldMask);


    //// tell the manager what to manage
    //mgr->setRoot  (ThePointLightNode);

    beginEditCP(TheSpotLightNode, Node::ChildrenFieldMask);
        TheSpotLightNode->addChild(scene);
    endEditCP(TheSpotLightNode, Node::ChildrenFieldMask);


    // tell the manager what to manage
    mgr->setRoot  (TheSpotLightNode);
    mgr->turnHeadlightOff();

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

