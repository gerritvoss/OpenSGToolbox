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

#ifndef _OSGDRAGGESTUREEVENT_H_
#define _OSGDRAGGESTUREEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDragGestureEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DragGestureEvent class. See \ref
           PageContribUserInterfaceDragGestureEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DragGestureEvent : public DragGestureEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DragGestureEventBase Inherited;
    typedef DragGestureEvent     Self;

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

    static  DragGestureEventTransitPtr      create(FieldContainerRefPtr Source,
                                                   Time TimeStamp,
                                                   const Pnt2f &DragLocation); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DragGestureEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DragGestureEvent(void);
    DragGestureEvent(const DragGestureEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DragGestureEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DragGestureEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DragGestureEvent &source);
};

typedef DragGestureEvent *DragGestureEventP;

OSG_END_NAMESPACE

#include "OSGDragGestureEventBase.inl"
#include "OSGDragGestureEvent.inl"

#endif /* _OSGDRAGGESTUREEVENT_H_ */
