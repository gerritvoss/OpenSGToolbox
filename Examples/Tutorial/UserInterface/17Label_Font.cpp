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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

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
#include "OSGDefaultListModel.h"
#include "OSGDefaultListComponentGenerator.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGListModel.h"

// Declare variables upfront 

// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

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
class FontListComponentGenerator;

typedef TransitPtr   < FontListComponentGenerator > FontListComponentGeneratorTransitPtr;

class FontListComponentGenerator : public DefaultListComponentGenerator
{
  private:
    friend class FieldContainer;
    std::map<std::string, UIFontRecPtr> _FontMap;

    FontListComponentGenerator &operator =(const FontListComponentGenerator &source)
    {
        return *this;
    }
    /*==========================  PUBLIC  =================================*/
  public:
    typedef          DefaultListComponentGenerator Inherited;
    typedef          FontListComponentGenerator Self;
    typedef Inherited::TypeObject TypeObject;

    OSG_GEN_INTERNALPTR(FontListComponentGenerator);

    ComponentTransitPtr getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
    {
        if(Value.empty()){
            return ComponentTransitPtr(NULL);
        }
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

        // Create using the DefaultListComponentGenerator a
        // Label (its default) with the Font name as its text
        ComponentRecPtr TheComponent = getListComponentFromString(Parent, FontFamilyString, Index, IsSelected, HasFocus);

        // Add the required Font to FontMapItor
        std::map<std::string, UIFontRecPtr>::iterator FontMapItor = _FontMap.find(FontFamilyString);
        if(FontMapItor != _FontMap.end() && TheComponent->getType().isDerivedFrom(TextComponent::getClassType()))
        {
            // Set the TextComponent's Font to be its correct Font
            dynamic_pointer_cast<TextComponent>(TheComponent)->setFont((*FontMapItor).second);
        }

        return ComponentTransitPtr(TheComponent);
    }

    const std::map<std::string, UIFontRecPtr>& getFontMap(void) const
    {
        return _FontMap;
    }

    static FieldContainerType &getClassType   (void)
    {
        return _type;
    }

    static UInt32              getClassTypeId (void)
    {
        return _type.getId();
    }

    static UInt16              getClassGroupId(void)
    {
        return _type.getGroupId();
    }

    FieldContainerType &getType         (void)
    {
        return _type;
    }

    const FieldContainerType &getType         (void) const
    {
        return _type;
    }

    static FontListComponentGeneratorTransitPtr create(void)
    {
        FontListComponentGeneratorTransitPtr fc(new FontListComponentGenerator());

        /******************************************************

          Determine which Fonts your computer can
          use as a Font and makes a vector
          containing them.

         ******************************************************/
        std::vector<std::string> family;
        TextFaceFactory::the()->getFontFamilies(family);

        /******************************************************

          Cycle through all available Fonts
          and add a Font of the type contained
          in its string name to a map containing
          both values.

         ******************************************************/
        std::cout << "Generating all of the fonts on you system.  This may take some time..." << std::endl;
        for (unsigned int i =0; i<family.size(); ++i)
        {
            //Create the Fonts
            UIFontRecPtr TheFont = UIFont::create();
            TheFont->setFamily(family[i]);
            TheFont->setSize(18);
            TheFont->setGlyphPixelSize(18);
            TheFont->setStyle(TextFace::STYLE_PLAIN);
            // Setup the FontMap map to pair the
            // string Font name with a Font with
            // that Font
            fc->_FontMap[family[i]] = TheFont;
        }

        return fc;
    }

  protected:

    static FieldContainerType  _type;

    FontListComponentGenerator(void) : Inherited()
    {
    }

    FontListComponentGenerator(const FontListComponentGenerator& source) : Inherited(source)
    {
    }

    ~FontListComponentGenerator(void)
    {
    }

};

FontListComponentGenerator::TypeObject
    FontListComponentGenerator::_type("FontListComponentGenerator",
                                      "DefaultListComponentGenerator",
                                      "NULL",
                                      0,
                                      reinterpret_cast<PrototypeCreateF>(&FontListComponentGenerator::createEmpty),
                                      NULL,
                                      NULL,
                                      NULL,//reinterpret_cast<InitalInsertDescFunc>(&DefaultListComponentGenerator::classDescInserter),
                                      false,
                                      0,
                                      "",
                                      "FontListComponentGenerator"
                                     );

OSG_BEGIN_NAMESPACE

OSG_GEN_CONTAINERPTR(FontListComponentGenerator);
/*! \ingroup GrpContribUserInterfaceFieldTraits
  \ingroup GrpLibOSGContribUserInterface
  */
