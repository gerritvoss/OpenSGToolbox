/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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
#ifndef _OSGVIDEOEVENT_H_
#define _OSGVIDEOEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"

#include <OpenSG/Input/OSGEvent.h>

#include "OSGVideoWrapperFields.h"

OSG_BEGIN_NAMESPACE

class OSG_VIDEOLIB_DLLMAPPING VideoEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    VideoWrapperPtr getSourceVideo(void) const;
    
    VideoEvent(FieldContainerPtr Source, Time TimeStamp, VideoWrapperPtr SourceVideo);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
    
  protected:
    VideoWrapperPtr _SourceVideo;
  
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGVideoEvent.inl"

#endif /* _OSGVIDEOEVENT_H_ */
