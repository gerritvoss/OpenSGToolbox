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

#ifndef _OSGLAYOUTSPRING_H_
#define _OSGLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLayoutSpringBase.h"
#include "OSGSpringLayoutFields.h"
#include "OSGComponentFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief LayoutSpring class. See \ref
           PageContribUserInterfaceLayoutSpring for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING LayoutSpring : public LayoutSpringBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    static Real32 VALUE_NOT_SET;

    typedef LayoutSpringBase Inherited;
    typedef LayoutSpring     Self;

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

    //Returns the maximum value of this LayoutSpringRefPtr.
    virtual Real32 getMinimumValue(void) const = 0;

    //Returns the Preferred value of this LayoutSpringRefPtr.
    virtual Real32 getPreferredValue(void) const = 0;

    //Returns the minimum value of this LayoutSpringRefPtr.
    virtual Real32 getMaximumValue(void) const = 0;

    //Returns the current value of this LayoutSpringRefPtr.
    virtual Real32 getValue(void) const = 0;

    //Sets the current value of this LayoutSpringRefPtr.
    virtual void setValue(const Real32& value) = 0;

    Real32 getStrain(void) const;

    void setStrain(Real32 strain);

    virtual bool isCyclic(const SpringLayout* l) const;

    //Returns a strut -- a spring whose minimum, preferred, and maximum values each have the value pref.
    static LayoutSpringRefPtr constant(const Real32& pref);

    //Returns a spring whose minimum, preferred, and maximum values have the values: min, pref, and max respectively.
    static LayoutSpringRefPtr constant(const Real32& min, const Real32& pref, const Real32& max);

    //Returns -s: a spring running in the opposite direction to s.
    static LayoutSpringRefPtr minus(LayoutSpringRefPtr s);

    //Returns s1+s2: a spring representing s1 and s2  in series.
    static LayoutSpringRefPtr sum(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2);

    //Returns max(s1, s2): a spring whose value is always greater than (or equal to) the values of both s1 and s2.
    static LayoutSpringRefPtr max(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2);

    
    static LayoutSpringRefPtr difference(LayoutSpringRefPtr s1, LayoutSpringRefPtr s2);

    static LayoutSpringRefPtr scale(LayoutSpringRefPtr s, const Real32& factor);

    static LayoutSpringRefPtr width(Component* const c);

    static LayoutSpringRefPtr height(Component* const c);
    static LayoutSpringRefPtr requestedWidth(Component* const c);

    static LayoutSpringRefPtr requestedHeight(Component* const c);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LayoutSpringBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LayoutSpring(void);
    LayoutSpring(const LayoutSpring &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LayoutSpring(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LayoutSpringBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LayoutSpring &source);
    
    Real32 range(bool contract) const;
};

typedef LayoutSpring *LayoutSpringP;

OSG_END_NAMESPACE

#include "OSGLayoutSpringBase.inl"
#include "OSGLayoutSpring.inl"

#endif /* _OSGLAYOUTSPRING_H_ */
