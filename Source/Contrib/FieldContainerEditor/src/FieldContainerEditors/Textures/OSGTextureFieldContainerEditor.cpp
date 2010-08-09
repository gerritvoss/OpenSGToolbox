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

#include "OSGTextureFieldContainerEditor.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"

#include "OSGTextureBaseChunk.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextureFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const FieldContainerType*> TextureFieldContainerEditor::_EditableTypes = std::vector<const FieldContainerType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureFieldContainerEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
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
                if(type->isDerivedFrom(TextureBaseChunk::getClassType()))
                {
                    _EditableTypes.push_back(type);
                    FieldContainerEditorFactory::the()->setDefaultEditor(type,
                                                                         &getClassType());
                    FieldContainerEditorFactory::the()->setEditorType(type,
                                                                      &getClassType(),
                                                                      "Texture");
                }
            }
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f TextureFieldContainerEditor::getContentRequestedSize(void) const
{
    return _GenericEditor->getContentRequestedSize() +
        Vec2f(0.0f,_ImageDisplayComponent->getPreferredSize().y());
}

const std::vector<const FieldContainerType*>& TextureFieldContainerEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

bool TextureFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    //Attach the image
	_ImageDisplayComponent->setTexture(dynamic_cast<TextureBaseChunk*>(fc));
	_ImageDisplayComponent->setRolloverTexture(dynamic_cast<TextureBaseChunk*>(fc));
	_ImageDisplayComponent->setDisabledTexture(dynamic_cast<TextureBaseChunk*>(fc));
	_ImageDisplayComponent->setFocusedTexture(dynamic_cast<TextureBaseChunk*>(fc));

    return true;
}

bool TextureFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the image
	_ImageDisplayComponent->setTexture(NULL);
	_ImageDisplayComponent->setRolloverTexture(NULL);
	_ImageDisplayComponent->setDisabledTexture(NULL);
	_ImageDisplayComponent->setFocusedTexture(NULL);

    return Inherited::dettachFieldContainer();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void TextureFieldContainerEditor::onCreate(const TextureFieldContainerEditor *Id)
{
	Inherited::onCreate(Id);

    if(Id != NULL)
    {
        Matrix m;
        m.setScale(Vec3f(3.0f,3.0f,1.0f));
        m.setTranslate(Pnt3f(-1.0f,-1.0f,0.0f));

        TextureTransformChunkRefPtr TextureTransform = TextureTransformChunk::create();
        TextureTransform->setMatrix(m);

        //Create the ImageComponent
        _ImageDisplayComponent = ImageComponent::create();
        _ImageDisplayComponent->setPreferredSize(Vec2f(250.0f,250.0f));
        _ImageDisplayComponent->setScale(ImageComponent::SCALE_STRETCH);
        _ImageDisplayComponent->setTransformation(TextureTransform);

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

void TextureFieldContainerEditor::onDestroy()
{
}

void TextureFieldContainerEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _ImageDisplayComponent = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

TextureFieldContainerEditor::TextureFieldContainerEditor(void) :
    Inherited()
{
}

TextureFieldContainerEditor::TextureFieldContainerEditor(const TextureFieldContainerEditor &source) :
    Inherited(source)
{
}

TextureFieldContainerEditor::~TextureFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextureFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TextureFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextureFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
