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

#include "OSGConfig.h"
#include "OSGCamera.h"

#include "OSGSound.h"
#include "OSGStatElemTypes.h"

OSG_BEGIN_NAMESPACE

/*! \brief SoundManager class. See \ref 
           PageSoundSoundManager for a description.
*/

class OSG_CONTRIBSOUND_DLLMAPPING SoundManager
{
  private:

    /*==========================  PUBLIC  =================================*/
  public:
    static SoundManager* the(void);

	//create a new sound object by its integer id
	virtual SoundTransitPtr createSound(void) const = 0;

    
    virtual void setCamera(Camera* const TheCamera);
    virtual Camera* getCamera(void) const;

    void attachUpdateProducer(ReflexiveContainer* const producer);
    void detachUpdateProducer(void);

    static StatElemDesc<StatIntElem    > statNChannels;

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
    void attachedUpdate(EventDetails* const details);
    virtual void update(const Time& ElapsedTime) = 0;

    CameraUnrecPtr _Camera;
    boost::signals2::connection _UpdateEventConnection;

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
