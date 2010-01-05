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
#ifndef _OSGINPUTSETTINGS_H_
#define _OSGINPUTSETTINGS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEM_DLLMAPPING InputSettings
{
   /*=========================  PUBLIC  ===============================*/
public:
   static InputSettings* the(void);

   UInt32 getUnitsPerMouseScrollClick(void) const;
   Real32 getMultipleClickRate(void) const;
   Real32 getMultipleClickMouseDriftAllowance(void) const;

   void setUnitsPerMouseScrollClick(const UInt32 Ratio);
   void setMultipleClickRate(const Real32 Rate);
   void setMultipleClickMouseDriftAllowance(const Real32 Allowance);
private:
   static InputSettings* _the;

   UInt32      _UnitsPerMouseScrollClick;
   Real32      _MultipleClickRate;
   Real32      _MultipleClickMouseDriftAllowance;

   InputSettings(void);
    
};

OSG_END_NAMESPACE

#include "OSGInputSettings.inl"

#endif /* _OSGINPUTSETTINGS_H_ */


