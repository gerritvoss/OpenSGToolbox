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

#ifndef _OSGPROXYLAYOUTSPRING_H_
#define _OSGPROXYLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGProxyLayoutSpringBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ProxyLayoutSpring class. See \ref 
           PageUserInterfaceProxyLayoutSpring for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ProxyLayoutSpring : public ProxyLayoutSpringBase
{
  private:

    typedef ProxyLayoutSpringBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  ProxyLayoutSpringPtr create (const UInt32& Edge, ComponentPtr TheComponent, SpringLayoutPtr TheLayout); 
    
    /*! \}                                                                 */

    //Returns the maximum value of this LayoutSpringPtr.
    virtual Int32 getMinimumValue(void) const;

    //Returns the Preferred value of this LayoutSpringPtr.
    virtual Int32 getPreferredValue(void) const;

    //Returns the minimum value of this LayoutSpringPtr.
    virtual Int32 getMaximumValue(void) const;

    //Returns the current value of this LayoutSpringPtr.
    virtual Int32 getValue(void) const;

    //Sets the current value of this LayoutSpringPtr.
    virtual void setValue(const Int32& value);
    
    virtual bool isCyclic(SpringLayoutPtr l) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ProxyLayoutSpringBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ProxyLayoutSpring(void);
    ProxyLayoutSpring(const ProxyLayoutSpring &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ProxyLayoutSpring(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ProxyLayoutSpringBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ProxyLayoutSpring &source);
    
    LayoutSpringPtr getConstraint(void) const;
};

typedef ProxyLayoutSpring *ProxyLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGProxyLayoutSpringBase.inl"
#include "OSGProxyLayoutSpring.inl"

#define OSGPROXYLAYOUTSPRING_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPROXYLAYOUTSPRING_H_ */
