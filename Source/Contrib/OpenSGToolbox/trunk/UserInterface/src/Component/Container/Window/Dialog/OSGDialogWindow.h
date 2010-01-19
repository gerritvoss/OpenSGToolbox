/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGDIALOGWINDOW_H_
#define _OSGDIALOGWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGDialogWindowBase.h"
#include "Event/OSGDialogWindowListener.h"
#include "Component/Text/OSGTextAreaFields.h"
#include "Component/Button/OSGButtonFields.h"
#include <set>
#include <vector>

#include <OpenSG/Toolbox/OSGEventListener.h>

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief DialogWindow class. See \ref 
           PageUserInterfaceDialogWindow for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DialogWindow : public DialogWindowBase
{
  private:

    typedef DialogWindowBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	enum MsgDialogType{MSG_ALERT=0, MSG_ERROR};
	enum InputDialogType{INPUT_BTNS=0, INPUT_COMBO, INPUT_TEXT};
	enum DialogButtons{BTN_OKCANCEL=0, BTN_YESNO, BTN_OKONLY, BTN_ACCEPTDENY};
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

    EventConnection addDialogWindowListener(DialogWindowListenerPtr Listener);
	bool isDialogWindowListenerAttached(DialogWindowListenerPtr Listener) const;
    void removeDialogWindowListener(DialogWindowListenerPtr Listener);

    EventConnection addEventListener(EventListenerPtr Listener);
	bool isEventListenerAttached(EventListenerPtr Listener) const;
    void removeEventListener(EventListenerPtr Listener);
	
	virtual void close(UInt32 intOption, std::string strInput);
    
	static DialogWindowPtr createMessageDialog(const std::string& Title, const std::string& Message, const int& Type, const bool& showCancel, const std::string& ConfirmBtnText = "OK", const std::string& CancelBtnText = "Cancel");
	static DialogWindowPtr createInputDialog(const std::string& Title, const std::string& Message, const int& Type, const bool& showCancel, const std::vector<std::string>& InputValues, const std::string& ConfirmBtnText = "OK", const std::string& CancelBtnText = "Cancel");
	

	/*=========================  PROTECTED  ===============================*/
  protected:
	class ConfirmButtonListener : public ActionListener
	{
		public :
			ConfirmButtonListener(DialogWindowPtr TheDialogWindow);
			virtual void actionPerformed(const ActionEventPtr e);
		protected :
			DialogWindowPtr _DialogWindow;
	};

	class CancelButtonListener : public ActionListener
	{
	public :
		CancelButtonListener(DialogWindowPtr TheDialogWindow);
        virtual void actionPerformed(const ActionEventPtr e);
	protected :
		DialogWindowPtr _DialogWindow;
	};

	class InputButtonListener : public ActionListener
	{
	public :
		InputButtonListener(DialogWindowPtr TheDialogWindow);
        virtual void actionPerformed(const ActionEventPtr e);
	protected :
		DialogWindowPtr _DialogWindow;
	};

	class ComboButtonListener : public ActionListener
	{
	public :
		ComboButtonListener(DialogWindowPtr TheDialogWindow);
        virtual void actionPerformed(const ActionEventPtr e);
	protected :
		DialogWindowPtr _DialogWindow;
	};

	class TextButtonListener : public ActionListener
	{
	public :
		TextButtonListener(DialogWindowPtr TheDialogWindow);
        virtual void actionPerformed(const ActionEventPtr e);
	protected :
		DialogWindowPtr _DialogWindow;
	};
    // Variables should all be in DialogWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DialogWindow(void);
    DialogWindow(const DialogWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DialogWindow(void); 

    /*! \}                                                                 */
	typedef std::set<DialogWindowListenerPtr> DialogWindowListenerSet;
    typedef DialogWindowListenerSet::iterator DialogWindowListenerSetItor;
    typedef DialogWindowListenerSet::const_iterator DialogWindowListenerSetConstItor;
	
    DialogWindowListenerSet       _DialogWindowListeners;
	    
	typedef std::set<EventListenerPtr> EventListenerSet;
    typedef EventListenerSet::iterator EventListenerSetItor;
    typedef EventListenerSet::const_iterator EventListenerSetConstItor;
	
    EventListenerSet       _EventListeners;
	
	virtual void produceDialogWindowClosing(UInt32 intOption, std::string strInput);
	virtual void produceDialogWindowClosed(UInt32 intOption, std::string strInput);
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DialogWindowBase;

    static void initMethod(void);
	static TextAreaPtr createTransparentTextArea(const std::string& Message);
	static void handleInputButton(const ButtonPtr& btn);
	// prohibit default functions (move to 'public' if you need one)

    void operator =(const DialogWindow &source);
};

typedef DialogWindow *DialogWindowP;

OSG_END_NAMESPACE

#include "OSGDialogWindowBase.inl"
#include "OSGDialogWindow.inl"

#endif /* _OSGDIALOGWINDOW_H_ */
