// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// TabPanel and its characteristics
// 
// Includes: TabPanel creation and example TabPanel, as well as 
// utilizing ActionListeners to add/remove Tabs on mouseclicks

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "styleddocumentattributes.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"


// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGLayers.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"
#include <OSGPlainDocument.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 15TabPanel Headers
#include <sstream>
#include "OSGButton.h"
#include "OSGLineBorder.h"
#include "OSGFlowLayout.h"
#include "OSGUIFont.h"
#include "OSGScrollPanel.h"
#include "OSGAdvancedTextDomArea.h"
#include "OSGTextEditor.h"
#include "OSGUIRectangle.h"

TextEditorRefPtr theTextEditor;
AdvancedTextDomAreaRefPtr ExampleAdvancedTextDomArea;

PlainDocumentRefPtr TheDocument;
ButtonRefPtr LoadButton;
ButtonRefPtr SaveButton;


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
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
    }
};

class TutorialMouseListener1 : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEventUnrecPtr e)
   {
	    if(e->getSource() == LoadButton)
		{	
			std::cout<<"Loading a file"<<std::endl;
			std::vector<WindowEventProducer::FileDialogFilter> Filters;
			Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));
			Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));


			std::vector<BoostPath> FilesToOpen;
			FilesToOpen = TutorialWindow->openFileDialog("Open File Window",
																							   Filters,
																							   BoostPath(".."),
																							   false);

			/*for(std::vector<BoostPath>::iterator Itor(FilesToOpen.begin()) ; Itor != FilesToOpen.end(); ++Itor)
			{
				_ContentPanel->addTabWithText(*Itor);
			}*/
			

			//GetSystemTime(&now);
			//unsigned int t1 = now.wSecond * 1000 + now.wMilliseconds;

			theTextEditor->loadNewFile(FilesToOpen[0]);

			//GetSystemTime(&now);
			//unsigned int t2 = now.wSecond * 1000 + now.wMilliseconds;

			//std::cout<<"\nstart time in milliseconds:"<<t1<<std::endl;	// start time in milliseconds
			//std::cout<<"\nduration in milliseconds:"<<t2-t1<<std::endl;		// end time in milliseconds

			
			//if(TheDocument) 
			//	ExampleTextDomArea->setDocumentModel(TheDocument);
			//else std::cout<<"Failed Loading the Document"<<std::endl;
		}
		else if(e->getSource() == SaveButton)
		{
			std::cout<<"Saving a file"<<std::endl;
			std::vector<WindowEventProducer::FileDialogFilter> Filters;
			Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));
			Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));

			BoostPath SavePath = TutorialWindow->saveFileDialog("Save File Window",
																									  Filters,
																									  std::string("newFile.lua"),
																									  BoostPath(".."),
																									  true);
			//theTextEditor->saveFile(SavePath);
		}
   }

};


