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

#ifndef _OSGRADIOBUTTON_H_
#define _OSGRADIOBUTTON_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGRadioButtonBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief RadioButton class. See \ref
           PageContribUserInterfaceRadioButton for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING RadioButton : public RadioButtonBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef RadioButtonBase Inherited;
    typedef RadioButton     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in RadioButtonBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RadioButton(void);
    RadioButton(const RadioButton &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RadioButton(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual void actionPreformed(ActionEventDetails* const e);
    virtual UIDrawObjectCanvas* getDrawnDrawObject(void) const;
    virtual UIDrawObjectCanvas* getBaseDrawObject(void) const;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RadioButtonBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RadioButton &source);
};

typedef RadioButton *RadioButtonP;

OSG_END_NAMESPACE

#include "OSGRadioButtonBase.inl"
#include "OSGRadioButton.inl"

#endif /* _OSGRADIOBUTTON_H_ */
