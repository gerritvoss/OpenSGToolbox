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

#include "OSGMatrixTransCompFieldEditor.h"
#include "OSGMatrix.h"
#include "OSGMathFieldTraits.h"
#include "OSGMathFields.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGTypeFactory.h"
#include "OSGFieldEditorFactory.h"
#include <boost/lexical_cast.hpp>
#include "OSGSpinner.h"
#include "OSGLabel.h"
#include <sstream>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMatrixTransCompFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGMatrixTransCompFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const DataType*> MatrixTransCompFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MatrixTransCompFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        _EditableTypes.push_back(&FieldTraits<Matrix4f>::getType());
        _EditableTypes.push_back(&FieldTraits<Matrix4fx>::getType());
        _EditableTypes.push_back(&FieldTraits<Matrix4d>::getType());
        for(UInt32 i(0) ; i<_EditableTypes.size(); ++i)
        {
            FieldEditorFactory::the()->setSingleDefaultEditor(_EditableTypes[i], &getClassType());
            FieldEditorFactory::the()->setEditorType(_EditableTypes[i], &getClassType(), "TransformationComponents");
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void MatrixTransCompFieldEditor::internalFieldChanged (void)
{
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());
    const DataType& type(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType());

    if(type == FieldTraits<Matrix4f>::getType())
    {
        Matrix Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFMatrix*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFMatrix*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        Vec3f Translation,Scale,EulerRotation;
        Quaternion Rotation, ScaleOrientation;
        Value.getTransform(Translation,Rotation,Scale,ScaleOrientation);
        Rotation.getEulerAngleDeg(EulerRotation);

        //Translation
        static_cast<Real32SpinnerModel*>(_TranslationXEditingSpinnerModels.get())->setNumberValue(Translation.x());
        static_cast<Real32SpinnerModel*>(_TranslationYEditingSpinnerModels.get())->setNumberValue(Translation.y());
        static_cast<Real32SpinnerModel*>(_TranslationZEditingSpinnerModels.get())->setNumberValue(Translation.z());
        
        //Rotation
        static_cast<Real32SpinnerModel*>(_RotationXEditingSpinnerModels.get())->setNumberValue(EulerRotation.x());
        static_cast<Real32SpinnerModel*>(_RotationYEditingSpinnerModels.get())->setNumberValue(EulerRotation.y());
        static_cast<Real32SpinnerModel*>(_RotationZEditingSpinnerModels.get())->setNumberValue(EulerRotation.z());

        //Scale
        static_cast<Real32SpinnerModel*>(_ScaleXEditingSpinnerModels.get())->setNumberValue(Scale.x());
        static_cast<Real32SpinnerModel*>(_ScaleYEditingSpinnerModels.get())->setNumberValue(Scale.y());
        static_cast<Real32SpinnerModel*>(_ScaleZEditingSpinnerModels.get())->setNumberValue(Scale.z());
    }
    else if(type == FieldTraits<Matrix4fx>::getType())
    {
        Matrix4fx Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFMatrix4fx*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFMatrix4fx*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        Vec3fx Translation,Scale,EulerRotation;
        Quaternionfx Rotation, ScaleOrientation;
        Value.getTransform(Translation,Rotation,Scale,ScaleOrientation);
        Rotation.getEulerAngleDeg(EulerRotation);

        //Translation
        static_cast<Fixed32SpinnerModel*>(_TranslationXEditingSpinnerModels.get())->setNumberValue(Translation.x());
        static_cast<Fixed32SpinnerModel*>(_TranslationYEditingSpinnerModels.get())->setNumberValue(Translation.y());
        static_cast<Fixed32SpinnerModel*>(_TranslationZEditingSpinnerModels.get())->setNumberValue(Translation.z());
        
        //Rotation
        static_cast<Fixed32SpinnerModel*>(_RotationXEditingSpinnerModels.get())->setNumberValue(EulerRotation.x());
        static_cast<Fixed32SpinnerModel*>(_RotationYEditingSpinnerModels.get())->setNumberValue(EulerRotation.y());
        static_cast<Fixed32SpinnerModel*>(_RotationZEditingSpinnerModels.get())->setNumberValue(EulerRotation.z());

        //Scale
        static_cast<Fixed32SpinnerModel*>(_ScaleXEditingSpinnerModels.get())->setNumberValue(Scale.x());
        static_cast<Fixed32SpinnerModel*>(_ScaleYEditingSpinnerModels.get())->setNumberValue(Scale.y());
        static_cast<Fixed32SpinnerModel*>(_ScaleZEditingSpinnerModels.get())->setNumberValue(Scale.z());
    }
    else if(type == FieldTraits<Matrix4d>::getType())
    {
        Matrix4d Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFMatrix4d*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFMatrix4d*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        Vec3d Translation,Scale,EulerRotation;
        Quaterniond Rotation, ScaleOrientation;
        Value.getTransform(Translation,Rotation,Scale,ScaleOrientation);
        Rotation.getEulerAngleDeg(EulerRotation);

        //Translation
        static_cast<Real64SpinnerModel*>(_TranslationXEditingSpinnerModels.get())->setNumberValue(Translation.x());
        static_cast<Real64SpinnerModel*>(_TranslationYEditingSpinnerModels.get())->setNumberValue(Translation.y());
        static_cast<Real64SpinnerModel*>(_TranslationZEditingSpinnerModels.get())->setNumberValue(Translation.z());
        
        //Rotation
        static_cast<Real64SpinnerModel*>(_RotationXEditingSpinnerModels.get())->setNumberValue(EulerRotation.x());
        static_cast<Real64SpinnerModel*>(_RotationYEditingSpinnerModels.get())->setNumberValue(EulerRotation.y());
        static_cast<Real64SpinnerModel*>(_RotationZEditingSpinnerModels.get())->setNumberValue(EulerRotation.z());

        //Scale
        static_cast<Real64SpinnerModel*>(_ScaleXEditingSpinnerModels.get())->setNumberValue(Scale.x());
        static_cast<Real64SpinnerModel*>(_ScaleYEditingSpinnerModels.get())->setNumberValue(Scale.y());
        static_cast<Real64SpinnerModel*>(_ScaleZEditingSpinnerModels.get())->setNumberValue(Scale.z());
    }

}
bool MatrixTransCompFieldEditor::internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    bool ReturnValue(Inherited::internalAttachField(fc, fieldId, index));
    if(ReturnValue)
    {
        const DataType& type(fc->getFieldDescription(fieldId)->getFieldType().getContentType());

        for(ConnectionsVector::iterator Itor(_SpinnerStateChangedConnections.begin()) ; Itor != _SpinnerStateChangedConnections.end(); ++Itor)
        {
            Itor->disconnect();
        }
        _SpinnerStateChangedConnections.clear();
    
        //Translation
        //X
        _TranslationXEditingSpinnerModels = createSpinnerModel(type,1.0f);

        _TranslationXEditingSpinner->setModel(_TranslationXEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_TranslationXEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));

        //Y
        _TranslationYEditingSpinnerModels = createSpinnerModel(type,1.0f);

        _TranslationYEditingSpinner->setModel(_TranslationYEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_TranslationYEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));

        //Z
        _TranslationZEditingSpinnerModels = createSpinnerModel(type,1.0f);

        _TranslationZEditingSpinner->setModel(_TranslationZEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_TranslationZEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));

    
        //Rotation
        //X
        _RotationXEditingSpinnerModels = createSpinnerModel(type,1.0f);

        _RotationXEditingSpinner->setModel(_RotationXEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_RotationXEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));

        //Y
        _RotationYEditingSpinnerModels = createSpinnerModel(type,1.0f);

        _RotationYEditingSpinner->setModel(_RotationYEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_RotationYEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));

        //Z
        _RotationZEditingSpinnerModels = createSpinnerModel(type,1.0f);

        _RotationZEditingSpinner->setModel(_RotationZEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_RotationZEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));

    
        //Scale
        //X
        _ScaleXEditingSpinnerModels = createSpinnerModel(type,0.1f);

        _ScaleXEditingSpinner->setModel(_ScaleXEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_ScaleXEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));

        //Y
        _ScaleYEditingSpinnerModels = createSpinnerModel(type,0.1f);

        _ScaleYEditingSpinner->setModel(_ScaleYEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_ScaleYEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));

        //Z
        _ScaleZEditingSpinnerModels = createSpinnerModel(type,0.1f);

        _ScaleZEditingSpinner->setModel(_ScaleZEditingSpinnerModels);
        _SpinnerStateChangedConnections.push_back(_ScaleZEditingSpinnerModels->connectStateChanged(boost::bind(&MatrixTransCompFieldEditor::handleSpinnerStateChanged, this, _1)));


    }
    return ReturnValue;
}

