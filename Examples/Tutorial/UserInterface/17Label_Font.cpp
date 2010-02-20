// OpenSG Tutorial Example: Creating a Label and Creating Fonts
//
// This tutorial explains how to change Fonts and create
// Labels
// 
// Includes: Font and Label creation and settings

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

// 17Label_Font Headers
#include "OSGLayers.h"
#include "OSGButton.h"
#include "OSGFlowLayout.h"
#include "OSGGradientLayer.h"
#include "OSGLookAndFeelManager.h"
//#include "OSGUIDefines.h"
#include "OSGScrollPanel.h"
#include "OSGTextFaceFactory.h"
#include <map>

// Include Label and Font headerfiles
#include "OSGLabel.h"
#include "OSGUIFont.h"

// List header files
#include "OSGList.h"
#include "OSGListSelectionListener.h"
#include "OSGDefaultListModel.h"
#include "OSGDefaultListComponentGenerator.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGListModel.h"


// Declare variables upfront 
std::map<std::string, UIFontRefPtr> FontMap;
LabelRefPtr ExampleLabel;
ListRefPtr FontList;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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
    typedef          DefaultListComponentGenerator Inherited;
    typedef          FontListComponentGenerator Self;
	typedef          FCRefPtr<Inherited::RefPtr,  Self      > PtrType;

	OSG_FIELD_CONTAINER_DECL(PtrType)
	
	virtual ComponentRefPtr getListComponent(ListRefPtr Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
    {
        // Create using the DefaultListComponentGenerator a
        // Label (its default) with the Font name as its text

        ComponentRefPtr TheComponent = Inherited::getListComponent(Parent, Value, Index, IsSelected, HasFocus);

        std::string FontFamilyString;
        // Converts the Fontname to correct type
        try
        {
            FontFamilyString = boost::any_cast<std::string>(Value);
        }
        catch(boost::bad_any_cast &)
        {
            FontFamilyString = "Times New Roman";
        }
        
        // Add the required Font to FontMapItor
        std::map<std::string, UIFontRefPtr>::iterator FontMapItor = FontMap.find(FontFamilyString);
        if(FontMapItor != FontMap.end() && TheComponent->getType().isDerivedFrom(TextComponent::getClassType()))
	    {
                // Set the TextComponent's Font to be its correct Font
                dynamic_pointer_cast<TextComponent>(TheComponent)->setFont((*FontMapItor).second);
        }

        return TheComponent;
    }

protected:

	static FieldContainerType  _type;

	FontListComponentGenerator(void) : Inherited()
    {
    }

	FontListComponentGenerator(const FontListComponentGenerator& source) : Inherited(source)
    {
    }

    virtual ~FontListComponentGenerator(void)
    {
    }
private:
	friend class FieldContainer;

    FontListComponentGenerator &operator =(const FontListComponentGenerator &source)
	{
		return *this;
	}
};

FieldContainerType FontListComponentGenerator::_type("FontListComponentGenerator",
                                     "DefaultListComponentGenerator",
                                      NULL,
                                      (PrototypeCreateF) &FontListComponentGenerator::createEmpty,
                                      NULL,
									  NULL,
                                      0);

OSG_FIELD_CONTAINER_INL_DEF(FontListComponentGenerator::Self, FontListComponentGenerator::PtrType)
OSG_FIELD_CONTAINER_DEF(FontListComponentGenerator::Self, FontListComponentGenerator::PtrType)
typedef FontListComponentGenerator::PtrType FontListComponentGeneratorRefPtr;

// Setup a FontListener to change the label's font
// when a different item in the FontList is
// selected
class FontListListener: public ListSelectionListener
{
  public:
    virtual void selectionChanged(const ListSelectionEventUnrecPtr e)
    {
        if(!FontList->getSelectionModel()->isSelectionEmpty())
        {
            std::string ValueStr("");
            
            try
            {
                ValueStr = boost::any_cast<std::string>(FontList->getValueAtIndex(FontList->getSelectionModel()->getAnchorSelectionIndex()));
            }
            catch(boost::bad_any_cast &)
            {
            }
            // Output selected font
            std::cout << "Setting Font: " << ValueStr << std::endl;

            // Get the Font and create new FontRefPtr
            UIFontRefPtr TheSelectedFont(FontMap[ValueStr]);

            if(TheSelectedFont != NULL)
            {
                // Set the font for ExampleLabel to be selected font
                    ExampleLabel->setFont(TheSelectedFont);
            }
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
        UIFontRefPtr TheFont = UIFont::create();
            TheFont->setFamily(family[i]);
            TheFont->setSize(16);
            TheFont->setStyle(TextFace::STYLE_PLAIN);
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
    UIFontRefPtr ExampleLabelFont = UIFont::create();
        //ExampleLabelFont->setFamily("Times New Roman");
		// Displayed Font will be default (this Font name does NOT exist)
        ExampleLabelFont->setFamily("RandomGibberishFontNameWhichDoesntExist");
        ExampleLabelFont->setSize(25);
        ExampleLabelFont->setStyle(TextFace::STYLE_PLAIN);

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
        -setAlignment(Vec2f): Determine the 
            alignment of the text a float 
			between 0.0 and 1.0.  Note: higher (and lower) 
			values are allowed, but will cause the text 
			to not be  completely displayed.

    ******************************************************/

	// Create a GradientBackground to add to the Label
    GradientLayerRefPtr ExampleLabelBackground = OSG::GradientLayer::create();
        ExampleLabelBackground->getColors().push_back(Color4f(1.0, 0.0, 0.0, 1.0));
		ExampleLabelBackground->getStops().push_back(0.0);
        ExampleLabelBackground->getColors().push_back(Color4f(0.0, 0.0, 1.0, 1.0));
		ExampleLabelBackground->getStops().push_back(1.0);
    ExampleLabel = OSG::Label::create();
        ExampleLabel->setBackgrounds(ExampleLabelBackground);
        ExampleLabel->setFont(ExampleLabelFont);
        ExampleLabel->setText("Change My Font!");
        ExampleLabel->setTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        //ExampleLabel->setActiveTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        ExampleLabel->setAlignment(Vec2f(0.5,0.5));
        ExampleLabel->setPreferredSize(Vec2f(200, 50));
        ExampleLabel->setTextSelectable(true);
    
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
	DefaultListModelRefPtr ListModel = DefaultListModel::create();

    // Display all Fonts available
    std::map<std::string, UIFontRefPtr>::iterator FontMapItor;
    for (FontMapItor = FontMap.begin(); FontMapItor != FontMap.end() ; ++FontMapItor)
    {
        // Add the Fonts to the List
        ListModel->pushBack(boost::any((*FontMapItor).first));
    }

    // Creates ComponentGenerator
	FontListComponentGeneratorRefPtr TheGenerator = FontListComponentGenerator::create();

    // Create the List of Fonts (see 18List for more information)
    FontList = List::create();
        FontList->setPreferredSize(Vec2f(200, 300));
        FontList->setOrientation(List::VERTICAL_ORIENTATION);
		FontList->setCellGenerator(TheGenerator);
		FontList->setModel(ListModel);
    ListSelectionModelRefPtr SelectionModel(new DefaultListSelectionModel);
    SelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
    FontList->setSelectionModel(SelectionModel);

    FontListListener TheFontListListener;
    FontList->getSelectionModel()->addListSelectionListener(&TheFontListListener);

    //ScrollPanel
    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(FontList);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    FlowLayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(ExampleLabel);
       MainInternalWindow->pushToChildren(ExampleScrollPanel);
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
            "17Label_Font");

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
