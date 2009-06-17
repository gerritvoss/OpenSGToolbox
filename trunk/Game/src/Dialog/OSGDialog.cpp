/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OSGDialog.h"

#include <boost/bind.hpp>

#include <time.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Dialog
A Dialog. 	 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Dialog::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void Dialog::update(const UpdateEvent& uE)
{
    if(!_displayed && getResponsePresentationDelay() > 0.0 && getDialogSound()->getTime(_dialogSoundChannelID) > getResponsePresentationDelay() && getInteractive())
    {
        DialogEvent e = DialogEvent(DialogPtr(this),getSystemTime());
        produceResponsesReady(e);
    }
}

void Dialog::start()
{
    DialogEvent e = DialogEvent(DialogPtr(this),getSystemTime());
    produceStarted(e);

    if(getDialogSound() != NullFC)
    {
        _dialogSoundChannelID = getDialogSound()->play();
    }

    if(!_displayed && getInteractive() && getResponsePresentationDelay() == 0.0)
    {
        produceResponsesReady(e);
    }

    if(!_displayed && !getInteractive() && getDialogSound() == NullFC && !getResponses().isEmpty())
    {
        _displayed = true;
        getResponses(0)->selectResponse();
    }
    if(getDialogSound() == NullFC && getResponses().isEmpty())
    {
        produceTerminated(e);
    }
}
void Dialog::terminate()
{
    DialogEvent e = DialogEvent(DialogPtr(this),getSystemTime());
    produceTerminated(e);
}
void Dialog::selectResponse()
{
    DialogEvent e = DialogEvent(DialogPtr(this),getSystemTime());
    produceResponseSelected(e);
}
void Dialog::pause()
{
    getDialogSound()->pauseToggle(_dialogSoundChannelID);
}
void Dialog::unpause()
{
    getDialogSound()->pauseToggle(_dialogSoundChannelID);
}

void Dialog::produceStarted(const DialogEvent& e)
{
    DialogListenerSet Listeners(_DialogListeners);
    for(DialogListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->started(e);
    }
}
void Dialog::produceEnded(const DialogEvent& e)
{
    DialogListenerSet Listeners(_DialogListeners);
    for(DialogListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->ended(e);
    }
}
void Dialog::produceResponseSelected(const DialogEvent& e)
{
    DialogListenerSet Listeners(_DialogListeners);
    for(DialogListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->responseSelected(e);
    }
}
void Dialog::produceResponsesReady(const DialogEvent& e)
{
    _displayed = true;
    DialogListenerSet Listeners(_DialogListeners);
    for(DialogListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->responsesReady(e);
    }
}
void Dialog::produceTerminated(const DialogEvent& e)
{
    DialogListenerSet Listeners(_DialogListeners);
    for(DialogListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->terminated(e);
    }
}

EventConnection Dialog::addDialogListener(DialogListenerPtr Listener)
{
   _DialogListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Dialog::isDialogListenerAttached, this, Listener),
       boost::bind(&Dialog::removeDialogListener, this, Listener));
}

void Dialog::removeDialogListener(DialogListenerPtr Listener)
{
   DialogListenerSetItor EraseIter(_DialogListeners.find(Listener));
   if(EraseIter != _DialogListeners.end())
   {
      _DialogListeners.erase(EraseIter);
   }
}

void Dialog::DialogListener::update(const UpdateEvent& e)
{
    _Dialog->update(e);
}

void Dialog::DialogListener::soundPlayed(const SoundEvent& e)
{
}

void Dialog::DialogListener::soundStopped(const SoundEvent& e)
{
}

void Dialog::DialogListener::soundPaused(const SoundEvent& e)
{
}

void Dialog::DialogListener::soundUnpaused(const SoundEvent& e)
{
}

void Dialog::DialogListener::soundLooped(const SoundEvent& e)
{
}

void Dialog::DialogListener::soundEnded(const SoundEvent& e)
{
    DialogEvent De = DialogEvent::DialogEvent(DialogPtr(_Dialog),getSystemTime());
    if(!_Dialog->_displayed && _Dialog->getInteractive() && _Dialog->getResponsePresentationDelay() < 0.0)
    {
        _Dialog->produceResponsesReady(De);
    }
    if(!_Dialog->getInteractive())
    {
        _Dialog->produceResponseSelected(De);
    }
    if(_Dialog->getResponses().isEmpty())
    {
        _Dialog->produceTerminated(De);
    }

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Dialog::Dialog(void) :
    Inherited(),
    _DialogListener(DialogPtr(this)),
    _displayed(false)
{
}

Dialog::Dialog(const Dialog &source) :
    Inherited(source),
    _DialogListener(DialogPtr(this)),
    _displayed(false)
{
}

Dialog::~Dialog(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Dialog::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Dialog::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Dialog NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDIALOGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDIALOGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDIALOGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

