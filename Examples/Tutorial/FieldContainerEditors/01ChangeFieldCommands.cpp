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
#include "OSGSysFieldTraits.h"
#include "OSGList.h"
#include "OSGMFieldListModel.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGGradientBackground.h"
#include "OSGPopupMenu.h"
#include "OSGDialogWindow.h"
#include "OSGUIDrawUtils.h"

#include "OSGCompoundUndoableCommand.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGAddFieldElementCommand.h"
#include "OSGInsertFieldElementCommand.h"
#include "OSGMoveFieldElementCommand.h"
#include "OSGSwapFieldElementCommand.h"
#include "OSGRemoveFieldElementCommand.h"
#include "OSGCreateFieldContainerCommand.h"
#include "OSGRandomPoolManager.h"

#include <sstream>
#include <boost/lexical_cast.hpp>

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
ListRefPtr MultiFieldList;
MFieldListModelRefPtr MultiFieldListModel;
ListRefPtr MultiPtrFieldList;
MFieldListModelRefPtr MultiPtrFieldListModel;
GradientBackgroundRefPtr TutorialBackground;
LabelRefPtr SinglePtrFieldLabel;
PanelRefPtr MultiPtrFieldInnerPanel;

PanelUnrecPtr createSingleFieldPanel(void);
PanelUnrecPtr createMultiFieldPanel(void);
PanelUnrecPtr createSinglePtrFieldPanel(void);
PanelUnrecPtr createMultiPtrFieldPanel(void);

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

ColorLayerRefPtr ChangableBackground;
LineBorderRefPtr ChangableBorder;

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

    /******************************************************

         Create an ActionListener to display text
         in the Console Window when the Button is
         pressed (causing an action).

    ******************************************************/

class SetBorderColorActionListener : public ActionListener
{
protected:
	Color4f _ChangeToColor;
	LineBorderRefPtr _TheBorder;
	CommandManagerPtr _CommandManager;

public:

	SetBorderColorActionListener(LineBorderRefPtr TheBorder, Color4f ChangeToColor, CommandManagerPtr Manager) : ActionListener(),
		_TheBorder(TheBorder),
		_ChangeToColor(ChangeToColor),
		_CommandManager(Manager)
	{
	}

   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::ostringstream StrStream;
        operator<<(StrStream, _ChangeToColor);
        SetFieldValueCommandPtr TheCommand = SetFieldValueCommand::create(_TheBorder,LineBorder::ColorFieldId, StrStream.str());

		_CommandManager->executeCommand(TheCommand);
    }
};

class SetBackgroundColorActionListener : public ActionListener
{
protected:
	Color4f _ChangeToColor;
	ColorLayerRefPtr _TutorialBackground;
	CommandManagerPtr _CommandManager;

public:

	SetBackgroundColorActionListener(ColorLayerRefPtr TutorialBackground, Color4f ChangeToColor, CommandManagerPtr Manager) : ActionListener(),
		_TutorialBackground(TutorialBackground),
		_ChangeToColor(ChangeToColor),
		_CommandManager(Manager)
	{
	}

   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::ostringstream StrStream;
        operator<<(StrStream, _ChangeToColor);
        SetFieldValueCommandPtr TheCommand = SetFieldValueCommand::create(_TutorialBackground,ColorLayer::ColorFieldId, StrStream.str());

		_CommandManager->executeCommand(TheCommand);
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
    TutorialBackground = GradientBackground::create();
    TutorialBackground->addLine(Color3f(1.0,0.0,0.0), 0.0);
    TutorialBackground->addLine(Color3f(0.0,1.0,0.0), 0.2);
    TutorialBackground->addLine(Color3f(0.0,0.0,1.0), 0.4);
    TutorialBackground->addLine(Color3f(0.0,1.0,1.0), 0.6);
    TutorialBackground->addLine(Color3f(1.0,1.0,0.0), 0.8);
    TutorialBackground->addLine(Color3f(1.0,1.0,1.0), 1.0);

