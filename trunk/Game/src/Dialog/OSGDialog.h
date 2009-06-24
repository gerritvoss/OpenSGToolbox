/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                   Authors: David Kabala, Eric Langkamp                    *
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

#ifndef _OSGDIALOG_H_
#define _OSGDIALOG_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include <OpenSG/Input/OSGEventConnection.h>
#include "OSGDialogBase.h"
#include "Event/OSGDialogListener.h"
#include <OpenSG/Sound/OSGSound.h>
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Input/OSGUpdateListener.h>
#include "OSGDialogHierarchy.h"
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief Dialog class. See \ref 
           PageGameDialog for a description.
*/

class OSG_GAMELIB_DLLMAPPING Dialog : public DialogBase
{
  private:

    typedef DialogBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /**************************************************************************//**
     * @fn	void start()
     * 
     * @brief	Starts the given dialog object.
     * 
     * @author	Langkamp. 
     * @date	6/15/2009. 
     *******************************************************`**********************/
    void start();

    /**************************************************************************//**
     * @fn	void terminate()
     * 
     * @brief	Simply produces a terminated event.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void terminate();

    /**************************************************************************//**
     * @fn	void selectResponse()
     * 
     * @brief	Used to select the given dialog object and produces a dialog selected event.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void selectResponse();

    /**************************************************************************//**
     * @fn	void pause()
     * 
     * @brief	Toggles the paused variable.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void pause();

    /**************************************************************************//**
     * @fn	void unpause()
     * 
     * @brief	Toggles the paused variable.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void unpause();
    virtual void produceEnded(const DialogEvent& e);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    /**************************************************************************//**
     * @fn	EventConnection addDialogListener(DialogListenerPtr Listener)
     * 
     * @brief	Simply adds a dialog listener to the given dialog object.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	Listener	The pointer of the dialog listener to be add. 
     * 
     * @return	. 
     *****************************************************************************/
    EventConnection addDialogListener(DialogListenerPtr Listener);

	/**************************************************************************//**
	 * @fn	bool isDialogListenerAttached(DialogListenerPtr Listener) const
	 * 
	 * @brief	Verifies whether or not a given DialogListener is attached.
	 * 
	 * @author	Langkamp. 
	 * @date	6/24/2009. 
	 * 
	 * @param	Listener	The DialogListenerPtr to be verified. 
	 * 
	 * @return	. 
	 *****************************************************************************/
	bool isDialogListenerAttached(DialogListenerPtr Listener) const;

    /**************************************************************************//**
     * @fn	void removeDialogListener(DialogListenerPtr Listener)
     * 
     * @brief	Removes a given Dialog Listener.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	Listener	The DialogListnerPtr of the Dialog Listener to be removed. 
     *****************************************************************************/
    void removeDialogListener(DialogListenerPtr Listener);

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    bool _displayed;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DialogBase.
    

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Dialog(void);
    Dialog(const Dialog &source);

    /*! \}                                                                 */

    
    UInt32 _dialogSoundChannelID;


    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Dialog(void); 

    typedef std::set<DialogListenerPtr> DialogListenerSet;
    typedef DialogListenerSet::iterator DialogListenerSetItor;
    typedef DialogListenerSet::const_iterator DialogListenerSetConstItor;

    void update(const UpdateEvent& e);

    class DialogListener : public UpdateListener, public SoundListener
    {
	public :
		DialogListener(DialogPtr TheDialog);
		
		virtual void update(const UpdateEvent& e);
        virtual void soundPlayed(const SoundEvent& e);

        virtual void soundStopped(const SoundEvent& e);

        virtual void soundPaused(const SoundEvent& e);

        virtual void soundUnpaused(const SoundEvent& e);

        virtual void soundLooped(const SoundEvent& e);

        virtual void soundEnded(const SoundEvent& e);
	protected :
		DialogPtr _Dialog;
	};

    DialogListenerSet       _DialogListeners;

    DialogListener          _DialogListener;

    virtual void produceStarted(const DialogEvent& e);
    virtual void produceResponseSelected(const DialogEvent& e);
    virtual void produceResponsesReady(const DialogEvent& e);
    virtual void produceTerminated(const DialogEvent& e);

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DialogBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Dialog &source);
};

typedef Dialog *DialogP;

OSG_END_NAMESPACE

#include "OSGDialogBase.inl"
#include "OSGDialog.inl"

#define OSGDIALOG_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDIALOG_H_ */
