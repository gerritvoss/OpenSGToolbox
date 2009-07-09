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

#ifndef _OSGACTION_TYPE_H_
#define _OSGACTION_TYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <OpenSG/OSGTypeBase.h>

OSG_BEGIN_NAMESPACE

class OSG_TOOLBOXLIB_DLLMAPPING ActionType : public TypeBase
{
    /*==========================  PUBLIC  =================================*/

  public :
    UInt32 getActionId(void) const;

    /*---------------------------------------------------------------------*/
    ActionType(const Char8  *szName, 
             const Char8  *szParentName,
             const UInt32  uiNameSpace = 0);
    
    /*---------------------------------------------------------------------*/
    virtual ~ActionType(void);

    /*---------------------------------------------------------------------*/
    bool operator ==(const ActionType &other) const;
    bool operator !=(const ActionType &other) const;

    /*=========================  PROTECTED  ===============================*/

  protected:
    UInt32 _uiActionTypeId;
    UInt32 _uiActionTypeRootId;

    typedef TypeBase Inherited;

    ActionType(const ActionType &source);

    /*==========================  PRIVATE  ================================*/
  private:

    void operator =(const ActionType &source);
};

typedef ActionType *ActionTypeP;

OSG_END_NAMESPACE
        
#include "OSGActionType.inl"

#endif /* _OSGACTION_TYPE_H_ */


