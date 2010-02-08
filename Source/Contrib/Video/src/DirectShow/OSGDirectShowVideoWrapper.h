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

#ifndef _OSGDIRECTSHOWVIDEOWRAPPER_H_
#define _OSGDIRECTSHOWVIDEOWRAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDirectShowVideoWrapperBase.h"
#ifdef _OSGTOOLBOX_VIDEO_USE_DIRECT_SHOW

#include <windows.h>
#include <dshow.h>

#pragma include_alias( "dxtrans.h", "qedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
#include <qedit.h>

OSG_BEGIN_NAMESPACE

/*! \brief DirectShowVideoWrapper class. See \ref
           PageContribVideoDirectShowVideoWrapper for a description.
*/

class OSG_CONTRIBVIDEO_DLLMAPPING DirectShowVideoWrapper : public DirectShowVideoWrapperBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DirectShowVideoWrapperBase Inherited;
    typedef DirectShowVideoWrapper     Self;

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
    virtual bool open(const std::string& ThePath);

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

    virtual ImageRefPtr getCurrentFrame(void);
    virtual bool updateImage(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DirectShowVideoWrapperBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DirectShowVideoWrapper(void);
    DirectShowVideoWrapper(const DirectShowVideoWrapper &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DirectShowVideoWrapper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    ICaptureGraphBuilder2* graphBuilder;
    IFilterGraph2* filterGraph;
    ISampleGrabber* sampleGrabber;
    
    bool videoInitialized;
    int videoWidth;
    int videoHeight;
    long* frameBuffer;
    long bufferSize;
    bool reachEndOnce;

    void uninitVideo();

    bool ConnectPins(IBaseFilter* outputFilter, 
                     unsigned int outputNum,
                     IBaseFilter* inputFilter,
                     unsigned int inputNum);

    void FindPin(IBaseFilter* baseFilter,
                 PIN_DIRECTION direction,
                 int pinNumber,
                 IPin** destPin);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DirectShowVideoWrapperBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DirectShowVideoWrapper &source);
};

typedef DirectShowVideoWrapper *DirectShowVideoWrapperP;

OSG_END_NAMESPACE

#include "OSGDirectShowVideoWrapperBase.inl"
#include "OSGDirectShowVideoWrapper.inl"

#endif /* _OSGDIRECTSHOWVIDEOWRAPPER_H_ */
