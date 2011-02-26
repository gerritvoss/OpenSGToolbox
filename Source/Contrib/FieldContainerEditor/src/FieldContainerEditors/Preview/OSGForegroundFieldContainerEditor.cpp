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

#include "OSGForegroundFieldContainerEditor.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGForeground.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGForegroundFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGForegroundFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const FieldContainerType*>
ForegroundFieldContainerEditor::_EditableTypes = std::vector<const FieldContainerType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ForegroundFieldContainerEditor::initMethod(InitPhase ePhase)
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
                if(type->isDerivedFrom(Foreground::getClassType()))
                {
                    _EditableTypes.push_back(type);
                    FieldContainerEditorFactory::the()->setDefaultEditor(type,
                                                                         &getClassType());
                    FieldContainerEditorFactory::the()->setEditorType(type,
                                                                      &getClassType(),
                                                                      "Foreground");
                }
            }
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const std::vector<const FieldContainerType*>& ForegroundFieldContainerEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

bool ForegroundFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    //Attach the foreground
    _PrimaryViewport->clearForegrounds();
    _PrimaryViewport->addForeground(dynamic_cast<Foreground*>(fc));

    return true;
}

bool ForegroundFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the foreground
    _PrimaryViewport->clearForegrounds();

    return Inherited::dettachFieldContainer();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ForegroundFieldContainerEditor::ForegroundFieldContainerEditor(void) :
    Inherited()
{
}

ForegroundFieldContainerEditor::ForegroundFieldContainerEditor(const ForegroundFieldContainerEditor &source) :
    Inherited(source)
{
}

ForegroundFieldContainerEditor::~ForegroundFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ForegroundFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ForegroundFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ForegroundFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
