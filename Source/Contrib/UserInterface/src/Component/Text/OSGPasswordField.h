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

#ifndef _OSGPASSWORDFIELD_H_
#define _OSGPASSWORDFIELD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPasswordFieldBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PasswordField class. See \ref
           PageContribUserInterfacePasswordField for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING PasswordField : public PasswordFieldBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PasswordFieldBase Inherited;
    typedef PasswordField     Self;

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

	virtual void mouseClicked(MouseEventDetails* const e);

	virtual std::string getDrawnText(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PasswordFieldBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PasswordField(void);
    PasswordField(const PasswordField &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PasswordField(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PasswordFieldBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PasswordField &source);
};

typedef PasswordField *PasswordFieldP;

OSG_END_NAMESPACE

#include "OSGPasswordFieldBase.inl"
#include "OSGPasswordField.inl"

#endif /* _OSGPASSWORDFIELD_H_ */
