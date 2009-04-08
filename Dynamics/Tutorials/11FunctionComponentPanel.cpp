// OpenSG Tutorial Example: Creating a Checkbox Button Component
//
// This tutorial explains how to edit the basic features of
// a Checkbox Button created in the OSG User Interface library.
// 
// Includes: 
//
//Checkbox buttons are special buttons that can are toggled between active and inactive when they are selected


// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGComboBox.h>
#include <OpenSG/UserInterface/OSGDerivedFieldContainerComboBoxModel.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>

#include <OpenSG/UserInterface/OSGFunctionComponent.h>
#include <OpenSG/UserInterface/OSGFunctionComponentPanel.h>
#include <OpenSG/UserInterface/OSGDefaultFunctionComponentIOTabComponentGenerator.h>
#include <OpenSG/Dynamics/OSGDataConverter.h>

#include <OpenSG/OSGFieldContainerFactoryImpl.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 12CheckboxButton Headers
#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIFont.h>

class TutorialWindowListener : public WindowAdapter
{
public:
    virtual void windowClosing(const WindowEvent& e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
        ExitApp = true;
    }
};

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

class ExampleButtonActionListener : public ActionListener
{
protected:
	FunctionComponentPanelPtr _ThePanel;
	ComboBoxPtr _TheComboBox;
	
public:	
	ExampleButtonActionListener(FunctionComponentPanelPtr ThePanel, ComboBoxPtr TheComboBox) : _ThePanel(ThePanel), _TheComboBox(TheComboBox)
	{
	}

   virtual void actionPerformed(const ActionEvent& e)
    {
		std::string TypeName;
	
		try
		{
			TypeName = boost::any_cast<FieldContainerType*>(_TheComboBox->getSelectedItem())->getCName();
		}
		catch(boost::bad_any_cast &e)
		{
			throw e;
		}
		
        FunctionPtr NewFunction = Function::Ptr::dcast(FieldContainerFactory::the()->createFieldContainer(TypeName.c_str()));
		
		//Create the Function User Interface Component
		RoundedCornerLineBorderPtr FunctionComponentBorder = RoundedCornerLineBorder::create();
		beginEditCP(FunctionComponentBorder, RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);
			FunctionComponentBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
			FunctionComponentBorder->setWidth(1.0f);
			FunctionComponentBorder->setCornerRadius(4.0f);
		endEditCP(FunctionComponentBorder, RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);
		
		//Create the Font
		UIFontPtr TheFont = UIFont::create();
		beginEditCP(TheFont, UIFont::FamilyFieldMask | UIFont::SizeFieldMask | UIFont::StyleFieldMask);
			TheFont->setFamily("Arial");
			TheFont->setSize(16);
			TheFont->setStyle(TextFace::STYLE_PLAIN);
		endEditCP(TheFont, UIFont::FamilyFieldMask | UIFont::SizeFieldMask | UIFont::StyleFieldMask);
		
		//Create the Default Tab Generator
		DefaultFunctionComponentIOTabComponentGeneratorPtr TabGenerator = DefaultFunctionComponentIOTabComponentGenerator::create();
			
		FunctionComponentPtr NewFunctionComponent = FunctionComponent::create();
		beginEditCP(NewFunctionComponent, FunctionComponent::InputTabComponentGeneratorFieldMask | FunctionComponent::OutputTabComponentGeneratorFieldMask | FunctionComponent::PreferredSizeFieldMask | FunctionComponent::BordersFieldMask | FunctionComponent::FunctionFieldMask | FunctionComponent::InputTabOrientationFieldMask | FunctionComponent::OutputTabOrientationFieldMask | FunctionComponent::InputTabAlignmentFieldMask | FunctionComponent::OutputTabAlignmentFieldMask | FunctionComponent::FontFieldMask | FunctionComponent::TextColorFieldMask | FunctionComponent::TextAlignmentFieldMask);
			NewFunctionComponent->setBorders(FunctionComponentBorder);
			NewFunctionComponent->setFunction(NewFunction);
			NewFunctionComponent->setInputTabOrientation(FunctionComponent::VERTICAL_ORIENTATION);
			NewFunctionComponent->setOutputTabOrientation(FunctionComponent::VERTICAL_ORIENTATION);
			NewFunctionComponent->setInputTabAlignment(Vec2f(0.0, 0.5));
			NewFunctionComponent->setOutputTabAlignment(Vec2f(1.0, 0.5));
			NewFunctionComponent->setFont(TheFont);
			NewFunctionComponent->setTextColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
			NewFunctionComponent->setTextAlignment(Vec2f(0.5, 0.5));
			
			//Add Generators
			NewFunctionComponent->setInputTabComponentGenerator(TabGenerator);
			NewFunctionComponent->setOutputTabComponentGenerator(TabGenerator);
			

		endEditCP(NewFunctionComponent, FunctionComponent::InputTabComponentGeneratorFieldMask | FunctionComponent::OutputTabComponentGeneratorFieldMask | FunctionComponent::PreferredSizeFieldMask | FunctionComponent::BordersFieldMask | FunctionComponent::FunctionFieldMask | FunctionComponent::InputTabOrientationFieldMask | FunctionComponent::OutputTabOrientationFieldMask | FunctionComponent::InputTabAlignmentFieldMask | FunctionComponent::OutputTabAlignmentFieldMask | FunctionComponent::FontFieldMask | FunctionComponent::TextColorFieldMask | FunctionComponent::TextAlignmentFieldMask);
			
		beginEditCP(_ThePanel, FunctionComponentPanel::ChildrenFieldMask);
			_ThePanel->getChildren().push_back(NewFunctionComponent);
		endEditCP(_ThePanel, FunctionComponentPanel::ChildrenFieldMask);
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
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

	//Function to attach to Component
	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);

