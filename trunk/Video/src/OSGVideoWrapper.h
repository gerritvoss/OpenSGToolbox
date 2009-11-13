/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Video                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
                           Authors: David Kabala                            
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

#ifndef _OSGVIDEOWRAPPER_H_
#define _OSGVIDEOWRAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"

#include <OpenSG/Toolbox/OSGPathType.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGTextureChunk.h>
#include <set>

#include "Events/OSGVideoListener.h"
#include "OSGVideoWrapperBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief VideoWrapper class. See \ref 
           PageVideoVideoWrapper for a description.
*/

class OSG_VIDEOLIB_DLLMAPPING VideoWrapper : public VideoWrapperBase
{
  private:

    typedef VideoWrapperBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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

    /*! \}                                                                 */
    virtual bool open(Path ThePath) = 0;

    virtual bool seek(Int64 SeekPos) = 0;
    virtual bool jump(Int64 Amount) = 0;
    virtual bool setRate(Real32 Rate) = 0;
    virtual Real32 getRate(void) const = 0;
    virtual bool play(void) = 0;
    virtual bool pause(void) = 0;
    virtual bool unpause(void) = 0;
    virtual bool pauseToggle(void) = 0;
    virtual bool stop(void) = 0;
    virtual bool close(void) = 0;
	
    virtual bool isPlaying(void) const = 0;
    virtual bool isStopped(void) const = 0;
    virtual bool isPaused(void) const = 0;
    virtual bool isInitialized(void) const = 0;

	virtual Int64 getPosition(void) const = 0;
	virtual Int64 getDuration(void) const = 0;

    virtual ImagePtr getCurrentFrame(void) = 0;
    virtual bool updateImage(void) = 0;
    virtual bool updateTexture(TextureChunkPtr TheTexture);

	ImagePtr getImage(void) const;

	//Events
    void addVideoListener(VideoListenerPtr Listener);
    void removeVideoListener(VideoListenerPtr Listener);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in VideoWrapperBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VideoWrapper(void);
    VideoWrapper(const VideoWrapper &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VideoWrapper(void); 

    /*! \}                                                                 */
    
	ImagePtr _VideoImage;
	
	typedef std::set<VideoListenerPtr> VideoListenerSet;
    typedef VideoListenerSet::iterator VideoListenerSetItor;
    typedef VideoListenerSet::const_iterator VideoListenerSetConstItor;
	
    VideoListenerSet       _VideoListeners;

	void producePaused(void);
	void produceUnpaused(void);
	void produceStarted(void);
	void produceStopped(void);
	void produceOpened(void);
	void produceClosed(void);
	void produceEnded(void);
	void produceCycled(void);
	void produceSeeked(void);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class VideoWrapperBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const VideoWrapper &source);
};

typedef VideoWrapper *VideoWrapperP;

OSG_END_NAMESPACE

#include "OSGVideoWrapperBase.inl"
#include "OSGVideoWrapper.inl"

#endif /* _OSGVIDEOWRAPPER_H_ */