	TheUndoManager = UndoManager::create();
	UndoManagerChangeListener TheUndoManagerChangeListener;
	TheUndoManager->addChangeListener(&TheUndoManagerChangeListener);
    
    LabelRefPtr SingleFieldLabel = OSG::Label::create();
    SingleFieldLabel->setText("Single Field");
    SingleFieldLabel->setBorders(NULL);
    SingleFieldLabel->setBackgrounds(NULL);

    LabelRefPtr MultiFieldLabel = OSG::Label::create();
    MultiFieldLabel->setText("Multi Field");
    MultiFieldLabel->setBorders(NULL);
    MultiFieldLabel->setBackgrounds(NULL);

    LabelRefPtr SinglePtrFieldLabel = OSG::Label::create();
    SinglePtrFieldLabel->setText("Single Ptr Field");
    SinglePtrFieldLabel->setBorders(NULL);
    SinglePtrFieldLabel->setBackgrounds(NULL);

    LabelRefPtr MultiPtrFieldLabel = OSG::Label::create();
    MultiPtrFieldLabel->setText("Multi Ptr Field");
    MultiPtrFieldLabel->setBorders(NULL);
    MultiPtrFieldLabel->setBackgrounds(NULL);

    TabPanelRefPtr ExampleTabPanel = OSG::TabPanel::create();
    ExampleTabPanel->setPreferredSize(Vec2f(600,600));
    ExampleTabPanel->addTab(SingleFieldLabel, createSingleFieldPanel());
    ExampleTabPanel->addTab(MultiFieldLabel, createMultiFieldPanel());
    ExampleTabPanel->addTab(SinglePtrFieldLabel, createSinglePtrFieldPanel());
    ExampleTabPanel->addTab(MultiPtrFieldLabel, createMultiPtrFieldPanel());
    ExampleTabPanel->setTabAlignment(0.5f);
    ExampleTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    ExampleTabPanel->setSelectedIndex(0);

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
       MainInternalWindow->pushToChildren(ExampleTabPanel);
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
            "01ChangeFieldCommands");

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