    //Create the Font
	UIFontPtr TheFont = UIFont::create();
	beginEditCP(TheFont, UIFont::FamilyFieldMask | UIFont::SizeFieldMask | UIFont::StyleFieldMask);
		TheFont->setFamily("Arial");
		TheFont->setSize(16);
		TheFont->setStyle(TextFace::STYLE_PLAIN);
	endEditCP(TheFont, UIFont::FamilyFieldMask | UIFont::SizeFieldMask | UIFont::StyleFieldMask);
	
    //Create the Function User Interface Component
    RoundedCornerLineBorderPtr FunctionComponentBorder = RoundedCornerLineBorder::create();
    beginEditCP(FunctionComponentBorder, RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);
        FunctionComponentBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
        FunctionComponentBorder->setWidth(1.0f);
        FunctionComponentBorder->setCornerRadius(4.0f);
    endEditCP(FunctionComponentBorder, RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);

	//Create the Default Tab Generator
    DefaultFunctionComponentIOTabComponentGeneratorPtr TabGenerator = DefaultFunctionComponentIOTabComponentGenerator::create();

    FunctionComponentPtr ExampleFunctionComponent = FunctionComponent::create();
    beginEditCP(ExampleFunctionComponent, FunctionComponent::InputTabComponentGeneratorFieldMask | FunctionComponent::OutputTabComponentGeneratorFieldMask | FunctionComponent::PreferredSizeFieldMask | FunctionComponent::BordersFieldMask | FunctionComponent::FunctionFieldMask | FunctionComponent::InputTabOrientationFieldMask | FunctionComponent::OutputTabOrientationFieldMask | FunctionComponent::InputTabAlignmentFieldMask | FunctionComponent::OutputTabAlignmentFieldMask | FunctionComponent::FontFieldMask | FunctionComponent::TextColorFieldMask | FunctionComponent::TextAlignmentFieldMask);
        ExampleFunctionComponent->setPreferredSize(Vec2f(100.0f,100.0f));
		ExampleFunctionComponent->setFunction(TheVec3fConverter);
        ExampleFunctionComponent->setBorders(FunctionComponentBorder);
		ExampleFunctionComponent->setInputTabOrientation(FunctionComponent::VERTICAL_ORIENTATION);
		ExampleFunctionComponent->setOutputTabOrientation(FunctionComponent::VERTICAL_ORIENTATION);
		ExampleFunctionComponent->setInputTabAlignment(Vec2f(0.0, 0.5));
		ExampleFunctionComponent->setOutputTabAlignment(Vec2f(1.0, 0.5));
		ExampleFunctionComponent->setFont(TheFont);
		ExampleFunctionComponent->setTextColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
		ExampleFunctionComponent->setTextAlignment(Vec2f(0.5, 0.5));
        
        //Add Generators
		ExampleFunctionComponent->setInputTabComponentGenerator(TabGenerator);
		ExampleFunctionComponent->setOutputTabComponentGenerator(TabGenerator);
		

    endEditCP(ExampleFunctionComponent, FunctionComponent::InputTabComponentGeneratorFieldMask | FunctionComponent::OutputTabComponentGeneratorFieldMask | FunctionComponent::PreferredSizeFieldMask | FunctionComponent::BordersFieldMask | FunctionComponent::FunctionFieldMask | FunctionComponent::InputTabOrientationFieldMask | FunctionComponent::OutputTabOrientationFieldMask | FunctionComponent::InputTabAlignmentFieldMask | FunctionComponent::OutputTabAlignmentFieldMask | FunctionComponent::FontFieldMask | FunctionComponent::TextColorFieldMask | FunctionComponent::TextAlignmentFieldMask);
	
