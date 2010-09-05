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
    virtual bool seek(Int64 SeekPos);
    virtual bool jump(Int64 Amount);
    virtual bool setRate(Real32 Rate);
    virtual Real32 getRate(void) const;
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
	
	virtual Int64 getPosition(void) const;
	virtual Int64 getDuration(void) const;

    virtual Image* getCurrentFrame(void);
    virtual bool updateImage(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in VLCVideoWrapperBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VLCVideoWrapper(void);
    VLCVideoWrapper(void *carbonWindow);
    VLCVideoWrapper(const VLCVideoWrapper &source, void *carbonWindow);

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

	static bool VLC_Execption_catch (libvlc_exception_t ex, std::string message);

    /*==========================  PRIVATE  ================================*/

  private:
    struct ctx	
    {
        UInt8*               pixels;
        Lock*                lock;
        //MainWindow*             mainWindow;
    };
	
	// media player handling the video being played
	libvlc_media_player_t * mTheMediaPlayer;

	// vlc struct holding data to the video file
    libvlc_media_t * mTheMedia;

	bool mPaused, mStopped, mInitialized;
	UInt32 videoWidth;
	UInt32 videoHeight; 
	bool reachEndOnce;
    void *theCarbonWindow;

    friend class FieldContainer;
    friend class VLCVideoWrapperBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const VLCVideoWrapper &source);
	
	struct ctx _VideoMemContext;
	
	static void lock(struct ctx* ctx, void** pp_ret);
	static void unlock(struct ctx* ctx);
	void processNewFrame(struct ctx* ctx);

    friend class FieldContainer;
    friend class VLCVideoWrapperBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VLCVideoWrapper &source);
};

struct ctx	
{
    UInt8*               pixels;
    LockRefPtr           lock;
    //MainWindow*             mainWindow;
};
typedef VLCVideoWrapper *VLCVideoWrapperP;

OSG_END_NAMESPACE

#include "OSGVLCVideoWrapperBase.inl"
#include "OSGVLCVideoWrapper.inl"

#endif /* OSG_WITH_VLC */

#endif /* _OSGVLCVIDEOWRAPPER_H_ */
