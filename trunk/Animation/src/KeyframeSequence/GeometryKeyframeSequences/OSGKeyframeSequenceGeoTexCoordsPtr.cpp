/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include "OSGKeyframeSequenceGeoTexCoordsPtr.h"
#include "Interpolation/OSGGeometryInterpolations.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::KeyframeSequenceGeoTexCoordsPtr

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeSequenceGeoTexCoordsPtr::initMethod (void)
{
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::STEP_INTERPOLATION, osg::SFGeoTexCoordsPtr::getClassType(), osg::KeyframeSequenceGeoTexCoordsPtr::stepFieldInterpolation);
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::SFGeoTexCoordsPtr::getClassType(), osg::KeyframeSequenceGeoTexCoordsPtr::linearFieldInterpolation);
}

bool KeyframeSequenceGeoTexCoordsPtr::linearFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
      const osg::MFReal32& Keys,
      const osg::UInt32& Cycling,
      const osg::Real32& Time,
      const osg::Real32& PrevTime,
      const osg::ValueReplacementPolicy& ReplacementPolicy,
      osg::Field& Result)
{
   if(ReplacementPolicy != OVERWRITE)
   {
      SWARNING << "Only the Overwrite replacement policy is defined for Geometry Aniamtions."  << std::endl;
      return false;
   }

   return lerp(osg::KeyframeSequenceGeoTexCoordsPtrPtr::dcast(KeyValues)->getBaseValues(),
               osg::KeyframeSequenceGeoTexCoordsPtrPtr::dcast(KeyValues)->getKeyframeDifferenceSets(),
               Keys,
               Time,
               static_cast<osg::SFGeoTexCoordsPtr&>(Result).getValue(),
               Cycling != 1);
}

bool KeyframeSequenceGeoTexCoordsPtr::stepFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
      const osg::MFReal32& Keys,
      const osg::UInt32& Cycling,
      const osg::Real32& Time,
      const osg::Real32& PrevTime,
      const osg::ValueReplacementPolicy& ReplacementPolicy,
      osg::Field& Result)
{
   if(ReplacementPolicy != OVERWRITE)
   {
      SWARNING << "Only the Overwrite replacement policy is defined for Geometry Aniamtions."  << std::endl;
      return false;
   }

   return step(osg::KeyframeSequenceGeoTexCoordsPtrPtr::dcast(KeyValues)->getBaseValues(),
               osg::KeyframeSequenceGeoTexCoordsPtrPtr::dcast(KeyValues)->getKeyframeDifferenceSets(),
               Keys,
               Time,
               static_cast<osg::SFGeoTexCoordsPtr&>(Result).getValue(),
               Cycling != 1);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyframeSequenceGeoTexCoordsPtr::KeyframeSequenceGeoTexCoordsPtr(void) :
    Inherited()
{
}

KeyframeSequenceGeoTexCoordsPtr::KeyframeSequenceGeoTexCoordsPtr(const KeyframeSequenceGeoTexCoordsPtr &source) :
    Inherited(source)
{
}

KeyframeSequenceGeoTexCoordsPtr::~KeyframeSequenceGeoTexCoordsPtr(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeSequenceGeoTexCoordsPtr::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void KeyframeSequenceGeoTexCoordsPtr::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump KeyframeSequenceGeoTexCoordsPtr NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGKEYFRAMESEQUENCEGEOTEXCOORDSPTRBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGKEYFRAMESEQUENCEGEOTEXCOORDSPTRBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGKEYFRAMESEQUENCEGEOTEXCOORDSPTRFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

