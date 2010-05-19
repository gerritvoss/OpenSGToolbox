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

// the general scene file loading handler
#include "OSGSceneFileHandler.h"

//Input
#include "OSGWindowUtils.h"
#include "OSGMouseAdapter.h"

// UserInterface Headers
#include "OSGInternalWindow.h"
#include "OSGUIForeground.h"
#include "OSGLayers.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGFlowLayout.h"
#include "OSGBorderLayout.h"
#include "OSGGridBagLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGGridBagLayoutConstraints.h"
#include "OSGGradientLayer.h"
#include "OSGLookAndFeelManager.h"
//#include "OSGUIDefines.h"
#include "OSGTypeFactory.h"

#include "OSGFieldContainerFactory.h"

// Include Label and Font headerfiles
#include "OSGLabel.h"

// List header files
#include "OSGList.h"
#include "OSGDefaultListModel.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGListModel.h"

#include "OSGScrollPanel.h"
#include "OSGPanel.h"
#include "OSGLabel.h"

#include <sstream>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Declare upfront so they can be referenced

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Ctrl+q
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

// Setup a listener to change the label's font
// when a different item in the list is
// selected
class TypeListListener: public MouseAdapter
{
  public:
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
    }
};

class OpenSGTypePanel
{
  public:

    class FCListListener: public ListSelectionListener
    {
      public:
        virtual void selectionChanged(const ListSelectionEventUnrecPtr e)
        {
            if(!_List->getSelectionModel()->isSelectionEmpty())
            {
                std::string ValueStr("");
                try
                {
                    ValueStr = boost::any_cast<std::string>(_List->getValueAtIndex(_List->getSelectionModel()->getAnchorSelectionIndex()));
                }
                catch(boost::bad_any_cast &)
                {
                }

                FieldContainerType* TheFCType = FieldContainerFactory::the()->findType(ValueStr.c_str());

                if(TheFCType != NULL)
                {

                    // Output selected font
                    std::cout << "Field ComponentContainer Type: " << TheFCType->getCName() << std::endl;
                    std::cout << std::setw(25) << "Field Name" << " | " << std::setw(22) << "Type" << " | " << std::setw(11) << "Cardinality"  << " | " << std::setw(25) << "Default Value" << std::endl;
                    for(UInt32 i(1) ; i<TheFCType->getNumFieldDescs()+1 ; ++i)
                    {
                        FieldDescriptionBase* Desc = TheFCType->getFieldDesc(i);
                        if(!Desc->isInternal())
                        {
                            const FieldType& TheField( Desc->getFieldType() );
                            std::cout << std::setw(25) << Desc->getCName() << " | " ;
                            std::cout << std::setw(22) << TheField.getContentType().getCName() << " | " ;
                            if(TheField.getCardinality() == FieldType::SingleField)
                            {
                                std::cout << std::setw(11) << "Single"  << " | " ;
                            }
                            else
                            {
                                std::cout << std::setw(11) << "Many"  << " | " ;
                            }

                            if(TheFCType->getPrototype() != NULL &&
                               TheFCType->getPrototype()->getField(Desc->getFieldId()) != NULL)
                            {
                                std::string Value;
                                //TheFCType->getPrototype()->getField(Desc->getFieldId())->getValueByStr(Value, 0);
                                std::cout << std::setw(25) << Value;
                            }

                            std::cout   << std::endl;
                        }
                    }
                    std::cout << std::endl << std::endl;
                }
            }
        }

        void setList(ListRefPtr TheList)
        {
            _List = TheList;
        }
      protected:
        ListRefPtr _List;
    };

  protected:
    PanelRefPtr _MainPanel;
    DefaultListModelRefPtr _TypeModel;
    DefaultListModelRefPtr _FieldTypeModel;
    DefaultListModelRefPtr _FieldContainerTypeModel;
    FCListListener TheFCListListener;

