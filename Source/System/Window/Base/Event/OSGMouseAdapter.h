/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGMOUSEADAPTER_H_
#define _OSGMOUSEADAPTER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSystemDef.h"

#include "OSGMouseListener.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING MouseAdapter : public MouseListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseClicked(const MouseEventRefPtr e);
    virtual void mouseEntered(const MouseEventRefPtr e);
    virtual void mouseExited(const MouseEventRefPtr e);
    virtual void mousePressed(const MouseEventRefPtr e);
    virtual void mouseReleased(const MouseEventRefPtr e);
};

typedef MouseAdapter* MouseAdapterPtr;

OSG_END_NAMESPACE

#endif /* _OSGMOUSEADAPTER_H_ */


