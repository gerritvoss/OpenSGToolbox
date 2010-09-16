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

#ifndef _OSGFCPTRFIELDEDITOR_H_
#define _OSGFCPTRFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFCPtrFieldEditorBase.h"
#include "OSGTextFieldFields.h"
#include "OSGMenuButtonFields.h"
#include "OSGLabelFields.h"
#include "OSGActionEventDetailsFields.h"
#include "OSGDialogWindowEventDetailsFields.h"
#include "OSGFCPtrEditorStore.h"

OSG_BEGIN_NAMESPACE

/*! \brief FCPtrFieldEditor class. See \ref
           PageContribFieldContainerEditorFCPtrFieldEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FCPtrFieldEditor : public FCPtrFieldEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FCPtrFieldEditorBase Inherited;
    typedef FCPtrFieldEditor     Self;

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

    virtual const std::vector<const DataType*>& getEditableTypes(void) const;

    FCPtrEditorStorePtr getFCStore(void) const;
    void setFCStore(FCPtrEditorStorePtr store);

    static FCPtrEditorStorePtr getDefaultFindFCStorePrototype(void);
    static void setDefaultFindFCStorePrototype(FCPtrEditorStorePtr fcStore);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FCPtrFieldEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FCPtrFieldEditor(void);
    FCPtrFieldEditor(const FCPtrFieldEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FCPtrFieldEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const FCPtrFieldEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    virtual bool internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index);
    virtual bool internalDettachField(void);

    virtual void internalFieldChanged (void);
    virtual void internalStartEditing (void);
    virtual void internalStopEditing  (void);
    virtual void internalCancelEditing(void);
    virtual void updateLayout(void);

    static std::vector<const DataType*> _EditableTypes;
    LabelRefPtr _NameTypeLabel;
    TextFieldRefPtr _EditingTextField;
    MenuButtonRefPtr _EditingMenuButton;
    std::string _InitialValue;
    
    virtual void openCreateHandler(void);
    virtual void openFindContainerHandler(void);

    void handleTextFieldFocusGained    (FocusEventDetails* const details);
    void handleTextFieldFocusLost      (FocusEventDetails* const details);
    void handleTextFieldActionPerformed(ActionEventDetails* const details);
    void handleTextFieldKeyTyped       (KeyEventDetails* const details);
    boost::signals2::connection _TextFieldFocusGainedConnection,
                                _TextFieldFocusLostConnection,
                                _TextFieldActionPerformedConnection,
                                _TextFieldKeyTypedConnection;

    void handleMenuButtonAction(ActionEventDetails* const details);
    boost::signals2::connection _MenuButtonActionConnection;

    void handleCreateContainerDialogClosed(DialogWindowEventDetails* const details);
    boost::signals2::connection _CreateContainerDialogClosedConnection;

    void handleFindContainerDialogClosed(DialogWindowEventDetails* const details);
    boost::signals2::connection _FindContainerDialogClosedConnection;

    FCPtrEditorStorePtr _FindFCStore;

    static FCPtrEditorStorePtr _DefaultFindFCStorePrototype;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FCPtrFieldEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FCPtrFieldEditor &source);
};

typedef FCPtrFieldEditor *FCPtrFieldEditorP;

OSG_END_NAMESPACE

#include "OSGFCPtrFieldEditorBase.inl"
#include "OSGFCPtrFieldEditor.inl"

#endif /* _OSGFCPTRFIELDEDITOR_H_ */
