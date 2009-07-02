/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSGMOUSEMOTIONADAPTER_H_
#define _OSGMOUSEMOTIONADAPTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "OSGMouseMotionListener.h"

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING MouseMotionAdapter : public MouseMotionListener
{
    /*=========================  PUBLIC  ===============================*/
public:
    virtual void mouseMoved(const MouseEvent& e);
    virtual void mouseDragged(const MouseEvent& e);
};

typedef MouseMotionAdapter* MouseMotionAdapterPtr;

OSG_END_NAMESPACE

#endif /* _OSGMOUSEMOTIONADAPTER_H_ */


