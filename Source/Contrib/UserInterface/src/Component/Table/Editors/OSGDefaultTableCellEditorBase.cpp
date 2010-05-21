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

#include <cstdlib>
#include <cstdio>
#include <boost/assign/list_of.hpp>

#include "OSGConfig.h"



#include "OSGTextField.h"               // DefaultEditor Class
#include "OSGSpinner.h"                 // DefaultNumberEditor Class
#include "OSGComboBox.h"                // DefaultGLenumEditor Class
#include "OSGCheckboxButton.h"          // DefaultBoolEditor Class

#include "OSGDefaultTableCellEditorBase.h"
#include "OSGDefaultTableCellEditor.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DefaultTableCellEditor
    A UI Default Table Cell Editor.
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var UInt32          DefaultTableCellEditorBase::_sfClickCountToStart
    
*/

/*! \var TextField *     DefaultTableCellEditorBase::_sfDefaultEditor
    
*/

/*! \var TextField *     DefaultTableCellEditorBase::_sfDefaultStringEditor
    
*/

/*! \var Spinner *       DefaultTableCellEditorBase::_sfDefaultNumberEditor
    
*/

/*! \var ComboBox *      DefaultTableCellEditorBase::_sfDefaultGLenumEditor
    
*/

/*! \var CheckboxButton * DefaultTableCellEditorBase::_sfDefaultBoolEditor
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<DefaultTableCellEditor *>::_type("DefaultTableCellEditorPtr", "TableCellEditorPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(DefaultTableCellEditor *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           DefaultTableCellEditor *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           DefaultTableCellEditor *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void DefaultTableCellEditorBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUInt32::Description(
        SFUInt32::getClassType(),
        "ClickCountToStart",
        "",
        ClickCountToStartFieldId, ClickCountToStartFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DefaultTableCellEditor::editHandleClickCountToStart),
        static_cast<FieldGetMethodSig >(&DefaultTableCellEditor::getHandleClickCountToStart));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecTextFieldPtr::Description(
        SFUnrecTextFieldPtr::getClassType(),
        "DefaultEditor",
        "",
        DefaultEditorFieldId, DefaultEditorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DefaultTableCellEditor::editHandleDefaultEditor),
        static_cast<FieldGetMethodSig >(&DefaultTableCellEditor::getHandleDefaultEditor));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecTextFieldPtr::Description(
        SFUnrecTextFieldPtr::getClassType(),
        "DefaultStringEditor",
        "",
        DefaultStringEditorFieldId, DefaultStringEditorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DefaultTableCellEditor::editHandleDefaultStringEditor),
        static_cast<FieldGetMethodSig >(&DefaultTableCellEditor::getHandleDefaultStringEditor));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecSpinnerPtr::Description(
        SFUnrecSpinnerPtr::getClassType(),
        "DefaultNumberEditor",
        "",
        DefaultNumberEditorFieldId, DefaultNumberEditorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DefaultTableCellEditor::editHandleDefaultNumberEditor),
        static_cast<FieldGetMethodSig >(&DefaultTableCellEditor::getHandleDefaultNumberEditor));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecComboBoxPtr::Description(
        SFUnrecComboBoxPtr::getClassType(),
        "DefaultGLenumEditor",
        "",
        DefaultGLenumEditorFieldId, DefaultGLenumEditorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DefaultTableCellEditor::editHandleDefaultGLenumEditor),
        static_cast<FieldGetMethodSig >(&DefaultTableCellEditor::getHandleDefaultGLenumEditor));

    oType.addInitialDesc(pDesc);

    pDesc = new SFUnrecCheckboxButtonPtr::Description(
        SFUnrecCheckboxButtonPtr::getClassType(),
        "DefaultBoolEditor",
        "",
        DefaultBoolEditorFieldId, DefaultBoolEditorFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&DefaultTableCellEditor::editHandleDefaultBoolEditor),
        static_cast<FieldGetMethodSig >(&DefaultTableCellEditor::getHandleDefaultBoolEditor));

    oType.addInitialDesc(pDesc);
}


DefaultTableCellEditorBase::TypeObject DefaultTableCellEditorBase::_type(
    DefaultTableCellEditorBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&DefaultTableCellEditorBase::createEmptyLocal),
    DefaultTableCellEditor::initMethod,
    DefaultTableCellEditor::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&DefaultTableCellEditor::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\"?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"DefaultTableCellEditor\"\n"
    "    parent=\"TableCellEditor\"\n"
    "    library=\"ContribUserInterface\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    structure=\"concrete\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    decoratable=\"false\"\n"
    "    useLocalIncludes=\"false\"\n"
    "    isNodeCore=\"false\"\n"
    "    authors=\"David Kabala (djkabala@gmail.com)                             \"\n"
    "    >\n"
    "    A UI Default Table Cell Editor.\n"
    "    <Field\n"
    "        name=\"ClickCountToStart\"\n"
    "        type=\"UInt32\"\n"
    "        category=\"data\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"3\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"DefaultEditor\"\n"
    "        type=\"TextField\"\n"
    "        category=\"pointer\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"DefaultStringEditor\"\n"
    "        type=\"TextField\"\n"
    "        category=\"pointer\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"DefaultNumberEditor\"\n"
    "        type=\"Spinner\"\n"
    "        category=\"pointer\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"DefaultGLenumEditor\"\n"
    "        type=\"ComboBox\"\n"
    "        category=\"pointer\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "    <Field\n"
    "        name=\"DefaultBoolEditor\"\n"
    "        type=\"CheckboxButton\"\n"
    "        category=\"pointer\"\n"
    "        cardinality=\"single\"\n"
    "        visibility=\"external\"\n"
    "        defaultValue=\"NULL\"\n"
    "        access=\"public\"\n"
    "        >\n"
    "    </Field>\n"
    "</FieldContainer>\n",
    "A UI Default Table Cell Editor.\n"
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &DefaultTableCellEditorBase::getType(void)
{
    return _type;
}

const FieldContainerType &DefaultTableCellEditorBase::getType(void) const
{
    return _type;
}

UInt32 DefaultTableCellEditorBase::getContainerSize(void) const
{
    return sizeof(DefaultTableCellEditor);
}

/*------------------------- decorator get ------------------------------*/


