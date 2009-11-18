/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <OpenSG/OSGConfig.h>

#include "OSGStubVideoWrapperBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief StubVideoWrapper class. See \ref 
           PageVideoStubVideoWrapper for a description.
*/

class OSG_VIDEOLIB_DLLMAPPING StubVideoWrapper : public StubVideoWrapperBase
{
  private:

    typedef StubVideoWrapperBase Inherited;

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
    virtual bool isStopped(void) const;
    virtual bool isPaused(void) const;
    virtual bool isInitialized(void) const;

	virtual Int64 getPosition(void) const;
	virtual Int64 getDuration(void) const;

    virtual ImagePtr getCurrentFrame(void);
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class StubVideoWrapperBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const StubVideoWrapper &source);
};

typedef StubVideoWrapper *StubVideoWrapperP;

OSG_END_NAMESPACE

#include "OSGStubVideoWrapperBase.inl"
#include "OSGStubVideoWrapper.inl"

#endif /* _OSGSTUBVIDEOWRAPPER_H_ */
