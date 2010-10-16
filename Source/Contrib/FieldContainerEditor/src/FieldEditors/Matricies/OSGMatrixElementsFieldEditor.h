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

#ifndef _OSGMATRIXELEMENTSFIELDEDITOR_H_
#define _OSGMATRIXELEMENTSFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMatrixElementsFieldEditorBase.h"
#include "OSGTextFieldFields.h"
#include "OSGActionEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief MatrixElementsFieldEditor class. See \ref
           PageContribFieldContainerEditorMatrixElementsFieldEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING MatrixElementsFieldEditor : public MatrixElementsFieldEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MatrixElementsFieldEditorBase Inherited;
    typedef MatrixElementsFieldEditor     Self;

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

    virtual UInt32 getNumRequestedRows(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MatrixElementsFieldEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MatrixElementsFieldEditor(void);
    MatrixElementsFieldEditor(const MatrixElementsFieldEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MatrixElementsFieldEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const MatrixElementsFieldEditor *Id = NULL);
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

    static std::vector<const DataType*> _EditableTypes;

    typedef std::vector<TextFieldRefPtr> TextFieldsVector;
    TextFieldsVector _EditingTextFields;
    Int16 _SelectedTextField;
    std::string _InitialValue;
    
    void handleTextFieldFocusGained    (FocusEventDetails* const details,
                                        UInt32 ElementIndex);
    void handleTextFieldFocusLost      (FocusEventDetails* const details,
                                        UInt32 ElementIndex);
    void handleTextFieldActionPerformed(ActionEventDetails* const details,
                                        UInt32 ElementIndex);
    void handleTextFieldKeyTyped       (KeyEventDetails* const details,
                                        UInt32 ElementIndex);

    typedef std::vector<boost::signals2::connection> ConnectionsVector;
    ConnectionsVector _TextFieldConnections;
    
    std::string getEditorValue(void) const;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MatrixElementsFieldEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MatrixElementsFieldEditor &source);
};

typedef MatrixElementsFieldEditor *MatrixElementsFieldEditorP;

OSG_END_NAMESPACE

#include "OSGMatrixElementsFieldEditorBase.inl"
#include "OSGMatrixElementsFieldEditor.inl"

#endif /* _OSGMATRIXELEMENTSFIELDEDITOR_H_ */
