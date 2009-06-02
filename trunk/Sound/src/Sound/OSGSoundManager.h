/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Sound                               *
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

#ifndef _OSGSOUNDMANAGER_H_
#define _OSGSOUNDMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGUpdateListener.h>

#include "OSGSound.h"

OSG_BEGIN_NAMESPACE

/*! \brief SoundManager class. See \ref 
           PageSoundSoundManager for a description.
*/

class OSG_SOUNDLIB_DLLMAPPING SoundManager : public UpdateListener
{
  private:

    /*==========================  PUBLIC  =================================*/
  public:
    static SoundManager* the(void);

	//create a new sound object by its integer id
	virtual SoundPtr createSound(void) const = 0;

    
    virtual void setCamera(CameraPtr TheCamera);
    virtual CameraPtr getCamera(void) const;

    void attachUpdateProducer(WindowEventProducerPtr TheProducer);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SoundManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */


    SoundManager(void);
    SoundManager(const SoundManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SoundManager(void); 

    /*! \}                                                                 */
    
    static SoundManager   *_the;

    static void setSoundManager(SoundManager *manager);
    static SoundManager* getDefaultSoundManager(void);

    CameraPtr _Camera;

	/**
	* update the sound system with current elapsed time
	*/
    /*==========================  PRIVATE  ================================*/
  private:
    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SoundManager &source);
};

OSG_END_NAMESPACE

#include "OSGSoundManager.inl"


#endif /* _OSGSOUNDMANAGER_H_ */
