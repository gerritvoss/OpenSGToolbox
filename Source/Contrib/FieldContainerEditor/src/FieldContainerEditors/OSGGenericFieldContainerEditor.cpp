/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGGenericFieldContainerEditor.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGFieldEditorFactory.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGPanel.h"
#include "OSGLabel.h"
#include "OSGTextArea.h"
#include "OSGSeparator.h"
#include "OSGFlowLayout.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGLookAndFeelManager.h"
#include "OSGColorLayer.h"
#include <boost/lexical_cast.hpp>
#include "OSGImage.h"

#include "OSGGridLayout.h"
#include "OSGGridBagLayout.h"
#include "OSGGridBagLayoutConstraints.h"

#include "OSGDocumentationUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGenericFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGGenericFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
std::vector<const FieldContainerType*> GenericFieldContainerEditor::_EditableTypes = std::vector<const FieldContainerType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GenericFieldContainerEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        //Fill in all of the editable types
        UInt32 NumTypes(FieldContainerFactory::the()->getNumTypes());
        UInt32 FoundTypes(0);
        FieldContainerType* type;
        for(UInt32 i(0) ; FoundTypes<NumTypes; ++i)
        {
            type = FieldContainerFactory::the()->findType(i);
            if(type != NULL)
            {
                ++FoundTypes;
                _EditableTypes.push_back(type);
                FieldContainerEditorFactory::the()->setEditorType(type, &getClassType(), "Generic");
            }
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f GenericFieldContainerEditor::getContentRequestedSize(void) const
{
    Real32 RequestedHeight(0.0f);

    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        RequestedHeight += getChildren(i)->getPreferredSize().y();
    }

    return Vec2f(1.0, RequestedHeight);
}

const std::vector<const FieldContainerType*>& GenericFieldContainerEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

bool GenericFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    dettachFieldContainer();

    //Update the Type and Id Labels
    _ContainerTypeLabel->setText(getEditingFC()->getType().getName());

    ComponentRecPtr TheToolTip = createFCToolTip(getEditingFC()->getType());
    _ContainerTypeLabel->setToolTip(TheToolTip);

    _ContainerIdLabel->setText(boost::lexical_cast<std::string>(getEditingFC()->getId()));

    //Create the Fields Panel
    updateFieldsPanel(fc);
    
    //Create the ProducedEvents Panel
    updateProducedEventsPanel(fc);


    //Tell my parent to update my size
    editSField(PreferredSizeFieldMask);

    return true;
}

Vec2f GenericFieldContainerEditor::getPreferredScrollableViewportSize(void)
{
    return getRequestedSize();
}

Int32 GenericFieldContainerEditor::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    return direction * (VisibleRectBottomRight[1] - VisibleRectTopLeft[1]);
}

bool GenericFieldContainerEditor::getScrollableTracksViewportHeight(void)
{
    return false;
}

bool GenericFieldContainerEditor::getScrollableTracksViewportWidth(void)
{
    return true;
}


bool GenericFieldContainerEditor::getScrollableHeightMinTracksViewport(void)
{
    return false;
}

bool GenericFieldContainerEditor::getScrollableWidthMinTracksViewport(void)
{
    return false;
}