SpinnerModelPtr MatrixTransCompFieldEditor::createSpinnerModel(const DataType& type, Real32 stepSize) const
{
    if(type == FieldTraits<Matrix4f>::getType())
    {
        Real32SpinnerModelPtr model(new Real32SpinnerModel());
        model->setMaximum(TypeTraits<Real32>::getMax());
        model->setMinimum(TypeTraits<Real32>::getMin());
        model->setStepSize(static_cast<Real32>(stepSize));
        return model;
    }
    else if(type == FieldTraits<Matrix4fx>::getType())
    {
        Fixed32SpinnerModelPtr model(new Fixed32SpinnerModel());
        model->setMaximum(TypeTraits<Fixed32>::getMax());
        model->setMinimum(TypeTraits<Fixed32>::getMin());
        model->setStepSize(static_cast<Fixed32>(stepSize));
        return model;
    }
    else if(type == FieldTraits<Matrix4d>::getType())
    {
        Real64SpinnerModelPtr model(new Real64SpinnerModel());
        model->setMaximum(TypeTraits<Real64>::getMax());
        model->setMinimum(TypeTraits<Real64>::getMin());
        model->setStepSize(static_cast<Real64>(stepSize));
        return model;
    }
    else
    {
        OSG_ASSERT(false && "Type not supported");
    }
}

