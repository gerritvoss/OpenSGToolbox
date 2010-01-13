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

#ifndef _OSGSOUNDEVENT_H_
#define _OSGSOUNDEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSoundEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SoundEvent class. See \ref
           PageContribSoundSoundEvent for a description.
*/

class OSG_CONTRIBSOUND_DLLMAPPING SoundEvent : public SoundEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SoundEventBase Inherited;
    typedef SoundEvent     Self;

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
    static  SoundEventTransitPtr      create(  FieldContainerUnrecPtr Source,
                                               Time TimeStamp,
                                               UInt32 Channel); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SoundEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SoundEvent(void);
    SoundEvent(const SoundEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SoundEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SoundEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SoundEvent &source);
};

typedef SoundEvent *SoundEventP;

OSG_END_NAMESPACE

#include "OSGSoundEventBase.inl"
#include "OSGSoundEvent.inl"

#endif /* _OSGSOUNDEVENT_H_ */