template <>
struct FieldTraits<FontListComponentGenerator *> :
public FieldTraitsFCPtrBase<FontListComponentGenerator *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<FontListComponentGenerator *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
        static const Char8    *getSName     (void);

    //    static const char *getSName(void) { return "SFFontListComponentGeneratorPtr"; }
    template<typename RefCountPolicy> inline
        static const Char8    *getMName     (void);

    //    static const char *getMName(void) { return "MFFontListComponentGeneratorPtr"; }
};

    template<> inline
const Char8 *FieldTraits<FontListComponentGenerator *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecFontListComponentGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<FontListComponentGenerator *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecFontListComponentGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<FontListComponentGenerator *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakFontListComponentGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<FontListComponentGenerator *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdFontListComponentGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<FontListComponentGenerator *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecFontListComponentGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<FontListComponentGenerator *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecFontListComponentGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<FontListComponentGenerator *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakFontListComponentGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<FontListComponentGenerator *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdFontListComponentGeneratorPtr"; 
}

/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<FontListComponentGenerator *,
        RecordedRefCountPolicy  > SFRecFontListComponentGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<FontListComponentGenerator *,
        UnrecordedRefCountPolicy> SFUnrecFontListComponentGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<FontListComponentGenerator *,
        WeakRefCountPolicy      > SFWeakFontListComponentGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<FontListComponentGenerator *,
        NoRefCountPolicy        > SFUncountedFontListComponentGeneratorPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<FontListComponentGenerator *,
        RecordedRefCountPolicy  > MFRecFontListComponentGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<FontListComponentGenerator *,
        UnrecordedRefCountPolicy> MFUnrecFontListComponentGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<FontListComponentGenerator *,
        WeakRefCountPolicy      > MFWeakFontListComponentGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<FontListComponentGenerator *,
        NoRefCountPolicy        > MFUncountedFontListComponentGeneratorPtr;
OSG_END_NAMESPACE

// Setup a Font to change the label's font
// when a different item in the FontList is
// selected
void handleSelectionChanged(ListSelectionEventDetails* const details,
                            List* const FontList,
                            Label* const ExampleLabel,
                            FontListComponentGenerator* const TheGenerator)
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

        // Get the Font and create new FontRecPtr
        UIFontRecPtr TheSelectedFont(TheGenerator->getFontMap().find(ValueStr)->second);

        if(TheSelectedFont != NULL)
        {
            // Set the font for ExampleLabel to be selected font
            ExampleLabel->setFont(TheSelectedFont);
        }
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
        UIFontRecPtr ExampleLabelFont = UIFont::create();
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
        GradientLayerRecPtr ExampleLabelBackground = GradientLayer::create();
        ExampleLabelBackground->editMFColors()->push_back(Color4f(1.0, 0.0, 0.0, 1.0));
        ExampleLabelBackground->editMFStops()->push_back(0.0);
        ExampleLabelBackground->editMFColors()->push_back(Color4f(0.0, 0.0, 1.0, 1.0));
        ExampleLabelBackground->editMFStops()->push_back(1.0);
        LabelRecPtr ExampleLabel = Label::create();
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
        // Creates ComponentGenerator
        FontListComponentGeneratorRecPtr TheGenerator = FontListComponentGenerator::create();

        // Create ListModel Component
        DefaultListModelRecPtr ListModel = DefaultListModel::create();

        // Display all Fonts available
        std::map<std::string, UIFontRecPtr>::const_iterator FontMapItor;
        for (FontMapItor = TheGenerator->getFontMap().begin();
             FontMapItor != TheGenerator->getFontMap().end() ;
             ++FontMapItor)
        {
            // Add the Fonts to the List
            ListModel->pushBack(boost::any((*FontMapItor).first));
        }

        // Create the List of Fonts (see 18List for more information)
        ListRecPtr FontList = List::create();
        FontList->setPreferredSize(Vec2f(200, 300));
        FontList->setOrientation(List::VERTICAL_ORIENTATION);
        FontList->setCellGenerator(TheGenerator);
        FontList->setModel(ListModel);
        FontList->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);

        FontList->
            getSelectionModel()->
                connectSelectionChanged(boost::bind(handleSelectionChanged, _1,
                                                    FontList.get(),
                                                    ExampleLabel.get(),
                                                    TheGenerator.get()));


        //ScrollPanel
        ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        ExampleScrollPanel->setViewComponent(FontList);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        FlowLayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleLabel);
        MainInternalWindow->pushToChildren(ExampleScrollPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
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
                                   "17Label_Font");

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
