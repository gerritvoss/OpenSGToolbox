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

#ifndef _OSGUPDATEEVENT_H_
#define _OSGUPDATEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGUpdateEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief UpdateEvent class. See \ref
           PageBaseUpdateEvent for a description.
*/

class OSG_BASE_DLLMAPPING UpdateEvent : public UpdateEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef UpdateEventBase Inherited;
    typedef UpdateEvent     Self;

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
    static UpdateEventTransitPtr create(  FieldContainerRefPtr Source,
                                        Time TimeStamp,
                                        Time ElapsedTime);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in UpdateEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    UpdateEvent(void);
    UpdateEvent(const UpdateEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~UpdateEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class UpdateEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const UpdateEvent &source);
};

typedef UpdateEvent *UpdateEventP;

OSG_END_NAMESPACE

#include "OSGUpdateEventBase.inl"
#include "OSGUpdateEvent.inl"

#endif /* _OSGUPDATEEVENT_H_ */
