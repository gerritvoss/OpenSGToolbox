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

#include "OSGDialogHierarchy.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DialogHierarchy
A Dialog. 	 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DialogHierarchy::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DialogHierarchy::reset()
{
    _mfCurrentDialogResponses.clear();
    setCurrentDialog(NullFC);
}

void DialogHierarchy::start()
{
    setCurrentDialog(getRootDialog());
    retrieveReponses();
    getCurrentDialog()->start();
}

void DialogHierarchy::AddXMLDialog(DialogPtr dialogNode)
{
    dialogNode->addDialogListener(&_DialogHierarchyListener);
}

DialogPtr DialogHierarchy::addDialog(std::string response, Real32 delayResponses, SoundPtr dialogSound, bool interactive, DialogPtr parentDialog)
{
    DialogPtr d = osg::Dialog::create();
    beginEditCP(d, Dialog::ResponseFieldMask | Dialog::ResponsePresentationDelayFieldMask | Dialog::DialogSoundFieldMask | Dialog::InteractiveFieldMask | Dialog::ParentDialogHierarchyFieldMask);
        d->setResponse(response);
        d->setResponsePresentationDelay(delayResponses);
        d->setDialogSound(dialogSound);
        d->setInteractive(interactive);
        d->setParentDialogHierarchy(DialogHierarchyPtr(this));
    endEditCP(d, Dialog::ResponseFieldMask | Dialog::ResponsePresentationDelayFieldMask | Dialog::DialogSoundFieldMask | Dialog::InteractiveFieldMask | Dialog::ParentDialogHierarchyFieldMask);

    d->addDialogListener(&_DialogHierarchyListener);

    if(parentDialog != NullFC)
    {
        beginEditCP(parentDialog, Dialog::ResponsesFieldMask);
            parentDialog->getResponses().push_back(d);
        endEditCP(parentDialog, Dialog::ResponsesFieldMask);
    }

    if(getRootDialog() == NullFC)
    {
        setRootDialog(d);
    }
    return d;
}

void DialogHierarchy::retrieveReponses()
{
    _mfCurrentDialogResponses = getCurrentDialog()->getResponses();
}

void DialogHierarchy::produceNewDialogStarted(const DialogHierarchyEventPtr e)
{
    DialogHierarchyListenerSet Listeners(_DialogHierarchyListeners);
    for(DialogHierarchyListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->newDialogStarted(e);
    }
    _Producer.produceEvent(NewDialogStartedMethodId,e);
}
void DialogHierarchy::produceDialogEnded(const DialogHierarchyEventPtr e)
{
    DialogHierarchyListenerSet Listeners(_DialogHierarchyListeners);
    for(DialogHierarchyListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->dialogEnded(e);
    }
    _Producer.produceEvent(DialogEndedMethodId,e);
}
void DialogHierarchy::produceDialogResponseSelected(const DialogHierarchyEventPtr e)
{
    DialogHierarchyListenerSet Listeners(_DialogHierarchyListeners);
    for(DialogHierarchyListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->dialogResponseSelected(e);
    }
    _Producer.produceEvent(DialogResponseSelectedMethodId,e);
}
void DialogHierarchy::produceDialogResponsesReady(const DialogHierarchyEventPtr e)
{
    DialogHierarchyListenerSet Listeners(_DialogHierarchyListeners);
    for(DialogHierarchyListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->dialogResponsesReady(e);
    }
    _Producer.produceEvent(DialogResponsesReadyMethodId,e);
}
void DialogHierarchy::produceTerminated(const DialogHierarchyEventPtr e)
{
    DialogHierarchyListenerSet Listeners(_DialogHierarchyListeners);
    for(DialogHierarchyListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->terminated(e);
    }
    _Producer.produceEvent(TerminatedMethodId,e);
}

void DialogHierarchy::DialogHierarchyListener::started(const DialogEventPtr e)
{
    _DialogHierarchy->produceNewDialogStarted(DialogHierarchyEvent::create(_DialogHierarchy,getSystemTime()));
}

void DialogHierarchy::DialogHierarchyListener::ended(const DialogEventPtr e)
{
    DialogPtr::dcast(e->getSource())->_displayed = false;
    _DialogHierarchy->produceDialogEnded(DialogHierarchyEvent::create(_DialogHierarchy,getSystemTime()));
}

void DialogHierarchy::DialogHierarchyListener::responseSelected(const DialogEventPtr e)
{
    _DialogHierarchy->produceDialogResponseSelected(DialogHierarchyEvent::create(_DialogHierarchy,getSystemTime()));

    const DialogEventPtr Pe = DialogEvent::create(_DialogHierarchy->getCurrentDialog(),getSystemTime());
    _DialogHierarchy->getCurrentDialog()->produceEnded(Pe);

    _DialogHierarchy->setCurrentDialog(DialogPtr::dcast(e->getSource()));
    _DialogHierarchy->retrieveReponses();
    _DialogHierarchy->getCurrentDialog()->start();
}

void DialogHierarchy::DialogHierarchyListener::responsesReady(const DialogEventPtr e)
{
    _DialogHierarchy->produceDialogResponsesReady(DialogHierarchyEvent::create(_DialogHierarchy,getSystemTime()));
}

void DialogHierarchy::DialogHierarchyListener::terminated(const DialogEventPtr e)
{
    _DialogHierarchy->produceTerminated(DialogHierarchyEvent::create(_DialogHierarchy,getSystemTime()));
}

EventConnection DialogHierarchy::addDialogHierarchyListener(DialogHierarchyListenerPtr Listener)
{
   _DialogHierarchyListeners.insert(Listener);
   return EventConnection(
       boost::bind(&DialogHierarchy::isDialogHierarchyListenerAttached, this, Listener),
       boost::bind(&DialogHierarchy::removeDialogHierarchyListener, this, Listener));
}

void DialogHierarchy::removeDialogHierarchyListener(DialogHierarchyListenerPtr Listener)
{
   DialogHierarchyListenerSetItor EraseIter(_DialogHierarchyListeners.find(Listener));
   if(EraseIter != _DialogHierarchyListeners.end())
   {
      _DialogHierarchyListeners.erase(EraseIter);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DialogHierarchy::DialogHierarchy(void) :
    Inherited(),
    _DialogHierarchyListener(DialogHierarchyPtr(this))
{
}

DialogHierarchy::DialogHierarchy(const DialogHierarchy &source) :
    Inherited(source),
    _DialogHierarchyListener(DialogHierarchyPtr(this))
{
}

DialogHierarchy::~DialogHierarchy(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DialogHierarchy::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DialogHierarchy::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DialogHierarchy NI" << std::endl;
}

OSG_END_NAMESPACE

