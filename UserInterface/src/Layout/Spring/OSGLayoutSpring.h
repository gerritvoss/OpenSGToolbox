/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGLayoutSpringBase.h"
#include "Layout/OSGSpringLayoutFields.h"
#include "Component/OSGComponentFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief LayoutSpring class. See \ref 
           PageUserInterfaceLayoutSpring for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING LayoutSpring : public LayoutSpringBase
{
  private:

    typedef LayoutSpringBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    static Real32 VALUE_NOT_SET;

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

    //Returns the maximum value of this LayoutSpringPtr.
    virtual Real32 getMinimumValue(void) const = 0;

    //Returns the Preferred value of this LayoutSpringPtr.
    virtual Real32 getPreferredValue(void) const = 0;

    //Returns the minimum value of this LayoutSpringPtr.
    virtual Real32 getMaximumValue(void) const = 0;

    //Returns the current value of this LayoutSpringPtr.
    virtual Real32 getValue(void) const = 0;

    //Sets the current value of this LayoutSpringPtr.
    virtual void setValue(const Real32& value) = 0;

    Real32 getStrain(void) const;

    void setStrain(Real32 strain);

    virtual bool isCyclic(SpringLayoutPtr l) const;

    //Returns a strut -- a spring whose minimum, preferred, and maximum values each have the value pref.
    static LayoutSpringPtr constant(const Real32& pref);

    //Returns a spring whose minimum, preferred, and maximum values have the values: min, pref, and max respectively.
    static LayoutSpringPtr constant(const Real32& min, const Real32& pref, const Real32& max);

    //Returns -s: a spring running in the opposite direction to s.
    static LayoutSpringPtr minus(LayoutSpringPtr s);

    //Returns s1+s2: a spring representing s1 and s2  in series.
    static LayoutSpringPtr sum(LayoutSpringPtr s1, LayoutSpringPtr s2);

    //Returns max(s1, s2): a spring whose value is always greater than (or equal to) the values of both s1 and s2.
    static LayoutSpringPtr max(LayoutSpringPtr s1, LayoutSpringPtr s2);

    
    static LayoutSpringPtr difference(LayoutSpringPtr s1, LayoutSpringPtr s2);

    static LayoutSpringPtr scale(LayoutSpringPtr s, const Real32& factor);

    static LayoutSpringPtr width(ComponentPtr c);

    static LayoutSpringPtr height(ComponentPtr c);

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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class LayoutSpringBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const LayoutSpring &source);
    
    Real32 range(bool contract) const;
};

typedef LayoutSpring *LayoutSpringP;

OSG_END_NAMESPACE

#include "OSGLayoutSpringBase.inl"
#include "OSGLayoutSpring.inl"

#define OSGLAYOUTSPRING_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGLAYOUTSPRING_H_ */
