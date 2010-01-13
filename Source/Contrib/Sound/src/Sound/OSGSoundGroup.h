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

#ifndef _OSGSOUNDGROUP_H_
#define _OSGSOUNDGROUP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSound.h"
#include "OSGSoundGroupBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SoundGroup class. See \ref
           PageContribSoundSoundGroup for a description.
*/

class OSG_CONTRIBSOUND_DLLMAPPING SoundGroup : public SoundGroupBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SoundGroupBase Inherited;
    typedef SoundGroup     Self;

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

    void stop(void);
    void pause(void);
    void unpause(void);
    void setVolume(Real32 volume);
    Real32 getVolume(void) const;
    void mute(bool muted);

    UInt32 getNumSounds(void) const;
    UInt32 getNumPlayingSounds(void) const;
    UInt32 getNumPlayingChannels(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SoundGroupBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SoundGroup(void);
    SoundGroup(const SoundGroup &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SoundGroup(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SoundGroupBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SoundGroup &source);
};

typedef SoundGroup *SoundGroupP;

OSG_END_NAMESPACE

#include "OSGSoundGroupBase.inl"
#include "OSGSoundGroup.inl"

#endif /* _OSGSOUNDGROUP_H_ */
