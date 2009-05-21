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
#include <OpenSG/OSGSysFieldDataType.h>

#include "OSGKeyframeAnimator.h"
#include "Interpolation/OSGInterpolationFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::KeyframeAnimator
Keyframe Animator Class. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeAnimator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


bool KeyframeAnimator::animate(const osg::InterpolationType& InterpType,
           const osg::ValueReplacementPolicy& ReplacementPolicy,
           const osg::UInt32& Cycling,
           const osg::Real32& time,
           const osg::Real32& prevTime,
           osg::Field& Result)
{
   if(Result.getCardinality() != osg::FieldType::SINGLE_FIELD)
   {
      SWARNING << "Result Field must be an SField NOT an MField." << std::endl;
      return false;
   }
   if( getKeyframeSequence() != NullFC)
   {
      return getKeyframeSequence()->interpolate(InterpType, time, prevTime, ReplacementPolicy, Cycling, Result);
   }
   else
   {
      return false;
   }
}
    
Real32 KeyframeAnimator::getLength(void) const
{
    if(getKeyframeSequence()->getSize() > 0)
    {
        return getKeyframeSequence()->getKeys().back();
    }
    else
    {
        return 0.0f;
    }
}

const DataType &KeyframeAnimator::getDataType(void) const
{
   return getKeyframeSequence()->getDataType();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyframeAnimator::KeyframeAnimator(void) :
    Inherited()
{
}

KeyframeAnimator::KeyframeAnimator(const KeyframeAnimator &source) :
    Inherited(source)
{
}

KeyframeAnimator::~KeyframeAnimator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeAnimator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void KeyframeAnimator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump KeyframeAnimator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGKEYFRAMEANIMATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGKEYFRAMEANIMATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGKEYFRAMEANIMATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

