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

void DialogHierarchy::DialogHierarchyListener::started(const DialogEvent& e)
{

}

void DialogHierarchy::DialogHierarchyListener::ended(const DialogEvent& e)
{
}

void DialogHierarchy::DialogHierarchyListener::responseSelected(const DialogEvent& e)
{
    DialogEvent Pe = DialogEvent(_DialogHierarchy->getCurrentDialog(),getSystemTime());
    _DialogHierarchy->getCurrentDialog()->produceEnded(Pe);
    _DialogHierarchy->getCurrentDialog()->_displayed = false;

    _DialogHierarchy->setCurrentDialog(DialogPtr::dcast(e.getSource()));
    _DialogHierarchy->retrieveReponses();
    _DialogHierarchy->getCurrentDialog()->start();
}

void DialogHierarchy::DialogHierarchyListener::responsesReady(const DialogEvent& e)
{
}

void DialogHierarchy::DialogHierarchyListener::terminated(const DialogEvent& e)
{
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
    static Char8 cvsid_hpp       [] = OSGDIALOGHIERARCHYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDIALOGHIERARCHYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDIALOGHIERARCHYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