	//Create add component combo box
	DerivedFieldContainerComboBoxModelPtr ExampleComboBoxModel = DerivedFieldContainerComboBoxModel::create();
    beginEditCP(ExampleComboBoxModel, DerivedFieldContainerComboBoxModel::DerivedFieldContainerTypesFieldMask);
        ExampleComboBoxModel->getDerivedFieldContainerTypes().push_back(std::string(Function::getClassType().getCName()));
    endEditCP(ExampleComboBoxModel, DerivedFieldContainerComboBoxModel::DerivedFieldContainerTypesFieldMask);
	
	ComboBoxPtr ComponentTypesComboBox = ComboBox::create();
	beginEditCP(ComponentTypesComboBox, ComboBox::EditableFieldMask | ComboBox::ModelFieldMask);
		ComponentTypesComboBox->setEditable(false);
		ComponentTypesComboBox->setModel(ExampleComboBoxModel);
	endEditCP(ComponentTypesComboBox, ComboBox::EditableFieldMask | ComboBox::ModelFieldMask);
	
	//Create add component button
	ButtonPtr AddFunctionComponentButton = osg::Button::create();
	beginEditCP(AddFunctionComponentButton,  Button::PreferredSizeFieldMask | Button::TextFieldMask);

            AddFunctionComponentButton->setPreferredSize(Vec2f(100, 25));
            AddFunctionComponentButton->setText("Add Component");

    endEditCP(AddFunctionComponentButton,  Button::PreferredSizeFieldMask | Button::TextFieldMask);


    ColorLayerPtr FunctionComponentPanelBackground = ColorLayer::create();
	beginEditCP(FunctionComponentPanelBackground,  ColorLayer::ColorFieldMask);
        FunctionComponentPanelBackground->setColor(Color4f(1.0,0.0,0.0,1.0));
	endEditCP(FunctionComponentPanelBackground,  ColorLayer::ColorFieldMask);


    //Create the Function User Interface Component
    RoundedCornerLineBorderPtr FunctionComponentPanelBorder = RoundedCornerLineBorder::create();
    beginEditCP(FunctionComponentPanelBorder, RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);
        FunctionComponentPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
        FunctionComponentPanelBorder->setWidth(5.0f);
        FunctionComponentPanelBorder->setCornerRadius(4.0f);
    endEditCP(FunctionComponentPanelBorder, RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);

    
    FunctionComponentPanelPtr ExampleFunctionComponentPanel = FunctionComponentPanel::create();
    beginEditCP(ExampleFunctionComponentPanel, FunctionComponentPanel::PreferredSizeFieldMask | FunctionComponentPanel::BordersFieldMask | FunctionComponentPanel::ChildrenFieldMask | FunctionComponentPanel::MiniMapSizeFieldMask);
        ExampleFunctionComponentPanel->setPreferredSize(Vec2f(600.0f,600.0f));
		ExampleFunctionComponentPanel->setMiniMapSize(Real32(0.15f));
        
        //Add Components
		ExampleFunctionComponentPanel->getChildren().push_back(ExampleFunctionComponent);
		
	    ExampleFunctionComponentPanel->setAllInsets(5.0);
	    ExampleFunctionComponentPanel->setBackgrounds(FunctionComponentPanelBackground);

    endEditCP(ExampleFunctionComponentPanel, FunctionComponentPanel::PreferredSizeFieldMask | FunctionComponentPanel::BordersFieldMask | FunctionComponentPanel::ChildrenFieldMask | FunctionComponentPanel::MiniMapSizeFieldMask);
	
    //Scroll Panel
	ScrollPanelPtr ExampleScrollPanel = ScrollPanel::create();
    beginEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        ExampleScrollPanel->setPreferredSize(Vec2f(600.0f,600.0f));
    endEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    
    ExampleScrollPanel->setViewComponent(ExampleFunctionComponentPanel);
	
    ExampleButtonActionListener TheExampleButtonActionListener(ExampleFunctionComponentPanel, ComponentTypesComboBox);
    AddFunctionComponentButton->addActionListener(&TheExampleButtonActionListener);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleScrollPanel);
	   MainInternalWindow->getChildren().push_back(AddFunctionComponentButton);
	   MainInternalWindow->getChildren().push_back(ComponentTypesComboBox);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.75f,0.75f));
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

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(850,850),
                                        "OpenSG 10UserInterface Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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