PanelUnrecPtr createSingleFieldPanel(void)
{

    ChangableBorder = OSG::LineBorder::create();
		ChangableBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    
	ChangableBackground = OSG::ColorLayer::create();
		ChangableBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    LabelRefPtr ChangableLabel = OSG::Label::create();

            ChangableLabel->setText("Changable");
            ChangableLabel->setBorders(ChangableBorder);
            ChangableLabel->setBackgrounds(ChangableBackground);

	//Command Buttons

    TheCommandManager = CommandManager::create(TheUndoManager);
    ButtonRefPtr BorderRedButton = OSG::Button::create();
            BorderRedButton->setText("Border Red");
    SetBorderColorActionListener* TheSetRedBorderColorActionListener = new SetBorderColorActionListener(ChangableBorder, Color4f(1.0,0.0,0.0,1.0), TheCommandManager);
    BorderRedButton->addActionListener(TheSetRedBorderColorActionListener);
	
    ButtonRefPtr BorderGreenButton = OSG::Button::create();
            BorderGreenButton->setText("Border Green");
    SetBorderColorActionListener* TheSetGreenBorderColorActionListener = new SetBorderColorActionListener(ChangableBorder, Color4f(0.0,1.0,0.0,1.0), TheCommandManager);
    BorderGreenButton->addActionListener(TheSetGreenBorderColorActionListener);
	
    ButtonRefPtr BorderBlueButton = OSG::Button::create();
            BorderBlueButton->setText("Border Blue");
    SetBorderColorActionListener* TheSetBlueBorderColorActionListener = new SetBorderColorActionListener(ChangableBorder, Color4f(0.0,0.0,1.0,1.0), TheCommandManager);
    BorderBlueButton->addActionListener(TheSetBlueBorderColorActionListener);
	
	//Background
    ButtonRefPtr BackgroundRedButton = OSG::Button::create();
            BackgroundRedButton->setText("Background Red");
    SetBackgroundColorActionListener* TheSetRedBackgroundColorActionListener = new SetBackgroundColorActionListener(ChangableBackground, Color4f(1.0,0.0,0.0,1.0), TheCommandManager);
    BackgroundRedButton->addActionListener(TheSetRedBackgroundColorActionListener);
	
    ButtonRefPtr BackgroundGreenButton = OSG::Button::create();
            BackgroundGreenButton->setText("Background Green");
    SetBackgroundColorActionListener* TheSetGreenBackgroundColorActionListener = new SetBackgroundColorActionListener(ChangableBackground, Color4f(0.0,1.0,0.0,1.0), TheCommandManager);
    BackgroundGreenButton->addActionListener(TheSetGreenBackgroundColorActionListener);
	
    ButtonRefPtr BackgroundBlueButton = OSG::Button::create();
            BackgroundBlueButton->setText("Background Blue");
    SetBackgroundColorActionListener* TheSetBlueBackgroundColorActionListener = new SetBackgroundColorActionListener(ChangableBackground, Color4f(0.0,0.0,1.0,1.0), TheCommandManager);
    BackgroundBlueButton->addActionListener(TheSetBlueBackgroundColorActionListener);

    LayoutRefPtr ThePanelLayout = OSG::FlowLayout::create();

    PanelRefPtr ThePanel = Panel::createEmpty();
    ThePanel->setLayout(ThePanelLayout);
    ThePanel->pushToChildren(BorderRedButton);
    ThePanel->pushToChildren(BorderGreenButton);
    ThePanel->pushToChildren(BorderBlueButton);
    ThePanel->pushToChildren(BackgroundRedButton);
    ThePanel->pushToChildren(BackgroundGreenButton);
    ThePanel->pushToChildren(BackgroundBlueButton);
    ThePanel->pushToChildren(ChangableLabel);

    return ThePanel;
    
}

class SetMultiFieldActionListener : public ActionListener, public DialogWindowListener
{
protected:

public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("1 0 0");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Set the value", "Please enter a color below", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }
   

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            SetFieldValueCommandPtr TheCommand = SetFieldValueCommand::create(TutorialBackground,GradientBackground::ColorFieldId, e->getInput(), MultiFieldList->getSelectionModel()->getMinSelectionIndex());

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};


class AddMultiFieldActionListener : public ActionListener, public DialogWindowListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("1 0 0");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Add value", "Please enter a color below", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            UndoableCommandPtr TheCommand1 = AddFieldElementCommand::create(TutorialBackground,GradientBackground::ColorFieldId, e->getInput());
            UndoableCommandPtr TheCommand2 = AddFieldElementCommand::create(TutorialBackground,GradientBackground::PositionFieldId, "1.0");

            std::vector<UndoableCommandPtr> CommandVec;
            CommandVec.push_back(TheCommand1);
            CommandVec.push_back(TheCommand2);

            CommandPtr TheCommand = CompoundUndoableCommand::create(CommandVec);
		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

class MoveMultiFieldActionListener : public ActionListener, public DialogWindowListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("0");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Move selected index to", "Please enter the index to move to", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            CommandPtr TheCommand = MoveFieldElementCommand::create(TutorialBackground,GradientBackground::ColorFieldId, MultiFieldList->getSelectionModel()->getMinSelectionIndex(), boost::lexical_cast<UInt32>(e->getInput()));

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

