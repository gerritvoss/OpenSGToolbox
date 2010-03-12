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

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 01 Button Headers
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

ColorLayerRefPtr ChangableBackground;
LineBorderRefPtr ChangableBorder;

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
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


class SetBorderColor;
typedef boost::shared_ptr<SetBorderColor> SetBorderColorRefPtr;

class SetBorderColor: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;

	LineBorderRefPtr _TheBorder;
	Color4f _ChangeToColor;
	Color4f _PreviousColor;

	SetBorderColor(LineBorderRefPtr TheBorder, Color4f ChangeToColor) : Inherited(),
		_TheBorder(TheBorder),
		_ChangeToColor(ChangeToColor)
	{
	}

	SetBorderColor(const SetBorderColor& source) : Inherited(source),
		_TheBorder(source._TheBorder),
		_ChangeToColor(source._ChangeToColor),
		_PreviousColor(source._PreviousColor)

	{
	}

	static CommandType _Type;
	
	virtual void execute(void)
	{
		_HasBeenDone = true;

		_PreviousColor = _TheBorder->getColor();

			_TheBorder->setColor(_ChangeToColor);
	}
public:

	virtual std::string getPresentationName(void) const
	{
		return getCommandDescription();
	}

	virtual std::string getCommandDescription(void) const
	{
		std::ostringstream Temp;
		OutStream osgStream(Temp);
		FieldTraits<Color4f>::putToStream(_ChangeToColor, osgStream);
		return std::string("Set Border Color to: ") + Temp.str();
	}

	virtual void redo(void)
	{
		Inherited::redo();
			_TheBorder->setColor(_ChangeToColor);
	}
	
	virtual void undo(void)
	{
		Inherited::undo();
			_TheBorder->setColor(_PreviousColor);
	}

	virtual bool isSignificant(void) const
	{
		return _ChangeToColor != _PreviousColor;
	}

    virtual const CommandType &getType(void) const
	{
		return _Type;
	}
	
    static const CommandType &getClassType(void)
	{
		return _Type;
	}

	virtual ~SetBorderColor(void)
	{
	}
	
	static SetBorderColorRefPtr create(LineBorderRefPtr TheBorder, Color4f ChangeToColor)
	{
		return SetBorderColorRefPtr(new SetBorderColor(TheBorder, ChangeToColor));
	}
};

CommandType SetBorderColor::_Type("SetBorderColor", "UndoableCommand");

class SetBackgroundColor;
typedef boost::shared_ptr<SetBackgroundColor> SetBackgroundColorRefPtr;

class SetBackgroundColor: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;

	ColorLayerRefPtr _TheBackground;
	Color4f _ChangeToColor;
	Color4f _PreviousColor;

	SetBackgroundColor(ColorLayerRefPtr TheBackground, Color4f ChangeToColor) : Inherited(),
		_TheBackground(TheBackground),
		_ChangeToColor(ChangeToColor)
	{
	}

	SetBackgroundColor(const SetBackgroundColor& source) : Inherited(source),
		_TheBackground(source._TheBackground),
		_ChangeToColor(source._ChangeToColor),
		_PreviousColor(source._PreviousColor)

	{
	}

	static CommandType _Type;
	
	virtual void execute(void)
	{
		_HasBeenDone = true;

		_PreviousColor = _TheBackground->getColor();

			_TheBackground->setColor(_ChangeToColor);
	}
public:

	virtual std::string getPresentationName(void) const
	{
		return getCommandDescription();
	}

	virtual std::string getCommandDescription(void) const
	{
		std::ostringstream Temp;
		OutStream osgStream(Temp);
		FieldTraits<Color4f>::putToStream(_ChangeToColor, osgStream);
		return std::string("Set Background Color to: ") + Temp.str();
	}


	virtual void redo(void)
	{
		Inherited::redo();
			_TheBackground->setColor(_ChangeToColor);
	}
	
	virtual void undo(void)
	{
		Inherited::undo();
			_TheBackground->setColor(_PreviousColor);
	}

	virtual bool isSignificant(void) const
	{
		return _ChangeToColor != _PreviousColor;
	}

    virtual const CommandType &getType(void) const
	{
		return _Type;
	}
	
    static const CommandType &getClassType(void)
	{
		return _Type;
	}

	virtual ~SetBackgroundColor(void)
	{
	}
	
	static SetBackgroundColorRefPtr create(ColorLayerRefPtr TheBackground, Color4f ChangeToColor)
	{
		return SetBackgroundColorRefPtr(new SetBackgroundColor(TheBackground, ChangeToColor));
	}
};

CommandType SetBackgroundColor::_Type("SetBackgroundColor", "UndoableCommand");
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
		SetBorderColorRefPtr TheCommand = SetBorderColor::create(_TheBorder, _ChangeToColor);

		_CommandManager->executeCommand(TheCommand);
    }
};

