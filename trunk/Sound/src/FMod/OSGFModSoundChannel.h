/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGFMODSOUNDCHANNEL_H_
#define _OSGFMODSOUNDCHANNEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGSoundDef.h"

#ifdef _OSG_TOOLBOX_USE_FMOD_

#include "Sound/OSGSoundChannel.h"
#include "fmod.hpp"

OSG_BEGIN_NAMESPACE

/*! \brief FModSoundChannel class. See \ref 
           PageSoundFModSoundChannel for a description.
*/

class OSG_SOUNDLIB_DLLMAPPING FModSoundChannel : public SoundChannel
{
  private:

    typedef SoundChannel Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    virtual bool isPlaying(void) const;
    virtual bool isValid(void) const;
	virtual void stop(void);

    
	virtual void pause(void);
	virtual void unpause(void);
	virtual void pauseToggle(void);
    virtual bool isPaused(void) const;

    
	virtual void seek(Real32 pos);
    virtual Real32 getTime(void) const;
	virtual Real32 getLength(void) const;


	virtual void setPosition(const Pnt3f &pos);
	virtual Pnt3f getPosition(void) const;

	virtual void setVelocity(const Vec3f &vec);
	virtual Vec3f getVelocity(void) const;

	virtual void setVolume(Real32 volume);
	virtual Real32 getVolume(void) const;
	virtual bool getMute(void) const;
	virtual void mute(bool shouldMute);

    void soundEnded(void);
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FModSoundChannel(void); 

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FModSoundChannelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FModSoundChannel(FMOD::Channel *channel);

    /*! \}                                                                 */
    FMOD::Channel *_FModChannel;
    
    /*==========================  PRIVATE  ================================*/
  private:
      friend class FModSound;
    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FModSoundChannel &source);
    FModSoundChannel(const FModSoundChannel &source);
};

typedef FModSoundChannel *FModSoundChannelP;

OSG_END_NAMESPACE

#include "OSGFModSoundChannel.inl"

#endif /* _OSG_TOOLBOX_USE_FMOD_ */

#endif /* _OSGFMODSOUNDCHANNEL_H_ */
