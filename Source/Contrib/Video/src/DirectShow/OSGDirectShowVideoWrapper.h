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

#ifdef OSG_WITH_DIRECT_SHOW

#include <atlbase.h>
#include <windows.h>
#include <dshow.h>
#include <guiddef.h>

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
    virtual bool open(const std::string& ThePath, Window* const window);
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
	
    virtual bool canSeekForward(void) const;
    virtual bool canSeekBackward(void) const;
	virtual Real64 getPosition(void) const;
	virtual Real64 getDuration(void) const;
    virtual UInt32 getWidth(void) const;
    virtual UInt32 getHeight(void) const;

    virtual bool hasAudio(void) const;
    virtual void enableAudio(void);
    virtual void disableAudio(void);
    virtual bool isAudioEnabled(void) const;

    virtual Real32 getAudioVolume(void) const;
    virtual void setAudioVolume(Real32 volume);

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
    // These are needed by the GraphBuilder
    CComPtr<IGraphBuilder>  _pGraphBuilder;          // GraphBuilder
    CComPtr<ICaptureGraphBuilder2>  _pGraphCaptureBuilder;          // GraphBuilder
    CComPtr<IMediaControl>  _pMediaControl;          // Media Control
    CComPtr<IMediaPosition> _pMediaPosition;          // Media Position
    CComPtr<IMediaEvent>    _pMediaEvent;          // Media Event
    CComPtr<IFileSourceFilter>       g_IFileSource; // interface to the WM ASF Reader
    //D3DFORMAT               g_TextureFormat; // Texture format

    // These are needed by the Source Filter
    CComPtr<IBaseFilter>    _pSourceFilter;          // Source Filter
    CComPtr<IPin>           _pSourceAudioPin;   // #0 Source Filter Output Pin (force to be audio) 
    CComPtr<IPin>           _pSourceVideoPin;   // #1 Source Filter Output Pin (force to be video) 

    CComPtr<IBaseFilter>    _pDecoderFilter;       // Decoder Filter
    CComPtr<IBaseFilter>    _pVideoRenderer;      // Video Renderer
    CComPtr<IPin>           _DecoderOutputPin;     // Decoder Filter Output Pin
    
    CComPtr<IBaseFilter>    _pNullAudioFilter;       // NULL Audio Filter
    CComPtr<IBaseFilter>    _pAudioRenderer;      // Audio Renderer
    

    CComPtr<IBaseFilter> _pSampleGrabberFilter;
    CComPtr<IBaseFilter> _pCSCFilter;
    ISampleGrabber* _pSampleGrabber;
    CComPtr<IPin>           _SampleGrabberIntputPin;     // SampleGrabber Intput Pin
    CComPtr<IPin>           _SampleGrabberOutputPin;     // SampleGrabber Output Pin

    
    DWORD dwROT;
    
    bool _VideoInitialized;
    Int32  _VideoWidth;
    Int32  _VideoHeight;
    long* _FrameBuffer;
    long _BufferSize;
    bool _ReachEndOnce;

    void uninitVideo();

    bool ConnectPins(IBaseFilter* outputFilter, 
                     unsigned int outputNum,
                     IBaseFilter* inputFilter,
                     unsigned int inputNum);

    void FindPin(IBaseFilter* baseFilter,
                 PIN_DIRECTION direction,
                 int pinNumber,
                 IPin** destPin);

    HRESULT ConnectWMVFile(const std::string& ThePath);
    HRESULT ConnectMPGFile(const std::string& ThePath);
    HRESULT ConnectAVCHDFile(const std::string& ThePath);
    HRESULT ConnectAVIFile(const std::string& ThePath);
    HRESULT ConnectSampleGrabber(void);
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

#endif /* OSG_WITH_DIRECT_SHOW */

#endif /* _OSGDIRECTSHOWVIDEOWRAPPER_H_ */