class InsertMultiFieldActionListener : public ActionListener, public DialogWindowListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("1 0 0");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Insert the value", "Please enter a color below", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            UndoableCommandPtr TheCommand1 = InsertFieldElementCommand::create(TutorialBackground,GradientBackground::ColorFieldId, e->getInput(), MultiFieldList->getSelectionModel()->getMinSelectionIndex());

            UndoableCommandPtr TheCommand2 = InsertFieldElementCommand::create(TutorialBackground,GradientBackground::PositionFieldId, "1.0", MultiFieldList->getSelectionModel()->getMinSelectionIndex());

            std::vector<UndoableCommandPtr> CommandVec;
            CommandVec.push_back(TheCommand1);
            CommandVec.push_back(TheCommand2);

            CommandPtr TheCommand = CompoundUndoableCommand::create(CommandVec);
		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

class SwapMultiFieldActionListener : public ActionListener, public DialogWindowListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("0");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Swap selected index with", "Please enter the index to move to", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            CommandPtr TheCommand = SwapFieldElementCommand::create(TutorialBackground,GradientBackground::ColorFieldId, MultiFieldList->getSelectionModel()->getMinSelectionIndex(), boost::lexical_cast<UInt32>(e->getInput()));

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

class RemoveMultiFieldActionListener : public ActionListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        if(!MultiFieldList->getSelectionModel()->isSelectionEmpty())
        {
            UndoableCommandPtr TheCommand1 = RemoveFieldElementCommand::create(TutorialBackground,GradientBackground::ColorFieldId, MultiFieldList->getSelectionModel()->getMinSelectionIndex());


            UndoableCommandPtr TheCommand2 = RemoveFieldElementCommand::create(TutorialBackground,GradientBackground::PositionFieldId, MultiFieldList->getSelectionModel()->getMinSelectionIndex());

            std::vector<UndoableCommandPtr> CommandVec;
            CommandVec.push_back(TheCommand1);
            CommandVec.push_back(TheCommand2);

            CommandPtr TheCommand = CompoundUndoableCommand::create(CommandVec);
		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

PanelUnrecPtr createMultiFieldPanel(void)
{
    //Popup Menu
    MenuItemRefPtr RemoveIndexMenuItem = MenuItem::create();
    RemoveIndexMenuItem->setText("Remove Index");
    RemoveIndexMenuItem->addActionListener(new RemoveMultiFieldActionListener());

    MenuItemRefPtr SetValueMenuItem = MenuItem::create();
    SetValueMenuItem->setText("Set Value");
    SetValueMenuItem->addActionListener(new SetMultiFieldActionListener());
    
    MenuItemRefPtr AddValueMenuItem = MenuItem::create();
    AddValueMenuItem->setText("Add Value");
    AddValueMenuItem->addActionListener(new AddMultiFieldActionListener());
    
    MenuItemRefPtr InsertIndexMenuItem = MenuItem::create();
    InsertIndexMenuItem->setText("Insert Value");
    InsertIndexMenuItem->addActionListener(new InsertMultiFieldActionListener());
    
    MenuItemRefPtr MoveIndexMenuItem = MenuItem::create();
    MoveIndexMenuItem->setText("Move Value");
    MoveIndexMenuItem->addActionListener(new MoveMultiFieldActionListener());
    
    MenuItemRefPtr SwapIndexMenuItem = MenuItem::create();
    SwapIndexMenuItem->setText("Swap Value");
    SwapIndexMenuItem->addActionListener(new SwapMultiFieldActionListener());

    PopupMenuRefPtr MultiFieldListPopupMenu = PopupMenu::create();
    MultiFieldListPopupMenu->addItem(SetValueMenuItem);
    MultiFieldListPopupMenu->addItem(AddValueMenuItem);
    MultiFieldListPopupMenu->addItem(InsertIndexMenuItem);
    MultiFieldListPopupMenu->addItem(MoveIndexMenuItem);
    MultiFieldListPopupMenu->addItem(SwapIndexMenuItem);
    MultiFieldListPopupMenu->addItem(RemoveIndexMenuItem);

    //Multi-field List Model
	MultiFieldListModel = MFieldListModel::create();
    MultiFieldListModel->setContainer(TutorialBackground);
    MultiFieldListModel->setFieldId(GradientBackground::ColorFieldId);
    //MultiFieldListModel->setFieldId(GradientBackground::PositionFieldId);

    //List
    MultiFieldList = List::create();
    MultiFieldList->setPreferredSize(Vec2f(200, 300));
    MultiFieldList->setOrientation(List::VERTICAL_ORIENTATION);
	MultiFieldList->setModel(MultiFieldListModel);
    ListSelectionModelPtr MultiFieldListSelectionModel(new DefaultListSelectionModel());
    MultiFieldList->setSelectionModel(MultiFieldListSelectionModel);
    MultiFieldList->setPopupMenu(MultiFieldListPopupMenu);

    // Create a ScrollPanel for easier viewing of the List
    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(MultiFieldList);

    // Create MainFramelayout
    FlowLayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
    MainInternalWindowLayout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);
    MainInternalWindowLayout->setMajorAxisAlignment(0.5f);
    MainInternalWindowLayout->setMinorAxisAlignment(0.5f);

    //Label
    LabelRefPtr ListLabel = Label::create();
    ListLabel->setText("Background Colors List");
    ListLabel->setPreferredSize(Vec2f(200.0f, ListLabel->getPreferredSize().y()));


    //Panel
    FlowLayoutRefPtr ThePanelLayout = OSG::FlowLayout::create();
    ThePanelLayout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);
    ThePanelLayout->setMajorAxisAlignment(0.5f);
    ThePanelLayout->setMinorAxisAlignment(0.5f);

    PanelRefPtr ThePanel = Panel::createEmpty();
    ThePanel->setLayout(ThePanelLayout);
    ThePanel->pushToChildren(ListLabel);
    ThePanel->pushToChildren(ExampleScrollPanel);

    return ThePanel;
    
}

