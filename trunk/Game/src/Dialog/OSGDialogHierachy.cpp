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

#include "OSGDialogHierachy.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DialogHierachy
A Dialog. 	 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DialogHierachy::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DialogHierachy::reset()
{
    _mfCurrentDialogResponses.clear();
    setCurrentDialog(NullFC);
}

void DialogHierachy::start()
{
    setCurrentDialog(getRootDialog());
    retrieveReponses();
    getCurrentDialog()->start();
}

DialogPtr DialogHierachy::addDialog(std::string response, Real32 delayResponses, SoundPtr dialogSound, bool interactive, DialogPtr parentDialog)
{

    DialogPtr d = osg::Dialog::create();
    beginEditCP(d, Dialog::ResponseFieldMask | Dialog::ResponsePresentationDelayFieldMask | Dialog::DialogSoundFieldMask | Dialog::InteractiveFieldMask | Dialog::ParentDialogHierachyFieldMask);
        d->setResponse(response);
        d->setResponsePresentationDelay(delayResponses);
        d->setDialogSound(dialogSound);
        d->setInteractive(interactive);
        d->setParentDialogHierachy(DialogHierachyPtr(this));
    endEditCP(d, Dialog::ResponseFieldMask | Dialog::ResponsePresentationDelayFieldMask | Dialog::DialogSoundFieldMask | Dialog::InteractiveFieldMask | Dialog::ParentDialogHierachyFieldMask);

    d->addDialogListener(&_DialogHierachyListener);

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

void DialogHierachy::retrieveReponses()
{
    _mfCurrentDialogResponses = getCurrentDialog()->getResponses();
}

void DialogHierachy::DialogHierachyListener::started(const DialogEvent& e)
{

}

void DialogHierachy::DialogHierachyListener::ended(const DialogEvent& e)
{
}

void DialogHierachy::DialogHierachyListener::responseSelected(const DialogEvent& e)
{
    DialogEvent Pe = DialogEvent(_DialogHierachy->getCurrentDialog(),getSystemTime());
    _DialogHierachy->getCurrentDialog()->produceEnded(Pe);
    _DialogHierachy->getCurrentDialog()->_displayed = false;

    _DialogHierachy->setCurrentDialog(DialogPtr::dcast(e.getSource()));
    _DialogHierachy->retrieveReponses();
    _DialogHierachy->getCurrentDialog()->start();
}

void DialogHierachy::DialogHierachyListener::responsesReady(const DialogEvent& e)
{
}

void DialogHierachy::DialogHierachyListener::terminated(const DialogEvent& e)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DialogHierachy::DialogHierachy(void) :
    Inherited(),
    _DialogHierachyListener(DialogHierachyPtr(this))
{
}

DialogHierachy::DialogHierachy(const DialogHierachy &source) :
    Inherited(source),
    _DialogHierachyListener(DialogHierachyPtr(this))
{
}

DialogHierachy::~DialogHierachy(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DialogHierachy::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DialogHierachy::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DialogHierachy NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDIALOGHIERACHYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDIALOGHIERACHYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDIALOGHIERACHYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

