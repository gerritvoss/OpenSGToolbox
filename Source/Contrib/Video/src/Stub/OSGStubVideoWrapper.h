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

#ifndef _OSGSTUBVIDEOWRAPPER_H_
#define _OSGSTUBVIDEOWRAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStubVideoWrapperBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief StubVideoWrapper class. See \ref
           PageContribVideoStubVideoWrapper for a description.
*/

class OSG_CONTRIBVIDEO_DLLMAPPING StubVideoWrapper : public StubVideoWrapperBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef StubVideoWrapperBase Inherited;
    typedef StubVideoWrapper     Self;

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

    // Variables should all be in StubVideoWrapperBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StubVideoWrapper(void);
    StubVideoWrapper(const StubVideoWrapper &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StubVideoWrapper(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class StubVideoWrapperBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StubVideoWrapper &source);
};

typedef StubVideoWrapper *StubVideoWrapperP;

OSG_END_NAMESPACE

#include "OSGStubVideoWrapperBase.inl"
#include "OSGStubVideoWrapper.inl"

#endif /* _OSGSTUBVIDEOWRAPPER_H_ */
