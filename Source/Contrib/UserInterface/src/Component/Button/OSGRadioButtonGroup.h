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

#ifndef _OSGRADIOBUTTONGROUP_H_
#define _OSGRADIOBUTTONGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGRadioButtonGroupBase.h"
#include "OSGButtonSelectedEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief RadioButtonGroup class. See \ref
           PageContribUserInterfaceRadioButtonGroup for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING RadioButtonGroup : public RadioButtonGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef RadioButtonGroupBase Inherited;
    typedef RadioButtonGroup     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    void addButton(RadioButton* const Button);
    void removeButton(RadioButton* const Button);
    void removeButton(UInt32 Index);
    UInt32 getButtonCount(void) const;

    bool isSelected(const RadioButton* const Button) const;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	void handleButtonSelected(ButtonSelectedEventDetails* const e);
    void handleButtonDeselected(ButtonSelectedEventDetails* const e);

    std::vector<boost::signals2::connection> _ButtonConnections;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RadioButtonGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RadioButtonGroup &source);
};

typedef RadioButtonGroup *RadioButtonGroupP;

OSG_END_NAMESPACE

#include "OSGRadioButton.h"

#include "OSGRadioButtonGroupBase.inl"
#include "OSGRadioButtonGroup.inl"

#endif /* _OSGRADIOBUTTONGROUP_H_ */
