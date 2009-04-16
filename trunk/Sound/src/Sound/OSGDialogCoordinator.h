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

#ifndef _OSGDIALOGCOORDINATOR_H_
#define _OSGDIALOGCOORDINATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDialogCoordinatorBase.h"
#include "OSGSoundEmitter.h"
#include "OSGSoundListener.h"
#include "OSGSoundManager.h"

OSG_BEGIN_NAMESPACE

/*! \brief DialogCoordinator class. See \ref 
           PageSoundDialogCoordinator for a description.
*/

class OSG_SOUNDLIB_DLLMAPPING DialogCoordinator : public DialogCoordinatorBase,
	public SoundListener
{
  private:

    typedef DialogCoordinatorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

	virtual void soundEnded(const SoundEvent& e);

	virtual void soundPlayed(const SoundEvent& e);
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

	virtual void addSoundEmitter(const SoundEmitterPtr emitter, const char role, const int startDialogID, const char* scriptFile = NULL);
	virtual void setScript(const char* script);
	virtual void start();
	virtual int getScriptPos();
	virtual void setSoundManager(SoundManagerPtr soundManager);

	virtual int getNext();  //return the next index of emitter that should be played
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
	char scriptFile[20][64];
	FILE *fid[20];
	int numSoundEmitter;
	SoundEmitterPtr emitters[20]; //sound emitter for voices
	char roles[20]; //character designation, c for clara, s for sam, low cases
	char* script;
	int currentLine[20]; //integer value for current lines pointer.
	int scriptPos;
	SoundManagerPtr soundManager;
    // Variables should all be in DialogCoordinatorBase.
	

	virtual void loadNext(int index);
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */
	
    DialogCoordinator(void);
    DialogCoordinator(const DialogCoordinator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DialogCoordinator(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DialogCoordinatorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DialogCoordinator &source);
};

typedef DialogCoordinator *DialogCoordinatorP;

OSG_END_NAMESPACE

#include "OSGDialogCoordinatorBase.inl"
#include "OSGDialogCoordinator.inl"

#define OSGDIALOGCOORDINATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDIALOGCOORDINATOR_H_ */
