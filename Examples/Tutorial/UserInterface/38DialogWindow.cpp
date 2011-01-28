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
#include "OSGDefaultColorSelectionModel.h"
// Activate the OpenSG namespace
OSG_USING_NAMESPACE


// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

void handleDialogClosed(DialogWindowEventDetails* const details,
                        Label* const OutputLabel)
{
    std::string strOutput;
    UInt32 intOption;

    if(details->getInput() != "" && details->getOption() !=
       DialogWindowEventDetails::DIALOG_OPTION_CANCEL)
        strOutput = details->getInput();
    else
    {
        intOption = details->getOption();
        switch (intOption) {
            case DialogWindowEventDetails::DIALOG_OPTION_OK:
                strOutput = "OK";
                break;
            case DialogWindowEventDetails::DIALOG_OPTION_CANCEL:
                strOutput = "CANCEL";
                break;
            case DialogWindowEventDetails::DIALOG_OPTION_YES:
                strOutput = "YES";
                break;
            case DialogWindowEventDetails::DIALOG_OPTION_NO:
                strOutput = "NO";
                break;
            default:
                strOutput = "Output Error";
                break;
        }
    }

    OutputLabel->setText("Dialog Window Output : " + strOutput);
}

void handleCreateDialogAction(ActionEventDetails* const details,
                              Label* const OutputLabel)
{
    std::string buttonText;
    DialogWindowRecPtr TheDialog;
    if(details->getSource()->getType().isDerivedFrom(Component::getClassType()))
    {
        buttonText = dynamic_cast<Button*>(details->getSource())->getText();
        if (buttonText.compare("Message") == 0)
        {
            TheDialog = DialogWindow::createMessageDialog("Error", "Error 404: Page Not Found!"/*, DialogWindow::MSG_ERROR*/,true);
        }
        else if(buttonText.compare("Color Chooser") == 0)
        {

            ColorSelectionModelRecPtr ColorModel = DefaultColorSelectionModel::create();
            TheDialog = DialogWindow::createColorChooserDialog("Choose a color", "Choose a color", true, ColorModel,true);
        }
        else
        {
            std::vector<std::string> inputValues;
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
        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(details->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(details->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);

        TheDialog->connectDialogWindowClosed(boost::bind(handleDialogClosed, _1, OutputLabel));

        dynamic_cast<Component*>(details->getSource())->getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
    }
}

int main(int argc, char **argv)
{
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

        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();


        LabelRecPtr OutputLabel = Label::create();
        OutputLabel->setText("");
        OutputLabel->setTextColor(Color4f(0, 0, 0, 1.0));
        OutputLabel->setAlignment(Vec2f(0.5,0.5));
        OutputLabel->setPreferredSize(Vec2f(200, 50));
        OutputLabel->setTextSelectable(false);

        PanelRecPtr ButtonPanel = Panel::createEmpty();

        ButtonRecPtr MessageDialogButton = Button::create();
        ButtonRecPtr InputComboDialogButton = Button::create();
        ButtonRecPtr InputTextDialogButton = Button::create();
        ButtonRecPtr InputBtnsDialogButton = Button::create();
        ButtonRecPtr InputListDialogButton = Button::create();
        ButtonRecPtr ColorChooserDialogButton = Button::create();

        MessageDialogButton->setMinSize(Vec2f(50, 25));
        MessageDialogButton->setMaxSize(Vec2f(200, 100));
        MessageDialogButton->setPreferredSize(Vec2f(100, 50));
        MessageDialogButton->setText("Message");
        MessageDialogButton->connectActionPerformed(boost::bind(handleCreateDialogAction,
                                                                _1,
                                                                OutputLabel.get()));

        InputComboDialogButton->setMinSize(Vec2f(50, 25));
        InputComboDialogButton->setMaxSize(Vec2f(200, 100));
        InputComboDialogButton->setPreferredSize(Vec2f(100, 50));
        InputComboDialogButton->setText("Input Combobox");
        InputComboDialogButton->connectActionPerformed(boost::bind(handleCreateDialogAction,
                                                                _1,
                                                                OutputLabel.get()));

        InputTextDialogButton->setMinSize(Vec2f(50, 25));
        InputTextDialogButton->setMaxSize(Vec2f(200, 100));
        InputTextDialogButton->setPreferredSize(Vec2f(100, 50));
        InputTextDialogButton->setText("Input Textbox");
        InputTextDialogButton->connectActionPerformed(boost::bind(handleCreateDialogAction,
                                                                _1,
                                                                OutputLabel.get()));

        InputListDialogButton->setMinSize(Vec2f(50, 25));
        InputListDialogButton->setMaxSize(Vec2f(200, 100));
        InputListDialogButton->setPreferredSize(Vec2f(100, 50));
        InputListDialogButton->setText("Input List");
        InputListDialogButton->connectActionPerformed(boost::bind(handleCreateDialogAction,
                                                                _1,
                                                                OutputLabel.get()));

        InputBtnsDialogButton->setMinSize(Vec2f(50, 25));
        InputBtnsDialogButton->setMaxSize(Vec2f(200, 100));
        InputBtnsDialogButton->setPreferredSize(Vec2f(100, 50));
        InputBtnsDialogButton->setText("Input Buttons");
        InputBtnsDialogButton->connectActionPerformed(boost::bind(handleCreateDialogAction,
                                                                _1,
                                                                OutputLabel.get()));

        ColorChooserDialogButton->setMinSize(Vec2f(50, 25));
        ColorChooserDialogButton->setMaxSize(Vec2f(200, 100));
        ColorChooserDialogButton->setPreferredSize(Vec2f(100, 50));
        ColorChooserDialogButton->setText("Color Chooser");
        ColorChooserDialogButton->connectActionPerformed(boost::bind(handleCreateDialogAction,
                                                                _1,
                                                                OutputLabel.get()));

        LayoutRecPtr ButtonPanelLayout = FlowLayout::create();
        ButtonPanel->pushToChildren(MessageDialogButton);
        ButtonPanel->pushToChildren(InputComboDialogButton);
        ButtonPanel->pushToChildren(InputTextDialogButton);
        ButtonPanel->pushToChildren(InputBtnsDialogButton);
        ButtonPanel->pushToChildren(InputListDialogButton);
        ButtonPanel->pushToChildren(ColorChooserDialogButton);
        ButtonPanel->setLayout(ButtonPanelLayout);
        ButtonPanel->setPreferredSize(Vec2f(600,175));

        // Create Background to be used with the MainInternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        // Create The Internal Window
        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        BoxLayoutRecPtr MainInternalWindowLayout = BoxLayout::create();

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

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);
        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "38DialogWindow");

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