    PanelRefPtr createTypePanel(void)
    {
        //Put all the FieldTypes into the model
        _TypeModel = DefaultListModel::create();
        for (UInt32 i(1); i <= TypeFactory::the()->getNumTypes() ; ++i)
        {
            TypeBase* TheType;
            TheType = TypeFactory::the()->findType(i);
            if(TheType != NULL)
            {
                // Add all available Fonts to it
                _TypeModel->pushBack(boost::any(std::string(TheType->getCName())));
            }
        }
        // Create TypeList
        ListRefPtr TypeList = List::create();
        TypeList->setPreferredSize( Vec2f (200, 300) );
        TypeList->setOrientation(List::VERTICAL_ORIENTATION);
        TypeList->setModel(_TypeModel);

        // Assign the Model, and SelectionModel
        // to the List
        // Creates and assigns a SelectionMode
        ListSelectionModelPtr  FieldSelectionModel(new DefaultListSelectionModel);
        FieldSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
        TypeList->setSelectionModel(FieldSelectionModel);

        GridBagLayoutConstraintsRefPtr TypeListScrollPanelConstraints = OSG::GridBagLayoutConstraints::create();
        TypeListScrollPanelConstraints->setGridX(0);
        TypeListScrollPanelConstraints->setGridY(0);
        TypeListScrollPanelConstraints->setGridHeight(1);
        TypeListScrollPanelConstraints->setGridWidth(2);
        TypeListScrollPanelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        TypeListScrollPanelConstraints->setVerticalAlignment(1.0);

        //TypeListScrollPanel
        ScrollPanelRefPtr TypeListScrollPanel = ScrollPanel::create();
        TypeListScrollPanel->setPreferredSize(Vec2f(200,300));
        TypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        TypeListScrollPanel->setConstraints(TypeListScrollPanelConstraints);
        TypeListScrollPanel->setViewComponent(TypeList);

        //Number of FieldContainerTypes Label
        GridBagLayoutConstraintsRefPtr NumTypesLabelConstraints = OSG::GridBagLayoutConstraints::create();
        NumTypesLabelConstraints->setGridX(0);
        NumTypesLabelConstraints->setGridY(1);
        NumTypesLabelConstraints->setGridHeight(1);
        NumTypesLabelConstraints->setGridWidth(1);
        NumTypesLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumTypesLabelConstraints->setWeightX(1.0);
        NumTypesLabelConstraints->setVerticalAlignment(0.0);

        LabelRefPtr NumTypesLabel = Label::create();
        NumTypesLabel->setText("Number Field Types: ");
        NumTypesLabel->setConstraints(NumTypesLabelConstraints);

        //Number of FieldContainerTypes Value Label
        GridBagLayoutConstraintsRefPtr NumTypesValueLabelConstraints = OSG::GridBagLayoutConstraints::create();
        NumTypesValueLabelConstraints->setGridX(1);
        NumTypesValueLabelConstraints->setGridY(1);
        NumTypesValueLabelConstraints->setGridHeight(1);
        NumTypesValueLabelConstraints->setGridWidth(1);
        NumTypesValueLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumTypesValueLabelConstraints->setWeightX(1.0);
        NumTypesValueLabelConstraints->setVerticalAlignment(0.0);

        LabelRefPtr NumTypesValueLabel = Label::create();
        std::stringstream TempSStream;
        TempSStream << TypeFactory::the()->getNumTypes();
        NumTypesValueLabel->setText(TempSStream.str());
        NumTypesValueLabel->setConstraints(NumTypesValueLabelConstraints);

        //Create Main Panel Layout
        GridBagLayoutRefPtr TypePanelLayout = OSG::GridBagLayout::create();
        TypePanelLayout->setColumns(2);
        TypePanelLayout->setRows(2);

        //Create Main Panel
        PanelRefPtr TypePanel = Panel::create();

        TypePanel->pushToChildren(TypeListScrollPanel);
        TypePanel->pushToChildren(NumTypesLabel);
        TypePanel->pushToChildren(NumTypesValueLabel);
        TypePanel->setLayout(TypePanelLayout);
        return TypePanel;
    }