class SinglePtrFieldCreateActionListener : public ActionListener, public DialogWindowListener
{
protected:

public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("ColorLayer");
        inputValues.push_back("EmptyLayer");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Create component background", "Please select the component background to create", DialogWindow::INPUT_COMBO,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }
   

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            //Create the Layer FieldContainer
            CreateFieldContainerCommandPtr CreateCommand = CreateFieldContainerCommand::create(e->getInput());

		    TheCommandManager->executeCommand(CreateCommand);

            //If the layer is a ColorLayer then give it a random color
            if(CreateCommand->getContainer()->getType() == ColorLayer::getClassType())
            {
                Color4f RandColor(RandomPoolManager::getRandomReal32(0.0f,1.0f),
                                  RandomPoolManager::getRandomReal32(0.0f,1.0f),
                                  RandomPoolManager::getRandomReal32(0.0f,1.0f),
                                  1.0f);

                dynamic_cast<ColorLayer*>(CreateCommand->getContainer())->setColor(RandColor);
            }


            //Set the background layer to use the newly create layer
            SetFieldValueCommandPtr SetFieldCommand = SetFieldValueCommand::create(SinglePtrFieldLabel,Component::BackgroundFieldId, boost::lexical_cast<std::string>(CreateCommand->getContainer()->getId()));

		    TheCommandManager->executeCommand(SetFieldCommand);
        }
    }
};

PanelUnrecPtr createSinglePtrFieldPanel(void)
{
    SinglePtrFieldLabel = OSG::Label::create();

    SinglePtrFieldLabel->setText("Changable");
    SinglePtrFieldLabel->setBorders(NULL);
    
    ButtonRefPtr SinglePtrFieldCreateBackgroundButton = OSG::Button::create();
    SinglePtrFieldCreateBackgroundButton->setText("Create Background");
    SinglePtrFieldCreateBackgroundButton->setPreferredSize(Vec2f(175.0f,SinglePtrFieldCreateBackgroundButton->getPreferredSize().y()));
    SinglePtrFieldCreateActionListener* TheCreateBackgroundActionListener = new SinglePtrFieldCreateActionListener();
    SinglePtrFieldCreateBackgroundButton->addActionListener(TheCreateBackgroundActionListener);

    LayoutRefPtr ThePanelLayout = OSG::FlowLayout::create();

    PanelRefPtr ThePanel = Panel::createEmpty();
    ThePanel->setLayout(ThePanelLayout);
    ThePanel->pushToChildren(SinglePtrFieldLabel);
    ThePanel->pushToChildren(SinglePtrFieldCreateBackgroundButton);

    return ThePanel;
    
}

