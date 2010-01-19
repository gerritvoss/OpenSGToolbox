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

#ifndef _OSGSOUNDEMITTER_H_
#define _OSGSOUNDEMITTER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGSoundDef.h"

#include "OSGSoundEmitterBase.h"
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/Input/OSGWindowEventProducerFields.h>

#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief SoundEmitter class. See \ref 
           PageSoundSoundEmitter for a description.
*/

class OSG_SOUNDLIB_DLLMAPPING SoundEmitter : public SoundEmitterBase
{
  private:

    typedef SoundEmitterBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

	void update(const Real32& elps);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    bool attachUpdateListener(WindowEventProducerPtr UpdateProducer);
    void dettachUpdateListener(WindowEventProducerPtr UpdateProducer);

    void emitSound(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SoundEmitterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SoundEmitter(void);
    SoundEmitter(const SoundEmitter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SoundEmitter(void); 

	class SystemUpdateListener : public UpdateListener
	{
	public:
		SystemUpdateListener(SoundEmitterPtr TheSystem);
        virtual void update(const UpdateEventPtr e);
	private:
		SoundEmitterPtr _System;
	};

	friend class SystemUpdateListener;

	SystemUpdateListener _SystemUpdateListener;
	
    virtual void update(const Time& elps);

    std::set<UInt32> _EmittedSoundChannels;

    /*! \}                                                                 */
	Pnt3f _PreviousPosition;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SoundEmitterBase;

    static void initMethod(void);


    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SoundEmitter &source);
};

typedef SoundEmitter *SoundEmitterP;

OSG_END_NAMESPACE

#include "OSGSoundEmitterBase.inl"
#include "OSGSoundEmitter.inl"

#define OSGSOUNDEMITTER_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGSOUNDEMITTER_H_ */
