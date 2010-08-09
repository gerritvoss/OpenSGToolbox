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

#ifndef _OSGGENERICNAMEATTACHMENTEDITOR_H_
#define _OSGGENERICNAMEATTACHMENTEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGenericNameAttachmentEditorBase.h"
#include "OSGCommandManager.h"
#include "OSGTextFieldFields.h"
#include "OSGActionEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief GenericNameAttachmentEditor class. See \ref
           PageContribFieldContainerEditorGenericNameAttachmentEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING GenericNameAttachmentEditor : public GenericNameAttachmentEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GenericNameAttachmentEditorBase Inherited;
    typedef GenericNameAttachmentEditor     Self;

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

    virtual void startEditing (void);
    virtual void stopEditing  (void);
    virtual void cancelEditing(void);
    virtual bool isEditing    (void) const;

    bool isTypeEditable(const DataType& type) const;

    bool attachContainer (FieldContainer* fc);
    bool dettachContainer(void);
    void updateLayout(void);

    void              setCommandManager(CommandManagerPtr manager);
    CommandManagerPtr getCommandManager(void                     ) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GenericNameAttachmentEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GenericNameAttachmentEditor(void);
    GenericNameAttachmentEditor(const GenericNameAttachmentEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GenericNameAttachmentEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const GenericNameAttachmentEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    void fieldChanged         (FieldContainer *fc, 
                               ConstFieldMaskArg whichField);

    void attachFieldCallback (void);
    void dettachFieldCallback(void);

    TextFieldRefPtr _EditingTextField;
    std::string _InitialValue;

    void handleTextFieldFocusGained    (FocusEventDetails* const details);
    void handleTextFieldFocusLost      (FocusEventDetails* const details);
    void handleTextFieldActionPerformed(ActionEventDetails* const details);
    void handleTextFieldKeyTyped       (KeyEventDetails* const details);
    boost::signals2::connection _TextFieldFocusGainedConnection,
                                _TextFieldFocusLostConnection,
                                _TextFieldActionPerformedConnection,
                                _TextFieldKeyTypedConnection;

    CommandManagerPtr _CmdManager;
    bool              _isEditing;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GenericNameAttachmentEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GenericNameAttachmentEditor &source);
};

typedef GenericNameAttachmentEditor *GenericNameAttachmentEditorP;

OSG_END_NAMESPACE

#include "OSGGenericNameAttachmentEditorBase.inl"
#include "OSGGenericNameAttachmentEditor.inl"

#endif /* _OSGGENERICNAMEATTACHMENTEDITOR_H_ */