Int32 GenericFieldContainerEditor::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    return 20;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void GenericFieldContainerEditor::updateFieldsPanel(FieldContainer* fc)
{
    _FieldsContainer->clearChildren();

    UInt32 NumFields(fc->getType().getNumFieldDescs());
    FieldDescriptionBase* Desc;
    FieldEditorComponentUnrecPtr TheEditor;
    LabelUnrecPtr TheLabel;
    ComponentRecPtr TheToolTip;
    GridBagLayoutConstraintsRefPtr LayoutConstraints;
    PanelRefPtr FieldPanel;
    UInt32 NumRows(0),NumRowsForField(1);

    BorderLayoutRefPtr TheBorderLayout = BorderLayout::create();
    BorderLayoutConstraintsRefPtr WestConstraint = BorderLayoutConstraints::create();
    WestConstraint->setRegion(BorderLayoutConstraints::BORDER_WEST);
    BorderLayoutConstraintsRefPtr CenterConstraint = BorderLayoutConstraints::create();
    CenterConstraint->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    //Backgrounds
    ColorLayerRefPtr HeaderBgLayer = ColorLayer::create();
    HeaderBgLayer->setColor(Color4f(0.7f,0.7f,0.7f,1.0f));

    ColorLayerRefPtr LightBgLayer = ColorLayer::create();
    LightBgLayer->setColor(Color4f(0.9f,0.9f,0.9f,1.0f));
    ColorLayerRefPtr DarkBgLayer = ColorLayer::create();
    DarkBgLayer->setColor(Color4f(0.8f,0.8f,0.8f,1.0f));

    LayoutConstraints = GridBagLayoutConstraints::create();
    LayoutConstraints->setGridX(0);
    LayoutConstraints->setGridY(NumRows);
    LayoutConstraints->setGridHeight(1);
    LayoutConstraints->setGridWidth(2);
    LayoutConstraints->setFill(GridBagLayoutConstraints::FILL_BOTH);

    LabelRecPtr FieldsLabel = Label::create();
    FieldsLabel->setAlignment(Vec2f(0.5f,0.5f));
    FieldsLabel->setText("Fields");
    FieldsLabel->setBackgrounds(HeaderBgLayer);
    FieldsLabel->setConstraints(LayoutConstraints);
    FieldsLabel->setFont(_BoldFont);

    _FieldsContainer->pushToChildren(FieldsLabel);
    ++NumRows;

    if(_GenericNameAttachmentEditor->isTypeEditable(fc->getType()))
    {
        //Create the Label
        TheLabel = Label::create();
        TheLabel->setText("Name");
        TheLabel->setBackgrounds(NULL);
        TheLabel->setConstraints(WestConstraint);
        TheLabel->setPreferredSize(Vec2f(160.0f,22.0f));

        //Attach the Generic Name Editor
        _GenericNameAttachmentEditor->setCommandManager(_CmdManager);
        _GenericNameAttachmentEditor->attachContainer(fc);
        _GenericNameAttachmentEditor->setConstraints(CenterConstraint);

        //Create the Panel
        LayoutConstraints = GridBagLayoutConstraints::create();
        LayoutConstraints->setGridX(0);
        LayoutConstraints->setGridY(NumRows);
        LayoutConstraints->setGridHeight(1);
        LayoutConstraints->setGridWidth(1);
        LayoutConstraints->setFill(GridBagLayoutConstraints::FILL_BOTH);

        FieldPanel = Panel::createEmpty();
        FieldPanel->setInset(Vec4f(1.0f,1.0f,1.0f,1.0f));
        FieldPanel->pushToChildren(TheLabel);
        FieldPanel->pushToChildren(_GenericNameAttachmentEditor);
        FieldPanel->setLayout(TheBorderLayout);
        FieldPanel->setConstraints(LayoutConstraints);
        FieldPanel->setBackgrounds(LightBgLayer);

        _FieldsContainer->pushToChildren(FieldPanel);
        ++NumRows;
    }

    UInt32 UsedFieldCount(0);
    for(UInt32 i(1) ; i<=NumFields ; ++i)
    {
        Desc = fc->getFieldDescription(i);
        if(Desc != NULL &&
           !Desc->isInternal() &&
           Desc->getFieldType().getClass() != FieldType::ParentPtrField &&
           //HACK: Stop the pixel field from being editable on Images
           !(fc->getType().isDerivedFrom(Image::getClassType()) &&
             Desc->getFieldId() == Image::PixelFieldId))
        {
            //Create the Editor
            TheEditor = FieldEditorFactory::the()->createDefaultEditor(fc, Desc->getFieldId(), _CmdManager);
            if(TheEditor != NULL)
            {
                NumRowsForField = TheEditor->getNumRequestedRows();
                pushToEditors(TheEditor);
                TheEditor->setConstraints(CenterConstraint);

                //Create the Label
                TheLabel = Label::create();
                TheLabel->setText(Desc->getCName());
                TheLabel->setBackgrounds(NULL);
                TheLabel->setConstraints(WestConstraint);
                TheLabel->setPreferredSize(Vec2f(160.0f,22.0f));
                TheToolTip = createFieldToolTip(Desc);
                TheLabel->setToolTip(TheToolTip);

                //Create the Panel
                LayoutConstraints = GridBagLayoutConstraints::create();
                LayoutConstraints->setGridX(0);
                LayoutConstraints->setGridY(NumRows);
                LayoutConstraints->setGridHeight(NumRowsForField);
                LayoutConstraints->setGridWidth(1);
                LayoutConstraints->setFill(GridBagLayoutConstraints::FILL_BOTH);


                FieldPanel = Panel::createEmpty();
                FieldPanel->setInset(Vec4f(1.0f,1.0f,1.0f,1.0f));
                FieldPanel->pushToChildren(TheLabel);
                FieldPanel->pushToChildren(TheEditor);
                FieldPanel->setLayout(TheBorderLayout);
                FieldPanel->setConstraints(LayoutConstraints);
                if((UsedFieldCount%2) == 0)
                {
                    FieldPanel->setBackgrounds(DarkBgLayer);
                }
                else
                {
                    FieldPanel->setBackgrounds(LightBgLayer);
                }

                _FieldsContainer->pushToChildren(FieldPanel);
                NumRows += NumRowsForField;
                TheEditor->setPreferredSize(Vec2f(50.0f,22.0f * NumRowsForField));
                ++UsedFieldCount;
            }
        }
    }

    //Set the number of rows for the grid layout
    dynamic_cast<GridBagLayout*>(_FieldsContainer->getLayout())->setRows(NumRows);
    _FieldsContainer->setPreferredSize(Vec2f(400.0f, NumRows*24.0f));
}

