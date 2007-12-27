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

#ifndef _OSGMAXLAYOUTSPRING_H_
#define _OSGMAXLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGMaxLayoutSpringBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MaxLayoutSpring class. See \ref 
           PageUserInterfaceMaxLayoutSpring for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING MaxLayoutSpring : public MaxLayoutSpringBase
{
  private:

    typedef MaxLayoutSpringBase Inherited;

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

    static  MaxLayoutSpringPtr create (LayoutSpringPtr TheSpring1, LayoutSpringPtr TheSpring2); 
    
    /*! \}                                                                 */
    virtual Int32 operation(const Int32& Left, const Int32& Right) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MaxLayoutSpringBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaxLayoutSpring(void);
    MaxLayoutSpring(const MaxLayoutSpring &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaxLayoutSpring(void); 

    /*! \}                                                                 */
    virtual void setNonClearValue(const Int32& value);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MaxLayoutSpringBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MaxLayoutSpring &source);
};

typedef MaxLayoutSpring *MaxLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGMaxLayoutSpringBase.inl"
#include "OSGMaxLayoutSpring.inl"

#define OSGMAXLAYOUTSPRING_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGMAXLAYOUTSPRING_H_ */
