/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class DefaultTableCellEditor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &DefaultTableCellEditorBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 DefaultTableCellEditorBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 DefaultTableCellEditorBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the DefaultTableCellEditor::_sfClickCountToStart field.

inline
UInt32 &DefaultTableCellEditorBase::editClickCountToStart(void)
{
    editSField(ClickCountToStartFieldMask);

    return _sfClickCountToStart.getValue();
}

//! Get the value of the DefaultTableCellEditor::_sfClickCountToStart field.
inline
      UInt32  DefaultTableCellEditorBase::getClickCountToStart(void) const
{
    return _sfClickCountToStart.getValue();
}

//! Set the value of the DefaultTableCellEditor::_sfClickCountToStart field.
inline
void DefaultTableCellEditorBase::setClickCountToStart(const UInt32 value)
{
    editSField(ClickCountToStartFieldMask);

    _sfClickCountToStart.setValue(value);
}

//! Get the value of the DefaultTableCellEditor::_sfDefaultEditor field.
inline
TextField * DefaultTableCellEditorBase::getDefaultEditor(void) const
{
    return _sfDefaultEditor.getValue();
}

//! Set the value of the DefaultTableCellEditor::_sfDefaultEditor field.
inline
void DefaultTableCellEditorBase::setDefaultEditor(TextField * const value)
{
    editSField(DefaultEditorFieldMask);

    _sfDefaultEditor.setValue(value);
}

//! Get the value of the DefaultTableCellEditor::_sfDefaultStringEditor field.
inline
TextField * DefaultTableCellEditorBase::getDefaultStringEditor(void) const
{
    return _sfDefaultStringEditor.getValue();
}

//! Set the value of the DefaultTableCellEditor::_sfDefaultStringEditor field.
inline
void DefaultTableCellEditorBase::setDefaultStringEditor(TextField * const value)
{
    editSField(DefaultStringEditorFieldMask);

    _sfDefaultStringEditor.setValue(value);
}

//! Get the value of the DefaultTableCellEditor::_sfDefaultNumberEditor field.
inline
Spinner * DefaultTableCellEditorBase::getDefaultNumberEditor(void) const
{
    return _sfDefaultNumberEditor.getValue();
}

//! Set the value of the DefaultTableCellEditor::_sfDefaultNumberEditor field.
inline
void DefaultTableCellEditorBase::setDefaultNumberEditor(Spinner * const value)
{
    editSField(DefaultNumberEditorFieldMask);

    _sfDefaultNumberEditor.setValue(value);
}

//! Get the value of the DefaultTableCellEditor::_sfDefaultGLenumEditor field.
inline
ComboBox * DefaultTableCellEditorBase::getDefaultGLenumEditor(void) const
{
    return _sfDefaultGLenumEditor.getValue();
}

//! Set the value of the DefaultTableCellEditor::_sfDefaultGLenumEditor field.
inline
void DefaultTableCellEditorBase::setDefaultGLenumEditor(ComboBox * const value)
{
    editSField(DefaultGLenumEditorFieldMask);

    _sfDefaultGLenumEditor.setValue(value);
}

//! Get the value of the DefaultTableCellEditor::_sfDefaultBoolEditor field.
inline
CheckboxButton * DefaultTableCellEditorBase::getDefaultBoolEditor(void) const
{
    return _sfDefaultBoolEditor.getValue();
}

//! Set the value of the DefaultTableCellEditor::_sfDefaultBoolEditor field.
inline
void DefaultTableCellEditorBase::setDefaultBoolEditor(CheckboxButton * const value)
{
    editSField(DefaultBoolEditorFieldMask);

    _sfDefaultBoolEditor.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void DefaultTableCellEditorBase::execSync (      DefaultTableCellEditorBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (ClickCountToStartFieldMask & whichField))
        _sfClickCountToStart.syncWith(pFrom->_sfClickCountToStart);

    if(FieldBits::NoField != (DefaultEditorFieldMask & whichField))
        _sfDefaultEditor.syncWith(pFrom->_sfDefaultEditor);

    if(FieldBits::NoField != (DefaultStringEditorFieldMask & whichField))
        _sfDefaultStringEditor.syncWith(pFrom->_sfDefaultStringEditor);

    if(FieldBits::NoField != (DefaultNumberEditorFieldMask & whichField))
        _sfDefaultNumberEditor.syncWith(pFrom->_sfDefaultNumberEditor);

    if(FieldBits::NoField != (DefaultGLenumEditorFieldMask & whichField))
        _sfDefaultGLenumEditor.syncWith(pFrom->_sfDefaultGLenumEditor);

    if(FieldBits::NoField != (DefaultBoolEditorFieldMask & whichField))
        _sfDefaultBoolEditor.syncWith(pFrom->_sfDefaultBoolEditor);
}
#endif


inline
const Char8 *DefaultTableCellEditorBase::getClassname(void)
{
    return "DefaultTableCellEditor";
}
OSG_GEN_CONTAINERPTR(DefaultTableCellEditor);

OSG_END_NAMESPACE

