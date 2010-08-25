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

#ifndef _OSGVIDEOWRAPPER_H_
#define _OSGVIDEOWRAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVideoWrapperBase.h"
#include "OSGPathType.h"
#include "OSGImage.h"
#include "OSGTextureObjChunk.h"
#include <set>

#include "OSGVideoWrapperBase.h"
#include "OSGVideoEventDetails.h"

OSG_BEGIN_NAMESPACE

/*! \brief VideoWrapper class. See \ref
           PageContribVideoVideoWrapper for a description.
*/

class OSG_CONTRIBVIDEO_DLLMAPPING VideoWrapper : public VideoWrapperBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VideoWrapperBase Inherited;
    typedef VideoWrapper     Self;

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
    virtual bool open(const BoostPath& ThePath, Window* const TheWindow);
    virtual bool open(const std::string& ThePath, Window* const TheWindow) = 0;

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

    virtual Image* getCurrentFrame(void) = 0;
    virtual bool updateImage(void) = 0;
    virtual bool updateTexture(TextureObjChunk* const TheTexture);

	Image* getImage(void) const;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    
	ImageRefPtr _VideoImage;
	
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

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VideoWrapper &source);
};

typedef VideoWrapper *VideoWrapperP;

OSG_END_NAMESPACE

#include "OSGVideoWrapperBase.inl"
#include "OSGVideoWrapper.inl"

#endif /* _OSGVIDEOWRAPPER_H_ */
