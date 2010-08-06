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
#include "OSGUIDrawingSurface.h"
#include "OSGInternalWindow.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"
#include "OSGUIDrawUtils.h"
#include "OSGLabel.h"
#include "OSGPanel.h"
#include "OSGBoxLayout.h"

// 01 Button Headers
#include "OSGButton.h"
#include "OSGDialogWindow.h"
#include "OSGColorLayer.h"
#include "OSGFlowLayout.h"
#include "OSGDialogWindowListener.h"
#include "OSGDefaultColorSelectionModel.h"
// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;
DefaultColorSelectionModelPtr ColorModel(new DefaultColorSelectionModel());
LabelRefPtr OutputLabel;
std::vector<std::string> inputValues;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Escape
// key to exit
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

class TutorialDialogListener : public DialogWindowListener
{
  public:

    virtual void dialogClosing(const DialogWindowEventUnrecPtr e)
    {   }

    virtual void dialogClosed(const DialogWindowEventUnrecPtr e)
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

        OutputLabel->setText("Dialog Window Output : " + strOutput);
    }
};

class CreateMessageBoxButtonActionListener : public ActionListener
{
  public:

    TutorialDialogListener CloseListener;
    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::string buttonText;
        DialogWindowRefPtr TheDialog;
        if(e->getSource()->getType().isDerivedFrom(Component::getClassType()))
        {
            buttonText = dynamic_cast<Button*>(e->getSource())->getText();
            if (buttonText.compare("Message") == 0)
            {
                TheDialog = DialogWindow::createMessageDialog("Error", "Error 404: Page Not Found!"/*, DialogWindow::MSG_ERROR*/,true);
            }
            else if(buttonText.compare("Color Chooser") == 0)
            {
                TheDialog = DialogWindow::createColorChooserDialog("Choose a color", "Choose a color", true, ColorSelectionModelPtr(ColorModel),true);
            }
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
                else if(buttonText.compare("Input List") == 0)
                    TheDialog = DialogWindow::createInputDialog("Input Dialog Title", "Please enter a choice below", DialogWindow::INPUT_LIST,true,inputValues);
            }
            Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
            TheDialog->setPosition(CenteredPosition);

            TheDialog->addDialogWindowListener(&CloseListener);

            dynamic_cast<Component*>(e->getSource())->getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
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

    PanelRefPtr ButtonPanel = OSG::Panel::createEmpty();

    ButtonRefPtr MessageDialogButton = OSG::Button::create();
    ButtonRefPtr InputComboDialogButton = OSG::Button::create();
    ButtonRefPtr InputTextDialogButton = OSG::Button::create();
    ButtonRefPtr InputBtnsDialogButton = OSG::Button::create();
    ButtonRefPtr InputListDialogButton = OSG::Button::create();
    ButtonRefPtr ColorChooserDialogButton = OSG::Button::create();

    MessageDialogButton->setMinSize(Vec2f(50, 25));
    MessageDialogButton->setMaxSize(Vec2f(200, 100));
    MessageDialogButton->setPreferredSize(Vec2f(100, 50));
    MessageDialogButton->setText("Message");

    CreateMessageBoxButtonActionListener TheExampleButtonActionListener;
    MessageDialogButton->addActionListener(&TheExampleButtonActionListener);

    InputComboDialogButton->setMinSize(Vec2f(50, 25));
    InputComboDialogButton->setMaxSize(Vec2f(200, 100));
    InputComboDialogButton->setPreferredSize(Vec2f(100, 50));
    InputComboDialogButton->setText("Input Combobox");

    //CreateMessageBoxButtonActionListener TheExampleButtonActionListener;
    InputComboDialogButton->addActionListener(&TheExampleButtonActionListener);

    InputTextDialogButton->setMinSize(Vec2f(50, 25));
    InputTextDialogButton->setMaxSize(Vec2f(200, 100));
    InputTextDialogButton->setPreferredSize(Vec2f(100, 50));
    InputTextDialogButton->setText("Input Textbox");
    InputTextDialogButton->addActionListener(&TheExampleButtonActionListener);

    InputListDialogButton->setMinSize(Vec2f(50, 25));
    InputListDialogButton->setMaxSize(Vec2f(200, 100));
    InputListDialogButton->setPreferredSize(Vec2f(100, 50));
    InputListDialogButton->setText("Input List");
    InputListDialogButton->addActionListener(&TheExampleButtonActionListener);

    InputBtnsDialogButton->setMinSize(Vec2f(50, 25));
    InputBtnsDialogButton->setMaxSize(Vec2f(200, 100));
    InputBtnsDialogButton->setPreferredSize(Vec2f(100, 50));
    InputBtnsDialogButton->setText("Input Buttons");
    InputBtnsDialogButton->addActionListener(&TheExampleButtonActionListener);

    //CreateMessageBoxButtonActionListener TheExampleButtonActionListener;

    ColorChooserDialogButton->addActionListener(&TheExampleButtonActionListener);
    ColorChooserDialogButton->setMinSize(Vec2f(50, 25));
    ColorChooserDialogButton->setMaxSize(Vec2f(200, 100));
    ColorChooserDialogButton->setPreferredSize(Vec2f(100, 50));
    ColorChooserDialogButton->setText("Color Chooser");

    ColorChooserDialogButton->addActionListener(&TheExampleButtonActionListener);

    LayoutRefPtr ButtonPanelLayout = OSG::FlowLayout::create();
    ButtonPanel->pushToChildren(MessageDialogButton);
    ButtonPanel->pushToChildren(InputComboDialogButton);
    ButtonPanel->pushToChildren(InputTextDialogButton);
    ButtonPanel->pushToChildren(InputBtnsDialogButton);
    ButtonPanel->pushToChildren(InputListDialogButton);
    ButtonPanel->pushToChildren(ColorChooserDialogButton);
    ButtonPanel->setLayout(ButtonPanelLayout);
    ButtonPanel->setPreferredSize(Vec2f(600,175));

    OutputLabel = OSG::Label::create();
    OutputLabel->setText("");
    OutputLabel->setTextColor(Color4f(0, 0, 0, 1.0));
    OutputLabel->setAlignment(Vec2f(0.5,0.5));
    OutputLabel->setPreferredSize(Vec2f(200, 50));
    OutputLabel->setTextSelectable(false);

    // Create Background to be used with the MainInternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    // Create The Internal Window
    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    BoxLayoutRefPtr MainInternalWindowLayout = OSG::BoxLayout::create();

    MainInternalWindowLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);			//Make the swap to see what happens Between Vertical and Horizontal!
    //MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
    // Assign the Button to the MainInternalWindow so it will be displayed
    // when the view is rendered.
    MainInternalWindow->pushToChildren(ButtonPanel);
    MainInternalWindow->pushToChildren(OutputLabel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.65f,0.65f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    /*MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ButtonPanel, -5, SpringLayoutConstraints::NORTH_EDGE, OutputLabel);
      MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
      MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
      MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
      MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20, SpringLayoutConstraints::NORTH_EDGE, InputPanel);
      */
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
                               "38DialogWindow");

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
