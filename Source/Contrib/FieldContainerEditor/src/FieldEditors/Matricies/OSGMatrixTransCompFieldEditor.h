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

#ifndef _OSGMATRIXTRANSCOMPFIELDEDITOR_H_
#define _OSGMATRIXTRANSCOMPFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMatrixTransCompFieldEditorBase.h"
#include "OSGSpinnerFields.h"
#include "OSGLabelFields.h"
#include "OSGChangeEventDetailsFields.h"
#include "OSGNumberSpinnerModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief MatrixTransCompFieldEditor class. See \ref
           PageContribFieldContainerEditorMatrixTransCompFieldEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING MatrixTransCompFieldEditor : public MatrixTransCompFieldEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MatrixTransCompFieldEditorBase Inherited;
    typedef MatrixTransCompFieldEditor     Self;

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

    // Variables should all be in MatrixTransCompFieldEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MatrixTransCompFieldEditor(void);
    MatrixTransCompFieldEditor(const MatrixTransCompFieldEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MatrixTransCompFieldEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const MatrixTransCompFieldEditor *Id = NULL);
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
    virtual void updateLayout         (void);
    virtual bool internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index);
    void         runCommand           (void);

    static std::vector<const DataType*> _EditableTypes;

    //Translation
    SpinnerRefPtr   _TranslationXEditingSpinner,
                    _TranslationYEditingSpinner,
                    _TranslationZEditingSpinner;

    SpinnerModelPtr _TranslationXEditingSpinnerModels,
                    _TranslationYEditingSpinnerModels,
                    _TranslationZEditingSpinnerModels;

    LabelRefPtr     _TranslationXEditingLabel,
                    _TranslationYEditingLabel,
                    _TranslationZEditingLabel;

    LabelRefPtr   _TranslationEditingLabel;

    //Rotation
    SpinnerRefPtr   _RotationXEditingSpinner,
                    _RotationYEditingSpinner,
                    _RotationZEditingSpinner;

    SpinnerModelPtr _RotationXEditingSpinnerModels,
                    _RotationYEditingSpinnerModels,
                    _RotationZEditingSpinnerModels;

    LabelRefPtr     _RotationXEditingLabel,
                    _RotationYEditingLabel,
                    _RotationZEditingLabel;

    LabelRefPtr   _RotationEditingLabel;

    //Scale
    SpinnerRefPtr   _ScaleXEditingSpinner,
                    _ScaleYEditingSpinner,
                    _ScaleZEditingSpinner;

    SpinnerModelPtr _ScaleXEditingSpinnerModels,
                    _ScaleYEditingSpinnerModels,
                    _ScaleZEditingSpinnerModels;

    LabelRefPtr     _ScaleXEditingLabel,
                    _ScaleYEditingLabel,
                    _ScaleZEditingLabel;

    LabelRefPtr   _ScaleEditingLabel;
    
    void handleSpinnerStateChanged(ChangeEventDetails* const details);

    typedef std::vector<boost::signals2::connection> ConnectionsVector;
    ConnectionsVector _SpinnerStateChangedConnections;
    
    std::string getEditorValue(void) const;
    SpinnerModelPtr createSpinnerModel(const DataType& type, Real32 stepSize) const;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MatrixTransCompFieldEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MatrixTransCompFieldEditor &source);
};

typedef MatrixTransCompFieldEditor *MatrixTransCompFieldEditorP;

OSG_END_NAMESPACE

#include "OSGMatrixTransCompFieldEditorBase.inl"
#include "OSGMatrixTransCompFieldEditor.inl"

#endif /* _OSGMATRIXTRANSCOMPFIELDEDITOR_H_ */
