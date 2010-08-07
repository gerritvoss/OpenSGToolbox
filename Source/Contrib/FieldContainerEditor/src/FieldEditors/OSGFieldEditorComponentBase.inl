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
 **     class FieldEditorComponent!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &FieldEditorComponentBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 FieldEditorComponentBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 FieldEditorComponentBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the FieldEditorComponent::_sfEditingFC field.
inline
FieldContainer * FieldEditorComponentBase::getEditingFC(void) const
{
    return _sfEditingFC.getValue();
}

//! Set the value of the FieldEditorComponent::_sfEditingFC field.
inline
void FieldEditorComponentBase::setEditingFC(FieldContainer * const value)
{
    editSField(EditingFCFieldMask);

    _sfEditingFC.setValue(value);
}
//! Get the value of the FieldEditorComponent::_sfEditingFieldId field.

inline
UInt32 &FieldEditorComponentBase::editEditingFieldId(void)
{
    editSField(EditingFieldIdFieldMask);

    return _sfEditingFieldId.getValue();
}

//! Get the value of the FieldEditorComponent::_sfEditingFieldId field.
inline
      UInt32  FieldEditorComponentBase::getEditingFieldId(void) const
{
    return _sfEditingFieldId.getValue();
}

//! Set the value of the FieldEditorComponent::_sfEditingFieldId field.
inline
void FieldEditorComponentBase::setEditingFieldId(const UInt32 value)
{
    editSField(EditingFieldIdFieldMask);

    _sfEditingFieldId.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void FieldEditorComponentBase::execSync (      FieldEditorComponentBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (EditingFCFieldMask & whichField))
        _sfEditingFC.syncWith(pFrom->_sfEditingFC);

    if(FieldBits::NoField != (EditingFieldIdFieldMask & whichField))
        _sfEditingFieldId.syncWith(pFrom->_sfEditingFieldId);
}
#endif


inline
const Char8 *FieldEditorComponentBase::getClassname(void)
{
    return "FieldEditorComponent";
}
OSG_GEN_CONTAINERPTR(FieldEditorComponent);

OSG_END_NAMESPACE

