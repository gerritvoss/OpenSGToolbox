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

#ifndef _OSGKEYACCELERATOREVENT_H_
#define _OSGKEYACCELERATOREVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyAcceleratorEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief KeyAcceleratorEvent class. See \ref
           PageContribUserInterfaceKeyAcceleratorEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING KeyAcceleratorEvent : public KeyAcceleratorEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef KeyAcceleratorEventBase Inherited;
    typedef KeyAcceleratorEvent     Self;

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

    static  KeyAcceleratorEventTransitPtr      create( FieldContainerRefPtr Source,
                                                       Time TimeStamp,
                                                       UInt32 TheKey,
                                                       UInt32 Modifiers); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in KeyAcceleratorEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    KeyAcceleratorEvent(void);
    KeyAcceleratorEvent(const KeyAcceleratorEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~KeyAcceleratorEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class KeyAcceleratorEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const KeyAcceleratorEvent &source);
};

typedef KeyAcceleratorEvent *KeyAcceleratorEventP;

OSG_END_NAMESPACE

#include "OSGKeyAcceleratorEventBase.inl"
#include "OSGKeyAcceleratorEvent.inl"

#endif /* _OSGKEYACCELERATOREVENT_H_ */