    PanelRefPtr createFieldTypePanel(void)
    {
        //Put all the FieldTypes into the model
        _FieldTypeModel = DefaultListModel::create();
        UInt32 NumTypesFound(0);
        for (UInt32 i(1); i <= TypeFactory::the()->getNumTypes() ; ++i)
        {
            TypeBase* TheType;
            TheType = TypeFactory::the()->findType(i);
            if(TheType != NULL &&
               dynamic_cast<FieldType*>(TheType) != NULL)
            {
                // Add all available Fonts to it
                _FieldTypeModel->pushBack(boost::any(std::string(TheType->getCName())));
                ++NumTypesFound;
            }
        }

        // Create FieldTypeList
        ListRefPtr FieldTypeList = List::create();
        FieldTypeList->setPreferredSize( Vec2f (200, 300) );
        FieldTypeList->setOrientation(List::VERTICAL_ORIENTATION);
        FieldTypeList->setModel(_FieldTypeModel);

        // Assign the Model, and SelectionModel
        // to the List
        // Creates and assigns a SelectionMode
        ListSelectionModelPtr  FieldSelectionModel(new DefaultListSelectionModel);
        FieldSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
        FieldTypeList->setSelectionModel(FieldSelectionModel);

        GridBagLayoutConstraintsRefPtr FieldTypeListScrollPanelConstraints = OSG::GridBagLayoutConstraints::create();
        FieldTypeListScrollPanelConstraints->setGridX(0);
        FieldTypeListScrollPanelConstraints->setGridY(0);
        FieldTypeListScrollPanelConstraints->setGridHeight(1);
        FieldTypeListScrollPanelConstraints->setGridWidth(2);
        FieldTypeListScrollPanelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        FieldTypeListScrollPanelConstraints->setVerticalAlignment(1.0);

        //FieldTypeListScrollPanel
        ScrollPanelRefPtr FieldTypeListScrollPanel = ScrollPanel::create();
        FieldTypeListScrollPanel->setPreferredSize(Vec2f(200,300));
        FieldTypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        FieldTypeListScrollPanel->setConstraints(FieldTypeListScrollPanelConstraints);
        FieldTypeListScrollPanel->setViewComponent(FieldTypeList);

        //Number of FieldContainerTypes Label
        GridBagLayoutConstraintsRefPtr NumFieldTypesLabelConstraints = OSG::GridBagLayoutConstraints::create();
        NumFieldTypesLabelConstraints->setGridX(0);
        NumFieldTypesLabelConstraints->setGridY(1);
        NumFieldTypesLabelConstraints->setGridHeight(1);
        NumFieldTypesLabelConstraints->setGridWidth(1);
        NumFieldTypesLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumFieldTypesLabelConstraints->setWeightX(1.0);
        NumFieldTypesLabelConstraints->setVerticalAlignment(0.0);

        LabelRefPtr NumFieldTypesLabel = Label::create();
        NumFieldTypesLabel->setText("Number Field Types: ");
        NumFieldTypesLabel->setConstraints(NumFieldTypesLabelConstraints);

        //Number of FieldContainerTypes Value Label
        GridBagLayoutConstraintsRefPtr NumFieldTypesValueLabelConstraints = OSG::GridBagLayoutConstraints::create();
        NumFieldTypesValueLabelConstraints->setGridX(1);
        NumFieldTypesValueLabelConstraints->setGridY(1);
        NumFieldTypesValueLabelConstraints->setGridHeight(1);
        NumFieldTypesValueLabelConstraints->setGridWidth(1);
        NumFieldTypesValueLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumFieldTypesValueLabelConstraints->setWeightX(1.0);
        NumFieldTypesValueLabelConstraints->setVerticalAlignment(0.0);

        LabelRefPtr NumFieldTypesValueLabel = Label::create();
        std::stringstream TempSStream;
        TempSStream << NumTypesFound;
        NumFieldTypesValueLabel->setText(TempSStream.str());
        NumFieldTypesValueLabel->setConstraints(NumFieldTypesValueLabelConstraints);

        //Create Main Panel Layout
        GridBagLayoutRefPtr FieldTypePanelLayout = OSG::GridBagLayout::create();
        FieldTypePanelLayout->setColumns(2);
        FieldTypePanelLayout->setRows(2);

        //Create Main Panel
        PanelRefPtr FieldTypePanel = Panel::create();

        FieldTypePanel->pushToChildren(FieldTypeListScrollPanel);
        FieldTypePanel->pushToChildren(NumFieldTypesLabel);
        FieldTypePanel->pushToChildren(NumFieldTypesValueLabel);
        FieldTypePanel->setLayout(FieldTypePanelLayout);
        return FieldTypePanel;
    }

