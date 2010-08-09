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

#ifndef _OSGCOMPONENTHEIGHTLAYOUTSPRING_H_
#define _OSGCOMPONENTHEIGHTLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComponentHeightLayoutSpringBase.h"
#include "OSGComponent.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComponentHeightLayoutSpring class. See \ref
           PageContribUserInterfaceComponentHeightLayoutSpring for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ComponentHeightLayoutSpring : public ComponentHeightLayoutSpringBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum SizeField
    {
        PREFERRED_SIZE = 0,
        MINIMUM_SIZE   = 1,
        MAXIMUM_SIZE   = 2,
        REQUESTED_SIZE = 3,
        SIZE           = 4
    };

    typedef ComponentHeightLayoutSpringBase Inherited;
    typedef ComponentHeightLayoutSpring     Self;

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

    static  ComponentHeightLayoutSpringTransitPtr      create          (Component* const TheComponent, UInt32 SizeField = PREFERRED_SIZE); 

    //Returns the maximum value of this LayoutSpringRefPtr.
    virtual Real32 getMinimumValue(void) const;

    //Returns the Preferred value of this LayoutSpringRefPtr.
    virtual Real32 getPreferredValue(void) const;

    //Returns the minimum value of this LayoutSpringRefPtr.
    virtual Real32 getMaximumValue(void) const;
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ComponentHeightLayoutSpringBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComponentHeightLayoutSpring(void);
    ComponentHeightLayoutSpring(const ComponentHeightLayoutSpring &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComponentHeightLayoutSpring(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComponentHeightLayoutSpringBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComponentHeightLayoutSpring &source);
};

typedef ComponentHeightLayoutSpring *ComponentHeightLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGComponentHeightLayoutSpringBase.inl"
#include "OSGComponentHeightLayoutSpring.inl"

#endif /* _OSGCOMPONENTHEIGHTLAYOUTSPRING_H_ */
