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
#include "OSGGridLayout.h"
#include <boost/lexical_cast.hpp>

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
    GridLayoutRefPtr TheLayout = dynamic_cast<GridLayout*>(getLayout());

    return TheLayout->preferredLayoutSize(getMFChildren(), this);//Vec2f(getPreferredSize().x(), (20.0f + TheLayout->getVerticalGap()) * (getMFChildren()->size()/+1));
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

    //Push the Type and Id Labels
    _ContainerTypeLabel->setText(getEditingFC()->getType().getName());
    pushToChildren(_ContainerTypeLabel);
    _ContainerIdLabel->setText(boost::lexical_cast<std::string>(getEditingFC()->getId()));
    pushToChildren(_ContainerIdLabel);

    if(_GenericNameAttachmentEditor->isTypeEditable(fc->getType()))
    {
        //Attach the Generic Name Editor
        _GenericNameAttachmentEditor->setCommandManager(_CmdManager);
        _GenericNameAttachmentEditor->attachContainer(fc);

        //Create the Label
        TheLabel = Label::create();
        TheLabel->setText("Name");

        pushToChildren(TheLabel);
        pushToChildren(_GenericNameAttachmentEditor);
    }

    for(UInt32 i(1) ; i<=NumFields ; ++i)
    {
        Desc = fc->getFieldDescription(i);
        if(Desc != 0 &&
           !Desc->isInternal() &&
           Desc->getFieldType().getCardinality() != FieldType::MultiField &&
           Desc->getFieldType().getClass() != FieldType::ParentPtrField)
        {
            //Create the Editor
            TheEditor = FieldEditorFactory::the()->createDefaultEditor(fc, Desc->getFieldId(), _CmdManager);
            if(TheEditor != NULL)
            {
                pushToEditors(TheEditor);

                //Create the Label
                TheLabel = Label::create();
                TheLabel->setText(Desc->getCName());

                pushToChildren(TheLabel);
                pushToChildren(TheEditor);
            }
        }
    }
    //Set the number of rows for the grid layout
    dynamic_cast<GridLayout*>(getLayout())->setRows(1+getMFChildren()->size()/2);

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
    dynamic_cast<GridLayout*>(getLayout())->setRows(0);

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
        GridLayoutRefPtr TheLayout = OSG::GridLayout::create();

        TheLayout->setRows(0);
        TheLayout->setColumns(2);
        TheLayout->setHorizontalGap(1);
        TheLayout->setVerticalGap(3);
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