void MatrixTransCompFieldEditor::internalStartEditing (void)
{
}

void MatrixTransCompFieldEditor::internalStopEditing  (void)
{
}

void MatrixTransCompFieldEditor::internalCancelEditing(void)
{
}

const std::vector<const DataType*>& MatrixTransCompFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void MatrixTransCompFieldEditor::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    Real32 VertGap(2.0);
    
    Vec2f CompLabelSize(60.0f, (BottomRight.y() - TopLeft.y() - VertGap*2.0f) / 3.0f);

    Vec2f ElementLabelSize(15.0f, CompLabelSize.y());

    Vec2f SpinnerSize(BottomRight - TopLeft - Vec2f(2.0f+CompLabelSize.x() + ElementLabelSize.x() * 3.0f,VertGap*2.0f));
    SpinnerSize = SpinnerSize * (1.0f/3.0f);

    //Translation
    _TranslationEditingLabel->setPosition(TopLeft);
    _TranslationEditingLabel->setSize(CompLabelSize);

    //X
    _TranslationXEditingLabel->setPosition(_TranslationEditingLabel->getPosition() + Vec2f(CompLabelSize.x(), 0.0f));
    _TranslationXEditingLabel->setSize(ElementLabelSize);

    _TranslationXEditingSpinner->setPosition(_TranslationXEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _TranslationXEditingSpinner->setSize(SpinnerSize);
    
    //Y
    _TranslationYEditingLabel->setPosition(_TranslationXEditingSpinner->getPosition() + Vec2f(SpinnerSize.x(), 0.0f));
    _TranslationYEditingLabel->setSize(ElementLabelSize);

    _TranslationYEditingSpinner->setPosition(_TranslationYEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _TranslationYEditingSpinner->setSize(SpinnerSize);

    //Z
    _TranslationZEditingLabel->setPosition(_TranslationYEditingSpinner->getPosition() + Vec2f(SpinnerSize.x(), 0.0f));
    _TranslationZEditingLabel->setSize(ElementLabelSize);

    _TranslationZEditingSpinner->setPosition(_TranslationZEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _TranslationZEditingSpinner->setSize(SpinnerSize);

    //Rotation
    _RotationEditingLabel->setPosition(_TranslationEditingLabel->getPosition() + Vec2f(0.0f,CompLabelSize.y()+VertGap));
    _RotationEditingLabel->setSize(CompLabelSize);

    //X
    _RotationXEditingLabel->setPosition(_RotationEditingLabel->getPosition() + Vec2f(CompLabelSize.x(), 0.0f));
    _RotationXEditingLabel->setSize(ElementLabelSize);

    _RotationXEditingSpinner->setPosition(_RotationXEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _RotationXEditingSpinner->setSize(SpinnerSize);
    
    //Y
    _RotationYEditingLabel->setPosition(_RotationXEditingSpinner->getPosition() + Vec2f(SpinnerSize.x(), 0.0f));
    _RotationYEditingLabel->setSize(ElementLabelSize);

    _RotationYEditingSpinner->setPosition(_RotationYEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _RotationYEditingSpinner->setSize(SpinnerSize);

    //Z
    _RotationZEditingLabel->setPosition(_RotationYEditingSpinner->getPosition() + Vec2f(SpinnerSize.x(), 0.0f));
    _RotationZEditingLabel->setSize(ElementLabelSize);

    _RotationZEditingSpinner->setPosition(_RotationZEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _RotationZEditingSpinner->setSize(SpinnerSize);

    //Scale
    _ScaleEditingLabel->setPosition(_RotationEditingLabel->getPosition() + Vec2f(0.0f,CompLabelSize.y()+VertGap));
    _ScaleEditingLabel->setSize(CompLabelSize);

    //X
    _ScaleXEditingLabel->setPosition(_ScaleEditingLabel->getPosition() + Vec2f(CompLabelSize.x(), 0.0f));
    _ScaleXEditingLabel->setSize(ElementLabelSize);

    _ScaleXEditingSpinner->setPosition(_ScaleXEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _ScaleXEditingSpinner->setSize(SpinnerSize);
    
    //Y
    _ScaleYEditingLabel->setPosition(_ScaleXEditingSpinner->getPosition() + Vec2f(SpinnerSize.x(), 0.0f));
    _ScaleYEditingLabel->setSize(ElementLabelSize);

    _ScaleYEditingSpinner->setPosition(_ScaleYEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _ScaleYEditingSpinner->setSize(SpinnerSize);

    //Z
    _ScaleZEditingLabel->setPosition(_ScaleYEditingSpinner->getPosition() + Vec2f(SpinnerSize.x(), 0.0f));
    _ScaleZEditingLabel->setSize(ElementLabelSize);

    _ScaleZEditingSpinner->setPosition(_ScaleZEditingLabel->getPosition() + Vec2f(ElementLabelSize.x(), 0.0f));
    _ScaleZEditingSpinner->setSize(SpinnerSize);
}

UInt32 MatrixTransCompFieldEditor::getNumRequestedRows(void) const
{
    return 4;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void MatrixTransCompFieldEditor::onCreate(const MatrixTransCompFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        //Translation
        //Label
        _TranslationEditingLabel = Label::create();
        _TranslationEditingLabel->setBackgrounds(NULL);
        _TranslationEditingLabel->setBorders(NULL);
        _TranslationEditingLabel->setText("Translate");
        pushToChildren(_TranslationEditingLabel);

        //X
        _TranslationXEditingLabel = Label::create();
        _TranslationXEditingLabel->setBackgrounds(NULL);
        _TranslationXEditingLabel->setBorders(NULL);
        _TranslationXEditingLabel->setText("X");
        _TranslationXEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_TranslationXEditingLabel);

        _TranslationXEditingSpinner = Spinner::create();
        pushToChildren(_TranslationXEditingSpinner);

        //Y
        _TranslationYEditingLabel = Label::create();
        _TranslationYEditingLabel->setBackgrounds(NULL);
        _TranslationYEditingLabel->setBorders(NULL);
        _TranslationYEditingLabel->setText("Y");
        _TranslationYEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_TranslationYEditingLabel);

        _TranslationYEditingSpinner = Spinner::create();
        pushToChildren(_TranslationYEditingSpinner);

        //Z
        _TranslationZEditingLabel = Label::create();
        _TranslationZEditingLabel->setBackgrounds(NULL);
        _TranslationZEditingLabel->setBorders(NULL);
        _TranslationZEditingLabel->setText("Z");
        _TranslationZEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_TranslationZEditingLabel);

        _TranslationZEditingSpinner = Spinner::create();
        pushToChildren(_TranslationZEditingSpinner);

        //Rotation
        //Label
        _RotationEditingLabel = Label::create();
        _RotationEditingLabel->setBackgrounds(NULL);
        _RotationEditingLabel->setBorders(NULL);
        _RotationEditingLabel->setText("Rotate");
        pushToChildren(_RotationEditingLabel);

        //X
        _RotationXEditingLabel = Label::create();
        _RotationXEditingLabel->setBackgrounds(NULL);
        _RotationXEditingLabel->setBorders(NULL);
        _RotationXEditingLabel->setText("X");
        _RotationXEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_RotationXEditingLabel);

        _RotationXEditingSpinner = Spinner::create();
        pushToChildren(_RotationXEditingSpinner);

        //Y
        _RotationYEditingLabel = Label::create();
        _RotationYEditingLabel->setBackgrounds(NULL);
        _RotationYEditingLabel->setBorders(NULL);
        _RotationYEditingLabel->setText("Y");
        _RotationYEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_RotationYEditingLabel);

        _RotationYEditingSpinner = Spinner::create();
        pushToChildren(_RotationYEditingSpinner);

        //Z
        _RotationZEditingLabel = Label::create();
        _RotationZEditingLabel->setBackgrounds(NULL);
        _RotationZEditingLabel->setBorders(NULL);
        _RotationZEditingLabel->setText("Z");
        _RotationZEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_RotationZEditingLabel);

        _RotationZEditingSpinner = Spinner::create();
        pushToChildren(_RotationZEditingSpinner);

        //Scale
        //Label
        _ScaleEditingLabel = Label::create();
        _ScaleEditingLabel->setBackgrounds(NULL);
        _ScaleEditingLabel->setBorders(NULL);
        _ScaleEditingLabel->setText("Scale");
        pushToChildren(_ScaleEditingLabel);

        //X
        _ScaleXEditingLabel = Label::create();
        _ScaleXEditingLabel->setBackgrounds(NULL);
        _ScaleXEditingLabel->setBorders(NULL);
        _ScaleXEditingLabel->setText("X");
        _ScaleXEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_ScaleXEditingLabel);

        _ScaleXEditingSpinner = Spinner::create();
        pushToChildren(_ScaleXEditingSpinner);

        //Y
        _ScaleYEditingLabel = Label::create();
        _ScaleYEditingLabel->setBackgrounds(NULL);
        _ScaleYEditingLabel->setBorders(NULL);
        _ScaleYEditingLabel->setText("Y");
        _ScaleYEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_ScaleYEditingLabel);

        _ScaleYEditingSpinner = Spinner::create();
        pushToChildren(_ScaleYEditingSpinner);

        //Z
        _ScaleZEditingLabel = Label::create();
        _ScaleZEditingLabel->setBackgrounds(NULL);
        _ScaleZEditingLabel->setBorders(NULL);
        _ScaleZEditingLabel->setText("Z");
        _ScaleZEditingLabel->setAlignment(Vec2f(1.0f,0.5f));
        pushToChildren(_ScaleZEditingLabel);

        _ScaleZEditingSpinner = Spinner::create();
        pushToChildren(_ScaleZEditingSpinner);
    }
}