    PanelRefPtr createFieldContainerTypePanel(void)
    {
        //Put all the FieldContainerTypes into the model
        _FieldContainerTypeModel = DefaultListModel::create();
        UInt32 NumTypesFound(0);
        for (UInt32 i(0); NumTypesFound < FieldContainerFactory::the()->getNumTypes() ; ++i)
        {
            FieldContainerType* TheType;
            TheType = FieldContainerFactory::the()->findType(i);
            if(TheType != NULL)
            {
                // Add all available Fonts to it
                _FieldContainerTypeModel->pushBack(boost::any(std::string(TheType->getCName())));
                ++NumTypesFound;
            }
        }

        // Create FieldContainerTypeList
        ListRefPtr FieldContainerTypeList = List::create();
        FieldContainerTypeList->setPreferredSize( Vec2f (200, 300) );
        FieldContainerTypeList->setOrientation(List::VERTICAL_ORIENTATION);
        FieldContainerTypeList->setModel(_FieldContainerTypeModel);

        // Assign the Model, and SelectionModel
        // to the List
        // Creates and assigns a SelectionMode
        ListSelectionModelPtr  FieldSelectionModel(new DefaultListSelectionModel);
        FieldSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
        FieldContainerTypeList->setSelectionModel(FieldSelectionModel);
        TheFCListListener.setList(FieldContainerTypeList);
        FieldContainerTypeList->getSelectionModel()->addListSelectionListener(&TheFCListListener);

        GridBagLayoutConstraintsRefPtr FieldContainerTypeListScrollPanelConstraints = OSG::GridBagLayoutConstraints::create();
        FieldContainerTypeListScrollPanelConstraints->setGridX(0);
        FieldContainerTypeListScrollPanelConstraints->setGridY(0);
        FieldContainerTypeListScrollPanelConstraints->setGridHeight(1);
        FieldContainerTypeListScrollPanelConstraints->setGridWidth(2);
        FieldContainerTypeListScrollPanelConstraints->setFill(GridBagLayoutConstraints::FILL_NONE);
        FieldContainerTypeListScrollPanelConstraints->setVerticalAlignment(1.0);

        //FieldContainerTypeListScrollPanel
        ScrollPanelRefPtr FieldContainerTypeListScrollPanel = ScrollPanel::create();
        FieldContainerTypeListScrollPanel->setPreferredSize(Vec2f(200,300));
        FieldContainerTypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        FieldContainerTypeListScrollPanel->setConstraints(FieldContainerTypeListScrollPanelConstraints);
        FieldContainerTypeListScrollPanel->setViewComponent(FieldContainerTypeList);

        //Number of FieldContainerTypes Label
        GridBagLayoutConstraintsRefPtr NumFCTypesLabelConstraints = OSG::GridBagLayoutConstraints::create();
        NumFCTypesLabelConstraints->setGridX(0);
        NumFCTypesLabelConstraints->setGridY(1);
        NumFCTypesLabelConstraints->setGridHeight(1);
        NumFCTypesLabelConstraints->setGridWidth(1);
        NumFCTypesLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumFCTypesLabelConstraints->setWeightX(1.0);
        NumFCTypesLabelConstraints->setVerticalAlignment(0.0);

        LabelRefPtr NumFCTypesLabel = Label::create();
        NumFCTypesLabel->setText("Number Field ComponentContainer Types: ");
        NumFCTypesLabel->setConstraints(NumFCTypesLabelConstraints);

        //Number of FieldContainerTypes Value Label
        GridBagLayoutConstraintsRefPtr NumFCTypesValueLabelConstraints = OSG::GridBagLayoutConstraints::create();
        NumFCTypesValueLabelConstraints->setGridX(1);
        NumFCTypesValueLabelConstraints->setGridY(1);
        NumFCTypesValueLabelConstraints->setGridHeight(1);
        NumFCTypesValueLabelConstraints->setGridWidth(1);
        NumFCTypesValueLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumFCTypesValueLabelConstraints->setWeightX(1.0);
        NumFCTypesValueLabelConstraints->setVerticalAlignment(0.0);

        LabelRefPtr NumFCTypesValueLabel = Label::create();
        std::stringstream TempSStream;
        TempSStream << FieldContainerFactory::the()->getNumTypes();
        NumFCTypesValueLabel->setText(TempSStream.str());
        NumFCTypesValueLabel->setConstraints(NumFCTypesValueLabelConstraints);

        //Create Main Panel Layout
        GridBagLayoutRefPtr FieldContainerTypePanelLayout = OSG::GridBagLayout::create();
        FieldContainerTypePanelLayout->setColumns(2);
        FieldContainerTypePanelLayout->setRows(2);

        //Create Main Panel
        PanelRefPtr FieldContainerTypePanel = Panel::create();

        FieldContainerTypePanel->pushToChildren(FieldContainerTypeListScrollPanel);
        FieldContainerTypePanel->pushToChildren(NumFCTypesLabel);
        FieldContainerTypePanel->pushToChildren(NumFCTypesValueLabel);
        FieldContainerTypePanel->setLayout(FieldContainerTypePanelLayout);


        return FieldContainerTypePanel;
    }
  public:
    PanelRefPtr getPanel(void) const
    {
        return _MainPanel;
    }