void GenericFieldContainerEditor::updateProducedEventsPanel(FieldContainer* fc)
{
    _ProducedEventsContainer->clearChildren();

    UInt32 NumEvents(fc->getNumEvents());
    const EventDescription * Desc;
    LabelUnrecPtr TheLabel;
    ComponentRecPtr TheToolTip;
    GridBagLayoutConstraintsRefPtr LayoutConstraints;
    UInt32 NumRows(0);

    if(NumEvents != 0)
    {
        BorderLayoutRefPtr TheBorderLayout = BorderLayout::create();
        BorderLayoutConstraintsRefPtr WestConstraint = BorderLayoutConstraints::create();
        WestConstraint->setRegion(BorderLayoutConstraints::BORDER_WEST);
        BorderLayoutConstraintsRefPtr CenterConstraint = BorderLayoutConstraints::create();
        CenterConstraint->setRegion(BorderLayoutConstraints::BORDER_CENTER);

        //Backgrounds
        ColorLayerRefPtr HeaderBgLayer = ColorLayer::create();
        HeaderBgLayer->setColor(Color4f(0.7f,0.7f,0.7f,1.0f));

        ColorLayerRefPtr LightBgLayer = ColorLayer::create();
        LightBgLayer->setColor(Color4f(0.9f,0.9f,0.9f,1.0f));
        ColorLayerRefPtr DarkBgLayer = ColorLayer::create();
        DarkBgLayer->setColor(Color4f(0.8f,0.8f,0.8f,1.0f));

        LabelRecPtr EventsLabel = Label::create();
        EventsLabel->setAlignment(Vec2f(0.5f,0.5f));
        EventsLabel->setText("Events");
        EventsLabel->setBackgrounds(HeaderBgLayer);
        EventsLabel->setFont(_BoldFont);

        _ProducedEventsContainer->pushToChildren(EventsLabel);
        ++NumRows;

        for(UInt32 i(1) ; i<=NumEvents ; ++i)
        {
            Desc = fc->getProducerType().getEventDescription(i);
            if(Desc != NULL)
            {
                //Create the Label
                TheLabel = Label::create();
                TheLabel->setText(Desc->getCName());
                TheToolTip = createEventToolTip(Desc);
                TheLabel->setToolTip(TheToolTip);
                if((i%2) == 0)
                {
                    TheLabel->setBackgrounds(DarkBgLayer);
                }
                else
                {
                    TheLabel->setBackgrounds(LightBgLayer);
                }

                _ProducedEventsContainer->pushToChildren(TheLabel);
                ++NumRows;
            }
        }
    }

    //Set the number of rows for the grid layout
    dynamic_cast<GridLayout*>(_ProducedEventsContainer->getLayout())->setRows(NumRows);
    _ProducedEventsContainer->setPreferredSize(Vec2f(400.0f,
                                                     NumRows*24.0f
                                                     + _ProducedEventsContainer->getTopInset()));
}

