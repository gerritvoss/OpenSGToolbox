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
#include "OSGSolidBackground.h"
#include "OSGUIDrawUtils.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGFieldContainerEditorDialog.h"
#include "OSGNameAttachment.h"
#include "OSGDialogWindow.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

//Ctrl+q handler
void keyTyped(KeyEventDetails* const details,
              CommandManagerPtr TheCommandManager,
              FieldContainer* const container,
              List* const UndoRedoList)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    if(details->getKey() == KeyEventDetails::KEY_E && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        openDefaultFCTreeEditorDialog(container, TheCommandManager, UndoRedoList->getParentWindow()->getParentDrawingSurface());
    }
}

void handleUndoButtonAction(ActionEventDetails* const details,
                            UndoManagerPtr TheUndoManager)
{
	TheUndoManager->undo();
}

void handleRedoButtonActionPerformed(ActionEventDetails* const details,
                            UndoManagerPtr TheUndoManager)
{
	TheUndoManager->redo();
}

void handleUndoManagerStateChanged(ChangeEventDetails* const details,
                                   Button* const undoButton,
                                   Button* const redoButton,
                                   DefaultListModel* const undoRedoListModel,
                                   UndoManagerPtr TheUndoManager)
{
	while(undoRedoListModel->getSize()-1 > TheUndoManager->numberOfRedos() + TheUndoManager->numberOfUndos())
	{
		undoRedoListModel->popBack();
	}

	//Resize
	while(undoRedoListModel->getSize()-1 < TheUndoManager->numberOfRedos() + TheUndoManager->numberOfUndos())
	{
		undoRedoListModel->pushBack(boost::any(std::string("")));
	}

	UInt32 UndoCount(TheUndoManager->numberOfUndos());
	for(UInt32 i(0) ; i<UndoCount ; ++i)
	{
		undoRedoListModel->set(i+1, boost::any(std::string(TheUndoManager->editToBeUndone(i)->getUndoPresentationName())));
	}
	UInt32 RedoCount(TheUndoManager->numberOfRedos());
	for(UInt32 i(0) ; i<RedoCount ; ++i)
	{
		undoRedoListModel->set(i+TheUndoManager->numberOfUndos()+1, boost::any(std::string(TheUndoManager->editToBeRedone(i)->getRedoPresentationName())));
	}

	if((UndoCount == 0 && undoButton->getEnabled()) ||
		(UndoCount != 0 && !undoButton->getEnabled()) )
	{
			undoButton->setEnabled(UndoCount != 0);
	}
	if((RedoCount == 0 && redoButton->getEnabled()) ||
		(RedoCount != 0 && !redoButton->getEnabled()) )
	{
			redoButton->setEnabled(RedoCount != 0);
	}
}

// Setup a FontListener to change the label's font
// when a different item in the FontList is
// selected
void handleUndoRedoListSelectionChanged(ListSelectionEventDetails* const details,
                                        UndoManagerPtr TheUndoManager)
{
	if(!dynamic_cast<ListSelectionModel*>(details->getSource())->isSelectionEmpty())
    {
		Int32 ListSelectedIndex(dynamic_cast<ListSelectionModel*>(details->getSource())->getAnchorSelectionIndex());

		TheUndoManager->undoOrRedoTo(ListSelectedIndex);
    }
}

int main(int argc, char **argv)
{
    preloadSharedObject("OSGImageFileIO");
    preloadSharedObject("OSGContribParticleSystem");

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

        // Make Torus Node (creates Torus in background of scene)
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

        // Tell the Manager what to manage
        sceneManager.setRoot(scene);
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        //Background
        SolidBackgroundRefPtr TutorialBackground = SolidBackground::create();
        TutorialBackground->setColor(Color3f(1.0,0.0,0.0));

    		    
        UndoManagerPtr TheUndoManager = UndoManager::create();
        CommandManagerPtr TheCommandManager = CommandManager::create(TheUndoManager);

        //UndoList
	    DefaultListModelRecPtr UndoRedoListModel = DefaultListModel::create();
        UndoRedoListModel->pushBack(boost::any(std::string("Top")));

	    ListRecPtr UndoRedoList = List::create();
        UndoRedoList->setPreferredSize(Vec2f(200, 300));
        UndoRedoList->setOrientation(List::VERTICAL_ORIENTATION);
	    UndoRedoList->setModel(UndoRedoListModel);

        UndoRedoList->getSelectionModel()->connectSelectionChanged(boost::bind(&handleUndoRedoListSelectionChanged, _1, TheUndoManager));

        ButtonRecPtr UndoButton = OSG::Button::create();
        UndoButton->setText("Undo");
	    UndoButton->setEnabled(false);
        UndoButton->connectActionPerformed(boost::bind(&handleUndoButtonAction, _1, TheUndoManager));
    	

        ButtonRecPtr RedoButton = OSG::Button::create();
        RedoButton->setText("Redo");
	    RedoButton->setEnabled(false);
        RedoButton->connectActionPerformed(boost::bind(&handleRedoButtonActionPerformed, _1, TheUndoManager));

        TheUndoManager->connectStateChanged(boost::bind(&handleUndoManagerStateChanged, _1, UndoButton.get(), RedoButton.get(), UndoRedoListModel.get(), TheUndoManager));

        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        ScrollPanelRefPtr UndoRedoScrollPanel = ScrollPanel::create();
        UndoRedoScrollPanel->setPreferredSize(Vec2f(200,200));
        UndoRedoScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        UndoRedoScrollPanel->setViewComponent(UndoRedoList);

        //Background Editor Field
        //FieldContainerEditorComponentRefPtr TheEditor = FieldContainerEditorFactory::the()->createDefaultEditor(TutorialBackground, TheCommandManager);
        FieldContainerEditorComponentRefPtr TheEditor = FieldContainerEditorFactory::the()->createDefaultEditor(RedoButton, TheCommandManager);
        //FieldContainerEditorComponentRefPtr TheEditor = FieldContainerEditorFactory::the()->createDefaultEditor(dynamic_cast<Geometry*>(TorusGeometryNode->getCore())->getMaterial(), TheCommandManager);

        ScrollPanelRefPtr EditorScrollPanel = ScrollPanel::create();
        EditorScrollPanel->setPreferredSize(Vec2f(300,400));
        EditorScrollPanel->setViewComponent(TheEditor);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
        InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
        LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
        MainInternalWindow->pushToChildren(EditorScrollPanel);
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


        // Add the UI Foreground Object to the Scene
        TutorialViewport->addForeground(TutorialUIForeground);
        TutorialViewport->setBackground(TutorialBackground);

        // Show the whole Scene
        sceneManager.showAll();
		sceneManager.setStatistics(true);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, TheCommandManager, TutorialViewport.get(), UndoRedoList.get()));


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                    WinSize,
                                    "03GenericFieldContainerEditor");

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
