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

#ifndef _OSGCOMPONENTWIDTHLAYOUTSPRING_H_
#define _OSGCOMPONENTWIDTHLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComponentWidthLayoutSpringBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComponentWidthLayoutSpring class. See \ref 
           PageUserInterfaceComponentWidthLayoutSpring for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ComponentWidthLayoutSpring : public ComponentWidthLayoutSpringBase
{
  private:

    typedef ComponentWidthLayoutSpringBase Inherited;

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

    static  ComponentWidthLayoutSpringPtr      create          (ComponentPtr TheComponent); 
    
    /*! \}                                                                 */

    //Returns the maximum value of this LayoutSpringPtr.
    virtual Int32 getMinimumValue(void) const;

    //Returns the Preferred value of this LayoutSpringPtr.
    virtual Int32 getPreferredValue(void) const;

    //Returns the minimum value of this LayoutSpringPtr.
    virtual Int32 getMaximumValue(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ComponentWidthLayoutSpringBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComponentWidthLayoutSpring(void);
    ComponentWidthLayoutSpring(const ComponentWidthLayoutSpring &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComponentWidthLayoutSpring(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComponentWidthLayoutSpringBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ComponentWidthLayoutSpring &source);
};

typedef ComponentWidthLayoutSpring *ComponentWidthLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGComponentWidthLayoutSpringBase.inl"
#include "OSGComponentWidthLayoutSpring.inl"

#define OSGCOMPONENTWIDTHLAYOUTSPRING_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCOMPONENTWIDTHLAYOUTSPRING_H_ */
