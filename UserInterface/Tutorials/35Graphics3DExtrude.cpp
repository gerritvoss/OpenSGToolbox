// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


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
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics3DExtrude.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGLabel.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGAbstractListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

ListSelectionModelPtr SelectionModel(new DefaultListSelectionModel());

// 20UIRectangle Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIRectangle.h>

// 12ComplexLayout Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGEmptyBorder.h>
#include <OpenSG/UserInterface/OSGEtchedBorder.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGCompoundUIBackground.h>

// 29Spinner Headers
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>
#include <OpenSG/UserInterface/OSGSpinner.h>
#include <OpenSG/UserInterface/OSGNumberSpinnerModel.h>

// 12CheckboxButton Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGCheckboxButton.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>


// Create the WindowEvent 
WindowEventProducerPtr TutorialWindowEventProducer;

// Global Spinner Models that will be affected by button listeners
Int32SpinnerModelPtr TheModel1(new Int32SpinnerModel());
Int32SpinnerModelPtr TheModel2(new Int32SpinnerModel());
Int32SpinnerModelPtr TheModel3(new Int32SpinnerModel());

// Create three materials to be add to 3d objects
ChunkMaterialPtr createRedMaterial(void);
ChunkMaterialPtr createBlueMaterial(void);
ChunkMaterialPtr createGreenMaterial(void);

// Create pointers for several 3d objects
NodePtr scene, ExampleTorus, ExampleCone, ExampleSphere, ExampleBox;

