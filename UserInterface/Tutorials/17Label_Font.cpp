// OpenSG Tutorial Example: Creating a Label and Creating Fonts
//
// This tutorial explains how to change Fonts and create
// Labels
// 
// Includes: Font and Label creation and settings


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
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 17Label_Font Headers
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/OSGTextFaceFactory.h>
#include <map>

// Include Label and Font headerfiles
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGUIFont.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGListSelectionListener.h>
#include <OpenSG/UserInterface/OSGAbstractListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListComponentGenerator.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGListModel.h>


// Declare variables upfront 
std::map<std::string, UIFontPtr> FontMap;
LabelPtr ExampleLabel;
ListPtr FontList;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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

    /******************************************************

            Creates a ListComponentGenerator class to 
            create Labels for the List which contain
            the Font name in that particular Font.

            This creates the DefaultListCell (a 
            Label with Text equal to the name
            of the Font) and then changes that
            Label's Font to be the Font contained
            within the Label.

            The ListComponentGenerator is what is
            used to create the Component
            values for the List.  The Default 
            is to simply create Label components
            which normally simply contain a text
            string.  In this case, the
            DefaultListComponentGenerator is 
            modified slightly to give each
            Label component the Font which
            its text will display.


    ******************************************************/

class FontListComponentGenerator : public DefaultListComponentGenerator
{
    /*==========================  PUBLIC  =================================*/
  public:
	virtual ComponentPtr getListComponent(ListPtr Parent, SharedFieldPtr Value, UInt32 Index, bool IsSelected, bool HasFocus)
    {
        // Create using the DefaultListComponentGenerator a
        // Label (its default) with the Font name as its text

        LabelPtr ListComponentLabel = Label::Ptr::dcast(
            DefaultListComponentGenerator::getListComponent(
            Parent, Value, Index, IsSelected, HasFocus)
            );

        std::string FontFamilyString;
        // Converts the Fontname to correct type
        if(Value->getType() == SFString::getClassType())
        {
            FontFamilyString = dynamic_cast<SFString*>(Value.get())->getValue();
        }
        else
        {
            // Gives a default Value
            FontFamilyString = "Times New Roman";
        }
        
        // Add the required Font to FontMapItor
        std::map<std::string, UIFontPtr>::iterator FontMapItor = FontMap.find(FontFamilyString);
        if(FontMapItor != FontMap.end())
        {
            beginEditCP(ListComponentLabel, Label::FontFieldMask);
                // Set the Label's Font to be its correct Font
                ListComponentLabel->setFont((*FontMapItor).second);
            endEditCP(ListComponentLabel, Label::FontFieldMask);
        }

        return ListComponentLabel;
    }

    FontListComponentGenerator(void)
    {
    }

    virtual ~FontListComponentGenerator(void)
    {
    }
};

// Setup a FontListener to change the label's font
// when a different item in the FontList is
// selected
class FontListListener: public ListSelectionListener
{
  public:
    virtual void selectionChanged(const ListSelectionEvent& e)
    {
        if(!FontList->getSelectionModel()->isSelectionEmpty())
        {
            std::string ValueStr("");
            SharedFieldPtr Value(FontList->getValueAtIndex(FontList->getSelectionModel()->getAnchorSelectionIndex()));
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
                // Set the font for ExampleLabel to be selected font
                beginEditCP(ExampleLabel, Label::FontFieldMask);
                    ExampleLabel->setFont(TheSelectedFont);
                endEditCP(ExampleLabel, Label::FontFieldMask);
            }
        }
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
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

    
    /******************************************************

            Determine which Fonts your computer can
            use as a Font and makes a vector
            containing them.

    ******************************************************/
    std::vector<std::string> family;
    TextFaceFactory::the().getFontFamilies(family);

    /******************************************************

            Cycle through all available Fonts
            and add a Font of the type contained
            in its string name to a map containing
            both values.

    ******************************************************/
    for (unsigned int i =0; i<family.size(); ++i)
    {
        //Create the Fonts
        UIFontPtr TheFont = UIFont::create();
        beginEditCP(TheFont, UIFont::FamilyFieldMask | UIFont::SizeFieldMask | UIFont::StyleFieldMask);
            TheFont->setFamily(family[i]);
            TheFont->setSize(16);
            TheFont->setStyle(TextFace::STYLE_PLAIN);
        endEditCP(TheFont, UIFont::FamilyFieldMask | UIFont::SizeFieldMask | UIFont::StyleFieldMask);
        // Setup the FontMap map to pair the
        // string Font name with a Font with
        // that Font
        FontMap[family[i]] = TheFont;
    }

    
    /******************************************************

            Create and edit a Font.

            -setFamily("Name"): Determines the style of the 
                Font.  All Fonts available on your machine
                will be displayed when you run this 
                tutorial in a List format.
            -setSize(int): Determines the size of the 
                Font.
            -setFont(TextFace::ENUM): Determines the 
                style of the Font.  Takes STYLE_PLAIN,
                STYLE_BOLD, and STYLE_ITALIC arguments.

			Note: for the Family type, a default is
			automatically given if the input is 
			something other than a recognized Font
			family.  In this Tutorial, this is
			only apparent initially as when a 
			Font in the List is selected, the Font
			changes.

    ******************************************************/
    UIFontPtr ExampleLabelFont = UIFont::create();
	beginEditCP(ExampleLabelFont, UIFont::FamilyFieldMask | UIFont::SizeFieldMask | UIFont::StyleFieldMask);
        //ExampleLabelFont->setFamily("Times New Roman");
		// Displayed Font will be default (this Font name does NOT exist)
        ExampleLabelFont->setFamily("RandomGibberishFontNameWhichDoesntExist");
        ExampleLabelFont->setSize(25);
        ExampleLabelFont->setStyle(TextFace::STYLE_PLAIN);
    endEditCP(ExampleLabelFont, UIFont::FamilyFieldMask | UIFont::SizeFieldMask | UIFont::StyleFieldMask);

