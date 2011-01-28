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
#include "OSGDefaultListSelectionModel.h"
#include "OSGListModel.h"

#include "OSGScrollPanel.h"
#include "OSGPanel.h"
#include "OSGLabel.h"
#include "OSGUIFont.h"
#include "OSGTextArea.h"
#include "OSGCellEditor.h"
#include "OSGComponentGenerator.h"

#include "OSGLayoutSpring.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"

#include "OSGFCFileHandler.h"
#include "OSGUIDrawObject.h"
#include "OSGComboBox.h"
#include "OSGFieldContainerComboBoxModel.h"
#include "OSGDerivedFieldContainerComboBoxModel.h"

#include <sstream>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with , but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// Declare upfront so they can be referenced

// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// Create a class to allow for the use of the Ctrl+q
void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

class OpenSGTypePanel
{
  protected:
    PanelRecPtr _MainPanel;
    ListModelRecPtr _FieldContainerTypeModel;
    TextAreaRecPtr _FCDescriptionArea;
    TextAreaRecPtr _XMLArea;
    FieldContainerComboBoxModelRecPtr _DerivedComboBoxModel;
    ListRecPtr _FieldContainerTypeList;

    void handleFCComboBoxSelectionChanged(ComboBoxSelectionEventDetails* const details)
    {
        FieldContainerType* FoundType(NULL);
        try
        {
            FoundType = boost::any_cast<FieldContainerType*>(_DerivedComboBoxModel->getSelectedItem());
        }
        catch(boost::bad_any_cast &)
        {
        }
        if(FoundType != NULL)
        {
            dynamic_pointer_cast<DerivedFieldContainerComboBoxModel>(_FieldContainerTypeModel)->editMFDerivedFieldContainerTypes()->clear();
            dynamic_pointer_cast<DerivedFieldContainerComboBoxModel>(_FieldContainerTypeModel)->editMFDerivedFieldContainerTypes()->push_back(std::string(FoundType->getCName()));
        }

    }

    void handleFCListSelectionChanged(ListSelectionEventDetails* const details)
    {
        if(!_FieldContainerTypeList->getSelectionModel()->isSelectionEmpty())
        {
            FieldContainerType* TheFCType(NULL);
            try
            {
                TheFCType = boost::any_cast<FieldContainerType*>(_FieldContainerTypeList->getValueAtIndex(_FieldContainerTypeList->getSelectionModel()->getAnchorSelectionIndex()));
            }
            catch(boost::bad_any_cast &)
            {
            }

            if(TheFCType != NULL)
            {
                //XML Text
                std::ostringstream TheStream;
                FCFileType::FCPtrStore NewContainers;
                FCFileType::FCTypeVector IgnoreContainers;
                FieldContainerRecPtr Prototype(TheFCType->getPrototype());
                if(Prototype != NULL)
                {
                    IgnoreContainers.push_back(UIFont::getClassType().getId());
                    NewContainers.insert(Prototype);
                    FCFileHandler::the()->write(NewContainers, TheStream,"xml",IgnoreContainers);
                }
                _XMLArea->setText(TheStream.str());


                //Fields Text
                std::stringstream OutputStream;

                OutputStream << "Field ComponentContainer Type: " << TheFCType->getCName() << std::endl;
                OutputStream << std::setw(25) << "Field Name" << " | " << std::setw(22) << "Type" << " | " << std::setw(11) << "Cardinality"  << " | " << std::setw(25) << "Default Value" << std::endl;
                for(UInt32 i(1) ; i<TheFCType->getNumFieldDescs()+1 ; ++i)
                {
                    FieldDescriptionBase* Desc = TheFCType->getFieldDesc(i);
                    if(!Desc->isInternal())
                    {
                        const FieldType& TheField(Desc->getFieldType());
                        OutputStream << std::setw(25) << Desc->getCName() << " | " ;
                        OutputStream << std::setw(22) << TheField.getContentType().getCName() << " | " ;
                        if(TheField.getCardinality() == FieldType::SingleField)
                        {
                            OutputStream << std::setw(11) << "Single"  << " | " ;
                        }
                        else
                        {
                            OutputStream << std::setw(11) << "Many"  << " | " ;
                        }

                        if(TheFCType->getPrototype() != NULL &&
                           TheFCType->getPrototype()->getField(Desc->getFieldId()) != NULL)
                        {
                            std::string Value;
                            //TheFCType->getPrototype()->getField(Desc->getFieldId())->getValueByStr(Value, 0);
                            OutputStream << std::setw(25) << Value;
                        }

                        OutputStream   << std::endl;
                    }
                }
                _FCDescriptionArea->setText(OutputStream.str());
            }
        }
    }

