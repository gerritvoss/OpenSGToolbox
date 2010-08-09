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

#ifndef _OSGBOOLFIELDEDITOR_H_
#define _OSGBOOLFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBoolFieldEditorBase.h"
#include "OSGCheckboxButtonFields.h"
#include "OSGButtonSelectedEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief BoolFieldEditor class. See \ref
           PageContribFieldContainerEditorBoolFieldEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING BoolFieldEditor : public BoolFieldEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef BoolFieldEditorBase Inherited;
    typedef BoolFieldEditor     Self;

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

    // Variables should all be in BoolFieldEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BoolFieldEditor(void);
    BoolFieldEditor(const BoolFieldEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BoolFieldEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const BoolFieldEditor *Id = NULL);
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
    void         runCommand           (bool value);

    static std::vector<const DataType*> _EditableTypes;
    CheckboxButtonRefPtr _EditingCheckbox;
    
    void handleButtonSelected(ButtonSelectedEventDetails* const details);
    void handleButtonDeselected(ButtonSelectedEventDetails* const details);
    boost::signals2::connection _ButtonSelectedConnection,
                                _ButtonDeselectedConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BoolFieldEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const BoolFieldEditor &source);
};

typedef BoolFieldEditor *BoolFieldEditorP;

OSG_END_NAMESPACE

#include "OSGBoolFieldEditorBase.inl"
#include "OSGBoolFieldEditor.inl"

#endif /* _OSGBOOLFIELDEDITOR_H_ */
