// OpenSG Tutorial Example: Creating a Label and Creating Fonts
//
// This tutorial explains how to change Fonts and create
// Labels
// 
// Includes: Font and Label creation and settings

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGMouseAdapter.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/OSGTextFaceFactory.h>

// Include Label and Font headerfiles
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGUIFont.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGAbstractListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListCellGenerator.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGListCellGenerator.h>
#include <OpenSG/UserInterface/OSGListModel.h>

#include <OpenSG/UserInterface/OSGScrollPanel.h>

#include <map>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
bool ExitApp = false;
std::map<std::string, UIFontPtr> FontMap;
// Declare upfront so they can be referenced
LabelPtr label1;
ListPtr list;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

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

	/******************************************************

			Creates a ListCellGenerator class to 
			create Labels for the List which contain
			the Font name in that particular Font.

			This creates the DefaultListCell (a 
			Label with Text equal to the name
			of the Font) and then changes that
			Label's Font to be the Font contained
			within the Label.


			cellgenerator craetes the components within the actual list itself; in this case they are labels

	******************************************************/

class FontListCellGenerator : public DefaultListCellGenerator
{
    /*==========================  PUBLIC  =================================*/
  public:
    virtual ComponentPtr getListCellGeneratorComponent(ListPtr list, SharedFieldPtr value, UInt32 index, bool isSelected, bool cellHasFocus)
    {
		// Create using the DefaultListCellGenerator 
		// a Label [its default] with Text equal to the
		// 
        LabelPtr TheLabel = Label::Ptr::dcast(
            DefaultListCellGenerator::getListCellGeneratorComponent(
            list, value, index, isSelected, cellHasFocus)
            );

        
		std::string FontFamilyString;
		if(value->getType() == SFString::getClassType())
		{
			FontFamilyString = dynamic_cast<SFString*>(value.get())->getValue();
		}
		else
		{
            FontFamilyString = "Times New Roman";
		}
		
		//Set the Font for the Label
        std::map<std::string, UIFontPtr>::iterator FontMapItor = FontMap.find(FontFamilyString);
        if(FontMapItor != FontMap.end())
        {
            beginEditCP(TheLabel, Label::FontFieldMask);
                TheLabel->setFont((*FontMapItor).second);
            endEditCP(TheLabel, Label::FontFieldMask);
        }

        return TheLabel;
    }

    FontListCellGenerator(void)
    {
    }

    virtual ~FontListCellGenerator(void)
    {
    }
};

