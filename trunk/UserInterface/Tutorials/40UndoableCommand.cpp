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
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 01 Button Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGDefaultListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>

#include <OpenSG/UserInterface/OSGUndoableCommand.h>
#include <OpenSG/UserInterface/OSGCommandManager.h>
#include <OpenSG/UserInterface/OSGUndoManager.h>

ColorLayerPtr ChangableBackground;
LineBorderPtr ChangableBorder;

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
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};


class SetBorderColor;
typedef boost::intrusive_ptr<SetBorderColor> SetBorderColorPtr;

class SetBorderColor: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;

	LineBorderPtr _TheBorder;
	Color4f _ChangeToColor;
	Color4f _PreviousColor;

	SetBorderColor(LineBorderPtr TheBorder, Color4f ChangeToColor) : Inherited(),
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

		beginEditCP(_TheBorder, LineBorder::ColorFieldMask);
			_TheBorder->setColor(_ChangeToColor);
		endEditCP(_TheBorder, LineBorder::ColorFieldMask);
	}
public:

	virtual std::string getPresentationName(void) const
	{
		return getCommandDescription();
	}

	virtual std::string getCommandDescription(void) const
	{
		std::string Temp;
		FieldDataTraits<Color4f>::putToString(_ChangeToColor, Temp);
		return std::string("Set Border Color to: ") + Temp;
	}

	virtual void redo(void)
	{
		Inherited::redo();
		beginEditCP(_TheBorder, LineBorder::ColorFieldMask);
			_TheBorder->setColor(_ChangeToColor);
		endEditCP(_TheBorder, LineBorder::ColorFieldMask);
	}
	
	virtual void undo(void)
	{
		Inherited::undo();
		beginEditCP(_TheBorder, LineBorder::ColorFieldMask);
			_TheBorder->setColor(_PreviousColor);
		endEditCP(_TheBorder, LineBorder::ColorFieldMask);
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
	
	static SetBorderColorPtr create(LineBorderPtr TheBorder, Color4f ChangeToColor)
	{
		return SetBorderColorPtr(new SetBorderColor(TheBorder, ChangeToColor));
	}
};

CommandType SetBorderColor::_Type("SetBorderColor", "UndoableCommand");

class SetBackgroundColor;
typedef boost::intrusive_ptr<SetBackgroundColor> SetBackgroundColorPtr;

class SetBackgroundColor: public UndoableCommand
{
protected:
	typedef UndoableCommand Inherited;

	ColorLayerPtr _TheBackground;
	Color4f _ChangeToColor;
	Color4f _PreviousColor;

	SetBackgroundColor(ColorLayerPtr TheBackground, Color4f ChangeToColor) : Inherited(),
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

		beginEditCP(_TheBackground, ColorLayer::ColorFieldMask);
			_TheBackground->setColor(_ChangeToColor);
		endEditCP(_TheBackground, ColorLayer::ColorFieldMask);
	}
