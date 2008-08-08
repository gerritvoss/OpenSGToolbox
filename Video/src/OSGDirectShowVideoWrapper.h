/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"

#include "OSGDirectShowVideoWrapperBase.h"

#include <windows.h>
#include <dshow.h>
#include <qedit.h>

OSG_BEGIN_NAMESPACE

/*! \brief DirectShowVideoWrapper class. See \ref 
           PageVideoDirectShowVideoWrapper for a description.
*/

class OSG_VIDEOLIB_DLLMAPPING DirectShowVideoWrapper : public DirectShowVideoWrapperBase
{
  private:

    typedef DirectShowVideoWrapperBase Inherited;

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
    virtual bool open(Path ThePath);

    virtual bool seek(Int64 SeekPos);
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

    virtual ImagePtr getCurrentFrame(void);
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
    

    ICaptureGraphBuilder2* graphBuilder;
    IFilterGraph2* filterGraph;
    ISampleGrabber* sampleGrabber;
    
    bool videoInitialized;
    int videoWidth;
    int videoHeight;
    long* frameBuffer;
    long bufferSize;

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

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DirectShowVideoWrapper &source);
};

typedef DirectShowVideoWrapper *DirectShowVideoWrapperP;

OSG_END_NAMESPACE

#include "OSGDirectShowVideoWrapperBase.inl"
#include "OSGDirectShowVideoWrapper.inl"

#define OSGDIRECTSHOWVIDEOWRAPPER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDIRECTSHOWVIDEOWRAPPER_H_ */