    /******************************************************


        Create and edit a Label.

        Note that all Component characteristics can be 
        modified as well (Background, PreferredSize, etc).

        -setFont(FontName): Determine the Font used
			with the Label.
        -setText("Text"): Determine the text on
			the Label.  Text will be displayed
			with this example.
        -setTextColor(Color4f): Determine the Font
			Color.
        -setVerticalAlignment(ENUM or float): Determine the 
            alignment of the text on the Vertical axis.
            Takes VERTICAL_TOP, VERTICAL_CENTER,
            and VERTICAL_BOTTOM arguments or a float 
			between 0.0 and 1.0.  Note: higher (and lower) 
			values are allowed, but will cause the text 
			to not be  completely displayed.
        -setHorizontalAlignment(ENUM or float):
			Determine the alignment of the text on the 
			Horizontal axis.  Takes HORIZONTAL_CENTER, HORIZONTAL_LEFT, 
            and HORIZONTAL_RIGHT arguments or a float 
			between 0.0 and 1.0.  Note: higher (and lower) 
			values are allowed, but will cause the text 
			to not be  completely displayed.

    ******************************************************/

	// Create a GradientBackground to add to the Label
    GradientUIBackgroundPtr ExampleLabelBackground = osg::GradientUIBackground::create();
    beginEditCP(ExampleLabelBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask);
        ExampleLabelBackground->setColorStart(Color4f(1.0, 0.0, 0.0, 1.0));
        ExampleLabelBackground->setColorEnd(Color4f(0.0, 0.0, 1.0, 1.0));
    endEditCP(ExampleLabelBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask);
    ExampleLabel = osg::Label::create();
    beginEditCP(ExampleLabel, Label::BackgroundsFieldMask | Label::FontFieldMask | Label::TextFieldMask | Label::TextColorFieldMask | Label::VerticalAlignmentFieldMask | Label::HorizontalAlignmentFieldMask | Label::PreferredSizeFieldMask | Label::TextSelectableFieldMask);
        ExampleLabel->setBackgrounds(ExampleLabelBackground);
        ExampleLabel->setFont(ExampleLabelFont);
        ExampleLabel->setText("Change My Font!");
        ExampleLabel->setTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        //ExampleLabel->setActiveTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        ExampleLabel->setVerticalAlignment(0.5);
        ExampleLabel->setHorizontalAlignment(0.5);
        ExampleLabel->setPreferredSize(Vec2f(200, 50));
        ExampleLabel->setTextSelectable(true);
    endEditCP(ExampleLabel, Label::BackgroundsFieldMask | Label::FontFieldMask | Label::TextFieldMask | Label::TextColorFieldMask | Label::VerticalAlignmentFieldMask | Label::HorizontalAlignmentFieldMask | Label::PreferredSizeFieldMask | Label::TextSelectableFieldMask);
    
    /******************************************************

            The following creates a List of all
            the Fonts available on your machine,
            and adds them to a ScrollPanel.

            For more information about Lists, see
            18List.

            For more information about ScrollBars 
            and ScrollPanels, see 27ScrollPanel.
            

    ******************************************************/
    // Create ListModel Component
    AbstractListModel ListModel;

    // Display all Fonts available
    std::map<std::string, UIFontPtr>::iterator FontMapItor;
    for (FontMapItor = FontMap.begin(); FontMapItor != FontMap.end() ; ++FontMapItor)
    {
        // Add the Fonts to the List
        ListModel.pushBack(SharedFieldPtr(new SFString((*FontMapItor).first)));
    }

    // Creates ComponentGenerator
    FontListComponentGenerator ComponentGenerator;
	ComponentGeneratorPtr TheGenerator(ComponentGenerator);

    // Create the List of Fonts (see 18List for more information)
    FontList = List::create();
    beginEditCP(FontList, List::PreferredSizeFieldMask | List::CellOrientationFieldMask | List::CellGeneratorFieldMask);
        FontList->setPreferredSize(Vec2f(200, 300));
        FontList->setCellOrientation(VERTICAL_ALIGNMENT);
		FontList->setCellGenerator(TheGenerator);
    endEditCP(FontList, List::PreferredSizeFieldMask | List::CellOrientationFieldMask | List::CellGeneratorFieldMask);
    FontList->setModel(&ListModel);
    ListSelectionModelPtr SelectionModel(new DefaultListSelectionModel);
    SelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
    FontList->setSelectionModel(SelectionModel);

    FontListListener TheFontListListener;
    FontList->getSelectionModel()->addListSelectionListener(&TheFontListListener);

    //ScrollPanel
    ScrollPanelPtr ExampleScrollPanel = ScrollPanel::create();
    beginEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    ExampleScrollPanel->setViewComponent(FontList);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    FlowLayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleLabel);
       MainInternalWindow->getChildren().push_back(ExampleScrollPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
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
                                        Vec2f(900,900),
                                        "OpenSG 17Label/Font Window");

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
