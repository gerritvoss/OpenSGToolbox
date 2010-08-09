/*************************************************
Welcome to the 04Background tutorial.  In this
tutorial, you will see how to use the 
different Backgrounds available and add them
to components.  The following Backgrounds
are introduced:

    ColorLayer
    CompoundLayer
	EmptyLayer
    GradientLayer
    MaterialLayer
    TextureLayer
    PatternLayer

Backgrounds are used simply to provide a background
for various components.  Using combinations, very
complex possibilities exist.  As with 03Border, the 
easiest way to understand the base differences
is to simply run this tutorial.

The following all are shown and explained
within this tutorial (note the specific
requirements of each Border are not listed
here):

All Backgrounds:
    Creating Background
	Setting Color
	Specifying style
	Adding Backgrounds to components


These tutorials contain potentially relevant
information:



*************************************************/




// OpenSG Tutorial Example: Creating a Layer
//
// This tutorial explains how to implement the 
// Layers offered by the OSG User Interface 
// library and how to modify their features.
// 
// Includes: explanations and examples of how to create
// and use the six different backgrounds included in the
// OSG User Interface library.
//
// Note that the Active Border and Layer are not set, 
// meaning that if pressed, the Buttons revert to the default
// settings for Layer and Border.


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// 04Layer Headers
#include "OSGLayers.h"
#include "OSGButton.h"
#include "OSGLineBorder.h"
#include "OSGFlowLayout.h"
#include "OSGLookAndFeelManager.h"
// Include Layer header files
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGImageFileHandler.h"


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