public:

	virtual std::string getPresentationName(void) const
	{
		return getCommandDescription();
	}

	virtual std::string getCommandDescription(void) const
	{
		std::string Temp;
		FieldDataTraits<Color4f>::putToString(_ChangeToColor, Temp);
		return std::string("Set Background Color to: ") + Temp;
	}


	virtual void redo(void)
	{
		Inherited::redo();
		beginEditCP(_TheBackground, ColorLayer::ColorFieldMask);
			_TheBackground->setColor(_ChangeToColor);
		endEditCP(_TheBackground, ColorLayer::ColorFieldMask);
	}
	
	virtual void undo(void)
	{
		Inherited::undo();
		beginEditCP(_TheBackground, ColorLayer::ColorFieldMask);
			_TheBackground->setColor(_PreviousColor);
		endEditCP(_TheBackground, ColorLayer::ColorFieldMask);
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
	
	static SetBackgroundColorPtr create(ColorLayerPtr TheBackground, Color4f ChangeToColor)
	{
		return SetBackgroundColorPtr(new SetBackgroundColor(TheBackground, ChangeToColor));
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
	LineBorderPtr _TheBorder;
	CommandManagerPtr _CommandManager;

public:

	SetBorderColorActionListener(LineBorderPtr TheBorder, Color4f ChangeToColor, CommandManagerPtr Manager) : ActionListener(),
		_TheBorder(TheBorder),
		_ChangeToColor(ChangeToColor),
		_CommandManager(Manager)
	{
	}

   virtual void actionPerformed(const ActionEvent& e)
    {
		SetBorderColorPtr TheCommand = SetBorderColor::create(_TheBorder, _ChangeToColor);

		_CommandManager->executeCommand(TheCommand);
    }
};

class SetBackgroundColorActionListener : public ActionListener
{
protected:
	Color4f _ChangeToColor;
	ColorLayerPtr _TheBackground;
	CommandManagerPtr _CommandManager;

public:

	SetBackgroundColorActionListener(ColorLayerPtr TheBackground, Color4f ChangeToColor, CommandManagerPtr Manager) : ActionListener(),
		_TheBackground(TheBackground),
		_ChangeToColor(ChangeToColor),
		_CommandManager(Manager)
	{
	}

   virtual void actionPerformed(const ActionEvent& e)
    {
		SetBackgroundColorPtr TheCommand = SetBackgroundColor::create(_TheBackground, _ChangeToColor);

		_CommandManager->executeCommand(TheCommand);
    }
};

ListPtr UndoRedoList;
UndoManagerPtr TheUndoManager;
DefaultListModelPtr UndoRedoListModel;
ButtonPtr UndoButton;
ButtonPtr RedoButton;

class UndoButtonActionListener : public ActionListener
{
protected:

public:

	UndoButtonActionListener(void) : ActionListener()
	{
	}

   virtual void actionPerformed(const ActionEvent& e)
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

   virtual void actionPerformed(const ActionEvent& e)
    {
		TheUndoManager->redo();
    }
};

class UndoManagerChangeListener : public ChangeListener
{
public:

	virtual void stateChanged(const ChangeEvent& e)
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
			beginEditCP(UndoButton, Button::EnabledFieldMask);
				UndoButton->setEnabled(UndoCount != 0);
			endEditCP(UndoButton, Button::EnabledFieldMask);
		}
		if((RedoCount == 0 && RedoButton->getEnabled()) ||
			(RedoCount != 0 && !RedoButton->getEnabled()) )
		{
			beginEditCP(RedoButton, Button::EnabledFieldMask);
				RedoButton->setEnabled(RedoCount != 0);
			endEditCP(RedoButton, Button::EnabledFieldMask);
		}
	}
};

// Setup a FontListener to change the label's font
// when a different item in the FontList is
// selected
class UndoRedoListListener: public ListSelectionListener
{
  public:
    virtual void selectionChanged(const ListSelectionEvent& e)
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
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();
    /******************************************************

                 Create an Button Component and
                 a simple Font.
                 See 17Label_Font for more
                 information about Fonts.

    ******************************************************/

    ChangableBorder = osg::LineBorder::create();
	beginEditCP(ChangableBorder, LineBorder::ColorFieldMask);
		ChangableBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
	endEditCP(ChangableBorder, LineBorder::ColorFieldMask);
    
	ChangableBackground = osg::ColorLayer::create();
	beginEditCP(ChangableBackground, ColorLayer::ColorFieldMask);
		ChangableBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(ChangableBackground, ColorLayer::ColorFieldMask);

    LabelPtr ChangableLabel = osg::Label::create();

