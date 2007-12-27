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

#ifndef _OSGABSTRACTLAYOUTSPRING_H_
#define _OSGABSTRACTLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractLayoutSpringBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractLayoutSpring class. See \ref 
           PageUserInterfaceAbstractLayoutSpring for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractLayoutSpring : public AbstractLayoutSpringBase
{
  private:

    typedef AbstractLayoutSpringBase Inherited;

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
    
    //Returns the current value of this LayoutSpringPtr.
    virtual Int32 getValue(void) const;

    //Sets the current value of this LayoutSpringPtr.
    virtual void setValue(const Int32& value);

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
    
    virtual void clear(void);
    virtual void setNonClearValue(const Int32& value);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractLayoutSpringBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractLayoutSpring &source);
};

typedef AbstractLayoutSpring *AbstractLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGAbstractLayoutSpringBase.inl"
#include "OSGAbstractLayoutSpring.inl"

#define OSGABSTRACTLAYOUTSPRING_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGABSTRACTLAYOUTSPRING_H_ */
