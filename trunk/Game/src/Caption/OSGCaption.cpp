/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

void Caption::setCaptionDialog(SoundPtr sound)
{

}

bool Caption::update(double timeStamp)
{
    CaptionEvent e = CaptionEvent(CaptionPtr(this),getSystemTime());
    if(getCurrentSegmentIndex() == -1)
    {
        if(getStartStamps(0) <= timeStamp)
        {
            setCurrentSegmentIndex(0);
            produceSegmentActivated(e);
            produceCaptionStarted(e);
            return true;
        }
    }
    else if(getEndStamps(getCurrentSegmentIndex()) <= timeStamp && getCurrentSegmentIndex() < getSegment().size()-1)
    {
        setCurrentSegmentIndex(getCurrentSegmentIndex()+1);
        return true;
    }
    if(getCurrentSegmentIndex() >= getSegment().size()-1)
    {
        produceCaptionEnded(e);
    }

    return false;
}

void Caption::produceSegmentActivated(const CaptionEvent& e)
{
	CaptionListenerSet Listeners(_CaptionListeners);
    for(CaptionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->segmentActivated(e);
    }
}

void Caption::produceCaptionStarted(const CaptionEvent& e)
{
    CaptionListenerSet Listeners(_CaptionListeners);
    for(CaptionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->captionStarted(e);
    }
}

void Caption::produceCaptionEnded(const CaptionEvent& e)
{
    CaptionListenerSet Listeners(_CaptionListeners);
    for(CaptionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->captionEnded(e);
    }
}

void Caption::actionPreformed(const CaptionEvent& e)
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



/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Caption::Caption(void) :
    Inherited()
{
}

Caption::Caption(const Caption &source) :
    Inherited(source)
{
}

Caption::~Caption(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Caption::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Caption::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Caption NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCAPTIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCAPTIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCAPTIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