    PanelTransitPtr createFieldContainerTypePanel(void)
    {
        LabelRecPtr DerivedComboBoxLabel = Label::create();
        DerivedComboBoxLabel->setText("Type:");

        //Create a ComboBox to select the DerivedFieldContainerType
        _DerivedComboBoxModel = FieldContainerComboBoxModel::create();
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(Component::getClassType().getCName()));
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(ComponentContainer::getClassType().getCName()));
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(AbstractWindow::getClassType().getCName()));
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(Border::getClassType().getCName()));
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(Layer::getClassType().getCName()));
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(UIFont::getClassType().getCName()));
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(CellEditor::getClassType().getCName()));
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(ComponentGenerator::getClassType().getCName()));
        _DerivedComboBoxModel->editMFFieldContainerTypes()->push_back(std::string(UIDrawObject::getClassType().getCName()));

        // Create another ComboBox
        ComboBoxRecPtr DerivedComboBox = ComboBox::create();

        // Set it to be uneditable
        DerivedComboBox->setEditable(false);
        DerivedComboBox->setModel(_DerivedComboBoxModel);

        //Put all the FieldContainerTypes into the model
        _FieldContainerTypeModel = DerivedFieldContainerComboBoxModel::create();

        _DerivedComboBoxModel->connectSelectionChanged(boost::bind(&OpenSGTypePanel::handleFCComboBoxSelectionChanged,
                                                                  this,
                                                                  _1));
        _DerivedComboBoxModel->setSelectedItem(0);

        // Create FieldContainerTypeList
        _FieldContainerTypeList = List::create();
        _FieldContainerTypeList->setPreferredSize( Vec2f (300, 300) );
        _FieldContainerTypeList->setOrientation(List::VERTICAL_ORIENTATION);
        _FieldContainerTypeList->setModel(_FieldContainerTypeModel);

        // Assign the Model, and SelectionModel
        // to the List
        // Creates and assigns a SelectionMode
        _FieldContainerTypeList->getSelectionModel()->connectSelectionChanged(boost::bind(&OpenSGTypePanel::handleFCListSelectionChanged,
                                                                                         this,
                                                                                         _1));

        //FieldContainerTypeListScrollPanel
        ScrollPanelRecPtr FieldContainerTypeListScrollPanel = ScrollPanel::create();
        FieldContainerTypeListScrollPanel->setPreferredSize(Vec2f(400,400));
        FieldContainerTypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        FieldContainerTypeListScrollPanel->setViewComponent(_FieldContainerTypeList);

        //Number of FieldContainerTypes Label

        LabelRecPtr NumFCTypesLabel = Label::create();
        NumFCTypesLabel->setText("Number Field ComponentContainer Types: ");



        //Number of FieldContainerTypes Value Label
        LabelRecPtr NumFCTypesValueLabel = Label::create();
        std::stringstream TempSStream;
        TempSStream << _FieldContainerTypeModel->getSize();
        NumFCTypesValueLabel->setText(TempSStream.str());

        //Field ComponentContainer Description TextArea
        //Windows Font
        UIFontRecPtr TextAreaFont = UIFont::create();
        TextAreaFont->setFamily("Courier New");
        TextAreaFont->setGap(3);
        TextAreaFont->setGlyphPixelSize(46);
        TextAreaFont->setSize(12);
        TextAreaFont->setTextureWidth(0);
        TextAreaFont->setStyle(TextFace::STYLE_PLAIN);

        _FCDescriptionArea = TextArea::create();

        _FCDescriptionArea->setFont(TextAreaFont);

        ScrollPanelRecPtr FCDescriptionAreaScrollPanel = ScrollPanel::create();
        //FCDescriptionAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //FCDescriptionAreaScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        FCDescriptionAreaScrollPanel->setViewComponent(_FCDescriptionArea);


        _XMLArea = TextArea::create();

        _XMLArea->setFont(TextAreaFont);

        ScrollPanelRecPtr XMLAreaScrollPanel = ScrollPanel::create();
        //XMLAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //XMLAreaScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ScrollPanelRecPtr TextAreaScrollPanel = ScrollPanel::create();
        XMLAreaScrollPanel->setViewComponent(_XMLArea);

        //Create Main Panel Layout
        SpringLayoutRecPtr FieldContainerTypePanelLayout = SpringLayout::create();

        //Create Main Panel
        PanelRecPtr FieldContainerTypePanel = Panel::create();

        FieldContainerTypePanel->pushToChildren(DerivedComboBoxLabel);
        FieldContainerTypePanel->pushToChildren(DerivedComboBox);
        FieldContainerTypePanel->pushToChildren(FieldContainerTypeListScrollPanel);
        FieldContainerTypePanel->pushToChildren(NumFCTypesLabel);
        FieldContainerTypePanel->pushToChildren(NumFCTypesValueLabel);
        FieldContainerTypePanel->pushToChildren(FCDescriptionAreaScrollPanel);
        FieldContainerTypePanel->pushToChildren(XMLAreaScrollPanel);
        FieldContainerTypePanel->setLayout(FieldContainerTypePanelLayout);

        //ComboBox Layout constraints
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DerivedComboBoxLabel, 0, SpringLayoutConstraints::NORTH_EDGE, FieldContainerTypePanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DerivedComboBoxLabel, 0, SpringLayoutConstraints::WEST_EDGE, FieldContainerTypePanel);

        //ComboBox Layout constraints
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DerivedComboBox, 0, SpringLayoutConstraints::NORTH_EDGE, FieldContainerTypePanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DerivedComboBox, 1, SpringLayoutConstraints::EAST_EDGE, DerivedComboBoxLabel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DerivedComboBox, 1, SpringLayoutConstraints::EAST_EDGE, FieldContainerTypeListScrollPanel);

        //Scrollbar Layout constraints
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, FieldContainerTypeListScrollPanel, 1, SpringLayoutConstraints::SOUTH_EDGE, DerivedComboBox);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, FieldContainerTypeListScrollPanel, 0, SpringLayoutConstraints::WEST_EDGE, FieldContainerTypePanel);

        //FieldContainerTypes Label Layout constraints
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, NumFCTypesLabel, 1, SpringLayoutConstraints::SOUTH_EDGE, FieldContainerTypeListScrollPanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, NumFCTypesLabel, 0, SpringLayoutConstraints::WEST_EDGE, FieldContainerTypeListScrollPanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, NumFCTypesLabel, -1, SpringLayoutConstraints::WEST_EDGE, NumFCTypesValueLabel);

        //FieldContainerTypes Label Layout constraints
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, NumFCTypesValueLabel, 1, SpringLayoutConstraints::SOUTH_EDGE, FieldContainerTypeListScrollPanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, NumFCTypesValueLabel, 0, SpringLayoutConstraints::EAST_EDGE, FieldContainerTypeListScrollPanel);

        //FieldContainer Description TextArea Layout constraints
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, FCDescriptionAreaScrollPanel, 1, SpringLayoutConstraints::SOUTH_EDGE, NumFCTypesLabel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, FCDescriptionAreaScrollPanel, 0, SpringLayoutConstraints::EAST_EDGE, FieldContainerTypePanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, FCDescriptionAreaScrollPanel, 0, SpringLayoutConstraints::WEST_EDGE, FieldContainerTypePanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, FCDescriptionAreaScrollPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, FieldContainerTypePanel);

        //XML TextArea Layout constraints
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, XMLAreaScrollPanel, 0, SpringLayoutConstraints::NORTH_EDGE, FieldContainerTypePanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, XMLAreaScrollPanel, 0, SpringLayoutConstraints::EAST_EDGE, FieldContainerTypePanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, XMLAreaScrollPanel, 1, SpringLayoutConstraints::EAST_EDGE, FieldContainerTypeListScrollPanel);
        FieldContainerTypePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, XMLAreaScrollPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, FieldContainerTypeListScrollPanel);


        return PanelTransitPtr(FieldContainerTypePanel);
    }
  public:
    PanelRecPtr getPanel(void) const
    {
        return _MainPanel;
    }

    OpenSGTypePanel(void)
    {

        _MainPanel = createFieldContainerTypePanel();
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

        // Make Main Scene Node
        NodeRecPtr scene = Node::create();
        {
            scene->setCore(Group::create());
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
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
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
                                   "51OpenSGFieldContainers");

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

