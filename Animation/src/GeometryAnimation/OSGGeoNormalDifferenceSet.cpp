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

#include "OSGGeoNormalDifferenceSet.h"
#include "Util/OSGGeoPropertyOperations.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GeoNormalDifferenceSet

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoNormalDifferenceSet::initMethod (void)
{
}

GeoNormalDifferenceSetPtr GeoNormalDifferenceSet::create(const GeoNormalsPtr BaseNormals, const GeoNormalsPtr ToNormals)
{
   //Check that both Normal Containers have the same number of Values
   if(BaseNormals->getSize() != ToNormals->getSize())
   {
      return NullFC;
   }
   GeoNormalDifferenceSetPtr Result = GeoNormalDifferenceSetBase::create();
   Result->setIndices( GeoIndicesUI32::create() );
   Result->setNormals( createEmptyFromBase(BaseNormals) );

   //Loop through each position of BaseNormals and ToNormals
   beginEditCP(Result);
   Result->getIndices()->push_back( -1 );
   for(UInt32 i=0 ; i<BaseNormals->getSize() ; ++i)
   {
      //If Normal i of ToNormals is different from BaseNormals
      if(ToNormals->getValue(i) != BaseNormals->getValue(i))
      {
         //Then add this Normal and its index to the DifferenceSet
         addValueAsBaseType(Result->getNormals(), ToNormals, i);
         if(Result->getIndices()->getValue(0) != -1)
         {
            Result->getIndices()->push_back( i );
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

GeoNormalDifferenceSet::GeoNormalDifferenceSet(void) :
    Inherited()
{
}

GeoNormalDifferenceSet::GeoNormalDifferenceSet(const GeoNormalDifferenceSet &source) :
    Inherited(source)
{
}

GeoNormalDifferenceSet::~GeoNormalDifferenceSet(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeoNormalDifferenceSet::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GeoNormalDifferenceSet::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeoNormalDifferenceSet NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGEONORMALDIFFERENCESETBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEONORMALDIFFERENCESETBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGEONORMALDIFFERENCESETFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