ComponentTransitPtr GenericFieldContainerEditor::createFieldToolTip(const FieldDescriptionBase *FieldDesc)
{
    std::string FieldDoc(doxygenToPlainFormatting(FieldDesc->getDocumentation()));

    //FieldName
    LabelRecPtr FieldLabel = Label::create();
    FieldLabel->setText(FieldDesc->getName());
    FieldLabel->setAlignment(Vec2f(0.0f,0.5f));
    FieldLabel->setBackgrounds(NULL);

    //CardinalityName
    LabelRecPtr CardinalityLabel = Label::create();
    std::string CardString;
    if(FieldDesc->getFieldType().getCardinality() == FieldType::SingleField)
    {
        CardString = "Single";
    }
    else
    {
        CardString = "Multi";
    }
    CardinalityLabel->setText(CardString);
    CardinalityLabel->setAlignment(Vec2f(0.5f,0.5f));
    CardinalityLabel->setBackgrounds(NULL);

    //TypeName
    LabelRecPtr TypeLabel = Label::create();
    TypeLabel->setText(FieldDesc->getFieldType().getContentType().getName());
    TypeLabel->setAlignment(Vec2f(1.0f,0.5f));
    TypeLabel->setBackgrounds(NULL);

    //Separator
    SeparatorRecPtr MainSeparator = Separator::create();
    MainSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    MainSeparator->setSeparatorSize(1.0f);
    MainSeparator->setPreferredSize(Vec2f(1.0f,5.0f));
    MainSeparator->setBackgrounds(NULL);

    //Set the layout constraints
    BorderLayoutConstraintsRecPtr CenterConstraints = BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    //Description Panel
    LabelRecPtr DescriptionLabel = Label::create();
    DescriptionLabel->setText("Description:");
    DescriptionLabel->setBackgrounds(NULL);

    TextAreaRecPtr DescriptionTextArea = TextArea::create();
    DescriptionTextArea->setText(FieldDoc);
    DescriptionTextArea->setEditable(false);
    DescriptionTextArea->setBorders(NULL);
    DescriptionTextArea->setBackgrounds(NULL);
    DescriptionTextArea->setConstraints(CenterConstraints);

    //Description Panel
    PanelRecPtr DescriptionPanel = Panel::create();
    BorderLayoutRecPtr DescriptionPanelLayout = BorderLayout::create();
    DescriptionPanel->setAllInsets(5.0f);
    DescriptionPanel->setLayout(DescriptionPanelLayout);
    DescriptionPanel->pushToChildren(DescriptionTextArea);
    DescriptionPanel->setBackgrounds(NULL);


    //ToolTip Layout
    PanelRecPtr ToolTipPanel = Panel::createEmpty();

    SpringLayoutRecPtr MainLayout = SpringLayout::create();

    //FieldLabel    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, FieldLabel, 5,
                              SpringLayoutConstraints::NORTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, FieldLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, FieldLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //CardinalityLabel    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CardinalityLabel, 5,
                              SpringLayoutConstraints::NORTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, CardinalityLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, CardinalityLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //TypeLabel    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TypeLabel, 5,
                              SpringLayoutConstraints::NORTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TypeLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TypeLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //MainSeparator    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MainSeparator, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, TypeLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MainSeparator, -15,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MainSeparator, 15,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //DescriptionTextArea
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DescriptionLabel, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, MainSeparator);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DescriptionLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DescriptionLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //DescriptionTextArea
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DescriptionPanel, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, DescriptionLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, DescriptionPanel, -5,
                              SpringLayoutConstraints::SOUTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DescriptionPanel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DescriptionPanel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //ToolTip Panel

    Component* DefaultToolTip(LookAndFeelManager::the()->getLookAndFeel()->getDefaultToolTip());
    ToolTipPanel->setBorders(DefaultToolTip->getBorder());
    ToolTipPanel->setBackgrounds(DefaultToolTip->getBackground());
    ToolTipPanel->setForegrounds(DefaultToolTip->getForeground());
    //ToolTipPanel->setPreferredSize(ToolTipTextArea->getRequestedSize() +
                                   //(2.0f * Insets));
    ToolTipPanel->setPreferredSize(Vec2f(300.0f,300.0f));
    ToolTipPanel->setLayout(MainLayout);
    ToolTipPanel->pushToChildren(FieldLabel);
    ToolTipPanel->pushToChildren(CardinalityLabel);
    ToolTipPanel->pushToChildren(TypeLabel);
    ToolTipPanel->pushToChildren(MainSeparator);
    ToolTipPanel->pushToChildren(DescriptionLabel);
    ToolTipPanel->pushToChildren(DescriptionPanel);

    Real32 Height(100.0f + DescriptionTextArea->getLineHeight()
                  * (DescriptionTextArea->getText().size()/40));
    ToolTipPanel->setPreferredSize(Vec2f(300.0f,Height));


    return ComponentTransitPtr(ToolTipPanel);
}

