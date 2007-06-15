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

#include "OSGKeyframeSequenceGeoPositionsPtr.h"
#include "Interpolation/OSGGeometryInterpolations.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::KeyframeSequenceGeoPositionsPtr

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeSequenceGeoPositionsPtr::initMethod (void)
{
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::STEP_INTERPOLATION, osg::SFGeoPositionsPtr::getClassType(), osg::KeyframeSequenceGeoPositionsPtr::stepFieldInterpolation);
   osg::InterpolationFactory::the()->registerFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::SFGeoPositionsPtr::getClassType(), osg::KeyframeSequenceGeoPositionsPtr::linearFieldInterpolation);
}


bool KeyframeSequenceGeoPositionsPtr::linearFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
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

   return lerp(osg::KeyframeSequenceGeoPositionsPtrPtr::dcast(KeyValues)->getBaseValues(),
               osg::KeyframeSequenceGeoPositionsPtrPtr::dcast(KeyValues)->getKeyframeDifferenceSets(),
               Keys,
               Time,
               static_cast<osg::SFGeoPositionsPtr&>(Result).getValue(),
               Cycling != 1);
}

bool KeyframeSequenceGeoPositionsPtr::stepFieldInterpolation(const osg::KeyframeSequencePtr& KeyValues,
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

   return step(osg::KeyframeSequenceGeoPositionsPtrPtr::dcast(KeyValues)->getBaseValues(),
               osg::KeyframeSequenceGeoPositionsPtrPtr::dcast(KeyValues)->getKeyframeDifferenceSets(),
               Keys,
               Time,
               static_cast<osg::SFGeoPositionsPtr&>(Result).getValue(),
               Cycling != 1);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyframeSequenceGeoPositionsPtr::KeyframeSequenceGeoPositionsPtr(void) :
    Inherited()
{
}

KeyframeSequenceGeoPositionsPtr::KeyframeSequenceGeoPositionsPtr(const KeyframeSequenceGeoPositionsPtr &source) :
    Inherited(source)
{
}

KeyframeSequenceGeoPositionsPtr::~KeyframeSequenceGeoPositionsPtr(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeSequenceGeoPositionsPtr::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void KeyframeSequenceGeoPositionsPtr::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump KeyframeSequenceGeoPositionsPtr NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGKEYFRAMESEQUENCEGEOPOSITIONSPTRBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGKEYFRAMESEQUENCEGEOPOSITIONSPTRBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGKEYFRAMESEQUENCEGEOPOSITIONSPTRFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

