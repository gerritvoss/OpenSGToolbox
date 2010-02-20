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

#ifndef _OSGBUTTONSELECTEDEVENT_H_
#define _OSGBUTTONSELECTEDEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGButtonSelectedEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ButtonSelectedEvent class. See \ref
           PageContribUserInterfaceButtonSelectedEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ButtonSelectedEvent : public ButtonSelectedEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ButtonSelectedEventBase Inherited;
    typedef ButtonSelectedEvent     Self;

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

    static  ButtonSelectedEventTransitPtr      create( FieldContainerRefPtr Source,
                                                       Time TimeStamp); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ButtonSelectedEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ButtonSelectedEvent(void);
    ButtonSelectedEvent(const ButtonSelectedEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ButtonSelectedEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ButtonSelectedEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ButtonSelectedEvent &source);
};

typedef ButtonSelectedEvent *ButtonSelectedEventP;

OSG_END_NAMESPACE

#include "OSGButtonSelectedEventBase.inl"
#include "OSGButtonSelectedEvent.inl"

#endif /* _OSGBUTTONSELECTEDEVENT_H_ */
