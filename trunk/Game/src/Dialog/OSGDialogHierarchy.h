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

#ifndef _OSGDIALOGHIERARCHY_H_
#define _OSGDIALOGHIERARCHY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGDialogHierarchyBase.h"
#include "OSGDialog.h"
#include "Event/OSGDialogListener.h"
#include "Event/OSGDialogHierarchyListener.h"
#include "OSGDialogInterface.h"


OSG_BEGIN_NAMESPACE

/*! \brief DialogHierarchy class. See \ref 
           PageGameDialogHierarchy for a description.
*/

class OSG_GAMELIB_DLLMAPPING DialogHierarchy : public DialogHierarchyBase
{
  private:

    typedef DialogHierarchyBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    DialogInterfacePtr _ParentDialogInterface;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */

    /**************************************************************************//**
     * @fn	void reset()
     * 
     * @brief	Sets all parameters of the given Dialog Hierarchy to what there were at the beginning.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void reset();

    /**************************************************************************//**
     * @fn	void start()
     * 
     * @brief	Sets the Root Dialog as the Current dialog and starts the current dialog.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void start();

    /**************************************************************************//**
     * @fn	DialogPtr addDialog(std::string response, Real32 delayResponses,
     * 		SoundPtr dialogSound, bool interactive, DialogPtr parentDialog)
     * 
     * @brief	Adds a dialog to the given dialog hierarchy by creating it within the method.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	response		A text string that will be used as either a question or a response. 
     * @param	delayResponses	The number of seconds before displaying the responses (if -1 it will wait until the end of the sound). 
     * @param	dialogSound		A soundPtr that is related to the text string. 
     * @param	interactive		A boolean variable to select whether or not responses should be displayed. 
     * @param	parentDialog	If this is the first dialog added this should be Null otherwise the parameter should be the dialogPtr of its parent. 
     * 
     * @return	DialogPtr to be used as a parent dialog parameter for following dialogs. 
     *****************************************************************************/
    DialogPtr addDialog(std::string response, Real32 delayResponses, SoundPtr dialogSound, bool interactive, DialogPtr parentDialog);

    /**************************************************************************//**
     * @fn	void retrieveReponses()
     * 
     * @brief	Internal helper method to be used to gather response dialogs of the current dialog.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     *****************************************************************************/
    void retrieveReponses();

    /**************************************************************************//**
     * @fn	void AddXMLDialog(DialogPtr dialogNode)
     * 
     * @brief	To be used with the xml reader when loading in new dialog.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	dialogNode	The dialogptr to be added the the given hierarchy. 
     *****************************************************************************/
    void AddXMLDialog(DialogPtr dialogNode);
    /*! \{                                                                 */

    /**************************************************************************//**
     * @fn	EventConnection addDialogHierarchyListener(DialogHierarchyListenerPtr L
     * 		istener)
     * 
     * @brief	Simply adds a dialog hierarchy listener to the given dialog hierarchy object.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	Listener	The pointer of the dialog hierarchy listener to be add. 
     * 
     * @return	. 
     *****************************************************************************/
    EventConnection addDialogHierarchyListener(DialogHierarchyListenerPtr Listener);

	/**************************************************************************//**
	 * @fn	bool isDialogHierarchyListenerAttached(DialogHierarchyListenerPtr Liste
	 * 		ner) const
	 * 
	 * @brief	Verifies whether or not a given DailogHierarchyListener is attached.
	 * 
	 * @author	Langkamp. 
	 * @date	6/24/2009. 
	 * 
	 * @param	Listener	The DailogHierarchyListenerPtr to be verified. 
	 * 
	 * @return	. 
	 *****************************************************************************/
	bool isDialogHierarchyListenerAttached(DialogHierarchyListenerPtr Listener) const;

    /**************************************************************************//**
     * @fn	void removeDialogHierarchyListener(DialogHierarchyListenerPtr Listener)
     * 
     * 
     * @brief	Removes a given Dialog Hierarchy Listener.
     * 
     * @author	Langkamp. 
     * @date	6/24/2009. 
     * 
     * @param	Listener	The DialogHierarchyPtr of the Dialog Hierarchy Listener to be removed. 
     *****************************************************************************/
    void removeDialogHierarchyListener(DialogHierarchyListenerPtr Listener);


    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;


    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DialogHierarchyBase.

    typedef std::set<DialogHierarchyListenerPtr> DialogHierarchyListenerSet;
    typedef DialogHierarchyListenerSet::iterator DialogHierarchyListenerSetItor;
    typedef DialogHierarchyListenerSet::const_iterator DialogHierarchyListenerSetConstItor;

    class DialogHierarchyListener : public DialogListener
    {
	public :
		DialogHierarchyListener(DialogHierarchyPtr TheDialogHierarchy);
		
        virtual void started(const DialogEventPtr e);
        virtual void ended(const DialogEventPtr e);
        virtual void responseSelected(const DialogEventPtr e);
        virtual void responsesReady(const DialogEventPtr e);
        virtual void terminated(const DialogEventPtr e);

	protected :

        DialogHierarchyPtr _DialogHierarchy;
	};

	DialogHierarchyListener          _DialogHierarchyListener;

    
    DialogHierarchyListenerSet       _DialogHierarchyListeners;

    virtual void produceNewDialogStarted(const DialogHierarchyEventPtr e);
    virtual void produceDialogEnded(const DialogHierarchyEventPtr e);
    virtual void produceDialogResponseSelected(const DialogHierarchyEventPtr e);
    virtual void produceDialogResponsesReady(const DialogHierarchyEventPtr e);
    virtual void produceTerminated(const DialogHierarchyEventPtr e);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DialogHierarchy(void);
    DialogHierarchy(const DialogHierarchy &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DialogHierarchy(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DialogHierarchyBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DialogHierarchy &source);
};

typedef DialogHierarchy *DialogHierarchyP;

OSG_END_NAMESPACE

#include "OSGDialogHierarchyBase.inl"
#include "OSGDialogHierarchy.inl"

#endif /* _OSGDIALOGHIERARCHY_H_ */
