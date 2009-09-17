/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                 Authors: David Kabala, Daniel Guilliams                   *
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

#define OSG_COMPILEVIDEOLIB

#include <OpenSG/OSGConfig.h>

#include "OSGVLCVideoWrapper.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::VLCVideoWrapper

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VLCVideoWrapper::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool VLCVideoWrapper::open(Path ThePath)
{
	return false;
}


bool VLCVideoWrapper::seek(Int64 SeekPos)
{
	return false;
}

bool VLCVideoWrapper::jump(Int64 Amount)
{
	return false;
}


bool VLCVideoWrapper::setRate(Real32 Rate)
{
	return false;
}


Real32 VLCVideoWrapper::getRate(void) const
{
	return 0.0f;
}

bool VLCVideoWrapper::play(void)
{
	return false;
}

bool VLCVideoWrapper::pause(void)
{
	return false;
}

bool VLCVideoWrapper::unpause(void)
{
	return false;
}

bool VLCVideoWrapper::pauseToggle(void)
{
	return false;
}

bool VLCVideoWrapper::stop(void)
{
	return false;
}

bool VLCVideoWrapper::close(void)
{
	return false;
}

bool VLCVideoWrapper::isPlaying(void) const
{
	return false;
}

bool VLCVideoWrapper::isPaused(void) const
{
	return false;
}

bool VLCVideoWrapper::isInitialized(void) const
{
	return false;
}

bool VLCVideoWrapper::isStopped(void) const
{
	return false;
}

	
Int64 VLCVideoWrapper::getPosition(void) const
{
	return 0;
}

Int64 VLCVideoWrapper::getDuration(void) const
{
	return 0;
}


ImagePtr VLCVideoWrapper::getCurrentFrame(void)
{
	return Image::create();
}

bool VLCVideoWrapper::updateImage(void)
{
	return false;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VLCVideoWrapper::VLCVideoWrapper(void) :
    Inherited()
{
}

VLCVideoWrapper::VLCVideoWrapper(const VLCVideoWrapper &source) :
    Inherited(source)
{
}

VLCVideoWrapper::~VLCVideoWrapper(void)
{
}

/*----------------------------- class specific ----------------------------*/

void VLCVideoWrapper::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void VLCVideoWrapper::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump VLCVideoWrapper NI" << std::endl;
}


OSG_END_NAMESPACE

