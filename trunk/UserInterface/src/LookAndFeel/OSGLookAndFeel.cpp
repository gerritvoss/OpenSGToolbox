/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>

#include "OSGLookAndFeel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LookAndFeel
UI LookAndFeel Interface. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LookAndFeel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LookAndFeel::initPrototypes(void)
{
    //Loop through all of my prototypes
    for(UInt32 i(0) ; i<getPrototypes().size(); ++i)
    {
        //Set them as their class prototypes
	    getPrototypes()[i]->getType().setPrototype(getPrototypes()[i]);
    }
    //Find all of the types that inherit off of the defined prototypes
    UInt32 NumFCTypes(FieldContainerFactory::the()->getNumTypes());
    const FieldContainerType* UndefinedPrototypeType(NULL);
    const FieldContainerType* ClosestAncestorType(NULL);
    FieldContainerPtr UndefinedPrototype(NullFC);
    FieldContainerPtr ClosestAncestorPrototype(NullFC);

    const FieldDescription* Desc(NULL);
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

        ClosestAncestorType = getClosestAncestor(UndefinedPrototypeType, getPrototypes().getValues());
        if(ClosestAncestorType != NULL &&
          *ClosestAncestorType != *UndefinedPrototypeType &&
          !UndefinedPrototypeType->isAbstract())
        {
            //SLOG << "UserInterface: LookAndFeel: Initializing undefined prototype for a derived user interface type" << std::endl
                 //<< "    Undefined Prototype Type: "   << UndefinedPrototypeType->getCName() << std::endl
                 //<< "    Closest Ancestor: "         << ClosestAncestorType->getCName() << std::endl;
            //For all of these types set the prototype values of all of the 
            //inherited fields to the same as the closest ancestor
            BitVector TheBitMask(0);
            for(UInt32 j(0); j<ClosestAncestorType->getNumFieldDescs() ; ++j)
            {
                TheBitMask |=  TypeTraits<BitVector>::One;
                TheBitMask << 1;
            }
            UndefinedPrototype = UndefinedPrototypeType->getPrototype();
            ClosestAncestorPrototype = ClosestAncestorType->getPrototype();
            //beginEditCP(UndefinedPrototype, TheBitMask);
                //for(UInt32 j(1); j<=ClosestAncestorType->getNumFieldDescs() ; ++j)
                //{
                    //Desc = ClosestAncestorType->getFieldDescription(j);

                    ////Set the field to the same as this closest ancestor
                    //UndefinedPrototype->getField(Desc->getFieldId())->setAbstrValue(*(ClosestAncestorPrototype->getField(Desc->getFieldId())));
                //}
            //endEditCP(UndefinedPrototype, TheBitMask);
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

void LookAndFeel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void LookAndFeel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LookAndFeel NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGLOOKANDFEELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLOOKANDFEELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLOOKANDFEELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

