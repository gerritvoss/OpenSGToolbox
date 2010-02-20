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

#ifndef _OSGSUMLAYOUTSPRING_H_
#define _OSGSUMLAYOUTSPRING_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSumLayoutSpringBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SumLayoutSpring class. See \ref
           PageContribUserInterfaceSumLayoutSpring for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SumLayoutSpring : public SumLayoutSpringBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SumLayoutSpringBase Inherited;
    typedef SumLayoutSpring     Self;

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

    static  SumLayoutSpringTransitPtr create (LayoutSpringRefPtr TheSpring1, LayoutSpringRefPtr TheSpring2); 
    
    virtual Real32 operation(const Real32& Left, const Real32& Right) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SumLayoutSpringBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SumLayoutSpring(void);
    SumLayoutSpring(const SumLayoutSpring &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SumLayoutSpring(void);

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
    friend class SumLayoutSpringBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SumLayoutSpring &source);
};

typedef SumLayoutSpring *SumLayoutSpringP;

OSG_END_NAMESPACE

#include "OSGSumLayoutSpringBase.inl"
#include "OSGSumLayoutSpring.inl"

#endif /* _OSGSUMLAYOUTSPRING_H_ */