SFUInt32 *DefaultTableCellEditorBase::editSFClickCountToStart(void)
{
    editSField(ClickCountToStartFieldMask);

    return &_sfClickCountToStart;
}

const SFUInt32 *DefaultTableCellEditorBase::getSFClickCountToStart(void) const
{
    return &_sfClickCountToStart;
}


//! Get the DefaultTableCellEditor::_sfDefaultEditor field.
const SFUnrecTextFieldPtr *DefaultTableCellEditorBase::getSFDefaultEditor(void) const
{
    return &_sfDefaultEditor;
}

SFUnrecTextFieldPtr *DefaultTableCellEditorBase::editSFDefaultEditor  (void)
{
    editSField(DefaultEditorFieldMask);

    return &_sfDefaultEditor;
}

//! Get the DefaultTableCellEditor::_sfDefaultStringEditor field.
const SFUnrecTextFieldPtr *DefaultTableCellEditorBase::getSFDefaultStringEditor(void) const
{
    return &_sfDefaultStringEditor;
}

SFUnrecTextFieldPtr *DefaultTableCellEditorBase::editSFDefaultStringEditor(void)
{
    editSField(DefaultStringEditorFieldMask);

    return &_sfDefaultStringEditor;
}

//! Get the DefaultTableCellEditor::_sfDefaultNumberEditor field.
const SFUnrecSpinnerPtr *DefaultTableCellEditorBase::getSFDefaultNumberEditor(void) const
{
    return &_sfDefaultNumberEditor;
}

SFUnrecSpinnerPtr   *DefaultTableCellEditorBase::editSFDefaultNumberEditor(void)
{
    editSField(DefaultNumberEditorFieldMask);

    return &_sfDefaultNumberEditor;
}

//! Get the DefaultTableCellEditor::_sfDefaultGLenumEditor field.
const SFUnrecComboBoxPtr *DefaultTableCellEditorBase::getSFDefaultGLenumEditor(void) const
{
    return &_sfDefaultGLenumEditor;
}

SFUnrecComboBoxPtr  *DefaultTableCellEditorBase::editSFDefaultGLenumEditor(void)
{
    editSField(DefaultGLenumEditorFieldMask);

    return &_sfDefaultGLenumEditor;
}