// Setup a listener to change the label's font
// when a different item in the list is
// selected
class FontListListener: public MouseAdapter
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
        std::string ValueStr("");
        SharedFieldPtr Value(list->getValueAtPoint(e));
        if(Value->getType() == SFString::getClassType())
        {
            ValueStr = dynamic_cast<SFString*>(Value.get())->getValue();
        }
		// Output selected font
        std::cout << "Setting Font: " << ValueStr << std::endl;

        // Get the Font and create new FontPtr
        UIFontPtr TheSelectedFont(FontMap[ValueStr]);

        if(TheSelectedFont != NullFC)
        {
            // Set the font for label1 to be selected font
	        beginEditCP(label1, Label::FontFieldMask);
		        label1->setFont(TheSelectedFont);
	        endEditCP(label1, Label::FontFieldMask);
        }
    }
};

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


    // Make Torus Node
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();

	
	/******************************************************

			Determine which Fonts your computer can
			use as a Font and makes an array
			containing them


	******************************************************/
	std::vector<std::string> family;
	TextFaceFactory::the().getFontFamilies(family);
	// Display all Fonts available
	for (unsigned int i =0; i<family.size(); ++i)
	{
        //Create the Font
        UIFontPtr TheFont = UIFont::create();
        beginEditCP(TheFont);
	        // Determines Font Family (as done above)	Note:
	        // a default setting is included if the Font 
	        // given to the Font does not exist; try putting
	        // random characters into setFamily.  
	        TheFont->setFamily(family[i]);
	        TheFont->setSize(16);
	        TheFont->setStyle(TextFace::STYLE_PLAIN);
        endEditCP(TheFont);
        FontMap[family[i]] = TheFont;
	}
	// Set default Font to Times New Roman if Wide
	// Latin is not included on your machine.  
	std::string buttonFontFamily("Arial");
	if (std::find(family.begin(), family.end(), buttonFontFamily) == family.end())
	{
		buttonFontFamily = "Times New Roman";
	}
	
	/******************************************************

			Create a Font.
			-setFamily(TYPE) determines what format the Font
				is.  The above For loop displays all the
				Font options you have on your machine in the
				console window.
			-setSize(SIZE) determines the size of the 
				Font.
			-setFont(TextFace::STYLE) determines the 
				style the Font is.  Options are: (all 
				preceeded by "TextFace::" : STYLE_PLAIN,
				STYLE_BOLD, STYLE_ITALIC,


	******************************************************/
	UIFontPtr labelFont = UIFont::create();
	beginEditCP(labelFont);
		// Determines Font Family (as determined above)	Note:
		// a default setting is included if the Font 
		// given to the Font does not exist; try putting
		// random characters in for setFamily.  
		labelFont->setFamily(buttonFontFamily);
		labelFont->setSize(25);
		labelFont->setStyle(TextFace::STYLE_PLAIN);
	endEditCP(labelFont);

	/******************************************************


		Create a few Labels and edit their characteristics.

		Note that all Component characteristics can be 
		modified as well (Background, PreferredSize, etc).

		-setFont(FONT_NAME) assigns a Font to the Label
		-setText("TEXT") displays TEXT on the Label (or
			whatever else is in the parenthesis
		-setTextColor(Color4f) sets the color of the 
			text
		-setVerticalAlignment(ALIGNMENT) determines the 
			alignment of the text on the Vertical Axis.
			Arguments are: VERTICAL_TOP, VERTICAL_CENTER,
			and VERTICAL_BOTTOM or a Float between 0.0
			and 1.0.  Note: higher (and lower) values are 
			allowed, but will cause the text to not be 
			completely displayed.
		-setHorizontalAlignment(ALIGNMENT) determines the
			alignment of the text on the Horizontal Axis.
			Arguments are: HORIZONTAL_CENTER, HORIZONTAL_LEFT, 
			and HORIZONTAL_RIGHT or a Float between 0.0
			and 1.0.  Note: higher (and lower) values are 
			allowed, but will cause the text to not be 
			completely displayed.

	******************************************************/
	GradientUIBackgroundPtr label1Background = osg::GradientUIBackground::create();
	beginEditCP(label1Background, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask);
		label1Background->setColorStart( Color4f(1.0, 0.0, 0.0, 1.0) );
		label1Background->setColorEnd( Color4f(0.0, 0.0, 1.0, 1.0) );
	endEditCP(label1Background, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask);
	label1 = osg::Label::create();
	beginEditCP(label1, Component::BackgroundFieldMask | Label::FontFieldMask | Label::TextFieldMask | Label::TextColorFieldMask | Label::VerticalAlignmentFieldMask | Label::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask);
		label1->setBackground(label1Background);
		label1->setFont(labelFont);
		label1->setText("Change My Font!");
		label1->setTextColor( Color4f(1.0, 1.0, 1.0, 1.0) );
		//label1->setActiveTextColor( Color4f(1.0, 1.0, 1.0, 1.0) );
		label1->setVerticalAlignment(0.5);
		label1->setHorizontalAlignment(0.5);
		label1->setPreferredSize( Vec2s(200, 50) );
	endEditCP(label1, Component::BackgroundFieldMask | Label::FontFieldMask | Label::TextFieldMask | Label::TextColorFieldMask | Label::VerticalAlignmentFieldMask | Label::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask);
	



	
	/******************************************************

			The following creates a list of all
			the fonts available on your machine.

			For more information about Lists, see
			18List.

			For more information about ScrollBars 
			and ScrollPanels, see 27ScrollPanel.
			

	******************************************************/
	// Create ListModel Component
	AbstractListModel Model;

	std::vector<std::string> FontFamilies;
	TextFaceFactory::the().getFontFamilies(FontFamilies);

	// Display all Fonts available
    std::map<std::string, UIFontPtr>::iterator FontMapItor;
	for (FontMapItor = FontMap.begin(); FontMapItor != FontMap.end() ; ++FontMapItor)
	{
	    // Add all available Fonts to it
	    Model.pushBack(SharedFieldPtr(new SFString((*FontMapItor).first)));
	}

	// Creates CellGenerator 
	FontListCellGenerator CellGenerator;


	// Create ListPtr
	list = List::create();
	beginEditCP(list, Component::PreferredSizeFieldMask | List::CellLayoutFieldMask);
		list->setPreferredSize( Vec2s (200, 300) );
        list->setCellLayout(VERTICAL_ALIGNMENT);
	endEditCP(list, Component::PreferredSizeFieldMask | List::CellLayoutFieldMask);
	// Assign the Model, CellGenerator, and SelectionModel
	// to the List
	list->setModel(&Model);
	// Assigns the CellGenerator created above
	list->setCellGenerator(&CellGenerator);
	// Creates and assigns a SelectionMode
    ListSelectionModelPtr  SelectionModel(new DefaultListSelectionModel);
    SelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
	list->setSelectionModel(SelectionModel);

    FontListListener TheFontListListener;
    list->addMouseListener(&TheFontListListener);

    //ScrollPanel
    ScrollPanelPtr TheScrollPanel = ScrollPanel::create();
    beginEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	    TheScrollPanel->setPreferredSize(Vec2s(200,300));
        TheScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    TheScrollPanel->setViewComponent(list);

	// Create The Main Frame
	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	FramePtr MainFrame = osg::Frame::create();
	FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();

	beginEditCP(MainFrame, Frame::ChildrenFieldMask);
	   MainFrame->getChildren().addValue(label1);
	   MainFrame->getChildren().addValue(TheScrollPanel);
	   MainFrame->setLayout(MainFrameLayout);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
 
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 17Label/Font Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}