ComponentTransitPtr GenericFieldContainerEditor::createEventToolTip(const EventDescription *EventDesc)
{
    std::string FieldDoc(doxygenToPlainFormatting(EventDesc->getDescription()));

    //TypeName
    LabelRecPtr TypeLabel = Label::create();
    TypeLabel->setText(EventDesc->getName());
    TypeLabel->setAlignment(Vec2f(0.5f,0.5f));
    TypeLabel->setBackgrounds(NULL);

    //Separator
    SeparatorRecPtr MainSeparator = Separator::create();
    MainSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    MainSeparator->setSeparatorSize(1.0f);
    MainSeparator->setPreferredSize(Vec2f(1.0f,5.0f));
    MainSeparator->setBackgrounds(NULL);

    //Consumable Label
    LabelRecPtr ConsumableLabel = Label::create();
    ConsumableLabel->setText(EventDesc->getConsumable() ? "Consumable" : "Not Consumable");
    ConsumableLabel->setAlignment(Vec2f(0.0f,0.5f));
    ConsumableLabel->setBackgrounds(NULL);

    //Set the layout constraints
    BorderLayoutConstraintsRecPtr CenterConstraints = BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    //Description Panel
    LabelRecPtr DescriptionLabel = Label::create();
    DescriptionLabel->setText("Description:");
    DescriptionLabel->setBackgrounds(NULL);

    TextAreaRecPtr DescriptionTextArea = TextArea::create();
    DescriptionTextArea->setText(FieldDoc);
    DescriptionTextArea->setEditable(false);
    DescriptionTextArea->setBorders(NULL);
    DescriptionTextArea->setBackgrounds(NULL);
    DescriptionTextArea->setConstraints(CenterConstraints);

    //Description Panel
    PanelRecPtr DescriptionPanel = Panel::create();
    BorderLayoutRecPtr DescriptionPanelLayout = BorderLayout::create();
    DescriptionPanel->setAllInsets(5.0f);
    DescriptionPanel->setLayout(DescriptionPanelLayout);
    DescriptionPanel->pushToChildren(DescriptionTextArea);
    DescriptionPanel->setBackgrounds(NULL);


    //ToolTip Layout
    PanelRecPtr ToolTipPanel = Panel::createEmpty();

    SpringLayoutRecPtr MainLayout = SpringLayout::create();

    //TypeLabel    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TypeLabel, 5,
                              SpringLayoutConstraints::NORTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TypeLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TypeLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //MainSeparator    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MainSeparator, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, TypeLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MainSeparator, -15,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MainSeparator, 15,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);
    //ConsumableLabel    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ConsumableLabel, 1,
                              SpringLayoutConstraints::NORTH_EDGE, MainSeparator);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ConsumableLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ConsumableLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //DescriptionTextArea
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DescriptionLabel, 5,
                              SpringLayoutConstraints::SOUTH_EDGE, ConsumableLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DescriptionLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DescriptionLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //DescriptionTextArea
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DescriptionPanel, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, DescriptionLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, DescriptionPanel, -5,
                              SpringLayoutConstraints::SOUTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DescriptionPanel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DescriptionPanel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //ToolTip Panel

    Component* DefaultToolTip(LookAndFeelManager::the()->getLookAndFeel()->getDefaultToolTip());
    ToolTipPanel->setBorders(DefaultToolTip->getBorder());
    ToolTipPanel->setBackgrounds(DefaultToolTip->getBackground());
    ToolTipPanel->setForegrounds(DefaultToolTip->getForeground());
    ToolTipPanel->setLayout(MainLayout);
    ToolTipPanel->pushToChildren(TypeLabel);
    ToolTipPanel->pushToChildren(MainSeparator);
    ToolTipPanel->pushToChildren(ConsumableLabel);
    ToolTipPanel->pushToChildren(DescriptionLabel);
    ToolTipPanel->pushToChildren(DescriptionPanel);

    Real32 Height(130.0f + DescriptionTextArea->getLineHeight()
                  * (DescriptionTextArea->getText().size()/40));
    ToolTipPanel->setPreferredSize(Vec2f(300.0f,Height));

    return ComponentTransitPtr(ToolTipPanel);
}