ChunkMaterialPtr createRedMaterial(void){ // Define what the material RedMaterial looks like

    ChunkMaterialPtr RedBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkPtr RedBackgroundMaterialChunk = MaterialChunk::create();
    beginEditCP(RedBackgroundMaterialChunk);
        RedBackgroundMaterialChunk->setAmbient(Color4f(1.0,0.0,0.0,1.0));
        RedBackgroundMaterialChunk->setDiffuse(Color4f(1.0,0.0,0.0,1.0));
        RedBackgroundMaterialChunk->setSpecular(Color4f(1.0,0.0,0.0,1.0));
    endEditCP(RedBackgroundMaterialChunk);

    beginEditCP(RedBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
        RedBackgroundMaterial->addChunk(RedBackgroundMaterialChunk);
    endEditCP(RedBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

    return RedBackgroundMaterial;

}
ChunkMaterialPtr createBlueMaterial(void){ // Define what the material BlueMaterial looks like

    ChunkMaterialPtr BlueBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkPtr BlueBackgroundMaterialChunk = MaterialChunk::create();
    beginEditCP(BlueBackgroundMaterialChunk);
        BlueBackgroundMaterialChunk->setAmbient(Color4f(0.0,0.0,0.8,1.0));
        BlueBackgroundMaterialChunk->setDiffuse(Color4f(0.0,0.0,0.8,1.0));
        BlueBackgroundMaterialChunk->setSpecular(Color4f(0.0,0.0,0.8,1.0));
    endEditCP(BlueBackgroundMaterialChunk);

    beginEditCP(BlueBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
        BlueBackgroundMaterial->addChunk(BlueBackgroundMaterialChunk);
    endEditCP(BlueBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

    return BlueBackgroundMaterial;

}
ChunkMaterialPtr createGreenMaterial(void){ // Define what the material GreenMaterial looks like

    ChunkMaterialPtr GreenBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkPtr GreenBackgroundMaterialChunk = MaterialChunk::create();
    beginEditCP(GreenBackgroundMaterialChunk);
        GreenBackgroundMaterialChunk->setAmbient(Color4f(0.0,1.0,0.0,1.0));
        GreenBackgroundMaterialChunk->setDiffuse(Color4f(0.0,1.0,0.0,1.0));
        GreenBackgroundMaterialChunk->setSpecular(Color4f(0.0,1.0,0.0,1.0));
    endEditCP(GreenBackgroundMaterialChunk);

    beginEditCP(GreenBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
        GreenBackgroundMaterial->addChunk(GreenBackgroundMaterialChunk);
    endEditCP(GreenBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

    return GreenBackgroundMaterial;

}

void create3DObjects(void) // creates several 3d objects, assigns materials to them, and translates them in 3D space
{
    // Make Object Nodes
    NodePtr ExampleTorusGeo = makeTorus(90, 270, 16, 16);
    NodePtr ExampleConeGeo = makeCone(150, 50, 16, true, true);
    NodePtr ExampleSphereGeo = makeSphere(4, 50);
    NodePtr ExampleBoxGeo = makeBox(100, 100, 100, 1, 1, 1);

    // AssignTextures - The materials are not currently used because something about the material causes a problem with viewing them in 3D
	// The problem is with OSGUIRectangle.cpp not rendering the 3D objects before the surface to be extruded
    
    /*beginEditCP(ExampleConeGeo->getCore());
        Geometry::Ptr::dcast(ExampleConeGeo->getCore())->setMaterial(createBlueMaterial());
    endEditCP(ExampleConeGeo->getCore());    

    beginEditCP(ExampleSphereGeo->getCore());
        Geometry::Ptr::dcast(ExampleSphereGeo->getCore())->setMaterial(createRedMaterial());
    endEditCP(ExampleSphereGeo->getCore());

    beginEditCP(ExampleBoxGeo->getCore());
        Geometry::Ptr::dcast(ExampleBoxGeo->getCore())->setMaterial(createGreenMaterial());
    endEditCP(ExampleBoxGeo->getCore());*/

    // Preform transformations on them
    Matrix mat; // A matrix variable which will be used to designate where each 3D object is drawn in 3D space
    
    // On Torus    
    mat.setTranslate(0.0,100.0,-200.0); // X=0.0, Y=100.0, Z=-200.0
    TransformPtr TorusTranCore = Transform::create();
    beginEditCP(TorusTranCore, Transform::MatrixFieldMask);
        TorusTranCore->setMatrix(mat);
    endEditCP(TorusTranCore, Transform::MatrixFieldMask);
    
    ExampleTorus = Node::create();
    beginEditCP(ExampleTorus, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ExampleTorus->setCore(TorusTranCore);
        ExampleTorus->addChild(ExampleTorusGeo);
    endEditCP(ExampleTorus, Node::CoreFieldMask | Node::ChildrenFieldMask);
    
    // On Sphere
    mat.setTranslate(0.0,100.0,-200.0); // X=0.0, Y=100.0, Z=-200.0

    TransformPtr SphereTranCore = Transform::create();
    beginEditCP(SphereTranCore, Transform::MatrixFieldMask);
        SphereTranCore->setMatrix(mat);
    endEditCP(SphereTranCore, Transform::MatrixFieldMask);
    
    ExampleSphere = Node::create();
    beginEditCP(ExampleSphere, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ExampleSphere->setCore(SphereTranCore);
        ExampleSphere->addChild(ExampleSphereGeo);
    endEditCP(ExampleSphere, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // On Cone
    mat.setTranslate(0.0,0.0,500.0); // X=0.0, Y=0.0, Z=500.0

    TransformPtr ConeTranCore = Transform::create();
    beginEditCP(ConeTranCore, Transform::MatrixFieldMask);
        ConeTranCore->setMatrix(mat);
    endEditCP(ConeTranCore, Transform::MatrixFieldMask);
    
    ExampleCone = Node::create();
    beginEditCP(ExampleCone, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ExampleCone->setCore(ConeTranCore);
        ExampleCone->addChild(ExampleConeGeo);
    endEditCP(ExampleCone, Node::CoreFieldMask | Node::ChildrenFieldMask);
        
    // On Box
    mat.setTranslate(250.0,250.0,400.0); // X=250.0, Y=250.0, Z=400.0

    TransformPtr ExampleBoxTranCore = Transform::create();
    beginEditCP(ExampleBoxTranCore, Transform::MatrixFieldMask);
        ExampleBoxTranCore->setMatrix(mat);
    endEditCP(ExampleBoxTranCore, Transform::MatrixFieldMask);
    
    ExampleBox = Node::create();
    beginEditCP(ExampleBox, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ExampleBox->setCore(ExampleBoxTranCore);
        ExampleBox->addChild(ExampleBoxGeo);
    endEditCP(ExampleBox, Node::CoreFieldMask | Node::ChildrenFieldMask);

    addRefCP(ExampleTorus);
    addRefCP(ExampleSphere);
    addRefCP(ExampleBox);
    addRefCP(ExampleCone);
}


class SingleIncrementButtonListener1 : public ButtonSelectedListener // Single Increment Button Listener for Spinner 1
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the button is selected set Spinner1 to increment by 1
        {         
            TheModel1->setStepSize(1);

        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the button is deselected set Spinner1 to increment by 2
   {
            TheModel1->setStepSize(2);
   }
};


class SingleIncrementButtonListener2 : public ButtonSelectedListener // Single Increment Button Listener for Spinner 2
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the button is selected set Spinner2 to increment by 1
        {         
            TheModel2->setStepSize(3);

        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the button is deselected set Spinner2 to increment by 2
   {
            TheModel2->setStepSize(4);
   }
};

class SingleIncrementButtonListener3 : public ButtonSelectedListener // Single Increment Button Listener for Spinner 3
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the button is selected set Spinner3 to increment by 1
        {         
            TheModel3->setStepSize(5);

        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the button is deselected set Spinner3 to increment by 2
   {
            TheModel3->setStepSize(6);
   }
};

class DoubleIncrementButtonListener1 : public ButtonSelectedListener // Double Increment Button Listener for Spinner 1
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the button is selected set Spinner3 to increment by 2
        {         
            TheModel1->setStepSize(2);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the button is deselected set Spinner3 to increment by 1
   {
            TheModel1->setStepSize(1);
   }
};


class DoubleIncrementButtonListener2 : public ButtonSelectedListener // Double Increment Button Listener for Spinner 2
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the button is selected set Spinner3 to increment by 2
        {         
            TheModel2->setStepSize(4);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the button is deselected set Spinner3 to increment by 1
   {
            TheModel2->setStepSize(3);
   }
};


class DoubleIncrementButtonListener3 : public ButtonSelectedListener // Double Increment Button Listener for Spinner 3
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the button is selected set Spinner3 to increment by 2
        {         
            TheModel3->setStepSize(6);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the button is deselected set Spinner3 to increment by 1
   {
            TheModel3->setStepSize(5);
   }
};



class TutorialKeyListener : public KeyListener // Key Listener to exit the application if escape key is pressed
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

class TutorialWindowListener : public WindowAdapter // Window Listener to exit the application if the window is closed
{
public:
    virtual void windowClosing(const WindowEvent& e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
        ExitApp = true;
    }
};

class TutorialMouseListener : public MouseListener // Mouse Listener to change the actions taken when receiving input via the mouse buttons
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
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK) // Enables the mouse to rotate the view, zoom in/out, and change the perspective in combination with the mouse motion listener
        {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
        }
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK) // Enables the mouse to rotate the view, zoom in/out, and change the perspective in combination with the mouse motion listener
        {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
        }
    }
};

class TutorialMouseMotionListener : public MouseMotionListener // Mouse Listener to change the actions taken when receiving input via the mouse motion
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK) // Enables the mouse to rotate the view, zoom in/out, and change the perspective in combination with the mouse button listener
        {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
        }
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK) // Enables the mouse to rotate the view, zoom in/out, and change the perspective in combination with the mouse button listener
        {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
        }
    }
};


class MakeTorus : public ButtonSelectedListener // Button listener for Add Torus check button
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the check button is selected draw the torus
        {         
            beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
                scene->addChild(ExampleTorus);
            endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the check button is deselected remove the torus
        {         
            beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
                scene->subChild(ExampleTorus);
            endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        }
};
class MakeSphere : public ButtonSelectedListener // Button listener for Add Sphere check button
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the check button is selected draw the sphere
        {         
            beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
                scene->addChild(ExampleSphere);
            endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the check button is deselected remove the sphere
   {
            beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
                scene->subChild(ExampleSphere);
            endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);    
   }
};
class MakeBox : public ButtonSelectedListener // Button listener for Add Box check button
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the check button is selected draw the box
        {         
            beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
                scene->addChild(ExampleBox);
            endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the check button is deselected remove the box
   {
            beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
                scene->subChild(ExampleBox);
            endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);   
   }
};
class MakeCone : public ButtonSelectedListener // Button listener for Add Cone check button
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e) // If the check button is selected draw the cone
        {         
            beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
                scene->addChild(ExampleCone);
            endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e) // If the check button is deselected remove the cone
   {
            beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
                scene->subChild(ExampleCone);
            endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);   
   }
};

