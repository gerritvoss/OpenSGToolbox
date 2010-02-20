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

#ifndef _OSGDEFAULTLOOKANDFEEL_H_
#define _OSGDEFAULTLOOKANDFEEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDefaultLookAndFeelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultLookAndFeel class. See \ref
           PageContribUserInterfaceDefaultLookAndFeel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DefaultLookAndFeel : public DefaultLookAndFeelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DefaultLookAndFeelBase Inherited;
    typedef DefaultLookAndFeel     Self;

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
	
	virtual void init(void);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DefaultLookAndFeelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultLookAndFeel(void);
    DefaultLookAndFeel(const DefaultLookAndFeel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultLookAndFeel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DefaultLookAndFeelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DefaultLookAndFeel &source);
};

typedef DefaultLookAndFeel *DefaultLookAndFeelP;

OSG_END_NAMESPACE

#include "OSGDefaultLookAndFeelBase.inl"
#include "OSGDefaultLookAndFeel.inl"

#endif /* _OSGDEFAULTLOOKANDFEEL_H_ */
