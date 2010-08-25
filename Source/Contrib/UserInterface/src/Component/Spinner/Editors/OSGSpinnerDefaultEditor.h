/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGSPINNERDEFAULTEDITOR_H_
#define _OSGSPINNERDEFAULTEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSpinnerDefaultEditorBase.h"
#include "OSGTextField.h"
#include "OSGSpinner.h"
#include "OSGChangeEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief SpinnerDefaultEditor class. See \ref
           PageContribUserInterfaceSpinnerDefaultEditor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SpinnerDefaultEditor : public SpinnerDefaultEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    friend class LookAndFeel;

    typedef SpinnerDefaultEditorBase Inherited;
    typedef SpinnerDefaultEditor     Self;

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
    virtual void updateLayout(void);
    
    //Pushes the currently edited value to the SpinnerModel.
    virtual void commitEdit(void);

    //Cancels the current edits and returns the editor to the previous value
    virtual void cancelEdit(void);

    //Disconnect this editor from the specified JSpinner.
    virtual void dismiss(Spinner* const spinner);
	
	//Set whether or not this Editor is Editable
	virtual void setEditable(bool Editable);

	//Get whether or not this Editor is Editable
	virtual bool getEditable(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SpinnerDefaultEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SpinnerDefaultEditor(void);
    SpinnerDefaultEditor(const SpinnerDefaultEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SpinnerDefaultEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const SpinnerDefaultEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    //This method is called when the spinner's model's state changes.
    virtual void handleModelStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _ModelStateChangedConnection;

    //Min Button Action
    void handleEditorTextFieldActionPerformed(ActionEventDetails* const e);
    void handleEditorTextFieldFocusLost(FocusEventDetails* const e);
    void handleEditorTextFieldKeyPressed(KeyEventDetails* const e);
    boost::signals2::connection _EditorTextFieldActionConnection,
                                _EditorTextFieldFocusLostConnection,
                                _EditorTextFieldKeyPressedConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SpinnerDefaultEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SpinnerDefaultEditor &source);
};

typedef SpinnerDefaultEditor *SpinnerDefaultEditorP;

OSG_END_NAMESPACE

#include "OSGSpinnerDefaultEditorBase.inl"
#include "OSGSpinnerDefaultEditor.inl"

#endif /* _OSGSPINNERDEFAULTEDITOR_H_ */