ComponentTransitPtr GenericFieldContainerEditor::createFCToolTip(const FieldContainerType &FCType)
{
    std::string FieldDoc(doxygenToPlainFormatting(FCType.getDocumentation()));

    //TypeName
    LabelRecPtr TypeLabel = Label::create();
    TypeLabel->setText(FCType.getName());
    TypeLabel->setAlignment(Vec2f(0.5f,0.5f));
    TypeLabel->setBackgrounds(NULL);

    //Separator
    SeparatorRecPtr MainSeparator = Separator::create();
    MainSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    MainSeparator->setSeparatorSize(1.0f);
    MainSeparator->setPreferredSize(Vec2f(1.0f,5.0f));
    MainSeparator->setBackgrounds(NULL);

    //Inheritance Panel Layout
    //LabelRecPtr InheritanceLabel = Label::create();
    //InheritanceLabel->setText("Inheritance");

    //FlowLayoutRecPtr InheritancePanelLayout = FlowLayout::create();
    //InheritancePanelLayout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);
    //InheritancePanelLayout->setVerticalGap(3.0f);
    //InheritancePanelLayout->setMajorAxisAlignment(0.0f);
    //InheritancePanelLayout->setMinorAxisAlignment(0.5f);
    //InheritancePanelLayout->setComponentAlignment(0.5f);

    ////Inheritance Panel
    //PanelRecPtr InheritancePanel = Panel::createEmpty();
    //InheritancePanel->setAllInsets(5.0f);
    //InheritancePanel->setLayout(InheritancePanelLayout);

    //const TypeBase *ParentType(&FCType);
    ////while()
    ////{
        ////ToolTipPanel->pushToChildren(DescriptionTextArea);
    ////}
    //LabelRecPtr TypeNameLabel = Label::create();
    //TypeNameLabel->setText(FCType.getName());
    //TypeNameLabel->setAlignment(Vec2f(0.5f,0.5f));

    //InheritancePanel->pushToChildren(TypeNameLabel);

    //Set the layout constraints
    BorderLayoutConstraintsRecPtr CenterConstraints = BorderLayoutConstraints::create();
    CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    //Description Panel
    LabelRecPtr DescriptionLabel = Label::create();
    DescriptionLabel->setText("Description:");
    DescriptionLabel->setBackgrounds(NULL);

    TextAreaRecPtr DescriptionTextArea = TextArea::create();
    DescriptionTextArea->setText(FieldDoc);
    DescriptionTextArea->setEditable(false);
    DescriptionTextArea->setBorders(NULL);
    DescriptionTextArea->setBackgrounds(NULL);
    DescriptionTextArea->setConstraints(CenterConstraints);

    //Description Panel
    PanelRecPtr DescriptionPanel = Panel::create();
    BorderLayoutRecPtr DescriptionPanelLayout = BorderLayout::create();
    DescriptionPanel->setAllInsets(5.0f);
    DescriptionPanel->setLayout(DescriptionPanelLayout);
    DescriptionPanel->pushToChildren(DescriptionTextArea);
    DescriptionPanel->setBackgrounds(NULL);


    //ToolTip Layout
    PanelRecPtr ToolTipPanel = Panel::createEmpty();

    SpringLayoutRecPtr MainLayout = SpringLayout::create();

    //TypeLabel    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TypeLabel, 5,
                              SpringLayoutConstraints::NORTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TypeLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TypeLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //MainSeparator    
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MainSeparator, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, TypeLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MainSeparator, -15,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MainSeparator, 15,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    ////InheritancePanel
    //MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, InheritanceLabel, 1,
                              //SpringLayoutConstraints::SOUTH_EDGE, MainSeparator);
    //MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InheritanceLabel, 0,
                              //SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    //MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InheritanceLabel, 0,
                              //SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    ////InheritancePanel
    //MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, InheritancePanel, 1,
                              //SpringLayoutConstraints::SOUTH_EDGE, InheritanceLabel);
    //MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InheritancePanel, 0,
                              //SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    //MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InheritancePanel, 0,
                              //SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);


    //DescriptionTextArea
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DescriptionLabel, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, MainSeparator);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DescriptionLabel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DescriptionLabel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //DescriptionTextArea
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, DescriptionPanel, 1,
                              SpringLayoutConstraints::SOUTH_EDGE, DescriptionLabel);
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, DescriptionPanel, -5,
                              SpringLayoutConstraints::SOUTH_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, DescriptionPanel, -5,
                              SpringLayoutConstraints::EAST_EDGE, ToolTipPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, DescriptionPanel, 5,
                              SpringLayoutConstraints::WEST_EDGE, ToolTipPanel);

    //ToolTip Panel

    Component* DefaultToolTip(LookAndFeelManager::the()->getLookAndFeel()->getDefaultToolTip());
    ToolTipPanel->setBorders(DefaultToolTip->getBorder());
    ToolTipPanel->setBackgrounds(DefaultToolTip->getBackground());
    ToolTipPanel->setForegrounds(DefaultToolTip->getForeground());
    ToolTipPanel->setLayout(MainLayout);
    ToolTipPanel->pushToChildren(TypeLabel);
    ToolTipPanel->pushToChildren(MainSeparator);
    //ToolTipPanel->pushToChildren(InheritanceLabel);
    //ToolTipPanel->pushToChildren(InheritancePanel);
    ToolTipPanel->pushToChildren(DescriptionLabel);
    ToolTipPanel->pushToChildren(DescriptionPanel);

    Real32 Height(100.0f + DescriptionTextArea->getLineHeight()
                  * (DescriptionTextArea->getText().size()/40));
    ToolTipPanel->setPreferredSize(Vec2f(300.0f,Height));

    return ComponentTransitPtr(ToolTipPanel);
}

