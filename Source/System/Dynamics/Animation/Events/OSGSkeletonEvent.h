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

#ifndef _OSGSKELETONEVENT_H_
#define _OSGSKELETONEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSkeletonEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonEvent class. See \ref
           PageDynamicsSkeletonEvent for a description.
*/

class OSG_DYNAMICS_DLLMAPPING SkeletonEvent : public SkeletonEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SkeletonEventBase Inherited;
    typedef SkeletonEvent     Self;

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
    static  SkeletonEventTransitPtr      create( FieldContainerRefPtr Source,
                                                 Time TimeStamp); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkeletonEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkeletonEvent(void);
    SkeletonEvent(const SkeletonEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkeletonEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkeletonEvent &source);
};

typedef SkeletonEvent *SkeletonEventP;

OSG_END_NAMESPACE

#include "OSGSkeletonEventBase.inl"
#include "OSGSkeletonEvent.inl"

#endif /* _OSGSKELETONEVENT_H_ */