//! Get the DefaultTableCellEditor::_sfDefaultBoolEditor field.
const SFUnrecCheckboxButtonPtr *DefaultTableCellEditorBase::getSFDefaultBoolEditor(void) const
{
    return &_sfDefaultBoolEditor;
}

SFUnrecCheckboxButtonPtr *DefaultTableCellEditorBase::editSFDefaultBoolEditor(void)
{
    editSField(DefaultBoolEditorFieldMask);

    return &_sfDefaultBoolEditor;
}





/*------------------------------ access -----------------------------------*/

UInt32 DefaultTableCellEditorBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ClickCountToStartFieldMask & whichField))
    {
        returnValue += _sfClickCountToStart.getBinSize();
    }
    if(FieldBits::NoField != (DefaultEditorFieldMask & whichField))
    {
        returnValue += _sfDefaultEditor.getBinSize();
    }
    if(FieldBits::NoField != (DefaultStringEditorFieldMask & whichField))
    {
        returnValue += _sfDefaultStringEditor.getBinSize();
    }
    if(FieldBits::NoField != (DefaultNumberEditorFieldMask & whichField))
    {
        returnValue += _sfDefaultNumberEditor.getBinSize();
    }
    if(FieldBits::NoField != (DefaultGLenumEditorFieldMask & whichField))
    {
        returnValue += _sfDefaultGLenumEditor.getBinSize();
    }
    if(FieldBits::NoField != (DefaultBoolEditorFieldMask & whichField))
    {
        returnValue += _sfDefaultBoolEditor.getBinSize();
    }

    return returnValue;
}

void DefaultTableCellEditorBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ClickCountToStartFieldMask & whichField))
    {
        _sfClickCountToStart.copyToBin(pMem);
    }
    if(FieldBits::NoField != (DefaultEditorFieldMask & whichField))
    {
        _sfDefaultEditor.copyToBin(pMem);
    }
    if(FieldBits::NoField != (DefaultStringEditorFieldMask & whichField))
    {
        _sfDefaultStringEditor.copyToBin(pMem);
    }
    if(FieldBits::NoField != (DefaultNumberEditorFieldMask & whichField))
    {
        _sfDefaultNumberEditor.copyToBin(pMem);
    }
    if(FieldBits::NoField != (DefaultGLenumEditorFieldMask & whichField))
    {
        _sfDefaultGLenumEditor.copyToBin(pMem);
    }
    if(FieldBits::NoField != (DefaultBoolEditorFieldMask & whichField))
    {
        _sfDefaultBoolEditor.copyToBin(pMem);
    }
}

void DefaultTableCellEditorBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ClickCountToStartFieldMask & whichField))
    {
        _sfClickCountToStart.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (DefaultEditorFieldMask & whichField))
    {
        _sfDefaultEditor.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (DefaultStringEditorFieldMask & whichField))
    {
        _sfDefaultStringEditor.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (DefaultNumberEditorFieldMask & whichField))
    {
        _sfDefaultNumberEditor.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (DefaultGLenumEditorFieldMask & whichField))
    {
        _sfDefaultGLenumEditor.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (DefaultBoolEditorFieldMask & whichField))
    {
        _sfDefaultBoolEditor.copyFromBin(pMem);
    }
}

