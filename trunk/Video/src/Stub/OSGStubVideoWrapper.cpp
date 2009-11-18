/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#ifndef OSG_COMPILEVIDEOLIB
#define OSG_COMPILEVIDEOLIB
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGStubVideoWrapper.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StubVideoWrapper

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StubVideoWrapper::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool StubVideoWrapper::open(const std::string& ThePath)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::seek(Int64 SeekPos)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::jump(Int64 Amount)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::setRate(Real32 Rate)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

Real32 StubVideoWrapper::getRate(void) const
{
    //The Stub Video Wrapper does nothing, intentionally
    return 1.0;
}

bool StubVideoWrapper::play(void)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::pause(void)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::unpause(void)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::pauseToggle(void)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::stop(void)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::close(void)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}


bool StubVideoWrapper::isPlaying(void) const
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::isStopped(void) const
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::isPaused(void) const
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

bool StubVideoWrapper::isInitialized(void) const
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}


Int64 StubVideoWrapper::getPosition(void) const
{
    //The Stub Video Wrapper does nothing, intentionally
    return 0;
}

Int64 StubVideoWrapper::getDuration(void) const
{
    //The Stub Video Wrapper does nothing, intentionally
    return 0;
}


ImagePtr StubVideoWrapper::getCurrentFrame(void)
{
    //The Stub Video Wrapper does nothing, intentionally
    return NullFC;
}

bool StubVideoWrapper::updateImage(void)
{
    //The Stub Video Wrapper does nothing, intentionally
    return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StubVideoWrapper::StubVideoWrapper(void) :
    Inherited()
{
}

StubVideoWrapper::StubVideoWrapper(const StubVideoWrapper &source) :
    Inherited(source)
{
}

StubVideoWrapper::~StubVideoWrapper(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StubVideoWrapper::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void StubVideoWrapper::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump StubVideoWrapper NI" << std::endl;
}


OSG_END_NAMESPACE