//Ctrl+q handler
void keyTyped(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
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

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
       
	    // Make Main Scene Node and add the Torus
        NodeRefPtr scene = OSG::Node::create();
            scene->setCore(OSG::Group::create());
            scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        /******************************************************

                Create the Layers.

        ******************************************************/

        ColorLayerRefPtr ExampleColorLayer = OSG::ColorLayer::create();
        CompoundLayerRefPtr ExampleCompoundLayer = OSG::CompoundLayer::create();
	    EmptyLayerRefPtr ExampleEmptyLayer = OSG::EmptyLayer::create();
        GradientLayerRefPtr ExampleGradientLayer = OSG::GradientLayer::create();
        MaterialLayerRefPtr ExampleMaterialLayer = OSG::MaterialLayer::create();
        TextureLayerRefPtr ExampleTextureLayer = OSG::TextureLayer::create();
        PatternLayerRefPtr ExamplePatternLayer = OSG::PatternLayer::create();
        GlassLayerRefPtr ExampleGlassLayer = OSG::GlassLayer::create();
        CompoundLayerRefPtr ExampleGlassCompoundLayer = OSG::CompoundLayer::create();

        /******************************************************

            The ColorLayer is a simple Layer
		    having just a Color to it.

		    -setColor(Color4f): Determine the Color of
			    the Layer.

        ******************************************************/

            ExampleColorLayer->setColor(Color4f(1.0,0.0,0.0,1.0));
    	
        /******************************************************

                The CompoundLayer allows you to 
			    combine multiple Backgrounds into one.

			    The Backgrounds are added sequentially;
			    so in this example the 
			    ExampleTextureLayer would be added 
			    first, and the ExampleGradientLayer
			    rendered on top of it.  

			    -getBackgrounds().push_back(BackgroundName):
				    Adds a Background to the 
				    CompoundBackground.

        ******************************************************/

            ExampleCompoundLayer->pushToBackgrounds(ExampleTextureLayer);
            ExampleCompoundLayer->pushToBackgrounds(ExampleGradientLayer);
    	
        /******************************************************

                The EmptyLayer is a Background
			    with no attributes.

        ******************************************************/

		    // Nothing!
    		
        /******************************************************

                The GradientLayer is a Background
			    which displays a gradient of Color.

			    -getColors().push_back(Color4f): Determines the 
				    starting Color for the gradient.
			    -getColors().push_back(Color4f): Determines the
				    ending Color for the gradient.
			    -setOrientation(ENUM): Determines the
				    gradient alignment.  Takes 
				    HORIZONTAL_ORIENTATION or 
				    VERTICAL_ORIENTATION arguments.

        ******************************************************/


            ExampleGradientLayer->editMFColors()->push_back(Color4f(1.0, 0.0, 0.0, 1.0));
            ExampleGradientLayer->editMFStops()->push_back(0.0);
            ExampleGradientLayer->editMFColors()->push_back(Color4f(0.0, 1.0, 0.0, 0.75));
            ExampleGradientLayer->editMFStops()->push_back(0.5);
            ExampleGradientLayer->editMFColors()->push_back(Color4f(0.0, 0.0, 1.0, 0.5));
            ExampleGradientLayer->editMFStops()->push_back(1.0);
            ExampleGradientLayer->setStartPosition(Vec2f(0.2f,0.2f));
            ExampleGradientLayer->setEndPosition(Vec2f(.6f,0.6f));
            ExampleGradientLayer->setSpreadMethod(GradientLayer::SPREAD_REFLECT);
    		
        /******************************************************

                The MaterialLayer is a Background
			    which is created using a Material (also
			    created here).

			    -setMaterial(MaterialName): Determine
				    which Material will be used to 
				    create the Background.

        ******************************************************/    
	    // Creates Material
        ChunkMaterialRefPtr LayerMaterial = ChunkMaterial::create();
        MaterialChunkRefPtr LayerMaterialChunk = MaterialChunk::create();
          LayerMaterialChunk->setAmbient(Color4f(1.0,0.0,0.0,1.0));
          LayerMaterialChunk->setDiffuse(Color4f(0.0,1.0,0.0,1.0));
          LayerMaterialChunk->setSpecular(Color4f(0.0,0.0,1.0,1.0));

            LayerMaterial->addChunk(LayerMaterialChunk);

	    // Edit MaterialLayer
            ExampleMaterialLayer->setMaterial(LayerMaterial);
    		
        /******************************************************

                The TextureLayer is a Background
			    which is created using a Texture (also
			    created here).

			    -setTexture(TextureName): Determine
				    which Texture will be used to 
				    create the Background.

        ******************************************************/   
	    // Creates Texture from Image
        TextureObjChunkRefPtr LayerTextureObjChunk = TextureObjChunk::create();
        ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/Checker.jpg");    
            LayerTextureObjChunk->setImage(LoadedImage);

	    // Edit TextureLayer
            ExampleTextureLayer->setTexture(LayerTextureObjChunk);

        /******************************************************

                The PatternLayer is a Background
			    which is created using a Texture (also
			    created here).

			    -setTexture(TextureName): Determine
				    which Texture will be used to 
				    create the Background.
			    -setPatternSize(Vec2f):
			    -setVerticalAlignment():
			    -setHorizontalAlignment():
			    -setHorizontalRepeat():
			    -setVerticalRepeat():
			    -setHorizontalRepeatValue():
			    -setVerticalRepeatValue():

        ******************************************************/  
        
       TextureObjChunkRefPtr LayerPatternChunk = TextureObjChunk::create();
       //ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/Checker.jpg");    
            LayerPatternChunk->setImage(LoadedImage);
            LayerPatternChunk->setWrapS(GL_REPEAT);
            LayerPatternChunk->setWrapT(GL_CLAMP_TO_EDGE);

            ExamplePatternLayer->setTexture(LayerPatternChunk);
            ExamplePatternLayer->setPatternSize(Vec2f(50.0f,50.0f));
            ExamplePatternLayer->setVerticalAlignment(0.5);
            ExamplePatternLayer->setHorizontalAlignment(0.0);
            ExamplePatternLayer->setHorizontalRepeat(PatternLayer::PATTERN_REPEAT_BY_POINT);
            ExamplePatternLayer->setVerticalRepeat(PatternLayer::PATTERN_REPEAT_ABSOLUTE);
            ExamplePatternLayer->setHorizontalRepeatValue(1.0);
            ExamplePatternLayer->setVerticalRepeatValue(2.0);
        /******************************************************

        ******************************************************/
        ExampleGlassLayer->setCenterColor(Color4f(1.0f,1.0f,1.0f,0.0f));
        ExampleGlassLayer->setEdgeColor(Color4f(1.0f,1.0f,1.0f,0.7f));

        /******************************************************

        ******************************************************/
        ExampleGlassCompoundLayer->pushToBackgrounds(ExampleColorLayer);
        ExampleGlassCompoundLayer->pushToBackgrounds(ExampleGlassLayer);
        
        /******************************************************

			    Create and edit Button Components to
			    display the Layers.

        ******************************************************/

        ButtonRefPtr ExampleColorLayerButton = OSG::Button::create();
        ButtonRefPtr ExampleCompoundLayerButton = OSG::Button::create();
        ButtonRefPtr ExampleEmptyLayerButton = OSG::Button::create();
        ButtonRefPtr ExampleGradientLayerButton = OSG::Button::create();    
        ButtonRefPtr ExampleMaterialLayerButton = OSG::Button::create();
        ButtonRefPtr ExampleTextureLayerButton = OSG::Button::create();
        ButtonRefPtr ExamplePatternLayerButton = OSG::Button::create();
        ButtonRefPtr ExampleGlassLayerButton = OSG::Button::create();
        ButtonRefPtr ExampleGlassCompoundLayerButton = OSG::Button::create();
        

            ExampleColorLayerButton->setText("Color Layer");
            ExampleColorLayerButton->setBackground(ExampleColorLayer);
            ExampleColorLayerButton->setActiveBackground(ExampleColorLayer);
            ExampleColorLayerButton->setRolloverBackground(ExampleColorLayer);
            ExampleColorLayerButton->setPreferredSize(Vec2f(150,50));

            ExampleCompoundLayerButton->setText("Compound Layer");
            ExampleCompoundLayerButton->setBackground(ExampleCompoundLayer);
            ExampleCompoundLayerButton->setActiveBackground(ExampleCompoundLayer);
            ExampleCompoundLayerButton->setRolloverBackground(ExampleCompoundLayer);
            ExampleCompoundLayerButton->setPreferredSize(Vec2f(150,50));

            ExampleEmptyLayerButton->setText("Empty Layer");
            ExampleEmptyLayerButton->setBackground(ExampleEmptyLayer);
            ExampleEmptyLayerButton->setActiveBackground(ExampleEmptyLayer);
            ExampleEmptyLayerButton->setRolloverBackground(ExampleEmptyLayer);
            ExampleEmptyLayerButton->setPreferredSize(Vec2f(150,50));

            ExampleGradientLayerButton->setText("Gradient Layer");
            ExampleGradientLayerButton->setBackground(ExampleGradientLayer);
            ExampleGradientLayerButton->setActiveBackground(ExampleGradientLayer);
            ExampleGradientLayerButton->setRolloverBackground(ExampleGradientLayer);
            ExampleGradientLayerButton->setPreferredSize(Vec2f(150,50));
        
            ExampleMaterialLayerButton->setText("Material Layer");
            ExampleMaterialLayerButton->setBackground(ExampleMaterialLayer);
            ExampleMaterialLayerButton->setActiveBackground(ExampleMaterialLayer);
            ExampleMaterialLayerButton->setRolloverBackground(ExampleMaterialLayer);
            ExampleMaterialLayerButton->setPreferredSize(Vec2f(150,50));
            ExampleMaterialLayerButton->setTextColor(Color4f(1.0,1.0,1.0,1.0));
            ExampleMaterialLayerButton->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
            ExampleMaterialLayerButton->setActiveTextColor(Color4f(1.0,1.0,1.0,1.0));

            ExampleTextureLayerButton->setText("Texture Layer");
            ExampleTextureLayerButton->setBackground(ExampleTextureLayer);
            ExampleTextureLayerButton->setActiveBackground(ExampleTextureLayer);
            ExampleTextureLayerButton->setRolloverBackground(ExampleTextureLayer);
            ExampleTextureLayerButton->setPreferredSize(Vec2f(150,50));
            ExampleTextureLayerButton->setTextColor(Color4f(0.0,1.0,0.0,1.0));
            ExampleTextureLayerButton->setRolloverTextColor(Color4f(0.0,1.0,0.0,1.0));
            ExampleTextureLayerButton->setActiveTextColor(Color4f(0.0,1.0,0.0,1.0));
        
            ExamplePatternLayerButton->setText("Pattern Layer");
            ExamplePatternLayerButton->setBackground(ExamplePatternLayer);
            ExamplePatternLayerButton->setActiveBackground(ExamplePatternLayer);
            ExamplePatternLayerButton->setRolloverBackground(ExamplePatternLayer);
            ExamplePatternLayerButton->setPreferredSize(Vec2f(150,50));
            ExamplePatternLayerButton->setTextColor(Color4f(0.0,1.0,0.0,1.0));
            ExamplePatternLayerButton->setRolloverTextColor(Color4f(0.0,1.0,0.0,1.0));
            ExamplePatternLayerButton->setActiveTextColor(Color4f(0.0,1.0,0.0,1.0));
        
            ExampleGlassLayerButton->setText("Glass Layer");
            ExampleGlassLayerButton->setBackground(ExampleGlassLayer);
            ExampleGlassLayerButton->setActiveBackground(ExampleGlassLayer);
            ExampleGlassLayerButton->setRolloverBackground(ExampleGlassLayer);
            ExampleGlassLayerButton->setPreferredSize(Vec2f(150,50));
            ExampleGlassLayerButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
            ExampleGlassLayerButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
            ExampleGlassLayerButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
        
            ExampleGlassCompoundLayerButton->setText("GlassCompound Layer");
            ExampleGlassCompoundLayerButton->setBackground(ExampleGlassCompoundLayer);
            ExampleGlassCompoundLayerButton->setActiveBackground(ExampleGlassCompoundLayer);
            ExampleGlassCompoundLayerButton->setRolloverBackground(ExampleGlassCompoundLayer);
            ExampleGlassCompoundLayerButton->setPreferredSize(Vec2f(150,50));
            ExampleGlassCompoundLayerButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
            ExampleGlassCompoundLayerButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
            ExampleGlassCompoundLayerButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));


        
        /******************************************************

			    Create a MainFrameBackground.  For almost
			    all Tutorials, this is simply a 
			    ColorLayer with a semi-transparent
			    white Background.

        ******************************************************/

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
            MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

	    //InternalWindow Layout
        LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

        InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();

           MainInternalWindow->pushToChildren(ExampleColorLayerButton);
           MainInternalWindow->pushToChildren(ExampleCompoundLayerButton);
           MainInternalWindow->pushToChildren(ExampleEmptyLayerButton);
           MainInternalWindow->pushToChildren(ExampleGradientLayerButton);
           MainInternalWindow->pushToChildren(ExampleMaterialLayerButton);
           MainInternalWindow->pushToChildren(ExampleTextureLayerButton);
           MainInternalWindow->pushToChildren(ExamplePatternLayerButton);
           MainInternalWindow->pushToChildren(ExampleGlassLayerButton);
           MainInternalWindow->pushToChildren(ExampleGlassCompoundLayerButton);
	       MainInternalWindow->setLayout(MainInternalWindowLayout);
           MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	       MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	       MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	       MainInternalWindow->setDrawTitlebar(false);
	       MainInternalWindow->setResizable(false);
        
        // Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
            TutorialDrawingSurface->setGraphics(TutorialGraphics);
            TutorialDrawingSurface->setEventProducer(TutorialWindow);
        
	    TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

            TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Create the SimpleSceneManager helper
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
            TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                WinSize,
                "04Background");

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