class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
        }
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
        }
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

    /******************************************************

             Add MouseListeners and WindowListeners 
			 to the WindowEvent.

    ******************************************************/

    TutorialMouseListener TheTutorialMouseListener;
	TutorialMouseListener1 BasicListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
	TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(90, 270, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


	LoadButton = Button::create();

	LoadButton->setMinSize(Vec2f(50, 25));
    LoadButton->setMaxSize(Vec2f(200, 100));
    LoadButton->setPreferredSize(Vec2f(100, 50));
    LoadButton->setToolTipText("Click to open a file browser window");
    LoadButton->setText("Load File");

	LoadButton->addActionListener(&BasicListener);
	  
	SaveButton = Button::create();

	SaveButton->setMinSize(Vec2f(50, 25));
    SaveButton->setMaxSize(Vec2f(200, 100));
    SaveButton->setPreferredSize(Vec2f(100, 50));
    SaveButton->setToolTipText("Click to save the currently opened file");
    SaveButton->setText("Save File");

	SaveButton->addActionListener(&BasicListener);

	theTextEditor = TextEditor::create();
	theTextEditor->setPreferredSize(Vec2f(600,400));

	/*

	UIFontRefPtr _Font = UIFont::create();
    _Font->setFamily("SANS");
    _Font->setGap(3);
    _Font->setGlyphPixelSize(46);
    _Font->setSize(15);
    _Font->setTextureWidth(0);
    _Font->setStyle(TextFace::STYLE_PLAIN);

	ExampleTextDomArea->setPreferredSize(Vec2f(600, 400));
	ExampleTextDomArea->setWrapStyleWord(false);
    ExampleTextDomArea->setMinSize(Vec2f(600,400));
	ExampleTextDomArea->setFont(_Font);

	ExampleAdvancedTextDomArea = OSG::AdvancedTextDomArea::create();
	ExampleAdvancedTextDomArea->setPreferredSize(Vec2f(600,400));
	ExampleAdvancedTextDomArea->setMinSize(Vec2f(600,400));
	ExampleAdvancedTextDomArea->setGutterVisible(true);
	ExampleAdvancedTextDomArea->pushToChildren(ExampleTextDomArea);
	ExampleAdvancedTextDomArea->setLayout(LayoutRefPtr(OSG::FlowLayout::create()));
	ExampleAdvancedTextDomArea->setPreferredSize(Vec2f(600,400));
	ExampleAdvancedTextDomArea->setMinSize(Vec2f(600,400));

	ScrollPanelRefPtr TextAreaScrollPanel = ScrollPanel::create();
    TextAreaScrollPanel->setPreferredSize(Vec2f(600,400));
	TextAreaScrollPanel->setMinSize(Vec2f(600,400));
	TextAreaScrollPanel->setViewComponent(ExampleAdvancedTextDomArea);

	*/	

    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

	LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

	InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
	MainInternalWindow->pushToChildren(theTextEditor);
	MainInternalWindow->pushToChildren(LoadButton);
	MainInternalWindow->pushToChildren(SaveButton);
	MainInternalWindow->setLayout(MainInternalWindowLayout);
	MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
	MainInternalWindow->setDrawTitlebar(true);
	MainInternalWindow->setResizable(false);


    /******************************************************

             The Drawing Surface is created the
			 same as with previous Tutorials
			 (however the MainInternalWindow is created
			 in a function below).

    ******************************************************/

    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
  
	TutorialDrawingSurface->openWindow(MainInternalWindow);

	/******************************************************

			Create the 3D UIRectangle.  This allows
			the DrawingSurface to be rotated relative
			to the screen, allowing a 3D aspect to
			the DrawingSurface.  The Surface
			can still be interacted with, so Buttons,
			Menus, etc. all will still function
			normally.

			-setPoint(Pnt3f): Determine the location
				of the UIRectangle in 3D space.  Keep
				in mind that (0,0,0) is located 
				directly in the center of the sceen.
				(For our purposes it is the center 
				of the tori.) The point is located
				on the lower left corner of the 
				rectangle.
			-setWidth(float): Determine the Width
				of the UIRectangle.  This may 
				physically appear different depending
				on where the UIRectangle is placed
				as above (due to it being located
				further away, etc).
			-setHeight(float): Determine the Height
				of the UIRectangle.  This may 
				physically appear different depending
				on where the UIRectangle is placed
				as above (due to it being located
				further away, etc).
			-setDrawingSurface(DrawingSurface):
				Determine what DrawingSurface is
				drawn on the UIRectangle.  This 
				will typically be the main
				DrawingSurface, however, multiple
				DrawingSurfaces can be used with
				multiple UIRectangles.


    ******************************************************/   

    //Make A 3D Rectangle to draw the UI on
    UIRectangleRefPtr ExampleUIRectangle = UIRectangle::create();
        ExampleUIRectangle->setPoint(Pnt3f(-400,-400,200));
        ExampleUIRectangle->setWidth(800.0);
        ExampleUIRectangle->setHeight(800.0);
        ExampleUIRectangle->setDrawingSurface(TutorialDrawingSurface);
    
	/******************************************************

			Because the previous Tutorials used a 
			Viewport to view the scene, which is
			no longer being used, the UIRectangle 
			must be added to the scene for it to 
			be displayed (identical to how the
			Torus is added).

			First, create a Node, and set its
			core to be the UIRectangle.  Then,
			add that to the scene Node which 
			is created above.  This scene is
			then set as the Root for the view.
			It is possible to change this Root
			to be just the UIRectangle (as
			commented out below).

    ******************************************************/   	
    NodeRefPtr ExampleUIRectangleNode = OSG::Node::create();
        ExampleUIRectangleNode->setCore(ExampleUIRectangle);
    
        // Add the UIRectangle as a child to the scene
        scene->addChild(ExampleUIRectangleNode);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);
    //mgr->setRoot(ExampleUIRectangleNode);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "3DNotepad!!");

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
//
//InternalWindowRefPtr createMainInternalWindow(void)
//{
//    /******************************************************
//
//            Create Button Components to be used with 
//            TabPanel and specify their characteristics.
//
//			Note: Buttons are used for simplicity,
//			any Component can be used as Tab content
//			or as a Tab.  A Panel with several
//			Buttons within it is also added.
//
//    ******************************************************/
//
//    ButtonRefPtr ExampleTabButton1 = OSG::Button::create();
//    ButtonRefPtr ExampleTabButton2 = OSG::Button::create();
//    ButtonRefPtr ExampleTabButton3 = OSG::Button::create();
//    ButtonRefPtr ExampleTabButton4 = OSG::Button::create();
//    ButtonRefPtr ExampleTabButton5 = OSG::Button::create();
//    ButtonRefPtr ExampleTabButton6 = OSG::Button::create();
//    ExampleTabContentA = OSG::Button::create();
//    ExampleTabContentB = OSG::Button::create();
//    ButtonRefPtr ExampleTabContentC = OSG::Button::create();
//    ButtonRefPtr ExampleTabContentD = OSG::Button::create();
//    ButtonRefPtr ExampleTabContentE = OSG::Button::create();
//    ButtonRefPtr ExampleTabContentF = OSG::Button::create();
//
//        ExampleTabButton1->setText("Tab1");
//    
//        ExampleTabButton2->setText("Tab2");
//        
//        ExampleTabButton3->setText("To Rotate");
//        
//        ExampleTabButton4->setText("Tab4");
//        
//        ExampleTabButton5->setText("To Zoom");
//        
//        ExampleTabButton6->setText("To Move");
//    
//        ExampleTabContentA->setText("Add another Tab");
//    // Add ActionListener
//    ExampleTabContentA->addActionListener( &TheAddTabActionListener);
//
//        ExampleTabContentB->setText("Add a Tab in Tab1!");
//    // Add ActionListener
//
//    ExampleTabContentB->addActionListener( &TheRemoveTabActionListener);
//
//        ExampleTabContentC->setText("Enable CapsLock, then rotate scene using left Mouse button!");
//        
//        ExampleTabContentD->setText("Enable CapsLock, then zoom in and out with right Mouse button and dragging");
//
//        ExampleTabContentE->setText("Enable CapsLock, then move using center Mouse button");
//        
//    /******************************************************
//
//            Create a Panel to add to the TabPanel
//
//    ******************************************************/
//
//    // Create and edit the Panel Buttons
//    ButtonRefPtr ExampleTabPanelButton1 = OSG::Button::create();
//    ButtonRefPtr ExampleTabPanelButton2 = OSG::Button::create();
//    ButtonRefPtr ExampleTabPanelButton3 = OSG::Button::create();
//    ButtonRefPtr ExampleTabPanelButton4 = OSG::Button::create();
//    ButtonRefPtr ExampleTabPanelButton5 = OSG::Button::create();
//    ButtonRefPtr ExampleTabPanelButton6 = OSG::Button::create();
//
//		ExampleTabPanelButton1->setText("This is a");
//	
//		ExampleTabPanelButton2->setText("sample");
//	
//		ExampleTabPanelButton3->setText("UIRectangle");
//	
//		ExampleTabPanelButton4->setText("containing");
//	
//		ExampleTabPanelButton5->setText("interactive");
//	
//		ExampleTabPanelButton6->setText("components");
//
//    // Create and edit Panel Layout
//    BoxLayoutRefPtr TabPanelLayout = OSG::BoxLayout::create();
//        TabPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
//
//    // Create and edit Panel
//    PanelRefPtr ExampleTabPanelPanel = OSG::Panel::create();
//        ExampleTabPanelPanel->setPreferredSize(Vec2f(180, 500));
//        ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton1);
//        ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton2);
//        ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton3);
//        ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton4);
//        ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton5);
//        ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton6);
//        ExampleTabPanelPanel->setLayout(TabPanelLayout);
//
//    ExampleTabPanel = OSG::TabPanel::create();
//        ExampleTabPanel->setPreferredSize(Vec2f(350,350));
//        ExampleTabPanel->addTab(ExampleTabButton1, ExampleTabContentA);
//        ExampleTabPanel->addTab(ExampleTabButton2, ExampleTabContentB);
//        ExampleTabPanel->addTab(ExampleTabButton3, ExampleTabContentC);
//        ExampleTabPanel->addTab(ExampleTabButton4, ExampleTabPanelPanel);
//        ExampleTabPanel->addTab(ExampleTabButton5, ExampleTabContentD);
//        ExampleTabPanel->addTab(ExampleTabButton6, ExampleTabContentE);
//        ExampleTabPanel->setTabAlignment(0.5f);
//        ExampleTabPanel->setTabPlacement(TabPanel::PLACEMENT_SOUTH);
//    ExampleTabPanel->setSelectedIndex(3);
//	
//    // Create The Main InternalWindow
//    // Create Background to be used with the Main InternalWindow
//    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
//        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
//
//    CardLayoutRefPtr MainInternalWindowLayout = OSG::CardLayout::create();
//
//    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
//       MainInternalWindow->pushToChildren(ExampleTabPanel);
//       MainInternalWindow->setLayout(MainInternalWindowLayout);
//       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
//	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
//	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
//	   MainInternalWindow->setDrawTitlebar(false);
//	   MainInternalWindow->setResizable(false);
//
//	return MainInternalWindow;
//}
//