bool GenericFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the Name Editor
    if(getEditingFC() &&
       _GenericNameAttachmentEditor->isTypeEditable(getEditingFC()->getType()))
    {
        _GenericNameAttachmentEditor->dettachContainer();
    }

    //Clear Children
    clearEditors();

    _FieldsContainer->clearChildren();
    _ProducedEventsContainer->clearChildren();

    //Set the number of rows for the grid layout
    dynamic_cast<GridBagLayout*>(_FieldsContainer->getLayout())->setRows(0);
    dynamic_cast<GridLayout*>(_ProducedEventsContainer->getLayout())->setRows(0);

    return Inherited::dettachFieldContainer();
}

void GenericFieldContainerEditor::updateShownPanels(void)
{
    if(getShowFields() &&
       getMFChildren()->findIndex(_FieldsContainer) < 0)
    {
        pushToChildren(_FieldsContainer);
    }
    else if(!getShowFields() &&
            getMFChildren()->findIndex(_FieldsContainer) >= 0)
    {
        removeObjFromChildren(_FieldsContainer);
    }

    if(getShowEvents() &&
       getMFChildren()->findIndex(_ProducedEventsContainer) < 0)
    {
        pushToChildren(_ProducedEventsContainer);
    }
    else if(!getShowEvents() &&
            getMFChildren()->findIndex(_ProducedEventsContainer) >= 0)
    {
        removeObjFromChildren(_ProducedEventsContainer);
    }
}


/*----------------------- constructors & destructors ----------------------*/

GenericFieldContainerEditor::GenericFieldContainerEditor(void) :
    Inherited()
{
}

GenericFieldContainerEditor::GenericFieldContainerEditor(const GenericFieldContainerEditor &source) :
    Inherited(source)
{
}

