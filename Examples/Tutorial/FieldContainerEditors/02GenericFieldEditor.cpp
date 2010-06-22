// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button and a ToggleButtoncreated in the OSG User 
// Interface library.
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
#include "OSGTabPanel.h"

#include "OSGButton.h"
#include "OSGLabel.h"
#include "OSGLayers.h"
#include "OSGBorders.h"
#include "OSGFlowLayout.h"
#include "OSGList.h"
#include "OSGDefaultListModel.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGScrollPanel.h"

#include "OSGUndoableCommand.h"
#include "OSGCommandManager.h"
#include "OSGUndoManager.h"
#include "OSGList.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGSolidBackground.h"
#include "OSGUIDrawUtils.h"
#include "OSGFieldEditorFactory.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

ListRefPtr UndoRedoList;
UndoManagerPtr TheUndoManager;
CommandManagerPtr TheCommandManager;
DefaultListModelRefPtr UndoRedoListModel;
ButtonRefPtr UndoButton;
ButtonRefPtr RedoButton;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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

class UndoButtonActionListener : public ActionListener
{
protected:

public:

	UndoButtonActionListener(void) : ActionListener()
	{
	}

   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
		TheUndoManager->undo();
    }
};

class RedoButtonActionListener : public ActionListener
{
protected:

public:

	RedoButtonActionListener(void) : ActionListener()
	{
	}

   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
		TheUndoManager->redo();
    }
};

class UndoManagerChangeListener : public ChangeListener
{
public:

	virtual void stateChanged(const ChangeEventUnrecPtr e)
	{
		while(UndoRedoListModel->getSize() > TheUndoManager->numberOfRedos() + TheUndoManager->numberOfUndos())
		{
			UndoRedoListModel->popBack();
		}

		//Resize
		while(UndoRedoListModel->getSize()-1 < TheUndoManager->numberOfRedos() + TheUndoManager->numberOfUndos())
		{
			UndoRedoListModel->pushBack(boost::any(std::string("")));
		}

		UInt32 UndoCount(TheUndoManager->numberOfUndos());
		for(UInt32 i(0) ; i<UndoCount ; ++i)
		{
			UndoRedoListModel->set(i+1, boost::any(std::string(TheUndoManager->editToBeUndone(i)->getUndoPresentationName())));
		}
		UInt32 RedoCount(TheUndoManager->numberOfRedos());
		for(UInt32 i(0) ; i<RedoCount ; ++i)
		{
			UndoRedoListModel->set(i+TheUndoManager->numberOfUndos()+1, boost::any(std::string(TheUndoManager->editToBeRedone(i)->getRedoPresentationName())));
		}

		if((UndoCount == 0 && UndoButton->getEnabled()) ||
			(UndoCount != 0 && !UndoButton->getEnabled()) )
		{
				UndoButton->setEnabled(UndoCount != 0);
		}
		if((RedoCount == 0 && RedoButton->getEnabled()) ||
			(RedoCount != 0 && !RedoButton->getEnabled()) )
		{
				RedoButton->setEnabled(RedoCount != 0);
		}
	}
};

// Setup a FontListener to change the label's font
// when a different item in the FontList is
// selected
class UndoRedoListListener: public ListSelectionListener
{
  public:
    virtual void selectionChanged(const ListSelectionEventUnrecPtr e)
    {
		if(!UndoRedoList->getSelectionModel()->isSelectionEmpty())
        {
			Int32 ListSelectedIndex(UndoRedoList->getSelectionModel()->getAnchorSelectionIndex());


			TheUndoManager->undoOrRedoTo(ListSelectedIndex);
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

    //Background
    SolidBackgroundRefPtr TutorialBackground = SolidBackground::create();
    TutorialBackground->setColor(Color3f(1.0,0.0,0.0));

	TheUndoManager = UndoManager::create();
	UndoManagerChangeListener TheUndoManagerChangeListener;
	TheUndoManager->addChangeListener(&TheUndoManagerChangeListener);
    TheCommandManager = CommandManager::create(TheUndoManager);

    //Background Editor Field
    FieldEditorComponentRefPtr TheEditor = FieldEditorFactory::the()->createDefaultEditor(TutorialBackground, SolidBackground::ColorFieldId, TheCommandManager);
    TheEditor->setPreferredSize(Vec2f(100.0f, 20.0f));
	
    //UndoList
	UndoRedoListModel = DefaultListModel::create();
    UndoRedoListModel->pushBack(boost::any(std::string("Top")));
	ListSelectionModelPtr UndoRedoListSelectionModel(new DefaultListSelectionModel());

	UndoRedoList = List::create();
    UndoRedoList->setPreferredSize(Vec2f(200, 300));
    UndoRedoList->setOrientation(List::VERTICAL_ORIENTATION);
	UndoRedoList->setModel(UndoRedoListModel);

    UndoRedoList->setSelectionModel(UndoRedoListSelectionModel);

    UndoRedoListListener TheUndoRedoListListener;
    UndoRedoList->getSelectionModel()->addListSelectionListener(&TheUndoRedoListListener);

    UndoButton = OSG::Button::create();
    UndoButton->setText("Undo");
	UndoButton->setEnabled(TheUndoManager->numberOfUndos() != 0);
    UndoButtonActionListener TheUndoButtonActionListener;
    UndoButton->addActionListener(&TheUndoButtonActionListener);
	

    RedoButton = OSG::Button::create();
    RedoButton->setText("Redo");
	RedoButton->setEnabled(TheUndoManager->numberOfRedos() != 0);
    RedoButtonActionListener TheRedoButtonActionListener;
    RedoButton->addActionListener(&TheRedoButtonActionListener);

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRefPtr UndoRedoScrollPanel = ScrollPanel::create();
    UndoRedoScrollPanel->setPreferredSize(Vec2f(200,200));
    UndoRedoScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    UndoRedoScrollPanel->setViewComponent(UndoRedoList);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
    MainInternalWindow->pushToChildren(TheEditor);
    MainInternalWindow->pushToChildren(UndoRedoScrollPanel);
    MainInternalWindow->pushToChildren(UndoButton);
    MainInternalWindow->pushToChildren(RedoButton);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.95f,0.95f));
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
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
    TutorialViewport->addForeground(TutorialUIForeground);
    TutorialViewport->setBackground(TutorialBackground);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                                WinSize,
                                "02GenericFieldEditor");

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
