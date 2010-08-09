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
 *   This class is a wrapper for FMOD::EventSystem class, it provides basic  *
 *   Operation such as loading an an FMod event data base, and loading evnets*
 *   in the database provided.                                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGFMODSOUNDMANAGER_H_
#define _OSGFMODSOUNDMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribSoundDef.h"

#ifdef OSG_WITH_FMOD

#include "OSGSoundManager.h"

#include "fmod.hpp"

OSG_BEGIN_NAMESPACE

/*! \brief FModSoundManager class. See \ref 
           PageSoundFModSoundManager for a description.
*/

void OSG_CONTRIBSOUND_DLLMAPPING FMOD_ERRCHECK(FMOD_RESULT result, std::string Location = std::string(""));

class OSG_CONTRIBSOUND_DLLMAPPING FModSoundManager : public SoundManager
{
  private:

    typedef SoundManager Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      
    static FModSoundManager* the(void);

	static bool init(void);
	static bool uninit(void);

	/**
	* update the sound system with current elapsed time
	*/
    virtual void update(const Time& ElapsedTime);	

	//create a new sound object by its integer id
	virtual SoundTransitPtr createSound(void) const;
    virtual void setCamera(CameraUnrecPtr TheCamera);
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    static FModSoundManager* _the;

    // Variables should all be in StubSoundManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FModSoundManager(void);
    FModSoundManager(const FModSoundManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FModSoundManager(void); 

    /*! \}                                                                 */
    

    FMOD::System* getSystem(void) const;
	Pnt3f _PreviousLisenerPosition;

    /*==========================  PRIVATE  ================================*/
  private:
      friend class SoundManager;
      friend class FModSound;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FModSoundManager &source);
    
    FMOD::System    *_FModSystem;
};

typedef FModSoundManager *FModSoundManagerP;

OSG_END_NAMESPACE

#include "OSGFModSoundManager.inl"


#endif /* OSG_WITH_FMOD */

#endif /* _OSGFMODSOUNDMANAGER_H_ */
