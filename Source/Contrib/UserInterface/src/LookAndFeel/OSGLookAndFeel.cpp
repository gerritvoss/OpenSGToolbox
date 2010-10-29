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

#include "OSGLookAndFeel.h"
#include "OSGFieldContainerFactory.h"
#include "OSGContainerUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLookAndFeelBase.cpp file.
// To modify it, please change the .fcd file (OSGLookAndFeel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LookAndFeel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LookAndFeel::initPrototypes(void)
{
    //Loop through all of my prototypes
    for(UInt32 i(0) ; i<getMFPrototypes()->size(); ++i)
    {
        //Set them as their class prototypes
        getPrototypes(i)->getType().setPrototype(getPrototypes(i));
        SNOTICE << "LookAndFeel: Redefining prototype for type: " 
                << getPrototypes(i)->getType().getName() << std::endl;
    }
}

void LookAndFeel::initUndefinedPrototypes(void)
{
    //Find all of the types that inherit off of the defined prototypes
    UInt32 NumFCTypes(FieldContainerFactory::the()->getNumTypes());
    const FieldContainerType* UndefinedPrototypeType(NULL);
    const FieldContainerType* ClosestAncestorType(NULL);
    FieldContainerRefPtr UndefinedPrototype(NULL);
    FieldContainerRefPtr ClosestAncestorPrototype(NULL);

    const FieldDescriptionBase* UndefinedPrototypeDesc(NULL);
    const FieldDescriptionBase* ClosestAncestorDesc(NULL);
    UInt32 NumTypesFound(0);
    for (UInt32 i(0); NumTypesFound < NumFCTypes ; ++i)
    {
        UndefinedPrototypeType = FieldContainerFactory::the()->findType(i);
        if(UndefinedPrototypeType == NULL)
        {
            continue;
        }
        else
        {
            ++NumTypesFound;
        }

        ClosestAncestorType = getClosestAncestor(UndefinedPrototypeType,
                                                 getMFPrototypes()->begin(),
                                                 getMFPrototypes()->end());
        if(ClosestAncestorType != NULL &&
           *ClosestAncestorType != *UndefinedPrototypeType &&
           !UndefinedPrototypeType->isAbstract())
        {
            SNOTICE << "UserInterface: LookAndFeel: Initializing undefined prototype for a derived user interface type" << std::endl
                    << "    Undefined Prototype Type: "   << UndefinedPrototypeType->getCName() << std::endl
                    << "    Closest Ancestor: "         << ClosestAncestorType->getCName() << std::endl;
            //For all of these types set the prototype values of all of the 
            //inherited fields to the same as the closest ancestor
            UndefinedPrototype = UndefinedPrototypeType->getPrototype();
            ClosestAncestorPrototype = ClosestAncestorType->getPrototype();
            for(UInt32 j(1); j<=ClosestAncestorType->getNumFieldDescs() ; ++j)
            {
                ClosestAncestorDesc = ClosestAncestorType->getFieldDesc(j);
                UndefinedPrototypeDesc = ClosestAncestorType->getFieldDesc(ClosestAncestorDesc->getCName());

                //Set the field to the same as this closest ancestor
                //Get the Undefined Field
                EditFieldHandlePtr UndefinedField =
                    UndefinedPrototype->editField(UndefinedPrototypeDesc->getFieldId());
                GetFieldHandlePtr ClosestAncestorField =
                    ClosestAncestorPrototype->getField(ClosestAncestorDesc->getFieldId());
                //Get the Closest Ancestor Field
                if(UndefinedField != NULL && 
                   ClosestAncestorField != NULL &&
                   !UndefinedPrototypeDesc->isInternal())
                {
                    if(UndefinedField->isPointerField())
                    {
                        UndefinedField->cloneValues(ClosestAncestorField);
                    }
                    else
                    {
                        UndefinedField->copyValues(ClosestAncestorField);
                    }
                }
            }
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LookAndFeel::LookAndFeel(void) :
    Inherited()
{
}

LookAndFeel::LookAndFeel(const LookAndFeel &source) :
    Inherited(source)
{
}

LookAndFeel::~LookAndFeel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LookAndFeel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LookAndFeel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LookAndFeel NI" << std::endl;
}

OSG_END_NAMESPACE
