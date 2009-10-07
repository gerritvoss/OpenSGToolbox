/*---------------------------------------------------------------------------*\
 *                          OpenSG ToolBox Game                              *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                   Authors: David Kabala, Eric Langkamp                    *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OSGCaption.h"

#include <boost/bind.hpp>

#include <time.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Caption
A Minimap. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Caption::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Caption::captionSegment(std::string s, Real32 start, Real32 end)
{
    getSegment().push_back(s);
    getStartStamps().push_back(start);
    getEndStamps().push_back(end);
}

void Caption::setupCaption()
{
    beginEditCP(getParentContainer(), InternalWindow::ChildrenFieldMask);
        getParentContainer()->getChildren().clear();
        getParentContainer()->getChildren().push_back(getComponentGenerator()->getCaptionComponent(NullFC,getSegment(getCurrentSegmentIndex())));
    endEditCP(getParentContainer(), InternalWindow::ChildrenFieldMask);
}

void Caption::start(UInt32 SoundChannelID)
{
    _SoundChannelID = SoundChannelID;
    _start = true;
}

void Caption::stop()
{
    _start = false;
    setCurrentSegmentIndex(-1);
    beginEditCP(getParentContainer(), InternalWindow::ChildrenFieldMask);
        getParentContainer()->getChildren().clear();
    endEditCP(getParentContainer(), InternalWindow::ChildrenFieldMask);
    getCaptionDialogSound()->stop(_SoundChannelID);
}

void Caption::pause()
{
    _start = false;
}

void Caption::update(const UpdateEventPtr e)
{
    if(_start)
    {
        if(getCurrentSegmentIndex() == -1)
        {
            if(getStartStamps(0) <= getCaptionDialogSound()->getTime(_SoundChannelID))
            {
                const CaptionEventPtr ce = CaptionEvent::create(CaptionPtr(this),getSystemTime());
                setCurrentSegmentIndex(0);
                produceCaptionStarted(ce);
                produceSegmentActivated(ce);
                _captionEndedCheck = false;
                setupCaption();
                return;
            }
        }
        else if(getEndStamps(getCurrentSegmentIndex()) <= getCaptionDialogSound()->getTime(_SoundChannelID) && getCurrentSegmentIndex() < getSegment().size()-1)
        {
            setCurrentSegmentIndex(getCurrentSegmentIndex()+1);
            produceSegmentActivated(CaptionEvent::create(CaptionPtr(this),getSystemTime()));
            setupCaption();
            return;
        }
        if(_captionEndedCheck)
        {
            return;
        }
        if(getCurrentSegmentIndex() >= getSegment().size()-1)
        {
            produceCaptionEnded(CaptionEvent::create(CaptionPtr(this),getSystemTime()));
            _captionEndedCheck = true;
        }
    }
    return;
}

void Caption::produceSegmentActivated(const CaptionEventPtr e)
{
	CaptionListenerSet Listeners(_CaptionListeners);
    for(CaptionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->segmentActivated(e);
    }
    produceEvent(SegmentActivatedMethodId,e);
}

void Caption::produceCaptionStarted(const CaptionEventPtr e)
{
    CaptionListenerSet Listeners(_CaptionListeners);
    for(CaptionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->captionStarted(e);
    }
    produceEvent(CaptionStartedMethodId,e);
}

void Caption::produceCaptionEnded(const CaptionEventPtr e)
{
    CaptionListenerSet Listeners(_CaptionListeners);
    for(CaptionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->captionEnded(e);
    }
    produceEvent(CaptionEndedMethodId,e);
}

void Caption::actionPreformed(const CaptionEventPtr e)
{
}

EventConnection Caption::addCaptionListener(CaptionListenerPtr Listener)
{
   _CaptionListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Caption::isCaptionListenerAttached, this, Listener),
       boost::bind(&Caption::removeCaptionListener, this, Listener));
}

void Caption::removeCaptionListener(CaptionListenerPtr Listener)
{
   CaptionListenerSetItor EraseIter(_CaptionListeners.find(Listener));
   if(EraseIter != _CaptionListeners.end())
   {
      _CaptionListeners.erase(EraseIter);
   }
}

void Caption::CaptionListener::update(const UpdateEventPtr e)
{
    _Caption->update(e);
}

void Caption::CaptionListener::soundPlayed(const SoundEventPtr e)
{
    _Caption->start(e->getChannel());
}

void Caption::CaptionListener::soundStopped(const SoundEventPtr e)
{
    _Caption->stop();
}

void Caption::CaptionListener::soundPaused(const SoundEventPtr e)
{
    _Caption->pause();
}

void Caption::CaptionListener::soundUnpaused(const SoundEventPtr e)
{
    _Caption->start(e->getChannel());
}

void Caption::CaptionListener::soundLooped(const SoundEventPtr e)
{
    _Caption->stop();
    _Caption->start(e->getChannel());
}

void Caption::CaptionListener::soundEnded(const SoundEventPtr e)
{
    _Caption->stop();
}

void Caption::attachWindowEventProducer(WindowEventProducerPtr TheEventProducer)
{
    TheEventProducer->addUpdateListener(&_CaptionListener);
}



/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Caption::Caption(void) :
    Inherited(),
    _CaptionListener(CaptionPtr(this)),
    _start(false),
    _SoundChannelID(0)
{
}

Caption::Caption(const Caption &source) :
    Inherited(source),
    _CaptionListener(CaptionPtr(this)),
    _start(false),
    _SoundChannelID(0)
{
}

Caption::~Caption(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Caption::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & CaptionDialogSoundFieldMask)
    {
        if(getCaptionDialogSound() != NullFC)
        {
            getCaptionDialogSound()->addSoundListener(&_CaptionListener);
        }
    }
}

void Caption::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Caption NI" << std::endl;
}

OSG_END_NAMESPACE

