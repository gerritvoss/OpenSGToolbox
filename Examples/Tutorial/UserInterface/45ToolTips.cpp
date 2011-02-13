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

#include "OSGButton.h"
#include "OSGLabel.h"
#include "OSGColorLayer.h"
#include "OSGFlowLayout.h"
#include "OSGUIDrawUtils.h"

//Animation
#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"
#include "OSGAnimationGroup.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);
AnimationTransitPtr createFadeInAnimation(Component* CompToAnimate);

//Ctrl+q handler
void keyTyped(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

void handleBelowToolTipActivated(ComponentEventDetails* const details)
{
    ComponentRecPtr TheComponent(dynamic_cast<Component*>(details->getSource()));

    TheComponent->setToolTipLocation(Pnt2f(0.0f,TheComponent->getSize().y()));
}

void handleFollowMouseMove(MouseEventDetails* const details,
                           Component* const TheComponent)
{
    Vec2f MouseOffset(10.0f,10.0f);
    TheComponent->setToolTipLocation(DrawingSurfaceToComponent(details->getLocation(),TheComponent)
                                     + MouseOffset);
}

void handleToolTipActivated(ComponentEventDetails* const details)
{
    Component* TheComponent(dynamic_cast<Component*>(details->getSource()));
    TheComponent->connectMouseMoved(boost::bind(handleFollowMouseMove,_1,TheComponent));
}

void handleToolTipDeactivated(ComponentEventDetails* const details)
{
    dynamic_cast<Component*>(details->getSource())->disconnectAllSlotsToolTipActivated();
}


void handleFadeInToolTipActivated(ComponentEventDetails* const details,
                                  WindowEventProducer* const TutorialWindow,
                                  Animation* const FadeInAnimation)
{
    FadeInAnimation->attachUpdateProducer(TutorialWindow);
    FadeInAnimation->start();
}

void handleFadeInToolTipDeactivated(ComponentEventDetails* const details,
                                    Animation* const FadeInAnimation)
{
    FadeInAnimation->stop();
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

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

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

        LabelRecPtr ToolTipLabel = Label::create();
        ToolTipLabel->setText("Large ToolTip Panel");

        ButtonRecPtr ToolTipButton = Button::create();
        ToolTipButton->setText("Button");

        LayoutRefPtr PanelLayout = FlowLayout::create();
        PanelRecPtr ExampleTooltip = Panel::create();
        ExampleTooltip->setPreferredSize(Vec2f(250.0f,50.0f));
        ExampleTooltip->setLayout(PanelLayout);
        ExampleTooltip->pushToChildren(ToolTipButton);
        ExampleTooltip->pushToChildren(ToolTipLabel);

        //Button with a large Panel as a ToolTip
        ButtonRefPtr LargePanelButton = Button::create();
        LargePanelButton->setText("Large");
        LargePanelButton->setToolTip(ExampleTooltip);

        //Button with a ToolTip that follows the mouse
        ButtonRefPtr MouseFollowButton = Button::create();
        MouseFollowButton->setText("Mouse Follow");
        MouseFollowButton->setToolTipText("Moving ToolTip");
        MouseFollowButton->connectToolTipActivated(boost::bind(handleToolTipActivated, _1));
        MouseFollowButton->connectToolTipDeactivated(boost::bind(handleToolTipDeactivated, _1));

        //Button with a ToolTip that is directly below the Button
        ButtonRefPtr BelowButton = Button::create();
        BelowButton->setText("Below");
        BelowButton->setToolTipText("Below ToolTip");
        BelowButton->connectToolTipActivated(boost::bind(handleBelowToolTipActivated, _1));

        //Button with a ToolTip that fades in
        ButtonRefPtr FadeInButton = Button::create();
        FadeInButton->setText("Fade In");
        FadeInButton->setToolTipText("Fade In ToolTip");

        //Create the Fade in animation
        AnimationRecPtr FadeInAnimation =
            createFadeInAnimation(FadeInButton->getToolTip());

        FadeInButton->connectToolTipActivated(boost::bind(handleFadeInToolTipActivated,
                                                          _1,
                                                          TutorialWindow.get(),
                                                          FadeInAnimation.get()));
        FadeInButton->connectToolTipDeactivated(boost::bind(handleFadeInToolTipDeactivated,
                                                            _1,
                                                            FadeInAnimation.get()));

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
        InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
        LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
        MainInternalWindow->pushToChildren(FadeInButton);
        MainInternalWindow->pushToChildren(BelowButton);
        MainInternalWindow->pushToChildren(LargePanelButton);
        MainInternalWindow->pushToChildren(MouseFollowButton);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
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

        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "45ToolTips");

        commitChanges();

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

AnimationTransitPtr createFadeInAnimation(Component* CompToAnimate)
{
    //Number Keyframe Sequence
    KeyframeNumberSequenceRecPtr OpacityKeyframes = KeyframeNumberSequenceReal32::create();
    OpacityKeyframes->addKeyframe(0.0,0.0f);
    OpacityKeyframes->addKeyframe(1.0,1.0f);
    
    //Animator
    KeyframeAnimatorRecPtr TheAnimator = KeyframeAnimator::create();
    TheAnimator->setKeyframeSequence(OpacityKeyframes);
    
    //Animation
    FieldAnimationRecPtr TheAnimation = FieldAnimation::create();
    TheAnimation->setAnimator(TheAnimator);
    TheAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheAnimation->setCycling(1);
    TheAnimation->setAnimatedField(CompToAnimate, Component::OpacityFieldId);

    return AnimationTransitPtr(TheAnimation);
}

