/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Sound                               *
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

#define OSG_COMPILESOUNDLIB

#include <OpenSG/OSGConfig.h>

#include "OSGSoundEmitter.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SoundEmitter
A SoundEmitter Core. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SoundEmitter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

//void SoundEmitter::update(){
	//assert(get
//	this->getParents(0);


bool SoundEmitter::attachUpdateListener(WindowEventProducerPtr UpdateProducer)
{
    if(UpdateProducer == NullFC)
    {
        return false;
    }

    UpdateProducer->addUpdateListener(&_SystemUpdateListener);

    return true;
}

void SoundEmitter::dettachUpdateListener(WindowEventProducerPtr UpdateProducer)
{
    if(UpdateProducer != NullFC)
    {
        UpdateProducer->removeUpdateListener(&_SystemUpdateListener);
    }
}
//}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SoundEmitter::update(const Time& elps)
{
	assert(getParents().size() == 1 && "A Sound Emitter NodeCore MUST have 1 and only 1 parent.");
	Matrix wm;
	getParents()[0]->getToWorld(wm);
	Pnt3f wp, origin(0, 0, 0);
	wm.mult(origin, wp);
	this->getSound()->setPosition(wp);
}

/*----------------------- constructors & destructors ----------------------*/

SoundEmitter::SoundEmitter(void) :
    Inherited(),
    _SystemUpdateListener(SoundEmitterPtr(this))
{
}

SoundEmitter::SoundEmitter(const SoundEmitter &source) :
    Inherited(source),
    _SystemUpdateListener(SoundEmitterPtr(this))
{
}

SoundEmitter::~SoundEmitter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SoundEmitter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SoundEmitter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SoundEmitter NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

void SoundEmitter::SystemUpdateListener::update(const UpdateEvent& e)
{
    _System->update(e.getElapsedTime());
}

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGSOUNDEMITTERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSOUNDEMITTERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSOUNDEMITTERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

