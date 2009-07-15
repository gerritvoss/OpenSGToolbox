/*---------------------------------------------------------------------------*\
 *                          OpenSG Animation                                 *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, freeman                                          *
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

#ifndef _ANIMATIONACTION_H_
#define _ANIMATIONACTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/Toolbox/OSGAction.h>

#include <OpenSG/Toolbox/OSGActionType.h>

#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

class OSG_ANIMATIONLIB_DLLMAPPING AnimationAction : public Action 
{
    /*=========================  PUBLIC  ===============================*/
  public:
    virtual void triggerAction(void);
    
    virtual const ActionType &getType(void);
    
  protected:
    AnimationAction(void);
};

typedef boost::shared_ptr<AnimationAction> AnimationActionPtr;

OSG_END_NAMESPACE

#endif /* _ANIMATIONACTION_H_ */


