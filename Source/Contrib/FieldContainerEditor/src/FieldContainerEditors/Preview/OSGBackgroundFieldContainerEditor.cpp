/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

#include "OSGConfig.h"

#include "OSGBackgroundFieldContainerEditor.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGBackground.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGBackgroundFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGBackgroundFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const FieldContainerType*>
BackgroundFieldContainerEditor::_EditableTypes = std::vector<const FieldContainerType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BackgroundFieldContainerEditor::initMethod(InitPhase ePhase)
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
                if(type->isDerivedFrom(Background::getClassType()))
                {
                    _EditableTypes.push_back(type);
                    FieldContainerEditorFactory::the()->setDefaultEditor(type,
                                                                         &getClassType());
                    FieldContainerEditorFactory::the()->setEditorType(type,
                                                                      &getClassType(),
                                                                      "Background");
                }
            }
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const std::vector<const FieldContainerType*>& BackgroundFieldContainerEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

bool BackgroundFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    //Attach the background
    _PrimaryViewport->setBackground(dynamic_cast<Background*>(fc));

    return true;
}

bool BackgroundFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the background
    _PrimaryViewport->setBackground(NULL);

    return Inherited::dettachFieldContainer();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BackgroundFieldContainerEditor::BackgroundFieldContainerEditor(void) :
    Inherited()
{
}

BackgroundFieldContainerEditor::BackgroundFieldContainerEditor(const BackgroundFieldContainerEditor &source) :
    Inherited(source)
{
}

BackgroundFieldContainerEditor::~BackgroundFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BackgroundFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BackgroundFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BackgroundFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
