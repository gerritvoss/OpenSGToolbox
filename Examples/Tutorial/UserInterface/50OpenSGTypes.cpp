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
#include "OSGListModel.h"

#include "OSGScrollPanel.h"
#include "OSGPanel.h"
#include "OSGLabel.h"

#include <sstream>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with , but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// Declare upfront so they can be referenced

// forward declaration so we can have the interesting stuff upfront
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

class OpenSGTypePanel
{
  protected:

    PanelRecPtr _MainPanel;
    DefaultListModelRecPtr _TypeModel;
    DefaultListModelRecPtr _FieldTypeModel;
    DefaultListModelRecPtr _FieldContainerTypeModel;
    ListRecPtr _FieldContainerTypeList;
    void handleFCListSelectionChanged(ListSelectionEventDetails* const details)
    {
        if(!_FieldContainerTypeList->getSelectionModel()->isSelectionEmpty())
        {
            std::string ValueStr("");
            try
            {
                ValueStr = boost::any_cast<std::string>(_FieldContainerTypeList->getValueAtIndex(_FieldContainerTypeList->getSelectionModel()->getAnchorSelectionIndex()));
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

    PanelTransitPtr createTypePanel(void)
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
        ListRecPtr TypeList = List::create();
        TypeList->setPreferredSize( Vec2f (200, 300) );
        TypeList->setOrientation(List::VERTICAL_ORIENTATION);
        TypeList->setModel(_TypeModel);

        GridBagLayoutConstraintsRecPtr TypeListScrollPanelConstraints = GridBagLayoutConstraints::create();
        TypeListScrollPanelConstraints->setGridX(0);
        TypeListScrollPanelConstraints->setGridY(0);
        TypeListScrollPanelConstraints->setGridHeight(1);
        TypeListScrollPanelConstraints->setGridWidth(2);
        TypeListScrollPanelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        TypeListScrollPanelConstraints->setVerticalAlignment(1.0);

        //TypeListScrollPanel
        ScrollPanelRecPtr TypeListScrollPanel = ScrollPanel::create();
        TypeListScrollPanel->setPreferredSize(Vec2f(200,300));
        TypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        TypeListScrollPanel->setConstraints(TypeListScrollPanelConstraints);
        TypeListScrollPanel->setViewComponent(TypeList);

        //Number of FieldContainerTypes Label
        GridBagLayoutConstraintsRecPtr NumTypesLabelConstraints = GridBagLayoutConstraints::create();
        NumTypesLabelConstraints->setGridX(0);
        NumTypesLabelConstraints->setGridY(1);
        NumTypesLabelConstraints->setGridHeight(1);
        NumTypesLabelConstraints->setGridWidth(1);
        NumTypesLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumTypesLabelConstraints->setWeightX(1.0);
        NumTypesLabelConstraints->setVerticalAlignment(0.0);

        LabelRecPtr NumTypesLabel = Label::create();
        NumTypesLabel->setText("Number Field Types: ");
        NumTypesLabel->setConstraints(NumTypesLabelConstraints);

        //Number of FieldContainerTypes Value Label
        GridBagLayoutConstraintsRecPtr NumTypesValueLabelConstraints = GridBagLayoutConstraints::create();
        NumTypesValueLabelConstraints->setGridX(1);
        NumTypesValueLabelConstraints->setGridY(1);
        NumTypesValueLabelConstraints->setGridHeight(1);
        NumTypesValueLabelConstraints->setGridWidth(1);
        NumTypesValueLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumTypesValueLabelConstraints->setWeightX(1.0);
        NumTypesValueLabelConstraints->setVerticalAlignment(0.0);

        LabelRecPtr NumTypesValueLabel = Label::create();
        std::stringstream TempSStream;
        TempSStream << TypeFactory::the()->getNumTypes();
        NumTypesValueLabel->setText(TempSStream.str());
        NumTypesValueLabel->setConstraints(NumTypesValueLabelConstraints);

        //Create Main Panel Layout
        GridBagLayoutRecPtr TypePanelLayout = GridBagLayout::create();
        TypePanelLayout->setColumns(2);
        TypePanelLayout->setRows(2);

        //Create Main Panel
        PanelRecPtr TypePanel = Panel::create();

        TypePanel->pushToChildren(TypeListScrollPanel);
        TypePanel->pushToChildren(NumTypesLabel);
        TypePanel->pushToChildren(NumTypesValueLabel);
        TypePanel->setLayout(TypePanelLayout);
        return PanelTransitPtr(TypePanel);
    }

    PanelTransitPtr createFieldTypePanel(void)
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
        ListRecPtr FieldTypeList = List::create();
        FieldTypeList->setPreferredSize( Vec2f (200, 300) );
        FieldTypeList->setOrientation(List::VERTICAL_ORIENTATION);
        FieldTypeList->setModel(_FieldTypeModel);

        GridBagLayoutConstraintsRecPtr FieldTypeListScrollPanelConstraints = GridBagLayoutConstraints::create();
        FieldTypeListScrollPanelConstraints->setGridX(0);
        FieldTypeListScrollPanelConstraints->setGridY(0);
        FieldTypeListScrollPanelConstraints->setGridHeight(1);
        FieldTypeListScrollPanelConstraints->setGridWidth(2);
        FieldTypeListScrollPanelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        FieldTypeListScrollPanelConstraints->setVerticalAlignment(1.0);

        //FieldTypeListScrollPanel
        ScrollPanelRecPtr FieldTypeListScrollPanel = ScrollPanel::create();
        FieldTypeListScrollPanel->setPreferredSize(Vec2f(200,300));
        FieldTypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        FieldTypeListScrollPanel->setConstraints(FieldTypeListScrollPanelConstraints);
        FieldTypeListScrollPanel->setViewComponent(FieldTypeList);

        //Number of FieldContainerTypes Label
        GridBagLayoutConstraintsRecPtr NumFieldTypesLabelConstraints = GridBagLayoutConstraints::create();
        NumFieldTypesLabelConstraints->setGridX(0);
        NumFieldTypesLabelConstraints->setGridY(1);
        NumFieldTypesLabelConstraints->setGridHeight(1);
        NumFieldTypesLabelConstraints->setGridWidth(1);
        NumFieldTypesLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumFieldTypesLabelConstraints->setWeightX(1.0);
        NumFieldTypesLabelConstraints->setVerticalAlignment(0.0);

        LabelRecPtr NumFieldTypesLabel = Label::create();
        NumFieldTypesLabel->setText("Number Field Types: ");
        NumFieldTypesLabel->setConstraints(NumFieldTypesLabelConstraints);

        //Number of FieldContainerTypes Value Label
        GridBagLayoutConstraintsRecPtr NumFieldTypesValueLabelConstraints = GridBagLayoutConstraints::create();
        NumFieldTypesValueLabelConstraints->setGridX(1);
        NumFieldTypesValueLabelConstraints->setGridY(1);
        NumFieldTypesValueLabelConstraints->setGridHeight(1);
        NumFieldTypesValueLabelConstraints->setGridWidth(1);
        NumFieldTypesValueLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumFieldTypesValueLabelConstraints->setWeightX(1.0);
        NumFieldTypesValueLabelConstraints->setVerticalAlignment(0.0);

        LabelRecPtr NumFieldTypesValueLabel = Label::create();
        std::stringstream TempSStream;
        TempSStream << NumTypesFound;
        NumFieldTypesValueLabel->setText(TempSStream.str());
        NumFieldTypesValueLabel->setConstraints(NumFieldTypesValueLabelConstraints);

        //Create Main Panel Layout
        GridBagLayoutRecPtr FieldTypePanelLayout = GridBagLayout::create();
        FieldTypePanelLayout->setColumns(2);
        FieldTypePanelLayout->setRows(2);

        //Create Main Panel
        PanelRecPtr FieldTypePanel = Panel::create();

        FieldTypePanel->pushToChildren(FieldTypeListScrollPanel);
        FieldTypePanel->pushToChildren(NumFieldTypesLabel);
        FieldTypePanel->pushToChildren(NumFieldTypesValueLabel);
        FieldTypePanel->setLayout(FieldTypePanelLayout);
        return PanelTransitPtr(FieldTypePanel);
    }

    PanelTransitPtr createFieldContainerTypePanel(void)
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
        _FieldContainerTypeList = List::create();
        _FieldContainerTypeList->setPreferredSize( Vec2f (200, 300) );
        _FieldContainerTypeList->setOrientation(List::VERTICAL_ORIENTATION);
        _FieldContainerTypeList->setModel(_FieldContainerTypeModel);

        // Assign the Model, and SelectionModel
        // to the List
        // Creates and assigns a SelectionMode
        _FieldContainerTypeList->getSelectionModel()->connectSelectionChanged(boost::bind(&OpenSGTypePanel::handleFCListSelectionChanged,
                                                                                         this,
                                                                                         _1));

        GridBagLayoutConstraintsRecPtr FieldContainerTypeListScrollPanelConstraints = GridBagLayoutConstraints::create();
        FieldContainerTypeListScrollPanelConstraints->setGridX(0);
        FieldContainerTypeListScrollPanelConstraints->setGridY(0);
        FieldContainerTypeListScrollPanelConstraints->setGridHeight(1);
        FieldContainerTypeListScrollPanelConstraints->setGridWidth(2);
        FieldContainerTypeListScrollPanelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        FieldContainerTypeListScrollPanelConstraints->setVerticalAlignment(1.0);

        //FieldContainerTypeListScrollPanel
        ScrollPanelRecPtr FieldContainerTypeListScrollPanel = ScrollPanel::create();
        FieldContainerTypeListScrollPanel->setPreferredSize(Vec2f(200,300));
        FieldContainerTypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        FieldContainerTypeListScrollPanel->setConstraints(FieldContainerTypeListScrollPanelConstraints);
        FieldContainerTypeListScrollPanel->setViewComponent(_FieldContainerTypeList);

        //Number of FieldContainerTypes Label
        GridBagLayoutConstraintsRecPtr NumFCTypesLabelConstraints = GridBagLayoutConstraints::create();
        NumFCTypesLabelConstraints->setGridX(0);
        NumFCTypesLabelConstraints->setGridY(1);
        NumFCTypesLabelConstraints->setGridHeight(1);
        NumFCTypesLabelConstraints->setGridWidth(1);
        NumFCTypesLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumFCTypesLabelConstraints->setWeightX(1.0);
        NumFCTypesLabelConstraints->setVerticalAlignment(0.0);

        LabelRecPtr NumFCTypesLabel = Label::create();
        NumFCTypesLabel->setText("Number FieldContainer Types: ");
        NumFCTypesLabel->setConstraints(NumFCTypesLabelConstraints);

        //Number of FieldContainerTypes Value Label
        GridBagLayoutConstraintsRecPtr NumFCTypesValueLabelConstraints = GridBagLayoutConstraints::create();
        NumFCTypesValueLabelConstraints->setGridX(1);
        NumFCTypesValueLabelConstraints->setGridY(1);
        NumFCTypesValueLabelConstraints->setGridHeight(1);
        NumFCTypesValueLabelConstraints->setGridWidth(1);
        NumFCTypesValueLabelConstraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        NumFCTypesValueLabelConstraints->setWeightX(1.0);
        NumFCTypesValueLabelConstraints->setVerticalAlignment(0.0);

        LabelRecPtr NumFCTypesValueLabel = Label::create();
        std::stringstream TempSStream;
        TempSStream << FieldContainerFactory::the()->getNumTypes();
        NumFCTypesValueLabel->setText(TempSStream.str());
        NumFCTypesValueLabel->setConstraints(NumFCTypesValueLabelConstraints);

        //Create Main Panel Layout
        GridBagLayoutRecPtr FieldContainerTypePanelLayout = GridBagLayout::create();
        FieldContainerTypePanelLayout->setColumns(2);
        FieldContainerTypePanelLayout->setRows(2);

        //Create Main Panel
        PanelRecPtr FieldContainerTypePanel = Panel::create();

        FieldContainerTypePanel->pushToChildren(FieldContainerTypeListScrollPanel);
        FieldContainerTypePanel->pushToChildren(NumFCTypesLabel);
        FieldContainerTypePanel->pushToChildren(NumFCTypesValueLabel);
        FieldContainerTypePanel->setLayout(FieldContainerTypePanelLayout);

        return PanelTransitPtr(FieldContainerTypePanel);
    }

