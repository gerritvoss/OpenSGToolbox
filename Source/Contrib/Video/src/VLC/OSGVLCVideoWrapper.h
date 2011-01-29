/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), David Naylor               *
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

#ifndef _OSGVLCVIDEOWRAPPER_H_
#define _OSGVLCVIDEOWRAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVLCVideoWrapperBase.h"

#ifdef OSG_WITH_VLC

#include "OSGLock.h"
#include "OSGImageFields.h"

#include <vlc/vlc.h>

OSG_BEGIN_NAMESPACE

/*! \brief VLCVideoWrapper class. See \ref
           PageContribVideoVLCVideoWrapper for a description.
*/

class OSG_CONTRIBVIDEO_DLLMAPPING VLCVideoWrapper : public VLCVideoWrapperBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VLCVideoWrapperBase Inherited;
    typedef VLCVideoWrapper     Self;

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
  	virtual bool open(BoostPath ThePath, Window* const TheWindow);
    virtual bool open(const std::string& ThePath, Window* const TheWindow);
    virtual bool seek(Real64 SeekPos);
    virtual bool jump(Real64 Amount);
    virtual bool setRate(Real64 Rate);
    virtual Real64 getRate(void) const;
    virtual bool play(void);
    virtual bool pause(void);
    virtual bool unpause(void);
    virtual bool pauseToggle(void);
    virtual bool stop(void);
    virtual bool close(void);
    virtual bool isPlaying(void) const;
    virtual bool isPaused(void) const;
    virtual bool isInitialized(void) const;
    virtual bool isStopped(void) const;
	
	virtual Real64 getPosition(void) const;
	virtual Real64 getDuration(void) const;
    virtual bool canSeekForward(void) const;
    virtual bool canSeekBackward(void) const;
    virtual UInt32 getWidth(void) const;
    virtual UInt32 getHeight(void) const;

    virtual bool hasAudio(void) const;
    virtual void enableAudio(void);
    virtual void disableAudio(void);
    virtual bool isAudioEnabled(void) const;

    virtual Real32 getAudioVolume(void) const;
    virtual void setAudioVolume(Real32 volume);

    virtual void setMute(bool Mute);
    virtual bool isMuted(void) const;

    virtual bool updateImage(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in VLCVideoWrapperBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VLCVideoWrapper(void);
    VLCVideoWrapper(const VLCVideoWrapper &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VLCVideoWrapper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const VLCVideoWrapper *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    static bool checkVLCError (const std::string& message);

    /*==========================  PRIVATE  ================================*/

  private:
    struct ctx	
    {
        UInt8*               _pixels;
        LockRefPtr           _lock;
        VLCVideoWrapper*     _VideoWrapper;
    };
	
	// media player handling the video being played
	libvlc_media_player_t * _MediaPlayer;

    libvlc_instance_t *_VLCInstance;

	bool _Initialized;
    bool _NextFrameReady;

    friend class FieldContainer;
    friend class VLCVideoWrapperBase;
    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const VLCVideoWrapper &source);
	
	struct ctx _VideoMemContext;
	
	static void* lock(void* userData, void** plane);
	static void unlock(void* userData, void* picture, void* const* plane);
	static void display(void* userData, void* picture);
    static void handleVLCEvents(const libvlc_event_t *pEvent, void *param);
};

typedef VLCVideoWrapper *VLCVideoWrapperP;

OSG_END_NAMESPACE

#include "OSGVLCVideoWrapperBase.inl"
#include "OSGVLCVideoWrapper.inl"

#endif /* OSG_WITH_VLC */

#endif /* _OSGVLCVIDEOWRAPPER_H_ */