	beginEditCP(ChangableLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
            ChangableLabel->setText("Changable");
            ChangableLabel->setBorders(ChangableBorder);
            ChangableLabel->setBackgrounds(ChangableBackground);
    endEditCP(ChangableLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);

	//Command Buttons
	TheUndoManager = UndoManager::create();
	UndoManagerChangeListener TheUndoManagerChangeListener;
	TheUndoManager->addChangeListener(&TheUndoManagerChangeListener);

	CommandManagerPtr TheCommandManager = CommandManager::create(TheUndoManager);
    ButtonPtr BorderRedButton = osg::Button::create();
    beginEditCP(BorderRedButton, Button::TextFieldMask );
            BorderRedButton->setText("Border Red");
    endEditCP(BorderRedButton, Button::TextFieldMask);
    SetBorderColorActionListener TheSetRedBorderColorActionListener(ChangableBorder, Color4f(1.0,0.0,0.0,1.0), TheCommandManager);
    BorderRedButton->addActionListener(&TheSetRedBorderColorActionListener);
	
    ButtonPtr BorderGreenButton = osg::Button::create();
    beginEditCP(BorderGreenButton, Button::TextFieldMask );
            BorderGreenButton->setText("Border Green");
    endEditCP(BorderGreenButton, Button::TextFieldMask);
    SetBorderColorActionListener TheSetGreenBorderColorActionListener(ChangableBorder, Color4f(0.0,1.0,0.0,1.0), TheCommandManager);
    BorderGreenButton->addActionListener(&TheSetGreenBorderColorActionListener);
	
    ButtonPtr BorderBlueButton = osg::Button::create();
    beginEditCP(BorderBlueButton, Button::TextFieldMask );
            BorderBlueButton->setText("Border Blue");
    endEditCP(BorderBlueButton, Button::TextFieldMask);
    SetBorderColorActionListener TheSetBlueBorderColorActionListener(ChangableBorder, Color4f(0.0,0.0,1.0,1.0), TheCommandManager);
    BorderBlueButton->addActionListener(&TheSetBlueBorderColorActionListener);
	
	//Background
    ButtonPtr BackgroundRedButton = osg::Button::create();
    beginEditCP(BackgroundRedButton, Button::TextFieldMask );
            BackgroundRedButton->setText("Background Red");
    endEditCP(BackgroundRedButton, Button::TextFieldMask);
    SetBackgroundColorActionListener TheSetRedBackgroundColorActionListener(ChangableBackground, Color4f(1.0,0.0,0.0,1.0), TheCommandManager);
    BackgroundRedButton->addActionListener(&TheSetRedBackgroundColorActionListener);
	
    ButtonPtr BackgroundGreenButton = osg::Button::create();
    beginEditCP(BackgroundGreenButton, Button::TextFieldMask );
            BackgroundGreenButton->setText("Background Green");
    endEditCP(BackgroundGreenButton, Button::TextFieldMask);
    SetBackgroundColorActionListener TheSetGreenBackgroundColorActionListener(ChangableBackground, Color4f(0.0,1.0,0.0,1.0), TheCommandManager);
    BackgroundGreenButton->addActionListener(&TheSetGreenBackgroundColorActionListener);
	
    ButtonPtr BackgroundBlueButton = osg::Button::create();
    beginEditCP(BackgroundBlueButton, Button::TextFieldMask );
            BackgroundBlueButton->setText("Background Blue");
    endEditCP(BackgroundBlueButton, Button::TextFieldMask);
    SetBackgroundColorActionListener TheSetBlueBackgroundColorActionListener(ChangableBackground, Color4f(0.0,0.0,1.0,1.0), TheCommandManager);
    BackgroundBlueButton->addActionListener(&TheSetBlueBackgroundColorActionListener);

	//UndoList
	UndoRedoListModel = DefaultListModel::create();
    UndoRedoListModel->pushBack(boost::any(std::string("Top")));
	ListSelectionModelPtr UndoRedoListSelectionModel(new DefaultListSelectionModel());

	UndoRedoList = List::create();
	beginEditCP(UndoRedoList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);
        UndoRedoList->setPreferredSize(Vec2f(200, 300));
        UndoRedoList->setOrientation(List::VERTICAL_ORIENTATION);
		UndoRedoList->setModel(UndoRedoListModel);
    endEditCP(UndoRedoList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);

    UndoRedoList->setSelectionModel(UndoRedoListSelectionModel);

    UndoRedoListListener TheUndoRedoListListener;
    UndoRedoList->getSelectionModel()->addListSelectionListener(&TheUndoRedoListListener);

    UndoButton = osg::Button::create();
	beginEditCP(UndoButton, Button::TextFieldMask | Button::EnabledFieldMask);
            UndoButton->setText("Undo");
			UndoButton->setEnabled(TheUndoManager->numberOfUndos() != 0);
    endEditCP(UndoButton, Button::TextFieldMask | Button::EnabledFieldMask);
    UndoButtonActionListener TheUndoButtonActionListener;
    UndoButton->addActionListener(&TheUndoButtonActionListener);
	

    RedoButton = osg::Button::create();
	beginEditCP(RedoButton, Button::TextFieldMask | Button::EnabledFieldMask);
            RedoButton->setText("Redo");
			RedoButton->setEnabled(TheUndoManager->numberOfRedos() != 0);
    endEditCP(RedoButton, Button::TextFieldMask | Button::EnabledFieldMask);
    RedoButtonActionListener TheRedoButtonActionListener;
    RedoButton->addActionListener(&TheRedoButtonActionListener);

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelPtr UndoRedoScrollPanel = ScrollPanel::create();
    beginEditCP(UndoRedoScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        UndoRedoScrollPanel->setPreferredSize(Vec2f(200,200));
        UndoRedoScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(UndoRedoScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    UndoRedoScrollPanel->setViewComponent(UndoRedoList);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(BorderRedButton);
       MainInternalWindow->getChildren().push_back(BorderGreenButton);
       MainInternalWindow->getChildren().push_back(BorderBlueButton);
       MainInternalWindow->getChildren().push_back(BackgroundRedButton);
       MainInternalWindow->getChildren().push_back(BackgroundGreenButton);
       MainInternalWindow->getChildren().push_back(BackgroundBlueButton);
       MainInternalWindow->getChildren().push_back(ChangableLabel);
       MainInternalWindow->getChildren().push_back(UndoRedoScrollPanel);
       MainInternalWindow->getChildren().push_back(UndoButton);
       MainInternalWindow->getChildren().push_back(RedoButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.95f,0.95f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);
	
	// Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

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
