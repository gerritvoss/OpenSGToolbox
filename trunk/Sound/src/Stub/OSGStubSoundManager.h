/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGSTUBSOUNDMANAGER_H_
#define _OSGSTUBSOUNDMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "Sound/OSGSoundManager.h"

OSG_BEGIN_NAMESPACE

/*! \brief StubSoundManager class. See \ref 
           PageSoundStubSoundManager for a description.
*/

class OSG_SOUNDLIB_DLLMAPPING StubSoundManager : public SoundManager
{
  private:

    typedef SoundManager Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      
    static StubSoundManager* the(void);

	virtual void init(void);
	virtual void uninit(void);

	/**
	* update the sound system with current elapsed time
	*/
    virtual void update(const UpdateEvent& e);

	/**
	* update listener's property, actual argument depends on the extended class
	*/
	virtual void setListenerProperties(const Pnt3f &lstnrPos, const Vec3f &velocity, const Vec3f &forward, const Vec3f &up);
	

	//create a new sound object by its integer id
	virtual SoundPtr createSound(void) const;
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    static StubSoundManager* _the;

    // Variables should all be in StubSoundManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StubSoundManager(void);
    StubSoundManager(const StubSoundManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StubSoundManager(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:
      friend class SoundManager;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const StubSoundManager &source);
};

typedef StubSoundManager *StubSoundManagerP;

OSG_END_NAMESPACE

#include "OSGStubSoundManager.inl"

#endif /* _OSGSTUBSOUNDMANAGER_H_ */
