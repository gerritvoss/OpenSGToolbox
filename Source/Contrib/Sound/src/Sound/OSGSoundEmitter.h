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

#ifndef _OSGSOUNDEMITTER_H_
#define _OSGSOUNDEMITTER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSoundEmitterBase.h"
#include "OSGSound.h"
#include "OSGWindowEventProducerFields.h"

#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief SoundEmitter class. See \ref
           PageContribSoundSoundEmitter for a description.
*/

class OSG_CONTRIBSOUND_DLLMAPPING SoundEmitter : public SoundEmitterBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SoundEmitterBase Inherited;
    typedef SoundEmitter     Self;

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

    void attachUpdateProducer(ReflexiveContainer* const producer);
    void detachUpdateProducer(void);

    void emitSound(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SoundEmitterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SoundEmitter(void);
    SoundEmitter(const SoundEmitter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SoundEmitter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual void update(EventDetails* const details);
    boost::signals2::connection _UpdateEventConnection;

    std::set<UInt32> _EmittedSoundChannels;

	Pnt3f _PreviousPosition;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SoundEmitterBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SoundEmitter &source);
};

typedef SoundEmitter *SoundEmitterP;

OSG_END_NAMESPACE

#include "OSGSoundEmitterBase.inl"
#include "OSGSoundEmitter.inl"

#endif /* _OSGSOUNDEMITTER_H_ */
