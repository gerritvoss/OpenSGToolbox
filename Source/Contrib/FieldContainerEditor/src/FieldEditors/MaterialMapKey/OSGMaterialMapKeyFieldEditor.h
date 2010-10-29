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

#ifndef _OSGMATERIALMAPKEYFIELDEDITOR_H_
#define _OSGMATERIALMAPKEYFIELDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMaterialMapKeyFieldEditorBase.h"
#include "OSGTextFieldFields.h"
#include "OSGActionEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief MaterialMapKeyFieldEditor class. See \ref
           PageContribFieldContainerEditorMaterialMapKeyFieldEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING MaterialMapKeyFieldEditor : public MaterialMapKeyFieldEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MaterialMapKeyFieldEditorBase Inherited;
    typedef MaterialMapKeyFieldEditor     Self;

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

    // Variables should all be in MaterialMapKeyFieldEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MaterialMapKeyFieldEditor(void);
    MaterialMapKeyFieldEditor(const MaterialMapKeyFieldEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MaterialMapKeyFieldEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const MaterialMapKeyFieldEditor *Id = NULL);
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
    void         runCommand           (void);

    static std::vector<const DataType*> _EditableTypes;
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
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MaterialMapKeyFieldEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MaterialMapKeyFieldEditor &source);
};

typedef MaterialMapKeyFieldEditor *MaterialMapKeyFieldEditorP;

OSG_END_NAMESPACE

#include "OSGMaterialMapKeyFieldEditorBase.inl"
#include "OSGMaterialMapKeyFieldEditor.inl"

#endif /* _OSGMATERIALMAPKEYFIELDEDITOR_H_ */