class SetBackgroundColorActionListener : public ActionListener
{
protected:
	Color4f _ChangeToColor;
	ColorLayerRefPtr _TheBackground;
	CommandManagerPtr _CommandManager;

public:

	SetBackgroundColorActionListener(ColorLayerRefPtr TheBackground, Color4f ChangeToColor, CommandManagerPtr Manager) : ActionListener(),
		_TheBackground(TheBackground),
		_ChangeToColor(ChangeToColor),
		_CommandManager(Manager)
	{
	}

   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
		UndoableCommandPtr TheCommand = SetBackgroundColor::create(_TheBackground, _ChangeToColor);

		_CommandManager->executeCommand(TheCommand);
    }
};

ListRefPtr UndoRedoList;
UndoManagerPtr TheUndoManager;
DefaultListModelRefPtr UndoRedoListModel;
ButtonRefPtr UndoButton;
ButtonRefPtr RedoButton;

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
    /******************************************************

                 Create an Button Component and
                 a simple Font.
                 See 17Label_Font for more
                 information about Fonts.

    ******************************************************/

    ChangableBorder = OSG::LineBorder::create();
		ChangableBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    
	ChangableBackground = OSG::ColorLayer::create();
		ChangableBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    LabelRefPtr ChangableLabel = OSG::Label::create();

            ChangableLabel->setText("Changable");
            ChangableLabel->setBorders(ChangableBorder);
            ChangableLabel->setBackgrounds(ChangableBackground);

	//Command Buttons
	TheUndoManager = UndoManager::create();
	UndoManagerChangeListener TheUndoManagerChangeListener;
	TheUndoManager->addChangeListener(&TheUndoManagerChangeListener);

	CommandManagerPtr TheCommandManager = CommandManager::create(TheUndoManager);
    ButtonRefPtr BorderRedButton = OSG::Button::create();
            BorderRedButton->setText("Border Red");
    SetBorderColorActionListener TheSetRedBorderColorActionListener(ChangableBorder, Color4f(1.0,0.0,0.0,1.0), TheCommandManager);
    BorderRedButton->addActionListener(&TheSetRedBorderColorActionListener);
	
    ButtonRefPtr BorderGreenButton = OSG::Button::create();
            BorderGreenButton->setText("Border Green");
    SetBorderColorActionListener TheSetGreenBorderColorActionListener(ChangableBorder, Color4f(0.0,1.0,0.0,1.0), TheCommandManager);
    BorderGreenButton->addActionListener(&TheSetGreenBorderColorActionListener);
	
    ButtonRefPtr BorderBlueButton = OSG::Button::create();
            BorderBlueButton->setText("Border Blue");
    SetBorderColorActionListener TheSetBlueBorderColorActionListener(ChangableBorder, Color4f(0.0,0.0,1.0,1.0), TheCommandManager);
    BorderBlueButton->addActionListener(&TheSetBlueBorderColorActionListener);
	
	//Background
    ButtonRefPtr BackgroundRedButton = OSG::Button::create();
            BackgroundRedButton->setText("Background Red");
    SetBackgroundColorActionListener TheSetRedBackgroundColorActionListener(ChangableBackground, Color4f(1.0,0.0,0.0,1.0), TheCommandManager);
    BackgroundRedButton->addActionListener(&TheSetRedBackgroundColorActionListener);
	
    ButtonRefPtr BackgroundGreenButton = OSG::Button::create();
            BackgroundGreenButton->setText("Background Green");
    SetBackgroundColorActionListener TheSetGreenBackgroundColorActionListener(ChangableBackground, Color4f(0.0,1.0,0.0,1.0), TheCommandManager);
    BackgroundGreenButton->addActionListener(&TheSetGreenBackgroundColorActionListener);
	
    ButtonRefPtr BackgroundBlueButton = OSG::Button::create();
            BackgroundBlueButton->setText("Background Blue");
    SetBackgroundColorActionListener TheSetBlueBackgroundColorActionListener(ChangableBackground, Color4f(0.0,0.0,1.0,1.0), TheCommandManager);
    BackgroundBlueButton->addActionListener(&TheSetBlueBackgroundColorActionListener);

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
       MainInternalWindow->pushToChildren(BorderRedButton);
       MainInternalWindow->pushToChildren(BorderGreenButton);
       MainInternalWindow->pushToChildren(BorderBlueButton);
       MainInternalWindow->pushToChildren(BackgroundRedButton);
       MainInternalWindow->pushToChildren(BackgroundGreenButton);
       MainInternalWindow->pushToChildren(BackgroundBlueButton);
       MainInternalWindow->pushToChildren(ChangableLabel);
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

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "40UndoableCommand");

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