  public:
    Panel* getPanel(void) const
    {
        return _MainPanel;
    }

    OpenSGTypePanel(void)
    {
        //Create the Type Panels
        GridBagLayoutConstraintsRecPtr TypePanelConstraints = GridBagLayoutConstraints::create();
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

        PanelRecPtr TypePanel = createTypePanel();
        TypePanel->setConstraints(TypePanelConstraints);


        GridBagLayoutConstraintsRecPtr FieldTypePanelConstraints = GridBagLayoutConstraints::create();
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

        PanelRecPtr FieldTypePanel = createFieldTypePanel();
        FieldTypePanel->setConstraints(FieldTypePanelConstraints);

        GridBagLayoutConstraintsRecPtr FieldContainerTypePanelConstraints = GridBagLayoutConstraints::create();
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

        PanelRecPtr FieldContainerTypePanel = createFieldContainerTypePanel();
        FieldContainerTypePanel->setConstraints(FieldContainerTypePanelConstraints);

        //Create Main Panel Layout
        GridBagLayoutRecPtr MainPanelLayout = GridBagLayout::create();

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

        // Make Torus Node
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node
        NodeRecPtr scene = Node::create();
        {
            scene->setCore(Group::create());

            // add the torus as a child
            scene->addChild(TorusGeometryNode);
        }

        // Create the Graphics
        GraphicsRecPtr graphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        BorderLayoutConstraintsRecPtr OpenSGTypePanelConstraints = BorderLayoutConstraints::create();
        OpenSGTypePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

        OpenSGTypePanel TheOpenSGTypePanel;
        TheOpenSGTypePanel.getPanel()->setConstraints(OpenSGTypePanelConstraints);


        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        BorderLayoutRecPtr MainInternalWindowLayout = BorderLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(TheOpenSGTypePanel.getPanel());
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);

        //Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(graphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr foreground = UIForeground::create();

        foreground->setDrawingSurface(TutorialDrawingSurface);

        // create the SimpleSceneManager helper

        // tell the manager what to manage
        sceneManager.setRoot  (scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr viewport = sceneManager.getWindow()->getPort(0);
        viewport->addForeground(foreground);

        // show the whole scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "50OpenSGTypes");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}

// redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}