    OpenSGTypePanel()
    {
        //Create the Type Panels
        GridBagLayoutConstraintsRefPtr TypePanelConstraints = OSG::GridBagLayoutConstraints::create();
        TypePanelConstraints->setGridX(0);
        TypePanelConstraints->setGridY(0);
        TypePanelConstraints->setGridHeight(1);
        TypePanelConstraints->setGridWidth(1);
        TypePanelConstraints->setFill(GridBagLayoutConstraints::FILL_BOTH);
        TypePanelConstraints->setWeightX(1.0);
        TypePanelConstraints->setWeightY(1.0);
        TypePanelConstraints->setPadBottom(2);
        TypePanelConstraints->setPadLeft(2);
        TypePanelConstraints->setPadRight(2);
        TypePanelConstraints->setPadTop(2);

        PanelRefPtr TypePanel = createTypePanel();
        TypePanel->setConstraints(TypePanelConstraints);


        GridBagLayoutConstraintsRefPtr FieldTypePanelConstraints = OSG::GridBagLayoutConstraints::create();
        FieldTypePanelConstraints->setGridX(1);
        FieldTypePanelConstraints->setGridY(0);
        FieldTypePanelConstraints->setGridHeight(1);
        FieldTypePanelConstraints->setGridWidth(1);
        FieldTypePanelConstraints->setFill(GridBagLayoutConstraints::FILL_BOTH);
        FieldTypePanelConstraints->setWeightX(1.0);
        FieldTypePanelConstraints->setWeightY(1.0);
        FieldTypePanelConstraints->setPadBottom(2);
        FieldTypePanelConstraints->setPadLeft(2);
        FieldTypePanelConstraints->setPadRight(2);
        FieldTypePanelConstraints->setPadTop(2);

        PanelRefPtr FieldTypePanel = createFieldTypePanel();
        FieldTypePanel->setConstraints(FieldTypePanelConstraints);

        GridBagLayoutConstraintsRefPtr FieldContainerTypePanelConstraints = OSG::GridBagLayoutConstraints::create();
        FieldContainerTypePanelConstraints->setGridX(2);
        FieldContainerTypePanelConstraints->setGridY(0);
        FieldContainerTypePanelConstraints->setGridHeight(1);
        FieldContainerTypePanelConstraints->setGridWidth(1);
        FieldContainerTypePanelConstraints->setFill(GridBagLayoutConstraints::FILL_BOTH);
        FieldContainerTypePanelConstraints->setWeightX(1.0);
        FieldContainerTypePanelConstraints->setWeightY(1.0);
        FieldContainerTypePanelConstraints->setPadBottom(2);
        FieldContainerTypePanelConstraints->setPadLeft(2);
        FieldContainerTypePanelConstraints->setPadRight(2);
        FieldContainerTypePanelConstraints->setPadTop(2);

        PanelRefPtr FieldContainerTypePanel = createFieldContainerTypePanel();
        FieldContainerTypePanel->setConstraints(FieldContainerTypePanelConstraints);

        //Create Main Panel Layout
        GridBagLayoutRefPtr MainPanelLayout = OSG::GridBagLayout::create();


        MainPanelLayout->setColumns(3);
        MainPanelLayout->setRows(1);

        //Create Main Panel
        _MainPanel = Panel::createEmpty();

        _MainPanel->pushToChildren(TypePanel);
        _MainPanel->pushToChildren(FieldTypePanel);
        _MainPanel->pushToChildren(FieldContainerTypePanel);
        _MainPanel->setLayout(MainPanelLayout);
    }
};

// Initialize GLUT & OpenSG and set up the scene
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


    // Make Torus Node
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodeRefPtr scene = OSG::Node::create();
    {
        scene->setCore(OSG::Group::create());

        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }

    // Create the Graphics
    GraphicsRefPtr graphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


    // Create ListModel Component
    /*AbstractListModel TypeModel;

    // Display all Types available
    for (UInt32 i(1); i < TypeFactory::the()->getNumTypes()+1 ; ++i)
    {
    TypeBase* TheType;
    TheType = TypeFactory::the()->findType(i);
    if(TheType != NULL)
    {
    // Add all available Fonts to it
    TypeModel.pushBack(boost::any(std::string(TheType->getCName())));
    }
    }*/



    BorderLayoutConstraintsRefPtr OpenSGTypePanelConstraints = OSG::BorderLayoutConstraints::create();
    OpenSGTypePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    OpenSGTypePanel TheOpenSGTypePanel;
    TheOpenSGTypePanel.getPanel()->setConstraints(OpenSGTypePanelConstraints);


    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    BorderLayoutRefPtr MainInternalWindowLayout = OSG::BorderLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(TheOpenSGTypePanel.getPanel());
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    //Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
    TutorialDrawingSurface->setGraphics(graphics);
    TutorialDrawingSurface->setEventProducer(TutorialWindow);

    TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr foreground = OSG::UIForeground::create();

    foreground->setDrawingSurface(TutorialDrawingSurface);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot  (scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr viewport = mgr->getWindow()->getPort(0);
    viewport->addForeground(foreground);

    // show the whole scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "50OpenSGTypes");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}
