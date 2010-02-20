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

#ifndef _OSGUNDOABLEEDITEVENT_H_
#define _OSGUNDOABLEEDITEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUndoableEditEventBase.h"
#include "OSGUndoableEdit.h"

OSG_BEGIN_NAMESPACE

/*! \brief UndoableEditEvent class. See \ref
           PageContribUserInterfaceUndoableEditEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING UndoableEditEvent : public UndoableEditEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UndoableEditEventBase Inherited;
    typedef UndoableEditEvent     Self;

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

    static  UndoableEditEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                      Time TimeStamp,
                                                      UndoableEditPtr TheUndoableEdit); 

    const UndoableEditPtr getUndoableEdit(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UndoableEditEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UndoableEditEvent(void);
    UndoableEditEvent(const UndoableEditEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UndoableEditEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    UndoableEditPtr _UndoableEdit;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UndoableEditEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UndoableEditEvent &source);
};

typedef UndoableEditEvent *UndoableEditEventP;

OSG_END_NAMESPACE

#include "OSGUndoableEditEventBase.inl"
#include "OSGUndoableEditEvent.inl"

#endif /* _OSGUNDOABLEEDITEVENT_H_ */
