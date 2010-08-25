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

#ifndef _OSGGENERICMULTIFIELDEDITOR_H_
#define _OSGGENERICMULTIFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGenericMultiFieldEditorBase.h"
#include "OSGScrollPanelFields.h"
#include "OSGFieldEditorComponentFields.h"
#include "OSGMFieldListModelFields.h"
#include "OSGListFields.h"
#include "OSGLabelFields.h"
#include "OSGMultiFieldListEditComponentGeneratorFields.h"
#include "OSGUIDrawingSurfaceFields.h"
#include "OSGDialogWindowEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief GenericMultiFieldEditor class. See \ref
           PageContribFieldContainerEditorGenericMultiFieldEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING GenericMultiFieldEditor : public GenericMultiFieldEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GenericMultiFieldEditorBase Inherited;
    typedef GenericMultiFieldEditor     Self;

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

    static void removeIndex(FieldContainer* const fc,
                            UInt32 fieldID,
                            UInt32 index,
                            UIDrawingSurface* const drawingSurface,
                            CommandManager* cmdMgr);

    static void insertAtIndex(FieldContainer* const fc,
                              UInt32 fieldID,
                              UInt32 index,
                              UIDrawingSurface* const drawingSurface,
                              CommandManager* cmdMgr);

    static void insertAtIndex(FieldContainer* const fc,
                              UInt32 fieldID,
                              UInt32 index,
                              const FieldContainerType* type,
                              CommandManager* cmdMgr);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GenericMultiFieldEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GenericMultiFieldEditor(void);
    GenericMultiFieldEditor(const GenericMultiFieldEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GenericMultiFieldEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const GenericMultiFieldEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    virtual void internalFieldChanged (void);
    virtual void internalStartEditing (void);
    virtual void internalStopEditing  (void);
    virtual void internalCancelEditing(void);
    virtual void updateLayout(void);
    bool internalAttachField(FieldContainer* fc, UInt32 fieldId, UInt32 index);
    bool internalDettachField(void);

    static std::vector<const DataType*> _EditableTypes;

    LabelRefPtr _ElementEndLabel;
    MFieldListModelRefPtr _FieldListModel;
    MultiFieldListEditComponentGeneratorRefPtr _FieldListGenerator;
    ListRefPtr _FieldList;
    ScrollPanelRefPtr _FieldElementsScrollPanel;
    std::vector<FieldEditorComponentRefPtr> _FieldEditors;

    void pushIndexEditor(FieldContainer* fc, UInt32 fieldId, UInt32 index);

    void handleListMouseClicked(MouseEventDetails* const details);
    boost::signals2::connection _ListMouseClickedConnection;

    static void handleInsertFCPtrDialogClosed(DialogWindowEventDetails* const details,
                                              FieldContainer* const fc,
                                              UInt32 fieldID,
                                              UInt32 index,
                                              CommandManager* cmdMgr);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GenericMultiFieldEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GenericMultiFieldEditor &source);
};

typedef GenericMultiFieldEditor *GenericMultiFieldEditorP;

OSG_END_NAMESPACE

#include "OSGGenericMultiFieldEditorBase.inl"
#include "OSGGenericMultiFieldEditor.inl"

#endif /* _OSGGENERICMULTIFIELDEDITOR_H_ */
