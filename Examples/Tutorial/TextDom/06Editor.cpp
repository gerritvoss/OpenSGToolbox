// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed

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
#include "OSGSimpleStatisticsForeground.h"

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

#include <OSGPlainDocument.h>
#include <OSGTextFileHandler.h>
#include <OSGTextEditor.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;
TextEditorRefPtr theTextEditor;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 03TextDomArea Headers
#include "OSGLayers.h"
#include "OSGButton.h"
#include "OSGLineBorder.h"
#include "OSGFlowLayout.h"
#include "OSGUIFont.h"
#include "OSGScrollPanel.h"
#include "OSGTextDomArea.h"
#include "OSGAdvancedTextDomArea.h"
#include "OSGButton.h"
#include "windows.h"
#include "OSGColorLayer.h"
#include "OSGLineBorder.h"

SYSTEMTIME now;

TextDomAreaRefPtr ExampleTextDomArea;
//AdvancedTextDomAreaRefPtr ExampleAdvancedTextDomArea;

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
	   else if(e->getKey() == KeyEvent::KEY_1 && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
	   {
		   theTextEditor->setClipboardVisible(!theTextEditor->getClipboardVisible());
	   }
	   else if(e->getKey() == KeyEvent::KEY_2 && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
	   {
		   theTextEditor->setIsSplit(!theTextEditor->getIsSplit());
	   }
	}

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

class TutorialMouseListener : public ActionListener
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
			

			GetSystemTime(&now);
			unsigned int t1 = now.wSecond * 1000 + now.wMilliseconds;

			theTextEditor->loadNewFile(FilesToOpen[0]);

			GetSystemTime(&now);
			unsigned int t2 = now.wSecond * 1000 + now.wMilliseconds;

			//std::cout<<"\nstart time in milliseconds:"<<t1<<std::endl;	// start time in milliseconds
			std::cout<<"\nduration in milliseconds:"<<t2-t1<<std::endl;		// end time in milliseconds

			
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
			ExampleTextDomArea->saveFile(SavePath);
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

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

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

    //// Create a simple Font to be used with the ExampleTextArea
    //UIFontRefPtr ExampleFont = OSG::UIFont::create();
    //     ExampleFont->setSize(16);

	TutorialMouseListener BasicListener;

  
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


	//Load Document
	//TheDocument = dynamic_pointer_cast<PlainDocument>(TextFileHandler::the()->read());


	UIFontRefPtr _Font = UIFont::create();
    _Font->setFamily("SANS");
    _Font->setGap(3);
    _Font->setGlyphPixelSize(46);
    _Font->setSize(15);
    _Font->setTextureWidth(0);
    _Font->setStyle(TextFace::STYLE_PLAIN);

	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
//	thePanel->setResizable(true);
	//pushToChildren(thePanel);

	/*if(TheDocument == NULL )
	{
		SWARNING<<"Error reading document.Exiting..."<<std::endl;
		return -1;
	}*/

		// Create a TextDomArea component
//		ExampleTextDomArea = OSG::TextDomArea::create();
//		ExampleTextDomArea->loadFile(BoostPath("D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TextDom\\Data\\SampleText3.txt"));
//
//        ExampleTextDomArea->setPreferredSize(Vec2f(600, 400));
//		ExampleTextDomArea->setWrapStyleWord(false);
//        ExampleTextDomArea->setMinSize(Vec2f(600,400));
//		//ExampleTextDomArea->setDocumentModel(TheDocument);
//		ExampleTextDomArea->setFont(_Font);
//		
//	ExampleAdvancedTextDomArea = OSG::AdvancedTextDomArea::create();
//	ExampleAdvancedTextDomArea->setPreferredSize(Vec2f(600,400));
//	ExampleAdvancedTextDomArea->setMinSize(Vec2f(600,400));
//	ExampleAdvancedTextDomArea->setGutterVisible(true);
////	ExampleAdvancedTextDomArea->setTextDomArea(ExampleTextDomArea);
//	ExampleAdvancedTextDomArea->pushToChildren(ExampleTextDomArea);
//	ExampleAdvancedTextDomArea->setLayout(LayoutRefPtr(OSG::FlowLayout::create()));
//	ExampleAdvancedTextDomArea->setPreferredSize(Vec2f(600,400));
//	ExampleAdvancedTextDomArea->setMinSize(Vec2f(600,400));


 //   ScrollPanelRefPtr TextAreaScrollPanel = ScrollPanel::create();
 //       TextAreaScrollPanel->setPreferredSize(Vec2f(600,400));
	//	TextAreaScrollPanel->setMinSize(Vec2f(600,400));
 //       //TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
 //   // Add the TextArea to the ScrollPanel so it is displayed
	//TextAreaScrollPanel->setViewComponent(ExampleAdvancedTextDomArea);
	ColorLayerRefPtr ExamplePanelBackground1 = OSG::ColorLayer::create();
    ExamplePanelBackground1->setColor(Color4f(0.0,0.0,0.0,1.0));

	LineBorderRefPtr ExamplePanelBorder1 = OSG::LineBorder::create();
    ExamplePanelBorder1->setColor(Color4f(0.9, 0.9, 0.9, 1.0));
    ExamplePanelBorder1->setWidth(3);

	theTextEditor = TextEditor::create();

	theTextEditor->setPreferredSize(Vec2f(600,400));
	//theTextEditor->setMinSize(Vec2f(600,400));
	//theTextEditor->setLayout(LayoutRefPtr(OSG::FlowLayout::create()));
    theTextEditor->setBackgrounds(ExamplePanelBackground1);
    theTextEditor->setBorders(ExamplePanelBorder1);
	//theTextEditor->pushToChildren(thePanel);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       //MainInternalWindow->pushToChildren(TextAreaScrollPanel);
	   MainInternalWindow->pushToChildren(theTextEditor);
	   MainInternalWindow->pushToChildren(LoadButton);
	   MainInternalWindow->pushToChildren(SaveButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
	   MainInternalWindow->setDrawTitlebar(true);
	   MainInternalWindow->setResizable(true);

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
	
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

    TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

	//mgr->setStatistics(true);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
		

    // Show the whole Scene
    mgr->showAll();

	
    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "03TextDomArea");

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
