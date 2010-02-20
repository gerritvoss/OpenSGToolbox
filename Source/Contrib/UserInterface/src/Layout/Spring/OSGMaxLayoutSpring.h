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

#ifndef _OSGMAXLAYOUTSPRING_H_
#define _OSGMAXLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMaxLayoutSpringBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MaxLayoutSpring class. See \ref
           PageContribUserInterfaceMaxLayoutSpring for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING MaxLayoutSpring : public MaxLayoutSpringBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MaxLayoutSpringBase Inherited;
    typedef MaxLayoutSpring     Self;

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

    static  MaxLayoutSpringTransitPtr create (LayoutSpringRefPtr TheSpring1, LayoutSpringRefPtr TheSpring2); 
    
    virtual Real32 operation(const Real32& Left, const Real32& Right) const;
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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual void setNonClearValue(const Real32& value);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MaxLayoutSpringBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaxLayoutSpring &source);
};

typedef MaxLayoutSpring *MaxLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGMaxLayoutSpringBase.inl"
#include "OSGMaxLayoutSpring.inl"

#endif /* _OSGMAXLAYOUTSPRING_H_ */
