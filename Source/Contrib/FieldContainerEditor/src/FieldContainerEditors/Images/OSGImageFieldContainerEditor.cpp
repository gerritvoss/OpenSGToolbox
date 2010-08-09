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

#include "OSGImageFieldContainerEditor.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"

#include "OSGImage.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGImageFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGImageFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const FieldContainerType*> ImageFieldContainerEditor::_EditableTypes = std::vector<const FieldContainerType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ImageFieldContainerEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        FieldContainerEditorFactory::the()->setDefaultEditor(&Image::getClassType(),
                                                             &getClassType());
        FieldContainerEditorFactory::the()->setEditorType(&Image::getClassType(),
                                                          &getClassType(),
                                                          "Image");
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f ImageFieldContainerEditor::getContentRequestedSize(void) const
{
    return _GenericEditor->getContentRequestedSize() +
        Vec2f(0.0f,_ImageDisplayComponent->getPreferredSize().y());
}

const std::vector<const FieldContainerType*>& ImageFieldContainerEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

bool ImageFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    //Attach the image
	_ImageDisplayComponent->setImages(dynamic_cast<Image*>(fc));

    return true;
}

bool ImageFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the image
	_ImageDisplayComponent->setImages(static_cast<Image*>(NULL));

    return Inherited::dettachFieldContainer();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ImageFieldContainerEditor::onCreate(const ImageFieldContainerEditor *Id)
{
	Inherited::onCreate(Id);

    if(Id != NULL)
    {
        //Create the ImageComponent
        _ImageDisplayComponent = ImageComponent::create();
        _ImageDisplayComponent->setPreferredSize(Vec2f(150.0f,150.0f));
        _ImageDisplayComponent->setScale(ImageComponent::SCALE_MAX_AXIS);

        SpringLayoutRefPtr TheLayout = SpringLayout::create();

        TheLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE,_ImageDisplayComponent, 0,SpringLayoutConstraints::NORTH_EDGE, this);
        TheLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE,_ImageDisplayComponent, 0,SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, this);

        TheLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE,_GenericEditor, 1,SpringLayoutConstraints::SOUTH_EDGE, _ImageDisplayComponent);
        TheLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE,_GenericEditor, 0,SpringLayoutConstraints::SOUTH_EDGE, this);
        TheLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE,_GenericEditor, 0,SpringLayoutConstraints::EAST_EDGE, this);
        TheLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _GenericEditor, 0,SpringLayoutConstraints::WEST_EDGE, this);

        setLayout(TheLayout);
        pushToChildren(_ImageDisplayComponent);
        pushToChildren(_GenericEditor);
    }
}

void ImageFieldContainerEditor::onDestroy()
{
}

void ImageFieldContainerEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _ImageDisplayComponent = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

ImageFieldContainerEditor::ImageFieldContainerEditor(void) :
    Inherited()
{
}

ImageFieldContainerEditor::ImageFieldContainerEditor(const ImageFieldContainerEditor &source) :
    Inherited(source)
{
}

ImageFieldContainerEditor::~ImageFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ImageFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ImageFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ImageFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
