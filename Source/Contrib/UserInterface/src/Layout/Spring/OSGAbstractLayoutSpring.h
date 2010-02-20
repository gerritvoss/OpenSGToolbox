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

#ifndef _OSGABSTRACTLAYOUTSPRING_H_
#define _OSGABSTRACTLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractLayoutSpringBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractLayoutSpring class. See \ref
           PageContribUserInterfaceAbstractLayoutSpring for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractLayoutSpring : public AbstractLayoutSpringBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractLayoutSpringBase Inherited;
    typedef AbstractLayoutSpring     Self;

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
    
    //Returns the current value of this LayoutSpringRefPtr.
    virtual Real32 getValue(void) const;

    //Sets the current value of this LayoutSpringRefPtr.
    virtual void setValue(const Real32& value);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractLayoutSpringBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractLayoutSpring(void);
    AbstractLayoutSpring(const AbstractLayoutSpring &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractLayoutSpring(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
    virtual void clear(void);
    virtual void setNonClearValue(const Real32& value);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractLayoutSpringBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractLayoutSpring &source);
};

typedef AbstractLayoutSpring *AbstractLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGAbstractLayoutSpringBase.inl"
#include "OSGAbstractLayoutSpring.inl"

#endif /* _OSGABSTRACTLAYOUTSPRING_H_ */
