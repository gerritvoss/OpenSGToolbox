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

#include "OSGSoundManagerBase.h"
#include "OSGSound.h"

OSG_BEGIN_NAMESPACE

/*! \brief SoundManager class. See \ref 
           PageSoundSoundManager for a description.
*/

class OSG_SOUNDLIB_DLLMAPPING SoundManager : public SoundManagerBase
{
  private:

    typedef SoundManagerBase Inherited;

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

	virtual void init(const char* arg, ...) = 0;
	virtual void uninit(void) = 0;

	/**
	* update the sound system with current elapsed time
	*/
	virtual void update(const Real32& elps) = 0;

	/**
	* update listener's property, actual argument depends on the extended class
	*/

	//virtual void setListenerProperties(const Pnt3f &lstnrPos, const Vec3f &velocity, const Vec3f &forward, const Vec3f &up) = 0;
	virtual void setListenerProperties(const Pnt3f &lstnrPos, const Vec3f &velocity, const Vec3f &forward, const Vec3f &up);
	
	virtual SoundPtr getSound(const int id) = 0;
	virtual SoundPtr getSound(const char* name) = 0;

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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SoundManagerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SoundManager &source);
};

typedef SoundManager *SoundManagerP;

OSG_END_NAMESPACE

#include "OSGSoundManagerBase.inl"
#include "OSGSoundManager.inl"

#define OSGSOUNDMANAGER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSOUNDMANAGER_H_ */
