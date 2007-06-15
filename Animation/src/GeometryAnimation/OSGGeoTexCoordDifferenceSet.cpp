/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
#include <OpenSG/OSGGeoPropPtrs.h>

#include "OSGGeoTexCoordDifferenceSet.h"
#include "Util/OSGGeoPropertyOperations.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GeoTexCoordDifferenceSet

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoTexCoordDifferenceSet::initMethod (void)
{
}

GeoTexCoordDifferenceSetPtr GeoTexCoordDifferenceSet::create(const GeoTexCoordsPtr BaseTexCoords, const GeoTexCoordsPtr ToTexCoords)
{
   //Check that both TexCoord Containers have the same number of Values
   if(BaseTexCoords->getSize() != ToTexCoords->getSize())
   {
      return NullFC;
   }
   GeoTexCoordDifferenceSetPtr Result = GeoTexCoordDifferenceSetBase::create();
   Result->setIndices( GeoIndicesUI32::create() );
   Result->setTexCoords( createEmptyFromBase(BaseTexCoords) );

   //Loop through each position of BaseTexCoords and ToTexCoords
   beginEditCP(Result);
   Result->getIndices()->addValue( -1 );
   for(UInt32 i=0 ; i<BaseTexCoords->getSize() ; ++i)
   {
      //If TexCoord i of ToTexCoords is different from BaseTexCoords
      if(ToTexCoords->getValue(i) != BaseTexCoords->getValue(i))
      {
         //Then add this TexCoord and its index to the DifferenceSet
         addValueAsBaseType(Result->getTexCoords(), ToTexCoords, i);
            if(Result->getIndices()->getValue(0) != -1)
            {
               Result->getIndices()->addValue( i );
            }
            else
            {
               Result->getIndices()->setValue( i, 0 );
            }
      }
   }
   endEditCP(Result);
   return Result;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoTexCoordDifferenceSet::GeoTexCoordDifferenceSet(void) :
    Inherited()
{
}

GeoTexCoordDifferenceSet::GeoTexCoordDifferenceSet(const GeoTexCoordDifferenceSet &source) :
    Inherited(source)
{
}

GeoTexCoordDifferenceSet::~GeoTexCoordDifferenceSet(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeoTexCoordDifferenceSet::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GeoTexCoordDifferenceSet::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeoTexCoordDifferenceSet NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.19 2003/05/05 10:05:28 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGGEOTEXCOORDDIFFERENCESETBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOTEXCOORDDIFFERENCESETBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGEOTEXCOORDDIFFERENCESETFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

