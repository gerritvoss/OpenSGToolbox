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

#ifndef _OSGCHECKBOXBUTTON_H_
#define _OSGCHECKBOXBUTTON_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCheckboxButtonBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CheckboxButton class. See \ref
           PageContribUserInterfaceCheckboxButton for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CheckboxButton : public CheckboxButtonBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CheckboxButtonBase Inherited;
    typedef CheckboxButton     Self;

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

    // Variables should all be in CheckboxButtonBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CheckboxButton(void);
    CheckboxButton(const CheckboxButton &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CheckboxButton(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual UIDrawObjectCanvas* getDrawnDrawObject(void) const;        
    virtual UIDrawObjectCanvas* getBaseDrawObject(void) const;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CheckboxButtonBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CheckboxButton &source);
};

typedef CheckboxButton *CheckboxButtonP;

OSG_END_NAMESPACE

#include "OSGCheckboxButtonBase.inl"
#include "OSGCheckboxButton.inl"

#endif /* _OSGCHECKBOXBUTTON_H_ */
