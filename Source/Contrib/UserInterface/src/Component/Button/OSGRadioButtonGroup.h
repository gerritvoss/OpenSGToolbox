/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#ifndef _OSGRADIOBUTTONGROUP_H_
#define _OSGRADIOBUTTONGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGRadioButtonGroupBase.h"
#include "Event/OSGButtonSelectedListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief RadioButtonGroup class. See \ref 
           PageUserInterfaceRadioButtonGroup for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING RadioButtonGroup : public RadioButtonGroupBase, public ButtonSelectedListener
{
  private:

    typedef RadioButtonGroupBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    void addButton(RadioButtonPtr Button);
    void removeButton(RadioButtonPtr Button);
    void removeButton(UInt32 Index);
    UInt32 getButtonCount(void) const;

    bool isSelected(const RadioButtonPtr Button) const;
	virtual void buttonSelected(const ButtonSelectedEventPtr e);
    virtual void buttonDeselected(const ButtonSelectedEventPtr e);

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in RadioButtonGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RadioButtonGroup(void);
    RadioButtonGroup(const RadioButtonGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RadioButtonGroup(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class RadioButtonGroupBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const RadioButtonGroup &source);
};

typedef RadioButtonGroup *RadioButtonGroupP;

OSG_END_NAMESPACE

#include "OSGRadioButtonGroupBase.inl"
#include "OSGRadioButtonGroup.inl"

#endif /* _OSGRADIOBUTTONGROUP_H_ */
