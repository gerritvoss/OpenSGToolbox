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
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIDrawUtils.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;
LabelPtr OutputLabel;
std::vector<std::string> inputValues;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 01 Button Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGDialogWindow.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGDialogWindowListener.h>

// Create a class to allow for the use of the Escape
// key to exit
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
   }
};

class TutorialDialogListener : public DialogWindowListener
{
public:

   virtual void dialogClosing(const DialogWindowEventPtr e)
   {   }

   virtual void dialogClosed(const DialogWindowEventPtr e)
   {
	   std::string strOutput;
	   UInt32 intOption;
	   
	   if(e->getInput() != "" && e->getOption() != DialogWindowEvent::DIALOG_OPTION_CANCEL)
		   strOutput = e->getInput();
	   else
	   {
			intOption = e->getOption();
			switch (intOption) {
				case DialogWindowEvent::DIALOG_OPTION_OK:
					strOutput = "OK";
				break;
				case DialogWindowEvent::DIALOG_OPTION_CANCEL:
					strOutput = "CANCEL";
				break;
				case DialogWindowEvent::DIALOG_OPTION_YES:
					strOutput = "YES";
				break;
				case DialogWindowEvent::DIALOG_OPTION_NO:
					strOutput = "NO";
				break;
				default:
					strOutput = "Output Error";
				break;
			}
	   }

	   beginEditCP(OutputLabel, Label::TextFieldMask);
	       OutputLabel->setText("Dialog Window Output : " + strOutput);
       endEditCP(OutputLabel, Label::TextFieldMask);
   }
};

class CreateMessageBoxButtonActionListener : public ActionListener
{
public:

   TutorialDialogListener CloseListener;
   virtual void actionPerformed(const ActionEventPtr e)
    {
		std::string buttonText;
		DialogWindowPtr TheDialog;
		if(e->getSource()->getType().isDerivedFrom(Component::getClassType()))
		{
			buttonText = Button::Ptr::dcast(e->getSource())->getText();
			if (buttonText == "Message")
				TheDialog = DialogWindow::createMessageDialog("Error", "Error 404: Page Not Found!", DialogWindow::MSG_ERROR,true);
			else
			{
				inputValues.clear();
				inputValues.push_back("Choice 1");	
				inputValues.push_back("Choice 2");	
				inputValues.push_back("Choice 3");	

				if (buttonText == "Input Combobox")
					TheDialog = DialogWindow::createInputDialog("Input Dialog Title", "Please choose an option below", DialogWindow::INPUT_COMBO,true,inputValues);
				else if (buttonText == "Input Buttons")
					TheDialog = DialogWindow::createInputDialog("Input Dialog Title", "Please choose an option below", DialogWindow::INPUT_BTNS,true,inputValues);
				else if (buttonText == "Input Textbox")
					TheDialog = DialogWindow::createInputDialog("Input Dialog Title", "Please enter a choice below", DialogWindow::INPUT_TEXT,true,inputValues);
			}
			Pnt2f CenteredPosition = calculateAlignment(Component::Ptr::dcast(e->getSource())->getParentWindow()->getPosition(), Component::Ptr::dcast(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
			beginEditCP(TheDialog, DialogWindow::PositionFieldMask);
				TheDialog->setPosition(CenteredPosition);
			endEditCP(TheDialog, DialogWindow::PositionFieldMask);
			
			TheDialog->addDialogWindowListener(&CloseListener);

			Component::Ptr::dcast(e->getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
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

	PanelPtr ButtonPanel = osg::Panel::create();

    ButtonPtr MessageDialogButton = osg::Button::create();
    ButtonPtr InputComboDialogButton = osg::Button::create();
    ButtonPtr InputTextDialogButton = osg::Button::create();
    ButtonPtr InputBtnsDialogButton = osg::Button::create();

    beginEditCP(MessageDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            MessageDialogButton->setMinSize(Vec2f(50, 25));
            MessageDialogButton->setMaxSize(Vec2f(200, 100));
            MessageDialogButton->setPreferredSize(Vec2f(100, 50));
            MessageDialogButton->setText("Message");
    endEditCP(MessageDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            
    CreateMessageBoxButtonActionListener TheExampleButtonActionListener;
    MessageDialogButton->addActionListener(&TheExampleButtonActionListener);
	
    beginEditCP(InputComboDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            InputComboDialogButton->setMinSize(Vec2f(50, 25));
            InputComboDialogButton->setMaxSize(Vec2f(200, 100));
            InputComboDialogButton->setPreferredSize(Vec2f(100, 50));
            InputComboDialogButton->setText("Input Combobox");
    endEditCP(InputComboDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            
    //CreateMessageBoxButtonActionListener TheExampleButtonActionListener;
    InputComboDialogButton->addActionListener(&TheExampleButtonActionListener);

	beginEditCP(InputTextDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            InputTextDialogButton->setMinSize(Vec2f(50, 25));
            InputTextDialogButton->setMaxSize(Vec2f(200, 100));
            InputTextDialogButton->setPreferredSize(Vec2f(100, 50));
            InputTextDialogButton->setText("Input Buttons");
    endEditCP(InputTextDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            
    //CreateMessageBoxButtonActionListener TheExampleButtonActionListener;
    InputTextDialogButton->addActionListener(&TheExampleButtonActionListener);

	beginEditCP(InputBtnsDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            InputBtnsDialogButton->setMinSize(Vec2f(50, 25));
            InputBtnsDialogButton->setMaxSize(Vec2f(200, 100));
            InputBtnsDialogButton->setPreferredSize(Vec2f(100, 50));
            InputBtnsDialogButton->setText("Input Textbox");
    endEditCP(InputBtnsDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            
    //CreateMessageBoxButtonActionListener TheExampleButtonActionListener;
    InputBtnsDialogButton->addActionListener(&TheExampleButtonActionListener);

    LayoutPtr ButtonPanelLayout = osg::FlowLayout::create();
	beginEditCP(ButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		ButtonPanel->getChildren().push_back(MessageDialogButton);
		ButtonPanel->getChildren().push_back(InputComboDialogButton);
		ButtonPanel->getChildren().push_back(InputTextDialogButton);
		ButtonPanel->getChildren().push_back(InputBtnsDialogButton);
		ButtonPanel->setLayout(ButtonPanelLayout);
		ButtonPanel->setPreferredSize(Vec2f(600,75));
	endEditCP(ButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);

    OutputLabel = osg::Label::create();
    beginEditCP(OutputLabel, Label::TextFieldMask | Label::TextColorFieldMask | Label::AlignmentFieldMask | Label::PreferredSizeFieldMask | Label::TextSelectableFieldMask);
        OutputLabel->setText("");
        OutputLabel->setTextColor(Color4f(0, 0, 0, 1.0));
        OutputLabel->setAlignment(Vec2f(0.5,0.5));
        OutputLabel->setPreferredSize(Vec2f(200, 50));
        OutputLabel->setTextSelectable(false);
    endEditCP(OutputLabel, Label::TextFieldMask | Label::TextColorFieldMask | Label::AlignmentFieldMask | Label::PreferredSizeFieldMask | Label::TextSelectableFieldMask);
    
    // Create Background to be used with the MainInternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    // Create The Internal Window
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    BoxLayoutPtr MainInternalWindowLayout = osg::BoxLayout::create();

    beginEditCP(MainInternalWindowLayout, BoxLayout::OrientationFieldMask);
	MainInternalWindowLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);			//Make the swap to see what happens Between Vertical and Horizontal!
	//MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
    endEditCP(MainInternalWindowLayout, BoxLayout::OrientationFieldMask); 
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       // Assign the Button to the MainInternalWindow so it will be displayed
       // when the view is rendered.
       MainInternalWindow->getChildren().push_back(ButtonPanel);
       MainInternalWindow->getChildren().push_back(OutputLabel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.65f,0.65f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

	/*MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ButtonPanel, -5, SpringLayoutConstraints::NORTH_EDGE, OutputLabel);
	MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20, SpringLayoutConstraints::NORTH_EDGE, InputPanel);
*/
    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::InternalWindowsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::InternalWindowsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
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