class SetMultiPtrFieldActionListener : public ActionListener, public DialogWindowListener
{
protected:

public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("0");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Assign the button by Id", "Please enter a button Id", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }
   

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            SetFieldValueCommandPtr TheCommand = SetFieldValueCommand::create(MultiPtrFieldInnerPanel,Panel::ChildrenFieldId, e->getInput(), MultiPtrFieldList->getSelectionModel()->getMinSelectionIndex());

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};


class AddMultiPtrFieldActionListener : public ActionListener, public DialogWindowListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("C");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Add a new button", "Please enter text for the button", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            ButtonUnrecPtr NewButton = Button::create();
            NewButton->setText(e->getInput());

            CommandPtr TheCommand = AddFieldElementCommand::create(MultiPtrFieldInnerPanel,Panel::ChildrenFieldId, boost::lexical_cast<std::string>(NewButton->getId()));

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

class MoveMultiPtrFieldActionListener : public ActionListener, public DialogWindowListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("0");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Move selected index to", "Please enter the index to move to", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            CommandPtr TheCommand = MoveFieldElementCommand::create(MultiPtrFieldInnerPanel,Panel::ChildrenFieldId, MultiPtrFieldList->getSelectionModel()->getMinSelectionIndex(), boost::lexical_cast<UInt32>(e->getInput()));

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

class InsertMultiPtrFieldActionListener : public ActionListener, public DialogWindowListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("C");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Insert a button", "Please enter text for the button", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            ButtonUnrecPtr NewButton = Button::create();
            NewButton->setText(e->getInput());

            CommandPtr TheCommand = InsertFieldElementCommand::create(MultiPtrFieldInnerPanel,Panel::ChildrenFieldId, boost::lexical_cast<std::string>(NewButton->getId()), MultiPtrFieldList->getSelectionModel()->getMinSelectionIndex());

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