void MatrixTransCompFieldEditor::onDestroy()
{
}

void MatrixTransCompFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    for(ConnectionsVector::iterator Itor(_SpinnerStateChangedConnections.begin()) ; Itor != _SpinnerStateChangedConnections.end(); ++Itor)
    {
        Itor->disconnect();
    }

    _SpinnerStateChangedConnections.clear();

    //Translation
    _TranslationXEditingSpinner = NULL;
    _TranslationYEditingSpinner = NULL;
    _TranslationZEditingSpinner = NULL;
    _TranslationEditingLabel = NULL;

    //Rotation
    _RotationXEditingSpinner = NULL;
    _RotationYEditingSpinner = NULL;
    _RotationZEditingSpinner = NULL;
    _RotationEditingLabel = NULL;

    //Scale
    _ScaleXEditingSpinner = NULL;
    _ScaleYEditingSpinner = NULL;
    _ScaleZEditingSpinner = NULL;
    _ScaleEditingLabel = NULL;
}

void MatrixTransCompFieldEditor::handleSpinnerStateChanged(ChangeEventDetails* const details)
{
    runCommand();
}
    
std::string MatrixTransCompFieldEditor::getEditorValue(void) const
{
    const DataType& type(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType());

    std::ostringstream StrStream;
    if(type == FieldTraits<Matrix4f>::getType())
    {
        Matrix4f Mat;
        Vec3f Translation,Scale;
        Quaternion Rotation;

        Translation.setValues(boost::any_cast<Real32>(_TranslationXEditingSpinner->getValue()),
                              boost::any_cast<Real32>(_TranslationYEditingSpinner->getValue()),
                              boost::any_cast<Real32>(_TranslationZEditingSpinner->getValue()));

        Rotation.setValue(osgDegree2Rad(boost::any_cast<Real32>(_RotationXEditingSpinnerModels->getValue())),
                          osgDegree2Rad(boost::any_cast<Real32>(_RotationYEditingSpinnerModels->getValue())),
                          osgDegree2Rad(boost::any_cast<Real32>(_RotationZEditingSpinnerModels->getValue())));

        Scale.setValues(boost::any_cast<Real32>(_ScaleXEditingSpinner->getValue()),
                        boost::any_cast<Real32>(_ScaleYEditingSpinner->getValue()),
                        boost::any_cast<Real32>(_ScaleZEditingSpinner->getValue()));

        Mat.setTransform(Translation, Rotation, Scale);

        StrStream << Mat;
    }
    else if(type == FieldTraits<Matrix4fx>::getType())
    {
        Matrix4fx Mat;
        Vec3fx Translation,Scale;
        Quaternionfx Rotation;

        Translation.setValues(boost::any_cast<Fixed32>(_TranslationXEditingSpinner->getValue()),
                              boost::any_cast<Fixed32>(_TranslationYEditingSpinner->getValue()),
                              boost::any_cast<Fixed32>(_TranslationZEditingSpinner->getValue()));

        Rotation.setValue(osgDegree2Rad(boost::any_cast<Fixed32>(_RotationXEditingSpinnerModels->getValue())),
                          osgDegree2Rad(boost::any_cast<Fixed32>(_RotationYEditingSpinnerModels->getValue())),
                          osgDegree2Rad(boost::any_cast<Fixed32>(_RotationZEditingSpinnerModels->getValue())));

        Scale.setValues(boost::any_cast<Fixed32>(_ScaleXEditingSpinner->getValue()),
                        boost::any_cast<Fixed32>(_ScaleYEditingSpinner->getValue()),
                        boost::any_cast<Fixed32>(_ScaleZEditingSpinner->getValue()));

        Mat.setTransform(Translation, Rotation, Scale);
        StrStream << Mat;
    }
    else if(type == FieldTraits<Matrix4d>::getType())
    {
        Matrix4d Mat;
        Vec3d Translation,Scale;
        Quaterniond Rotation;

        Translation.setValues(boost::any_cast<Real64>(_TranslationXEditingSpinner->getValue()),
                              boost::any_cast<Real64>(_TranslationYEditingSpinner->getValue()),
                              boost::any_cast<Real64>(_TranslationZEditingSpinner->getValue()));

        Rotation.setValue(osgDegree2Rad(boost::any_cast<Real64>(_RotationXEditingSpinnerModels->getValue())),
                          osgDegree2Rad(boost::any_cast<Real64>(_RotationYEditingSpinnerModels->getValue())),
                          osgDegree2Rad(boost::any_cast<Real64>(_RotationZEditingSpinnerModels->getValue())));

        Scale.setValues(boost::any_cast<Real64>(_ScaleXEditingSpinner->getValue()),
                        boost::any_cast<Real64>(_ScaleYEditingSpinner->getValue()),
                        boost::any_cast<Real64>(_ScaleZEditingSpinner->getValue()));

        Mat.setTransform(Translation, Rotation, Scale);
        StrStream << Mat;
    }

    return StrStream.str();
}

void MatrixTransCompFieldEditor::runCommand  (void)
{
    //Call the command to set the Field
    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), getEditingFieldId(), getEditorValue(), getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

/*----------------------- constructors & destructors ----------------------*/

MatrixTransCompFieldEditor::MatrixTransCompFieldEditor(void) :
    Inherited()
{
}

MatrixTransCompFieldEditor::MatrixTransCompFieldEditor(const MatrixTransCompFieldEditor &source) :
    Inherited(source)
{
}

MatrixTransCompFieldEditor::~MatrixTransCompFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MatrixTransCompFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MatrixTransCompFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MatrixTransCompFieldEditor NI" << std::endl;
}

OSG_END_NAMESPACE