GenericFieldContainerEditor::~GenericFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/
void GenericFieldContainerEditor::onCreate(const GenericFieldContainerEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        _BoldFont = UIFont::create();
        UIFontUnrecPtr ProtoFont(dynamic_cast<Label*>(Label::getClassType().getPrototype())->getFont());
        _BoldFont->setFamily(ProtoFont->getFamily());
        _BoldFont->setGlyphPixelSize(ProtoFont->getGlyphPixelSize());
        _BoldFont->setSize(ProtoFont->getSize());
        _BoldFont->setStyle(TextFace::STYLE_BOLD);

        BorderLayoutConstraintsRefPtr WestConstraint = BorderLayoutConstraints::create();
        WestConstraint->setRegion(BorderLayoutConstraints::BORDER_WEST);

        BorderLayoutConstraintsRefPtr NorthConstraint = BorderLayoutConstraints::create();
        NorthConstraint->setRegion(BorderLayoutConstraints::BORDER_NORTH);

        BorderLayoutConstraintsRefPtr CenterConstraint = BorderLayoutConstraints::create();
        CenterConstraint->setRegion(BorderLayoutConstraints::BORDER_CENTER);

        BorderLayoutConstraintsRefPtr SouthConstraint = BorderLayoutConstraints::create();
        SouthConstraint->setRegion(BorderLayoutConstraints::BORDER_SOUTH);

        //Backgournds
        ColorLayerRefPtr HeaderBgLayer = ColorLayer::create();
        HeaderBgLayer->setColor(Color4f(0.7f,0.7f,0.7f,1.0f));

        //Type Panel
        _ContainerTypeLabel = Label::create();
        _ContainerTypeLabel->setAlignment(Vec2f(0.5f,0.5f));
        _ContainerTypeLabel->setBackgrounds(HeaderBgLayer);
        _ContainerTypeLabel->setConstraints(WestConstraint);
        _ContainerTypeLabel->setPreferredSize(Vec2f(160.0f,22.0f));

        _ContainerIdLabel = Label::create();
        _ContainerIdLabel->setAlignment(Vec2f(0.5f,0.5f));
        _ContainerIdLabel->setBackgrounds(HeaderBgLayer);
        _ContainerIdLabel->setConstraints(CenterConstraint);


        BorderLayoutRefPtr TheBorderLayout = BorderLayout::create();
        PanelRefPtr TypePanel = Panel::createEmpty();
        TypePanel->setPreferredSize(Vec2f(160.0f,33.0f));
        TypePanel->setInset(Vec4f(1.0f,1.0f,1.0f,10.0f));
        TypePanel->pushToChildren(_ContainerIdLabel);
        TypePanel->pushToChildren(_ContainerTypeLabel);
        TypePanel->setLayout(TheBorderLayout);
        TypePanel->setConstraints(NorthConstraint);
        pushToChildren(TypePanel);

        //Fields Panel
        GridBagLayoutRecPtr AllFieldsPanelLayout = GridBagLayout::create();
        AllFieldsPanelLayout->setColumns(1);

        _FieldsContainer = Panel::createEmpty();
        _FieldsContainer->setConstraints(CenterConstraint);
        _FieldsContainer->setLayout(AllFieldsPanelLayout);
        if(getShowFields())
        {
            pushToChildren(_FieldsContainer);
        }

        //Events Panel
        GridLayoutRecPtr AllProducedEventsPanelLayout = GridLayout::create();
        AllProducedEventsPanelLayout->setColumns(1);
        AllProducedEventsPanelLayout->setHorizontalGap(0.0f);
        AllProducedEventsPanelLayout->setVerticalGap(0.0f);

        _ProducedEventsContainer = Panel::createEmpty();
        _ProducedEventsContainer->setConstraints(SouthConstraint);
        _ProducedEventsContainer->setLayout(AllProducedEventsPanelLayout);
        _ProducedEventsContainer->setInset(Vec4f(0.0f,0.0f,15.0f,0.0f));
        if(getShowEvents())
        {
            pushToChildren(_ProducedEventsContainer);
        }

        //Main Layout
        BorderLayoutRefPtr MainLayout = BorderLayout::create();
        setLayout(MainLayout);

        _GenericNameAttachmentEditor = GenericNameAttachmentEditor::create();
    }
}

void GenericFieldContainerEditor::onDestroy()
{
}

void GenericFieldContainerEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _ContainerTypeLabel = NULL;
    _ContainerIdLabel = NULL;
    _GenericNameAttachmentEditor = NULL;
    _FieldsContainer = NULL;
    _ProducedEventsContainer = NULL;
}

void GenericFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if( whichField & ChildrenFieldMask)
    {
        //Layout needs to be recalculated for my parent ComponentContainer
        updateContainerLayout();
    }

    if( (whichField & ShowFieldsFieldMask) ||
        (whichField & ShowEventsFieldMask))
    {
        updateShownPanels();
    }
}

void GenericFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GenericFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
