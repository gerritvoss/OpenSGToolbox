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

#define OSG_COMPILEANIMATIONLIB

#include <OpenSG/OSGConfig.h>

#include "OSGKeyframeSequence.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::KeyframeSequence
KeyframeSequence is the base class of all Keyframe Sequences. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyframeSequence::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool KeyframeSequence::interpolate(const InterpolationType& Type, const Real32& time, const Real32& prevTime, const osg::ValueReplacementPolicy& ReplacePolicy, bool isCyclic, osg::Field& Result, UInt32 Index, Real32 Blend)
{
    RawInterpFuncion InterpFunc(getRawInterpFuncion(Type));
    if(InterpFunc.empty())
    {
        SWARNING << "KeyframeSequence::interpolate(...): No Interpolation function of type: " << Type << std::endl;
        return false;
    }
    ReplacementFuncion ReplaceFunc(getReplacementFuncion());
    if(ReplaceFunc.empty())
    {
        SWARNING << "KeyframeSequence::interpolate(...): No Replacement function." << std::endl;
        return false;
    }

    return ReplaceFunc(InterpFunc, time, prevTime, ReplacePolicy, isCyclic, Result, Index, Blend);
}

RawInterpFuncion KeyframeSequence::getRawInterpFuncion(const InterpolationType& Type)
{
    switch(Type)
    {
    case STEP_INTERPOLATION:
        return getStepInterpFuncion();
        break;
    case LINEAR_INTERPOLATION:
        return getLinearInterpFuncion();
        break;
    case LINEAR_NORMAL_INTERPOLATION:
        return getLinearNormalInterpFuncion();
        break;
    case CUBIC_INTERPOLATION:
        return getCubicInterpFuncion();
        break;
    default:
        return RawInterpFuncion();
        break;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyframeSequence::KeyframeSequence(void) :
    Inherited()
{
}

KeyframeSequence::KeyframeSequence(const KeyframeSequence &source) :
    Inherited(source)
{
}

KeyframeSequence::~KeyframeSequence(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyframeSequence::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void KeyframeSequence::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump KeyframeSequence NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGKEYFRAMESEQUENCEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGKEYFRAMESEQUENCEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGKEYFRAMESEQUENCEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

