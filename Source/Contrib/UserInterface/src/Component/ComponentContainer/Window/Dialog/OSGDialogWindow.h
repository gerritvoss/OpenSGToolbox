/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Mark Stenerson             *
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

#include "OSGDialogWindowBase.h"
#include "OSGTextAreaFields.h"
#include "OSGButtonFields.h"
#include <vector>

#include "OSGComboBoxFields.h"
#include "OSGTextFieldFields.h"
#include "OSGListFields.h"
#include "OSGColorChooserFields.h"
#include "OSGColorSelectionModelFields.h"
#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief DialogWindow class. See \ref
           PageContribUserInterfaceDialogWindow for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DialogWindow : public DialogWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum MsgDialogType
    {
        MSG_ALERT = 0,
        MSG_ERROR = 1
    };

	enum InputDialogType
    {
        INPUT_BTNS  = 0,
        INPUT_COMBO = 1,
        INPUT_TEXT  = 2,
        INPUT_LIST  = 4,
        INPUT_MESSAGE  = 5
    };

	enum DialogButtons
    {
        BTN_OKCANCEL   = 0,
        BTN_YESNO      = 1,
        BTN_OKONLY     = 2,
        BTN_ACCEPTDENY = 3
    };

    typedef DialogWindowBase Inherited;
    typedef DialogWindow     Self;

    typedef std::vector<boost::any> TransientObjectVector;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
	
	virtual void close(UInt32 intOption, std::string strInput, UInt32 intInputIndex);
    
	static DialogWindowUnrecPtr createMessageDialog(const std::string& Title,
                                                    const std::string& Message,
                                                    bool showCancel,
                                                    const std::string& ConfirmBtnText = "OK",
                                                    const std::string& CancelBtnText = "Cancel");

	static DialogWindowUnrecPtr createInputDialog(const std::string& Title,
                                                  const std::string& Message,
                                                  UInt32 Type,
                                                  bool showCancel,
                                                  const std::vector<std::string>& InputValues,
                                                  const std::string& ConfirmBtnText = "OK",
                                                  const std::string& CancelBtnText = "Cancel");

	static DialogWindowUnrecPtr createButtonsInputDialog(const std::string& Title,
                                                  const std::string& Message,
                                                  bool showCancel,
                                                  const std::vector<std::string>& InputValues,
                                                  const std::string& ConfirmBtnText = "OK",
                                                  const std::string& CancelBtnText = "Cancel");

	static DialogWindowUnrecPtr createListInputDialog(const std::string& Title,
                                                  const std::string& Message,
                                                  bool showCancel,
                                                  const std::vector<std::string>& InputValues,
                                                  const std::string& ConfirmBtnText = "OK",
                                                  const std::string& CancelBtnText = "Cancel");

	static DialogWindowUnrecPtr createComboInputDialog(const std::string& Title,
                                                  const std::string& Message,
                                                  bool showCancel,
                                                  const std::vector<std::string>& InputValues,
                                                  const std::string& ConfirmBtnText = "OK",
                                                  const std::string& CancelBtnText = "Cancel");

	static DialogWindowUnrecPtr createTextInputDialog(const std::string& Title,
                                                  const std::string& Message,
                                                  bool showCancel,
                                                  const std::vector<std::string>& InputValues,
                                                  const std::string& ConfirmBtnText = "OK",
                                                  const std::string& CancelBtnText = "Cancel");
	
    static DialogWindowUnrecPtr createColorChooserDialog(const std::string& Title, 
                                                         const std::string& Message, 
                                                         bool showAlpha,
                                                         ColorSelectionModel* const colorModel,
                                                         bool showCancel, 
                                                         const std::string& ConfirmBtnText = "OK", 
                                                         const std::string& CancelBtnText = "Cancel");

    void handleConfirmButtonAction(ActionEventDetails* const e);
    void handleCancelButtonAction(ActionEventDetails* const e);
    void handleInputButtonAction(ActionEventDetails* const e);
    void handleListButtonAction(ActionEventDetails* const e);
    void handleComboButtonAction(ActionEventDetails* const e);
    void handleTextButtonAction(ActionEventDetails* const e);
    /*=========================  PROTECTED  ===============================*/

  protected:

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    boost::signals2::connection _ConfirmButtonActionConnection;

    boost::signals2::connection _CancelButtonActionConnection;

    boost::signals2::connection _InputButtonActionConnection;

    boost::signals2::connection _ListButtonActionConnection;

    boost::signals2::connection _ComboButtonActionConnection;

    boost::signals2::connection _TextButtonActionConnection;

	virtual void produceDialogWindowClosing(UInt32 intOption,
                                            std::string strInput,
                                            UInt32 intInputIndex);
    virtual void produceDialogWindowClosed(UInt32 intOption,
                                           std::string strInput,
                                           UInt32 intInputIndex);

    ComboBoxRefPtr _InputComboBox;
    ListRefPtr _InputList;
    TextFieldRefPtr _InputTextField;
    UInt32 _InputType;

	static TextAreaTransitPtr createTransparentTextArea(const std::string& Message);
	static void handleInputButton(Button* const btn);

    TransientObjectVector _TransientObjects;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DialogWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DialogWindow &source);
};

typedef DialogWindow *DialogWindowP;

OSG_END_NAMESPACE

#include "OSGDialogWindowBase.inl"
#include "OSGDialogWindow.inl"

#endif /* _OSGDIALOGWINDOW_H_ */
