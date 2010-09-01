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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGQuaternionEulerFieldEditor.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSysFieldTraits.h"
#include "OSGMathFieldTraits.h"
#include "OSGMathFields.h"
#include "OSGStringUtils.h"
#include "OSGSpinner.h"
#include "OSGLabel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGQuaternionEulerFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGQuaternionEulerFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const DataType*> QuaternionEulerFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void QuaternionEulerFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        _EditableTypes.push_back(&FieldTraits<Quaternion>::getType());
        //_EditableTypes.push_back(&FieldTraits<Quaternionfx>::getType());

        
        for(UInt32 i(0) ; i<_EditableTypes.size(); ++i)
        {
            FieldEditorFactory::the()->setSingleDefaultEditor(_EditableTypes[i], &getClassType());
            FieldEditorFactory::the()->setEditorType(_EditableTypes[i], &getClassType(), "Euler");
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool QuaternionEulerFieldEditor::internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    Inherited::internalAttachField(fc, fieldId, index);
    const DataType& type(fc->getFieldDescription(fieldId)->getFieldType().getContentType());

    for(UInt32 i(0) ; i<_SpinnerStateChangedConnections.size() ; ++i)
    {
        _SpinnerStateChangedConnections[i].disconnect();
    }

    _SpinnerStateChangedConnections.clear();

    _EditingSpinnerModels.clear();
    
    if(type == FieldTraits<Quaternion>::getType())
    {
        for(UInt8 i(0) ; i<3 ; ++i)
        {
            Real32SpinnerModelPtr model(new Real32SpinnerModel());
            model->setMaximum(TypeTraits<Real32>::getMax());
            model->setMinimum(TypeTraits<Real32>::getMin());
            model->setStepSize(TypeTraits<Real32>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners[i]->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels[i]->connectStateChanged(boost::bind(&QuaternionEulerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    /*else if(type == FieldTraits<Quaternionfx>::getType())
    {
        for(UInt8 i(0) ; i<3 ; ++i)
        {
            Fixed32SpinnerModelPtr model(new Fixed32SpinnerModel());
            model->setMaximum(TypeTraits<Fixed32>::getMax());
            model->setMinimum(TypeTraits<Fixed32>::getMin());
            model->setStepSize(TypeTraits<Fixed32>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners[i]->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinners[i]->connectStateChanged(boost::bind(&QuaternionEulerFieldEditor::handleSpinnerStateChanged, this, _1));
        }
    }*/
    else
    {
        return false;
    }

    return true;
}

void QuaternionEulerFieldEditor::internalFieldChanged (void)
{
    const DataType& type(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType());
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

    for(UInt32 i(0) ; i<_SpinnerStateChangedConnections.size() ; ++i)
    {
        _SpinnerStateChangedConnections[i].disconnect();
    }

    _SpinnerStateChangedConnections.clear();

    if(type == FieldTraits<Quaternion>::getType())
    {
        Quaternion Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFQuaternion*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFQuaternion*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        //Get the Euler angles
        Vec3f EulerValue;
        Value.getEulerAngleDeg(EulerValue);
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(EulerValue[i]);
        }
    }
    //else if(type == FieldTraits<Quaternionfx>::getType())
    //{
    //    Quaternion Value;
    //    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    //    {
    //        Value = static_cast<const SFQuaternionfx*>(TheFieldHandle->getField())->getValue();
    //    }
    //    else
    //    {
    //        Value = static_cast<const MFQuaternionfx*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
    //    }
    //    //Get the Euler angles
    //    Vec3fx EulerValue;
    //    Value.getEulerAngleDeg(EulerValue);
    //    for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
    //    {
    //        static_cast<Fixed32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(EulerValue[i]);
    //    }
    //}
    else
    {
        assert(false && "Should not reach this.");
    }
    for(UInt32 i(0) ; i<_EditingSpinners.size() ; ++i)
    {
        _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels[i]->connectStateChanged(boost::bind(&QuaternionEulerFieldEditor::handleSpinnerStateChanged, this, _1)));
    }
}

void QuaternionEulerFieldEditor::internalStartEditing (void)
{
}

void QuaternionEulerFieldEditor::internalStopEditing  (void)
{
}

void QuaternionEulerFieldEditor::runCommand  (void)
{
    //Call the command to set the Field

    Quaternion q;
    q.setValue(osgDegree2Rad(boost::any_cast<Real32>(_EditingSpinnerModels[0]->getValue())),
               osgDegree2Rad(boost::any_cast<Real32>(_EditingSpinnerModels[1]->getValue())),
               osgDegree2Rad(boost::any_cast<Real32>(_EditingSpinnerModels[2]->getValue())));

    std::string Value("");
    for(UInt32 i(0) ; i<4 ; ++i)
    {
        Value += boost::lexical_cast<std::string>(q[i]) + " ";
    }

    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), 
                                                                      getEditingFieldId(), 
                                                                      Value, 
                                                                      getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void QuaternionEulerFieldEditor::internalCancelEditing(void)
{
}

const std::vector<const DataType*>& QuaternionEulerFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void QuaternionEulerFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);
    
    Vec2f LabelSize(25.0f, BottomRight.y() - TopLeft.y());

    Vec2f SpinnerSize(BottomRight - TopLeft - Vec2f(_EditingSpinners.size()-1,0.0f));
    SpinnerSize[0] = (SpinnerSize[0]/static_cast<Real32>(_EditingSpinners.size()))-LabelSize[0];

    for(UInt32 i(0) ; i<_EditingSpinners.size() ; ++i)
    {
        _EditingLabels[i]->setPosition(TopLeft + Vec2f(LabelSize.x() * static_cast<Real32>(i) + (SpinnerSize.x() + 1.0f) * static_cast<Real32>(i), 0.0f));
        _EditingLabels[i]->setSize(LabelSize);
        _EditingSpinners[i]->setPosition(TopLeft + Vec2f(LabelSize.x() * static_cast<Real32>(i+1) + (SpinnerSize.x() + 1.0f) * static_cast<Real32>(i), 0.0f));
        _EditingSpinners[i]->setSize(SpinnerSize);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

QuaternionEulerFieldEditor::QuaternionEulerFieldEditor(void) :
    Inherited()
{
}

QuaternionEulerFieldEditor::QuaternionEulerFieldEditor(const QuaternionEulerFieldEditor &source) :
    Inherited(source)
{
}

QuaternionEulerFieldEditor::~QuaternionEulerFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/
void QuaternionEulerFieldEditor::onCreate(const QuaternionEulerFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        //Labels
        for(UInt8 i(0) ; i<3 ; ++i)
        {
            _EditingSpinners.push_back(Spinner::create());
            _EditingLabels.push_back(Label::create());
            _EditingLabels.back()->setAlignment(Vec2f(0.85f, 0.5f));
            switch(i)
            {
            case 0:
                _EditingLabels.back()->setText("X");
                break;
            case 1:
                _EditingLabels.back()->setText("Y");
                break;
            case 2:
                _EditingLabels.back()->setText("Z");
                break;
            }
            pushToChildren(_EditingLabels.back());
            pushToChildren(_EditingSpinners.back());
        }
    }
}

void QuaternionEulerFieldEditor::onDestroy()
{
}

void QuaternionEulerFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingSpinners.clear();
    _EditingLabels.clear();
    _EditingSpinnerModels.clear();

    for(UInt32 i(0) ; i<_SpinnerStateChangedConnections.size() ; ++i)
    {
        _SpinnerStateChangedConnections[i].disconnect();
    }
    _SpinnerStateChangedConnections.clear();
}


void QuaternionEulerFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void QuaternionEulerFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump QuaternionEulerFieldEditor NI" << std::endl;
}

void QuaternionEulerFieldEditor::handleSpinnerStateChanged(ChangeEventDetails* const details)
{
    runCommand();
}

OSG_END_NAMESPACE
