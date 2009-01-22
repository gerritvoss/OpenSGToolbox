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

#ifndef _OSGSTUBMANAGER_H_
#define _OSGSTUBMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGStubManagerBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief StubManager class. See \ref 
           PageSoundStubManager for a description.
*/

class OSG_SOUNDLIB_DLLMAPPING StubManager : public StubManagerBase
{
  private:

    typedef StubManagerBase Inherited;

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

	/**
	* default initialization with out loading the .FEV file, 
	* to load .FEV and set the path to the file and .FSB file
	* typical use: init(const char* mediaPath, const char* mediaFile, const int maxChannel);
	*/
	virtual void init(const char* arg, ...);

	/**
	* release the fmod eventsystem object
	*/
	virtual void uninit(void);

	/**
	* create and return an Fmod event wrapper object found in the .FEV and .FSB file
	* @param path, the path in the .FEV file to locate the specific FMod event instance
	*/
	SoundPtr getSound(const char* name);

	/**
	* create and return an Fmod event wrapper object found in the .FEV and .FSB file
	* @param id, id from the Fmod designer, which can be found in the optional output .h and text file
	*/
	SoundPtr getSound(const int id);
	

	void update(const Real32& elps);
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in StubManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StubManager(void);
    StubManager(const StubManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StubManager(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class StubManagerBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const StubManager &source);
};

typedef StubManager *StubManagerP;

OSG_END_NAMESPACE

#include "OSGStubManagerBase.inl"
#include "OSGStubManager.inl"

#define OSGSTUBMANAGER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSTUBMANAGER_H_ */
