/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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
 * This is a wrapper class for FMOD::Event class, it provide basic operations*
 * such as start/stop playing sound/music and get the current status.        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGFMODSOUND_H_
#define _OSGFMODSOUND_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGSoundDef.h"

#ifdef _OSG_TOOLBOX_USE_FMOD_

#include "OSGFModSoundBase.h"
#include "fmod.hpp"
#include "fmod_errors.h"


OSG_BEGIN_NAMESPACE

/*! \brief FModSound class. See \ref 
           PageSoundFModSound for a description.
*/

class OSG_SOUNDLIB_DLLMAPPING FModSound : public FModSoundBase
{
  private:

    typedef FModSoundBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	//friend FMOD_RESULT  F_CALLBACK fmod_callback(FMOD_EVENT *  event, 	FMOD_EVENT_CALLBACKTYPE  type, 	void *  param1, 	void *  param2, 	void *  userdata);
	

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;
   

	virtual UInt32 play(void);
	virtual Real32 getLength(void) const;

    virtual UInt32 getNumChannels(void) const;
    virtual UInt32 getNumPlayingChannels(void) const;
    virtual bool isPlaying(UInt32 ChannelID) const;
    virtual bool isValid(UInt32 ChannelID) const;
	virtual void stop(UInt32 ChannelID);

    
	virtual void pause(UInt32 ChannelID);
	virtual void unpause(UInt32 ChannelID);
	virtual void pauseToggle(UInt32 ChannelID);
    virtual bool isPaused(UInt32 ChannelID) const;

    
	virtual void seek(Real32 pos, UInt32 ChannelID);
    virtual Real32 getTime(UInt32 ChannelID) const;


	virtual void setChannelPosition(const Pnt3f &pos, UInt32 ChannelID);
	virtual Pnt3f getChannelPosition(UInt32 ChannelID) const;

	virtual void setChannelVelocity(const Vec3f &vec, UInt32 ChannelID);
	virtual Vec3f getChannelVelocity(UInt32 ChannelID) const;

	virtual void setChannelVolume(Real32 volume, UInt32 ChannelID);
	virtual Real32 getChannelVolume(UInt32 ChannelID) const;
	virtual bool getMute(UInt32 ChannelID) const;
	virtual void mute(bool shouldMute, UInt32 ChannelID);

    void soundEnded(FMOD::Channel *channel);
	virtual void setAllChannelsVolume(Real32 volume);
	virtual void stopAllChannels(void);
	virtual void setAllChannelPaused(bool paused);
	virtual void setAllChannelMute(bool shouldMute);
	
	 /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FModSoundBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FModSound(void);
    FModSound(const FModSound &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FModSound(void); 

    /*! \}                                                                 */
    
    FMOD::Sound *_FModSound;

    typedef std::map<UInt32, FMOD::Channel*> ChannelMap;
    typedef ChannelMap::iterator ChannelMapItor;

    ChannelMap _ChannelMap;

    UInt32 generateChannelID(void) const;
    UInt32 addChannel(FMOD::Channel* channel);
    UInt32 getChannelID(FMOD::Channel* channel) const;
    void removeChannel(UInt32 ChannelID);

    FMOD::Channel* getChannel(UInt32 ChannelID) const;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FModSoundBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FModSound &source);
};

typedef FModSound *FModSoundP;

OSG_END_NAMESPACE

#include "OSGFModSoundBase.inl"
#include "OSGFModSound.inl"

#define OSGFMODSOUND_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSG_TOOLBOX_USE_FMOD_ */

#endif /* _OSGFMODSOUND_H_ */