//! create a new instance of the class
DefaultTableCellEditorTransitPtr DefaultTableCellEditorBase::createLocal(BitVector bFlags)
{
    DefaultTableCellEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<DefaultTableCellEditor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
DefaultTableCellEditorTransitPtr DefaultTableCellEditorBase::createDependent(BitVector bFlags)
{
    DefaultTableCellEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<DefaultTableCellEditor>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
DefaultTableCellEditorTransitPtr DefaultTableCellEditorBase::create(void)
{
    DefaultTableCellEditorTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<DefaultTableCellEditor>(tmpPtr);
    }

    return fc;
}

DefaultTableCellEditor *DefaultTableCellEditorBase::createEmptyLocal(BitVector bFlags)
{
    DefaultTableCellEditor *returnValue;

    newPtr<DefaultTableCellEditor>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
DefaultTableCellEditor *DefaultTableCellEditorBase::createEmpty(void)
{
    DefaultTableCellEditor *returnValue;

    newPtr<DefaultTableCellEditor>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr DefaultTableCellEditorBase::shallowCopyLocal(
    BitVector bFlags) const
{
    DefaultTableCellEditor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DefaultTableCellEditor *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr DefaultTableCellEditorBase::shallowCopyDependent(
    BitVector bFlags) const
{
    DefaultTableCellEditor *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const DefaultTableCellEditor *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr DefaultTableCellEditorBase::shallowCopy(void) const
{
    DefaultTableCellEditor *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const DefaultTableCellEditor *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

DefaultTableCellEditorBase::DefaultTableCellEditorBase(void) :
    Inherited(),
    _sfClickCountToStart      (UInt32(3)),
    _sfDefaultEditor          (NULL),
    _sfDefaultStringEditor    (NULL),
    _sfDefaultNumberEditor    (NULL),
    _sfDefaultGLenumEditor    (NULL),
    _sfDefaultBoolEditor      (NULL)
{
}

DefaultTableCellEditorBase::DefaultTableCellEditorBase(const DefaultTableCellEditorBase &source) :
    Inherited(source),
    _sfClickCountToStart      (source._sfClickCountToStart      ),
    _sfDefaultEditor          (NULL),
    _sfDefaultStringEditor    (NULL),
    _sfDefaultNumberEditor    (NULL),
    _sfDefaultGLenumEditor    (NULL),
    _sfDefaultBoolEditor      (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

DefaultTableCellEditorBase::~DefaultTableCellEditorBase(void)
{
}

void DefaultTableCellEditorBase::onCreate(const DefaultTableCellEditor *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        DefaultTableCellEditor *pThis = static_cast<DefaultTableCellEditor *>(this);

        pThis->setDefaultEditor(source->getDefaultEditor());

        pThis->setDefaultStringEditor(source->getDefaultStringEditor());

        pThis->setDefaultNumberEditor(source->getDefaultNumberEditor());

        pThis->setDefaultGLenumEditor(source->getDefaultGLenumEditor());

        pThis->setDefaultBoolEditor(source->getDefaultBoolEditor());
    }
}

GetFieldHandlePtr DefaultTableCellEditorBase::getHandleClickCountToStart (void) const
{
    SFUInt32::GetHandlePtr returnValue(
        new  SFUInt32::GetHandle(
             &_sfClickCountToStart,
             this->getType().getFieldDesc(ClickCountToStartFieldId),
             const_cast<DefaultTableCellEditorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DefaultTableCellEditorBase::editHandleClickCountToStart(void)
{
    SFUInt32::EditHandlePtr returnValue(
        new  SFUInt32::EditHandle(
             &_sfClickCountToStart,
             this->getType().getFieldDesc(ClickCountToStartFieldId),
             this));


    editSField(ClickCountToStartFieldMask);

    return returnValue;
}

GetFieldHandlePtr DefaultTableCellEditorBase::getHandleDefaultEditor   (void) const
{
    SFUnrecTextFieldPtr::GetHandlePtr returnValue(
        new  SFUnrecTextFieldPtr::GetHandle(
             &_sfDefaultEditor,
             this->getType().getFieldDesc(DefaultEditorFieldId),
             const_cast<DefaultTableCellEditorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DefaultTableCellEditorBase::editHandleDefaultEditor  (void)
{
    SFUnrecTextFieldPtr::EditHandlePtr returnValue(
        new  SFUnrecTextFieldPtr::EditHandle(
             &_sfDefaultEditor,
             this->getType().getFieldDesc(DefaultEditorFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DefaultTableCellEditor::setDefaultEditor,
                    static_cast<DefaultTableCellEditor *>(this), _1));

    editSField(DefaultEditorFieldMask);

    return returnValue;
}

GetFieldHandlePtr DefaultTableCellEditorBase::getHandleDefaultStringEditor (void) const
{
    SFUnrecTextFieldPtr::GetHandlePtr returnValue(
        new  SFUnrecTextFieldPtr::GetHandle(
             &_sfDefaultStringEditor,
             this->getType().getFieldDesc(DefaultStringEditorFieldId),
             const_cast<DefaultTableCellEditorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DefaultTableCellEditorBase::editHandleDefaultStringEditor(void)
{
    SFUnrecTextFieldPtr::EditHandlePtr returnValue(
        new  SFUnrecTextFieldPtr::EditHandle(
             &_sfDefaultStringEditor,
             this->getType().getFieldDesc(DefaultStringEditorFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DefaultTableCellEditor::setDefaultStringEditor,
                    static_cast<DefaultTableCellEditor *>(this), _1));

    editSField(DefaultStringEditorFieldMask);

    return returnValue;
}

GetFieldHandlePtr DefaultTableCellEditorBase::getHandleDefaultNumberEditor (void) const
{
    SFUnrecSpinnerPtr::GetHandlePtr returnValue(
        new  SFUnrecSpinnerPtr::GetHandle(
             &_sfDefaultNumberEditor,
             this->getType().getFieldDesc(DefaultNumberEditorFieldId),
             const_cast<DefaultTableCellEditorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DefaultTableCellEditorBase::editHandleDefaultNumberEditor(void)
{
    SFUnrecSpinnerPtr::EditHandlePtr returnValue(
        new  SFUnrecSpinnerPtr::EditHandle(
             &_sfDefaultNumberEditor,
             this->getType().getFieldDesc(DefaultNumberEditorFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DefaultTableCellEditor::setDefaultNumberEditor,
                    static_cast<DefaultTableCellEditor *>(this), _1));

    editSField(DefaultNumberEditorFieldMask);

    return returnValue;
}

GetFieldHandlePtr DefaultTableCellEditorBase::getHandleDefaultGLenumEditor (void) const
{
    SFUnrecComboBoxPtr::GetHandlePtr returnValue(
        new  SFUnrecComboBoxPtr::GetHandle(
             &_sfDefaultGLenumEditor,
             this->getType().getFieldDesc(DefaultGLenumEditorFieldId),
             const_cast<DefaultTableCellEditorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DefaultTableCellEditorBase::editHandleDefaultGLenumEditor(void)
{
    SFUnrecComboBoxPtr::EditHandlePtr returnValue(
        new  SFUnrecComboBoxPtr::EditHandle(
             &_sfDefaultGLenumEditor,
             this->getType().getFieldDesc(DefaultGLenumEditorFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DefaultTableCellEditor::setDefaultGLenumEditor,
                    static_cast<DefaultTableCellEditor *>(this), _1));

    editSField(DefaultGLenumEditorFieldMask);

    return returnValue;
}

GetFieldHandlePtr DefaultTableCellEditorBase::getHandleDefaultBoolEditor (void) const
{
    SFUnrecCheckboxButtonPtr::GetHandlePtr returnValue(
        new  SFUnrecCheckboxButtonPtr::GetHandle(
             &_sfDefaultBoolEditor,
             this->getType().getFieldDesc(DefaultBoolEditorFieldId),
             const_cast<DefaultTableCellEditorBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr DefaultTableCellEditorBase::editHandleDefaultBoolEditor(void)
{
    SFUnrecCheckboxButtonPtr::EditHandlePtr returnValue(
        new  SFUnrecCheckboxButtonPtr::EditHandle(
             &_sfDefaultBoolEditor,
             this->getType().getFieldDesc(DefaultBoolEditorFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&DefaultTableCellEditor::setDefaultBoolEditor,
                    static_cast<DefaultTableCellEditor *>(this), _1));

    editSField(DefaultBoolEditorFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void DefaultTableCellEditorBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    DefaultTableCellEditor *pThis = static_cast<DefaultTableCellEditor *>(this);

    pThis->execSync(static_cast<DefaultTableCellEditor *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *DefaultTableCellEditorBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    DefaultTableCellEditor *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const DefaultTableCellEditor *>(pRefAspect),
                  dynamic_cast<const DefaultTableCellEditor *>(this));

    return returnValue;
}
#endif

void DefaultTableCellEditorBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<DefaultTableCellEditor *>(this)->setDefaultEditor(NULL);

    static_cast<DefaultTableCellEditor *>(this)->setDefaultStringEditor(NULL);

    static_cast<DefaultTableCellEditor *>(this)->setDefaultNumberEditor(NULL);

    static_cast<DefaultTableCellEditor *>(this)->setDefaultGLenumEditor(NULL);

    static_cast<DefaultTableCellEditor *>(this)->setDefaultBoolEditor(NULL);


}


OSG_END_NAMESPACE