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
#include "OSGColorLayer.h"
#include <boost/lexical_cast.hpp>
#include "OSGImage.h"

#include "OSGGridBagLayout.h"
#include "OSGGridBagLayoutConstraints.h"

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
    //GridLayoutRefPtr TheLayout = dynamic_cast<GridLayout*>(getLayout());

    //return TheLayout->preferredLayoutSize(getMFChildren(), this);//Vec2f(getPreferredSize().x(), (20.0f + TheLayout->getVerticalGap()) * (getMFChildren()->size()/+1));

    return Vec2f(1.0,dynamic_cast<GridBagLayout*>(getLayout())->getRows()*24.0f);
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

    UInt32 NumFields(fc->getType().getNumFieldDescs());
    FieldDescriptionBase* Desc;
    FieldEditorComponentUnrecPtr TheEditor;
    LabelUnrecPtr TheLabel;
    GridBagLayoutConstraintsRefPtr LayoutConstraints;
    PanelRefPtr FieldPanel;
    UInt32 NumRows(0),NumRowsForField(1);

    BorderLayoutRefPtr TheLayout = BorderLayout::create();
    BorderLayoutConstraintsRefPtr WestConstraint = OSG::BorderLayoutConstraints::create();
    WestConstraint->setRegion(BorderLayoutConstraints::BORDER_WEST);
    BorderLayoutConstraintsRefPtr CenterConstraint = OSG::BorderLayoutConstraints::create();
    CenterConstraint->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    //Backgournds
    ColorLayerRefPtr HeaderBgLayer = ColorLayer::create();
    HeaderBgLayer->setColor(Color4f(0.7f,0.7f,0.7f,1.0f));

    ColorLayerRefPtr LightBgLayer = ColorLayer::create();
    LightBgLayer->setColor(Color4f(0.9f,0.9f,0.9f,1.0f));
    ColorLayerRefPtr DarkBgLayer = ColorLayer::create();
    DarkBgLayer->setColor(Color4f(0.8f,0.8f,0.8f,1.0f));

    //Push the Type and Id Labels
    _ContainerTypeLabel->setText(getEditingFC()->getType().getName());
    _ContainerTypeLabel->setBackgrounds(NULL);
    _ContainerTypeLabel->setConstraints(WestConstraint);
    _ContainerTypeLabel->setPreferredSize(Vec2f(160.0f,22.0f));

    _ContainerIdLabel->setText(boost::lexical_cast<std::string>(getEditingFC()->getId()));
    _ContainerIdLabel->setBackgrounds(NULL);
    _ContainerIdLabel->setConstraints(CenterConstraint);

    LayoutConstraints = GridBagLayoutConstraints::create();

    LayoutConstraints->setGridX(0);
    LayoutConstraints->setGridY(NumRows);
    LayoutConstraints->setGridHeight(1);
    LayoutConstraints->setGridWidth(1);
    LayoutConstraints->setFill(GridBagLayoutConstraints::FILL_BOTH);

    FieldPanel = Panel::createEmpty();
    FieldPanel->setBackgrounds(HeaderBgLayer);
    FieldPanel->setInset(Vec4f(1.0f,1.0f,1.0f,1.0f));
    FieldPanel->pushToChildren(_ContainerIdLabel);
    FieldPanel->pushToChildren(_ContainerTypeLabel);
    FieldPanel->setLayout(TheLayout);
    FieldPanel->setConstraints(LayoutConstraints);
    pushToChildren(FieldPanel);
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
        FieldPanel->setLayout(TheLayout);
        FieldPanel->setConstraints(LayoutConstraints);
        FieldPanel->setBackgrounds(LightBgLayer);

        pushToChildren(FieldPanel);
        ++NumRows;
    }

    UInt32 UsedFieldCount(0);
    for(UInt32 i(1) ; i<=NumFields ; ++i)
    {
        Desc = fc->getFieldDescription(i);
        if(Desc != 0 &&
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
                FieldPanel->setLayout(TheLayout);
                FieldPanel->setConstraints(LayoutConstraints);
                if((UsedFieldCount%2) == 0)
                {
                    FieldPanel->setBackgrounds(DarkBgLayer);
                }
                else
                {
                    FieldPanel->setBackgrounds(LightBgLayer);
                }

                pushToChildren(FieldPanel);
                NumRows += NumRowsForField;
                TheEditor->setPreferredSize(Vec2f(50.0f,22.0f * NumRowsForField));
                ++UsedFieldCount;
            }
        }
    }
    //Set the number of rows for the grid layout
    dynamic_cast<GridBagLayout*>(getLayout())->setRows(NumRows);

    return true;
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
    clearChildren();
    clearEditors();

    //Set the number of rows for the grid layout
    dynamic_cast<GridBagLayout*>(getLayout())->setRows(0);

    return Inherited::dettachFieldContainer();
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
        GridBagLayoutRefPtr TheLayout = GridBagLayout::create();

        TheLayout->setRows(0);
        TheLayout->setColumns(1);
        setLayout(TheLayout);

        _ContainerTypeLabel = Label::create();
        _ContainerTypeLabel->setAlignment(Vec2f(0.5f,0.5f));
        _ContainerIdLabel = Label::create();
        _ContainerIdLabel->setAlignment(Vec2f(0.5f,0.5f));
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
}


void GenericFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if( (whichField & ChildrenFieldMask))
    {
        //Layout needs to be recalculated for my parent ComponentContainer
        updateContainerLayout();
    }
}

void GenericFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GenericFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