class SwapMultiPtrFieldActionListener : public ActionListener, public DialogWindowListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("0");

        DialogWindowRefPtr TheDialog;
        TheDialog = DialogWindow::createInputDialog("Swap selected index with", "Please enter the index to swap with", DialogWindow::INPUT_TEXT,true,inputValues);
        TheDialog->setAllwaysOnTop(true);
        TheDialog->addDialogWindowListener(this);

        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
    }

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {
    }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
    {
        if(e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
        {
            CommandPtr TheCommand = SwapFieldElementCommand::create(MultiPtrFieldInnerPanel,Panel::ChildrenFieldId, MultiPtrFieldList->getSelectionModel()->getMinSelectionIndex(), boost::lexical_cast<UInt32>(e->getInput()));

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

class RemoveMultiPtrFieldActionListener : public ActionListener
{
public:
   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        if(!MultiPtrFieldList->getSelectionModel()->isSelectionEmpty())
        {
            UndoableCommandPtr TheCommand = RemoveFieldElementCommand::create(MultiPtrFieldInnerPanel,Panel::ChildrenFieldId, MultiPtrFieldList->getSelectionModel()->getMinSelectionIndex());

		    TheCommandManager->executeCommand(TheCommand);
        }
    }
};

PanelUnrecPtr createMultiPtrFieldPanel(void)
{
    //Buttons for Inner Panel
    ButtonRefPtr AButton = Button::create();
    AButton->setText("A");

    ButtonRefPtr BButton = Button::create();
    BButton->setText("B");

    //Inner Panel
    LayoutRefPtr MultiPtrFieldInnerPanelLayout = OSG::FlowLayout::create();

    MultiPtrFieldInnerPanel = OSG::Panel::create();
    MultiPtrFieldInnerPanel->setLayout(MultiPtrFieldInnerPanelLayout);
    MultiPtrFieldInnerPanel->setPreferredSize(Vec2f(200.0f, 200.0f));
    MultiPtrFieldInnerPanel->pushToChildren(AButton);
    MultiPtrFieldInnerPanel->pushToChildren(BButton);

    //Popup Menu
    MenuItemRefPtr RemoveIndexMenuItem = MenuItem::create();
    RemoveIndexMenuItem->setText("Remove Index");
    RemoveIndexMenuItem->addActionListener(new RemoveMultiPtrFieldActionListener());

    MenuItemRefPtr SetValueMenuItem = MenuItem::create();
    SetValueMenuItem->setText("Set Value");
    SetValueMenuItem->addActionListener(new SetMultiPtrFieldActionListener());
    
    MenuItemRefPtr AddValueMenuItem = MenuItem::create();
    AddValueMenuItem->setText("Add Value");
    AddValueMenuItem->addActionListener(new AddMultiPtrFieldActionListener());
    
    MenuItemRefPtr InsertIndexMenuItem = MenuItem::create();
    InsertIndexMenuItem->setText("Insert Value");
    InsertIndexMenuItem->addActionListener(new InsertMultiPtrFieldActionListener());
    
    MenuItemRefPtr MoveIndexMenuItem = MenuItem::create();
    MoveIndexMenuItem->setText("Move Value");
    MoveIndexMenuItem->addActionListener(new MoveMultiPtrFieldActionListener());
    
    MenuItemRefPtr SwapIndexMenuItem = MenuItem::create();
    SwapIndexMenuItem->setText("Swap Value");
    SwapIndexMenuItem->addActionListener(new SwapMultiPtrFieldActionListener());

    PopupMenuRefPtr MultiPtrFieldListPopupMenu = PopupMenu::create();
    MultiPtrFieldListPopupMenu->addItem(SetValueMenuItem);
    MultiPtrFieldListPopupMenu->addItem(AddValueMenuItem);
    MultiPtrFieldListPopupMenu->addItem(InsertIndexMenuItem);
    MultiPtrFieldListPopupMenu->addItem(MoveIndexMenuItem);
    MultiPtrFieldListPopupMenu->addItem(SwapIndexMenuItem);
    MultiPtrFieldListPopupMenu->addItem(RemoveIndexMenuItem);

    //Multi-field List Model
	MultiPtrFieldListModel = MFieldListModel::create();
    MultiPtrFieldListModel->setContainer(MultiPtrFieldInnerPanel);
    MultiPtrFieldListModel->setFieldId(Panel::ChildrenFieldId);

    //List
    MultiPtrFieldList = List::create();
    MultiPtrFieldList->setPreferredSize(Vec2f(200, 300));
    MultiPtrFieldList->setOrientation(List::VERTICAL_ORIENTATION);
	MultiPtrFieldList->setModel(MultiPtrFieldListModel);
    ListSelectionModelPtr MultiPtrFieldListSelectionModel(new DefaultListSelectionModel());
    MultiPtrFieldList->setSelectionModel(MultiPtrFieldListSelectionModel);
    MultiPtrFieldList->setPopupMenu(MultiPtrFieldListPopupMenu);

    // Create a ScrollPanel for easier viewing of the List
    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(MultiPtrFieldList);


    LayoutRefPtr ThePanelLayout = OSG::FlowLayout::create();

    PanelRefPtr ThePanel = Panel::createEmpty();
    ThePanel->setLayout(ThePanelLayout);
    ThePanel->pushToChildren(MultiPtrFieldInnerPanel);
    ThePanel->pushToChildren(ExampleScrollPanel);

    return ThePanel;
    
}