// Assign listeners to the classes that make the 3D objects
MakeTorus RightPanelCheck1Listener;
MakeBox RightPanelCheck2Listener;
MakeSphere RightPanelCheck3Listener;
MakeCone RightPanelCheck4Listener;

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialMouseListener mouseListener;
    TutorialMouseMotionListener mouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&mouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&mouseMotionListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);

	// Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(90, 270, 16, 16);

    // Make Main Scene Node and add the Torus
	create3DObjects();
    scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
		//scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    Graphics3DExtrudePtr TutorialGraphics = osg::Graphics3DExtrude::create();
    beginEditCP(TutorialGraphics);
        TutorialGraphics->setEnablePolygonAntiAliasing(false);
        TutorialGraphics->setExtrudeLength(-40.0);
    beginEditCP(TutorialGraphics);

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************

        Create nine Button Components (button1, button2,
		 button3, button4, button5, button6, button7, button8
        and button9) and their AbsoluteLayoutConstraints.

        AbsoluteLayoutConstraints are used within the 
        AbsoluteLayout to define where the Components will
        be placed.  Most other Layouts do not need 
        Constraints, as they place things within the Layout
        automatically.

    ******************************************************/

    ButtonPtr button1 = osg::Button::create();
    ButtonPtr button2 = osg::Button::create();
    ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
    ButtonPtr button5 = osg::Button::create();
    ButtonPtr button6 = osg::Button::create();
	ButtonPtr button7 = osg::Button::create();
    ButtonPtr button8 = osg::Button::create();
    ButtonPtr button9 = osg::Button::create();

    /******************************************************

        Edit Button Components and assign text,
        PreferredSize, and AbsoluteLayoutConstraints

    ******************************************************/

    // Create a simple Font to be used with the Button
    UIFontPtr sampleFont = osg::UIFont::create();
    beginEditCP(sampleFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::GapFieldMask | UIFont::GlyphPixelSizeFieldMask | UIFont::TextureWidthFieldMask | UIFont::StyleFieldMask);
        sampleFont->setFamily("SANS");
        sampleFont->setGap(1);
        sampleFont->setGlyphPixelSize(46);
        sampleFont->setSize(16);
        //sampleFont->setTextureWidth(0);
        sampleFont->setStyle(TextFace::STYLE_PLAIN);
    endEditCP(sampleFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::GapFieldMask | UIFont::GlyphPixelSizeFieldMask | UIFont::TextureWidthFieldMask | UIFont::StyleFieldMask);

    ColorUIBackgroundPtr button1Background = ColorUIBackground::create();
    beginEditCP(button1Background);
		button1Background->setColor(Color4f(1.0,0.0,0.0,1.0));
    endEditCP(button1Background);

	//Define each button and give them each a name
	beginEditCP(button1, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        button1->setPreferredSize(Vec2f(100,50));
        button1->setSize(Vec2f(100,50));
        button1->setText("Button 1");
        button1->setTextColor(Color4f(0.0,0.0,0.0,1.0));
        button1->setFont(sampleFont);
    endEditCP(button1, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button2, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        button2->setPreferredSize(Vec2f(100,50));
        button2->setSize(Vec2f(100,50));
        button2->setText("Button 2");
        button2->setFont(sampleFont);
    endEditCP(button2, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button3,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);
        button3->setPreferredSize(Vec2f(100,50));
        button3->setSize(Vec2f(100,50));
        button3->setText("Button 3");
        button3->setFont(sampleFont);
    endEditCP(button3,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button4, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        button4->setPreferredSize(Vec2f(100,50));
        button4->setSize(Vec2f(100,50));
        button4->setText("Button 4");
        button4->setTextColor(Color4f(0.0,0.0,0.0,1.0));
        button4->setFont(sampleFont);
    endEditCP(button4, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button5, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        button5->setPreferredSize(Vec2f(100,50));
        button5->setSize(Vec2f(100,50));
        button5->setText("Button 5");
        button5->setFont(sampleFont);
    endEditCP(button5, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button6,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);
        button6->setPreferredSize(Vec2f(100,50));
        button6->setSize(Vec2f(100,50));
        button6->setText("Button 6");
        button6->setFont(sampleFont);
    endEditCP(button6,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);

	beginEditCP(button7, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        button7->setPreferredSize(Vec2f(100,50));
        button7->setSize(Vec2f(100,50));
        button7->setText("Button 7");
        button7->setTextColor(Color4f(0.0,0.0,0.0,1.0));
        button7->setFont(sampleFont);
    endEditCP(button7, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button8, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        button8->setPreferredSize(Vec2f(100,50));
        button8->setSize(Vec2f(100,50));
        button8->setText("Button 8");
        button8->setFont(sampleFont);
    endEditCP(button8, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button9,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);
        button9->setPreferredSize(Vec2f(100,50));
        button9->setSize(Vec2f(100,50));
        button9->setText("Button 9");
        button9->setFont(sampleFont);
    endEditCP(button9,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);

	// Create a label, label1, and put some text in it
	LabelPtr TheLabel1 = Label::create();
    beginEditCP(TheLabel1,  Label::TextFieldMask);
		TheLabel1->setText("Label #1");
    endEditCP(TheLabel1,  Label::TextFieldMask);

	// Create a label, label2, and put some text in it
	LabelPtr TheLabel2 = Label::create();
    beginEditCP(TheLabel2,  Label::TextFieldMask);
		TheLabel2->setText("Label #2");
    endEditCP(TheLabel2,  Label::TextFieldMask);

	// Create a label, label3, and put some text in it
	LabelPtr TheLabel3 = Label::create();
    beginEditCP(TheLabel3,  Label::TextFieldMask);
		TheLabel3->setText("Label #3");
    endEditCP(TheLabel3,  Label::TextFieldMask);
	
    /******************************************************

            Create ListModel.  This is where you set
            the values for the List.

            After creating an AbstractListModel,
            do the following to make a list.
            
            First, create SFStrings and use the 
            .setValue("VALUE") function to set their
            values.  Then, use the .pushBack(&SFStringName)
            to add them to the List.

            Next, create the ListSelectionModel
            defaults.

            Finally, actually create the List.  Set
            its Model, and SelectionModel
            as shown below.  Finally, choose the
            type of display for the List (choices outlined
            below).

            

    ******************************************************/
    // Create ListModel Component to add things to
    AbstractListModel Model1;

    // Add values to it
    Model1.pushBack(SharedFieldPtr(new SFString("Red")));
    Model1.pushBack(SharedFieldPtr(new SFString("Green")));
    Model1.pushBack(SharedFieldPtr(new SFString("Blue")));
    Model1.pushBack(SharedFieldPtr(new SFString("Orange")));
    Model1.pushBack(SharedFieldPtr(new SFString("Purple")));
    Model1.pushBack(SharedFieldPtr(new SFString("Yellow")));
    Model1.pushBack(SharedFieldPtr(new SFString("White")));
    Model1.pushBack(SharedFieldPtr(new SFString("Black")));
    Model1.pushBack(SharedFieldPtr(new SFString("Gray")));
    Model1.pushBack(SharedFieldPtr(new SFString("Brown")));
    Model1.pushBack(SharedFieldPtr(new SFString("Indigo")));
    Model1.pushBack(SharedFieldPtr(new SFString("Pink")));
    Model1.pushBack(SharedFieldPtr(new SFString("Violet")));
    Model1.pushBack(SharedFieldPtr(new SFString("Mauve")));
    Model1.pushBack(SharedFieldPtr(new SFString("Peach")));

	// Create ListModel Component to add things to
    AbstractListModel Model2;

    // Add values to it
    Model2.pushBack(SharedFieldPtr(new SFString("Taco Pizza")));
    Model2.pushBack(SharedFieldPtr(new SFString("Spaghetti")));
    Model2.pushBack(SharedFieldPtr(new SFString("Chicken Fingers")));
    Model2.pushBack(SharedFieldPtr(new SFString("Buffalo Wings")));
    Model2.pushBack(SharedFieldPtr(new SFString("Cheesesticks")));
    Model2.pushBack(SharedFieldPtr(new SFString("Bloomin' Onion")));
    Model2.pushBack(SharedFieldPtr(new SFString("French Fries")));
    Model2.pushBack(SharedFieldPtr(new SFString("Cheeseburger")));
    Model2.pushBack(SharedFieldPtr(new SFString("Onion Rings")));
    Model2.pushBack(SharedFieldPtr(new SFString("Curly Fries")));
    Model2.pushBack(SharedFieldPtr(new SFString("Chocolate Milkshake")));
    Model2.pushBack(SharedFieldPtr(new SFString("All-Meat Pizza")));
    Model2.pushBack(SharedFieldPtr(new SFString("Supreme Pizza")));
    Model2.pushBack(SharedFieldPtr(new SFString("Veggie Pizza")));
    Model2.pushBack(SharedFieldPtr(new SFString("Cheese Pizza")));

	// Create ListModel Component to add things to
    AbstractListModel Model3;

    // Add values to it
    Model3.pushBack(SharedFieldPtr(new SFString("London")));
    Model3.pushBack(SharedFieldPtr(new SFString("Paris")));
    Model3.pushBack(SharedFieldPtr(new SFString("Amsterdam")));
    Model3.pushBack(SharedFieldPtr(new SFString("Manama")));
    Model3.pushBack(SharedFieldPtr(new SFString("Dubai")));
    Model3.pushBack(SharedFieldPtr(new SFString("Madrid")));
    Model3.pushBack(SharedFieldPtr(new SFString("Berlin")));
    Model3.pushBack(SharedFieldPtr(new SFString("Beijing")));
    Model3.pushBack(SharedFieldPtr(new SFString("Seoul")));
    Model3.pushBack(SharedFieldPtr(new SFString("Oslow")));
    Model3.pushBack(SharedFieldPtr(new SFString("Beirut")));
    Model3.pushBack(SharedFieldPtr(new SFString("Baghdad")));
    Model3.pushBack(SharedFieldPtr(new SFString("Mexico City")));
    Model3.pushBack(SharedFieldPtr(new SFString("Washington DC")));
    Model3.pushBack(SharedFieldPtr(new SFString("Moscow")));

    // Create ListSelectionModel
    // (normally will be default).
    // Note that the DefaultListSelectionModel was
    // created at the top of this file before
    // the ActionListeners
    //DefaultListSelectionModel SelectionModel;

	
    // Create Background to be used with the Main Frame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        //MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
		MainFrameBackground->setColor(Color4f(0.0,0.0,0.0,0.0));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    
	// Create ListPtr
    ListPtr list1 = List::create();
    beginEditCP(list1);
        list1->setPreferredSize(Vec2f(200,300));
        list1->setBackgrounds(MainFrameBackground);
        list1->setCellOrientation(VERTICAL_ALIGNMENT);
        //list->setCellOrientation(HORIZONTAL_ALIGNMENT);
    endEditCP(list1);

	// Create ListPtr
    ListPtr list2 = List::create();
    beginEditCP(list2);
        list2->setPreferredSize(Vec2f(200,300));
        list2->setBackgrounds(MainFrameBackground);
        list2->setCellOrientation(VERTICAL_ALIGNMENT);
        //list->setCellOrientation(HORIZONTAL_ALIGNMENT);
    endEditCP(list2);

	// Create ListPtr
    ListPtr list3 = List::create();
    beginEditCP(list3);
        list3->setPreferredSize(Vec2f(200,300));
        list3->setBackgrounds(MainFrameBackground);
        list3->setCellOrientation(VERTICAL_ALIGNMENT);
        //list->setCellOrientation(HORIZONTAL_ALIGNMENT);
    endEditCP(list3);

    // Assign the Model, and SelectionModel
    // to the List
    list1->setModel(&Model1);
    list1->setSelectionModel(SelectionModel);

	// Assign the Model, and SelectionModel
    // to the List
    list2->setModel(&Model2);
    list2->setSelectionModel(SelectionModel);


	// Assign the Model, and SelectionModel
    // to the List
    list3->setModel(&Model3);
    list3->setSelectionModel(SelectionModel);


    /******************************************************

            Determine the SelectionModel
            -SINGLE_SELECTION lets you select ONE item
                via a single mouse click
            -SINGLE_INTERVAL_SELECTION lets you select
                one interval via mouse and SHIFT key
            -MULTIPLE_INTERVAL_SELECTION lets you select
                via mouse, and SHIFT and CONTRL keys

            Note: this tutorial is currently set up
            to allow for this to be changed via Buttons
            with ActionListeners attached to them so
            this code is commented out

    ******************************************************/

    //SelectionModel.setMode(DefaultListSelectionModel::SINGLE_SELECTION);
    //SelectionModel.setMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
    //SelectionModel.setMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);

    //ScrollPanel
    ScrollPanelPtr TheScrollPanel1 = ScrollPanel::create();
    beginEditCP(TheScrollPanel1, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TheScrollPanel1->setPreferredSize(Vec2f(100,300));
        TheScrollPanel1->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TheScrollPanel1, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    TheScrollPanel1->setViewComponent(list1);

	//ScrollPanel
    ScrollPanelPtr TheScrollPanel2 = ScrollPanel::create();
    beginEditCP(TheScrollPanel2, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TheScrollPanel2->setPreferredSize(Vec2f(100,300));
        TheScrollPanel2->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel2->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TheScrollPanel2, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    TheScrollPanel2->setViewComponent(list2);

	//ScrollPanel
    ScrollPanelPtr TheScrollPanel3 = ScrollPanel::create();
    beginEditCP(TheScrollPanel1, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TheScrollPanel3->setPreferredSize(Vec2f(100,300));
        TheScrollPanel3->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel3->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TheScrollPanel3, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    TheScrollPanel3->setViewComponent(list3);

	/******************************************************
            
            Create three Spinner Models.  These dictate 
            how the Spinners functions.
            -setMaximum(int): Determine the Maximum 
                value the Spinner can have.
            -setMinimum(int): Determine the Minimum 
                value the Spinner can have.
            -setStepSize(int): Determine the 
                incremental step size.
            -setValue(SharedFieldPtr(new SFInt32(int)):
                Determine initial starting value
                of the Spinner.

            Note: the StepSize can be changed 
            dynamically as done in this 
            Tutorial with ButtonSelectedListeners.
 
    ******************************************************/    

    //Spinner Model, TheModel1, used for spinner #1
    TheModel1->setMaximum(100);
    TheModel1->setMinimum(-100);
    TheModel1->setStepSize(2);
    TheModel1->setValue(SharedFieldPtr(new SFInt32(0)));

	//Spinner Model, TheModel2, used for spinner #2
	TheModel2->setMaximum(100);
    TheModel2->setMinimum(-100);
    TheModel2->setStepSize(4);
    TheModel2->setValue(SharedFieldPtr(new SFInt32(0)));

	//Spinner Model, TheModel3, used for spinner #3
	TheModel3->setMaximum(100);
    TheModel3->setMinimum(-100);
    TheModel3->setStepSize(6);
    TheModel3->setValue(SharedFieldPtr(new SFInt32(0)));

    /******************************************************
            
            Create three Spinners and and assign each a 
			Model.
 
    ******************************************************/    

	//Spinner #1 will be called ExampleSpinner1 and uses TheModel1
    SpinnerPtr ExampleSpinner1 = Spinner::create();
    ExampleSpinner1->setModel(TheModel1);

	//Spinner #2 will be called ExampleSpinner2 and uses TheModel2
	SpinnerPtr ExampleSpinner2 = Spinner::create();
    ExampleSpinner2->setModel(TheModel2);

	//Spinner #3 will be called ExampleSpinner3 and uses TheModel3
	SpinnerPtr ExampleSpinner3 = Spinner::create();
    ExampleSpinner3->setModel(TheModel3);

  /******************************************************
            
            Create several Radio Buttons to allow
            for certain characteristics of the
            Spinners to be changed dynamically.
			Each spinner is changed independantly
			of the other spinners and radio button groups.
            See 14RadioButton for more 
            information about RadioButtons.
 
    ******************************************************/    

	// Create two radio buttons, SingleIncrementButton1 and DoubleIncrementButton1
    RadioButtonPtr SingleIncrementButton1 = RadioButton::create();
    RadioButtonPtr DoubleIncrementButton1 = RadioButton::create();

	// Create two radio buttons, SingleIncrementButton2 and DoubleIncrementButton2
	RadioButtonPtr SingleIncrementButton2 = RadioButton::create();
    RadioButtonPtr DoubleIncrementButton2 = RadioButton::create();

	// Create two radio buttons, SingleIncrementButton3 and DoubleIncrementButton3
	RadioButtonPtr SingleIncrementButton3 = RadioButton::create();
    RadioButtonPtr DoubleIncrementButton3 = RadioButton::create();
    
	// Edit SingleIncrementButton1 and assign it text
	beginEditCP(SingleIncrementButton1, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
        SingleIncrementButton1->setText("Increment by 1");
        SingleIncrementButton1->setPreferredSize(Vec2f(100,50));
    endEditCP(SingleIncrementButton1, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
	// Make a button listener and assign it to SingleIncrementButton1
    SingleIncrementButtonListener1 TheSingleIncrementButtonListener1;
    SingleIncrementButton1->addButtonSelectedListener(&TheSingleIncrementButtonListener1);

	// Edit DoubleIncrementButton1, make it pre-selected, and assign it text
	beginEditCP(DoubleIncrementButton1, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
        DoubleIncrementButton1->setText("Increment by 2");
        DoubleIncrementButton1->setPreferredSize(Vec2f(100,50));
        DoubleIncrementButton1->setSelected(true);
    endEditCP(DoubleIncrementButton1, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
	// Make a button listener and assign it to DoubleIncrementButton1
    DoubleIncrementButtonListener1 TheDoubleIncrementButtonListener1;
    DoubleIncrementButton1->addButtonSelectedListener(&TheDoubleIncrementButtonListener1);

	// Edit SingleIncrementButton2 and assign it text
	beginEditCP(SingleIncrementButton2, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
        SingleIncrementButton2->setText("Increment by 3");
        SingleIncrementButton2->setPreferredSize(Vec2f(100,50));
    endEditCP(SingleIncrementButton2, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
	// Make a button listener and assign it to SingleIncrementButton2
    SingleIncrementButtonListener2 TheSingleIncrementButtonListener2;
    SingleIncrementButton2->addButtonSelectedListener(&TheSingleIncrementButtonListener2);

	// Edit DoubleIncrementButton2, make it pre-selected, and assign it text
	beginEditCP(DoubleIncrementButton2, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
        DoubleIncrementButton2->setText("Increment by 4");
        DoubleIncrementButton2->setPreferredSize(Vec2f(100,50));
        DoubleIncrementButton2->setSelected(true);
    endEditCP(DoubleIncrementButton2, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
	// Make a button listener and assign it to DoubleIncrementButton2
    DoubleIncrementButtonListener2 TheDoubleIncrementButtonListener2;
    DoubleIncrementButton2->addButtonSelectedListener(&TheDoubleIncrementButtonListener2);

	// Edit SingleIncrementButton3 and assign it text
	beginEditCP(SingleIncrementButton3, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
        SingleIncrementButton3->setText("Increment by 5");
        SingleIncrementButton3->setPreferredSize(Vec2f(100,50));
    endEditCP(SingleIncrementButton1, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
	// Make a button listener and assign it to SingleIncrementButton3
    SingleIncrementButtonListener3 TheSingleIncrementButtonListener3;
    SingleIncrementButton3->addButtonSelectedListener(&TheSingleIncrementButtonListener3);

	// Edit DoubleIncrementButton3, make it pre-selected, and assign it text
	beginEditCP(DoubleIncrementButton3, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
        DoubleIncrementButton3->setText("Increment by 6");
        DoubleIncrementButton3->setPreferredSize(Vec2f(100,50));
        DoubleIncrementButton3->setSelected(true);
    endEditCP(DoubleIncrementButton3, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
	// Make a button listener and assign it to DoubleIncrementButton3
    DoubleIncrementButtonListener3 TheDoubleIncrementButtonListener3;
    DoubleIncrementButton3->addButtonSelectedListener(&TheDoubleIncrementButtonListener1);

	// Create a radio button group and assign two radio buttons to it
    RadioButtonGroup SelectionRadioButtonGroup1;
	SelectionRadioButtonGroup1.addButton(SingleIncrementButton1);
    SelectionRadioButtonGroup1.addButton(DoubleIncrementButton1);

	// Create a radio button group and assign two radio buttons to it
	RadioButtonGroup SelectionRadioButtonGroup2;
	SelectionRadioButtonGroup2.addButton(SingleIncrementButton2);
    SelectionRadioButtonGroup2.addButton(DoubleIncrementButton2);

	// Create a radio button group and assign two radio buttons to it
	RadioButtonGroup SelectionRadioButtonGroup3;
	SelectionRadioButtonGroup3.addButton(SingleIncrementButton3);
    SelectionRadioButtonGroup3.addButton(DoubleIncrementButton3);
	
	// Create and edit the CheckBoxes
    CheckboxButtonPtr Check1 = osg::CheckboxButton::create();
    CheckboxButtonPtr Check2 = osg::CheckboxButton::create();
    CheckboxButtonPtr Check3 = osg::CheckboxButton::create();
    CheckboxButtonPtr Check4 = osg::CheckboxButton::create();

	beginEditCP(Check1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        Check1->setText("Show Torus");
        Check1->setPreferredSize(Vec2f(125,50));
        Check1->setHorizontalAlignment(0.0);
    endEditCP(Check1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        // Add Listener
        Check1->addButtonSelectedListener(&RightPanelCheck1Listener);
    
    beginEditCP(Check2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        Check2->setText("Show Box");
        Check2->setPreferredSize(Vec2f(125,50));
        Check2->setHorizontalAlignment(0.0);
    endEditCP(Check2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        // Add Listener
        Check2->addButtonSelectedListener(&RightPanelCheck2Listener);

    beginEditCP(Check3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        Check3->setText("Show Sphere");
        Check3->setPreferredSize(Vec2f(125,50));
        Check3->setHorizontalAlignment(0.0);
    endEditCP(Check3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        // Add Listener
        Check3->addButtonSelectedListener(&RightPanelCheck3Listener);

    beginEditCP(Check4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        Check4->setText("Show Cone");
        Check4->setPreferredSize(Vec2f(125,50));
        Check4->setHorizontalAlignment(0.0);
    endEditCP(Check4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        // Add Listener
        Check4->addButtonSelectedListener(&RightPanelCheck4Listener);

    // Create The Main Frame
    // Create Background to be used with the Main Frame
    EmptyUIBackgroundPtr MainBackground = osg::EmptyUIBackground::create();
    
    EmptyBorderPtr MainFrameLineBorder = EmptyBorder::create();

	// Create layouts to be used in the main frame and panels
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
    BoxLayoutPtr ExamplePanel2Layout = osg::BoxLayout::create();
	BoxLayoutPtr ExamplePanel3Layout = osg::BoxLayout::create();

    beginEditCP(ExamplePanel2Layout, BoxLayout::OrientationFieldMask);
	ExamplePanel2Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(ExamplePanel2Layout, BoxLayout::OrientationFieldMask);

	beginEditCP(ExamplePanel3Layout, BoxLayout::OrientationFieldMask);
        ExamplePanel3Layout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
    endEditCP(ExamplePanel3Layout, BoxLayout::OrientationFieldMask);

	// Create several panels that will be assigned layouts, borders, and backgrounds and will have objects added to them
	PanelPtr ExamplePanel1 = osg::Panel::create();
    PanelPtr ExamplePanel2 = osg::Panel::create();
	PanelPtr ExamplePanel3 = osg::Panel::create();
	PanelPtr ExamplePanel4 = osg::Panel::create();
    PanelPtr ExamplePanel5 = osg::Panel::create();
	PanelPtr ExamplePanel6 = osg::Panel::create();
	PanelPtr ExamplePanel7 = osg::Panel::create();
    PanelPtr ExamplePanel8 = osg::Panel::create();
	PanelPtr ExamplePanel9 = osg::Panel::create();
	PanelPtr ExamplePanel10 = osg::Panel::create();
    PanelPtr ExamplePanel11 = osg::Panel::create();
	PanelPtr ExamplePanel12 = osg::Panel::create();
	PanelPtr ExamplePanel13 = osg::Panel::create();
	PanelPtr ExamplePanel14 = osg::Panel::create();
	
	// Edit the panels and add buttons, lists, check boxes, labels, radio buttons, spinners, and even other panels to each as desired.
	beginEditCP(ExamplePanel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel1->setPreferredSize(Vec2f(425,175));
        ExamplePanel1->getChildren().addValue(button1);
		ExamplePanel1->getChildren().addValue(button2);
		ExamplePanel1->getChildren().addValue(button3);
        ExamplePanel1->setLayout(MainInternalWindowLayout);
        ExamplePanel1->setBackgrounds(MainBackground);
        ExamplePanel1->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    beginEditCP(ExamplePanel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel2->setPreferredSize(Vec2f(425,375));
        ExamplePanel2->getChildren().addValue(TheLabel1);
		ExamplePanel2->getChildren().addValue(TheScrollPanel1);
        ExamplePanel2->setLayout(ExamplePanel2Layout);
        ExamplePanel2->setBackgrounds(MainBackground);
        ExamplePanel2->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel3, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel3->setPreferredSize(Vec2f(425,125));
        ExamplePanel3->getChildren().addValue(SingleIncrementButton1);
		ExamplePanel3->getChildren().addValue(DoubleIncrementButton1);
		ExamplePanel3->getChildren().addValue(ExampleSpinner1);
        ExamplePanel3->setLayout(MainInternalWindowLayout);
        ExamplePanel3->setBackgrounds(MainBackground);
        ExamplePanel3->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel3, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel4, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel4->setPreferredSize(Vec2f(425,175));
        ExamplePanel4->getChildren().addValue(button4);
		ExamplePanel4->getChildren().addValue(button5);
		ExamplePanel4->getChildren().addValue(button6);
        ExamplePanel4->setLayout(MainInternalWindowLayout);
        ExamplePanel4->setBackgrounds(MainBackground);
        ExamplePanel4->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel4, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    beginEditCP(ExamplePanel5, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel5->setPreferredSize(Vec2f(425,375));
        ExamplePanel5->getChildren().addValue(TheLabel2);
		ExamplePanel5->getChildren().addValue(TheScrollPanel2);
        ExamplePanel5->setLayout(ExamplePanel2Layout);
        ExamplePanel5->setBackgrounds(MainBackground);
        ExamplePanel5->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel5, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel6, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel6->setPreferredSize(Vec2f(425,125));
        ExamplePanel6->getChildren().addValue(SingleIncrementButton2);
		ExamplePanel6->getChildren().addValue(DoubleIncrementButton2);
		ExamplePanel6->getChildren().addValue(ExampleSpinner2);
        ExamplePanel6->setLayout(MainInternalWindowLayout);
        ExamplePanel6->setBackgrounds(MainBackground);
        ExamplePanel6->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel6, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel7, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel7->setPreferredSize(Vec2f(425,175));
        ExamplePanel7->getChildren().addValue(button7);
		ExamplePanel7->getChildren().addValue(button8);
		ExamplePanel7->getChildren().addValue(button9);
        ExamplePanel7->setLayout(MainInternalWindowLayout);
        ExamplePanel7->setBackgrounds(MainBackground);
        ExamplePanel7->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel7, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    beginEditCP(ExamplePanel8, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel8->setPreferredSize(Vec2f(425,375));
        ExamplePanel8->getChildren().addValue(TheLabel3);
		ExamplePanel8->getChildren().addValue(TheScrollPanel3);
        ExamplePanel8->setLayout(ExamplePanel2Layout);
        ExamplePanel8->setBackgrounds(MainBackground);
        ExamplePanel8->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel8, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel9, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel9->setPreferredSize(Vec2f(425,125));
        ExamplePanel9->getChildren().addValue(SingleIncrementButton3);
		ExamplePanel9->getChildren().addValue(DoubleIncrementButton3);
		ExamplePanel9->getChildren().addValue(ExampleSpinner3);
        ExamplePanel9->setLayout(MainInternalWindowLayout);
        ExamplePanel9->setBackgrounds(MainBackground);
        ExamplePanel9->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel9, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel10, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel10->setPreferredSize(Vec2f(425,675));
		ExamplePanel10->getChildren().addValue(ExamplePanel1);
		ExamplePanel10->getChildren().addValue(ExamplePanel2);
		ExamplePanel10->getChildren().addValue(ExamplePanel3);
        ExamplePanel10->setLayout(MainInternalWindowLayout);
        ExamplePanel10->setBackgrounds(MainBackground);
        ExamplePanel10->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel10, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    beginEditCP(ExamplePanel11, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel11->setPreferredSize(Vec2f(425,675));
		ExamplePanel11->getChildren().addValue(ExamplePanel5);
		ExamplePanel11->getChildren().addValue(ExamplePanel6);
		ExamplePanel11->getChildren().addValue(ExamplePanel4);
        ExamplePanel11->setLayout(MainInternalWindowLayout);
        ExamplePanel11->setBackgrounds(MainBackground);
        ExamplePanel11->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel11, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel12, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel12->setPreferredSize(Vec2f(425,675));
		ExamplePanel12->getChildren().addValue(ExamplePanel9);
		ExamplePanel12->getChildren().addValue(ExamplePanel7);
		ExamplePanel12->getChildren().addValue(ExamplePanel8);
        ExamplePanel12->setLayout(MainInternalWindowLayout);
        ExamplePanel12->setBackgrounds(MainBackground);
        ExamplePanel12->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel12, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel13, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel13->setPreferredSize(Vec2f(1300,700));
		ExamplePanel13->getChildren().addValue(ExamplePanel10);
		ExamplePanel13->getChildren().addValue(ExamplePanel11);
		ExamplePanel13->getChildren().addValue(ExamplePanel12);
        ExamplePanel13->setLayout(ExamplePanel3Layout);
        ExamplePanel13->setBackgrounds(MainBackground);
        ExamplePanel13->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel13, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

	beginEditCP(ExamplePanel14, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel14->setPreferredSize(Vec2f(1300,200));
		ExamplePanel14->getChildren().addValue(Check1);
		ExamplePanel14->getChildren().addValue(Check2);
		ExamplePanel14->getChildren().addValue(Check3);
		ExamplePanel14->getChildren().addValue(Check4);
        ExamplePanel14->setLayout(ExamplePanel3Layout);
        ExamplePanel14->setBackgrounds(MainBackground);
        ExamplePanel14->setBorders(MainFrameLineBorder);
    endEditCP(ExamplePanel12, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    // Create The Main InternalWindow

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::BordersFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().addValue(ExamplePanel13);
       MainInternalWindow->getChildren().addValue(ExamplePanel14);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainBackground);
       MainInternalWindow->setBorders(MainFrameLineBorder);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::BordersFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    //Make A 3D Rectangle to draw the UI on
    UIRectanglePtr UIRectCore = UIRectangle::create();
    beginEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
        UIRectCore->setPoint(Pnt3f(-650.0,-450.0,370.0)); // Set the initial point in the center of the drawing surface.
        UIRectCore->setWidth(1300.0); // Set the width of the drawing surface
        UIRectCore->setHeight(900.0); // Set the height of the drawing surface
        UIRectCore->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
    
    NodePtr UIRectNode = osg::Node::create();
    beginEditCP(UIRectNode, Node::CoreFieldMask);
        UIRectNode->setCore(UIRectCore);
    endEditCP(UIRectNode, Node::CoreFieldMask);
    
    beginEditCP(scene, Node::ChildrenFieldMask);
        // add the UIRect as a child
        scene->addChild(UIRectNode);
    endEditCP(scene, Node::ChildrenFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(950,750),
                                        "OpenSG 35Graphics3DExtrude Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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
