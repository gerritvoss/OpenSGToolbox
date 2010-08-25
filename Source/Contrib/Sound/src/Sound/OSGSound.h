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

#ifndef _OSGSOUND_H_
#define _OSGSOUND_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSoundBase.h"
#include "OSGSoundEventDetails.h"

OSG_BEGIN_NAMESPACE

/*! \brief Sound class. See \ref
           PageContribSoundSound for a description.
*/

class OSG_CONTRIBSOUND_DLLMAPPING Sound : public SoundBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SoundBase Inherited;
    typedef Sound     Self;

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

	virtual UInt32 play(void) = 0;
	virtual Real32 getLength(void) const = 0;
    
    //Channel Methods
    virtual UInt32 getNumChannels(void) const = 0;
    virtual UInt32 getNumPlayingChannels(void) const = 0;
    virtual bool isPlaying(UInt32 ChannelID) const = 0;
    virtual bool isValid(UInt32 ChannelID) const = 0;
	virtual void stop(UInt32 ChannelID) = 0;

    
	virtual void pause(UInt32 ChannelID) = 0;
	virtual void unpause(UInt32 ChannelID) = 0;
	virtual void pauseToggle(UInt32 ChannelID) = 0;
    virtual bool isPaused(UInt32 ChannelID) const = 0;

    
	virtual void seek(Real32 pos, UInt32 ChannelID) = 0;
    virtual Real32 getTime(UInt32 ChannelID) const = 0;


	virtual void setChannelPosition(const Pnt3f &pos, UInt32 ChannelID) = 0;
	virtual Pnt3f getChannelPosition(UInt32 ChannelID) const = 0;

	virtual void setChannelVelocity(const Vec3f &vec, UInt32 ChannelID) = 0;
	virtual Vec3f getChannelVelocity(UInt32 ChannelID) const = 0;

	virtual void setChannelVolume(Real32 volume, UInt32 ChannelID) = 0;
	virtual Real32 getChannelVolume(UInt32 ChannelID) const = 0;
	virtual bool getMute(UInt32 ChannelID) const = 0;
	virtual void mute(bool shouldMute, UInt32 ChannelID) = 0;

    
	virtual void setAllChannelsVolume(Real32 volume) = 0;
	virtual void stopAllChannels(void) = 0;
	virtual void setAllChannelPaused(bool paused) = 0;
	virtual void setAllChannelMute(bool shouldMute) = 0;
    
    static  SoundTransitPtr      create(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SoundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Sound(void);
    Sound(const Sound &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Sound(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void produceSoundPlayed(UInt32 TheChannel);
    void produceSoundStopped(UInt32 TheChannel);
    void produceSoundPaused(UInt32 TheChannel);
    void produceSoundUnpaused(UInt32 TheChannel);
    void produceSoundLooped(UInt32 TheChannel);
    void produceSoundEnded(UInt32 TheChannel);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SoundBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Sound &source);
};

typedef Sound *SoundP;

OSG_END_NAMESPACE

#include "OSGSoundBase.inl"
#include "OSGSound.inl"

#endif /* _OSGSOUND_H_ */
