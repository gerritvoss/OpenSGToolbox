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
#ifndef _OSGRADIOBUTTONGROUP_H_
#define _OSGRADIOBUTTONGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <vector>
#include "Component/OSGRadioButtonFields.h"
#include "Event/OSGButtonSelectedListener.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING RadioButtonGroup : public ButtonSelectedListener
{
  /*=========================  PUBLIC  ===============================*/
public:
    void addButton(RadioButtonPtr Button);
    void removeButton(RadioButtonPtr Button);
    void removeButton(UInt32 Index);
    UInt32 getButtonCount(void) const;

    bool isSelected(const RadioButtonPtr Button) const;
    void setSelected(RadioButtonPtr Button, bool SelectedValue);
	virtual void buttonSelected(const ButtonSelectedEvent& e);
   virtual void buttonDeselected(const ButtonSelectedEvent& e);

    RadioButtonGroup(void);
private:
    std::vector<RadioButtonPtr> _Buttons;
    RadioButtonPtr _SelectedButton;
};

OSG_END_NAMESPACE

#include "OSGRadioButtonGroup.inl"

#endif /* _OSGRADIOBUTTONGROUP_H_ */
