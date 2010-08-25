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

#ifndef _OSGQUATERNIONEULERFIELDEDITOR_H_
#define _OSGQUATERNIONEULERFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQuaternionEulerFieldEditorBase.h"
#include "OSGSpinnerFields.h"
#include "OSGLabelFields.h"
#include "OSGChangeEventDetailsFields.h"
#include "OSGNumberSpinnerModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief QuaternionEulerFieldEditor class. See \ref
           PageContribFieldContainerEditorQuaternionEulerFieldEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING QuaternionEulerFieldEditor : public QuaternionEulerFieldEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef QuaternionEulerFieldEditorBase Inherited;
    typedef QuaternionEulerFieldEditor     Self;

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

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in QuaternionEulerFieldEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    QuaternionEulerFieldEditor(void);
    QuaternionEulerFieldEditor(const QuaternionEulerFieldEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~QuaternionEulerFieldEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const QuaternionEulerFieldEditor *Id = NULL);
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
    virtual bool internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index);
    virtual void updateLayout         (void);
    void         runCommand           (void);

    static std::vector<const DataType*> _EditableTypes;
    std::vector<SpinnerRefPtr>   _EditingSpinners;
    std::vector<LabelRefPtr>   _EditingLabels;
    std::vector<SpinnerModelPtr> _EditingSpinnerModels;
    
    void handleSpinnerStateChanged(ChangeEventDetails* const details);
    std::vector<boost::signals2::connection> _SpinnerStateChangedConnections;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class QuaternionEulerFieldEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const QuaternionEulerFieldEditor &source);
};

typedef QuaternionEulerFieldEditor *QuaternionEulerFieldEditorP;

OSG_END_NAMESPACE

#include "OSGQuaternionEulerFieldEditorBase.inl"
#include "OSGQuaternionEulerFieldEditor.inl"

#endif /* _OSGQUATERNIONEULERFIELDEDITOR_H_ */
