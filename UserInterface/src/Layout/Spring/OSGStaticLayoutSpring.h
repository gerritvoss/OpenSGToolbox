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

#ifndef _OSGSTATICLAYOUTSPRING_H_
#define _OSGSTATICLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGStaticLayoutSpringBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief StaticLayoutSpring class. See \ref 
           PageUserInterfaceStaticLayoutSpring for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING StaticLayoutSpring : public StaticLayoutSpringBase
{
  private:

    typedef StaticLayoutSpringBase Inherited;

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

    virtual void dump(      UInt32     uiIndent, 
                      const BitVector  bvFlags ) const;

    /*! \}                                                                 */
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  StaticLayoutSpringPtr      create          (const Int32& Preferred); 
    static  StaticLayoutSpringPtr      create          (const Int32& Minimum, const Int32& Preferred, const Int32& Maximum); 
    
    /*! \}                                                                 */

    //Returns the maximum value of this LayoutSpringPtr.
    virtual Int32 getMinimumValue(void) const;

    //Returns the Preferred value of this LayoutSpringPtr.
    virtual Int32 getPreferredValue(void) const;

    //Returns the minimum value of this LayoutSpringPtr.
    virtual Int32 getMaximumValue(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in StaticLayoutSpringBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StaticLayoutSpring(void);
    StaticLayoutSpring(const StaticLayoutSpring &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StaticLayoutSpring(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class StaticLayoutSpringBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const StaticLayoutSpring &source);
};

typedef StaticLayoutSpring *StaticLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGStaticLayoutSpringBase.inl"
#include "OSGStaticLayoutSpring.inl"

#define OSGSTATICLAYOUTSPRING_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSTATICLAYOUTSPRING_H_ */
