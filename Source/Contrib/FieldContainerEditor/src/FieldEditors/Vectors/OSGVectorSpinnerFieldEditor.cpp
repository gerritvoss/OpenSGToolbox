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

#include "OSGVectorSpinnerFieldEditor.h"
#include "OSGSetFieldValueCommand.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSysFieldTraits.h"
#include "OSGVecFieldTraits.h"
#include "OSGStringUtils.h"
#include "OSGSpinner.h"
#include "OSGLabel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGVectorSpinnerFieldEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGVectorSpinnerFieldEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const DataType*> VectorSpinnerFieldEditor::_EditableTypes = std::vector<const DataType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VectorSpinnerFieldEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::FactoryPost)
    {
        //ub
        _EditableTypes.push_back(&FieldTraits<Vec2ub>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt2ub>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec3ub>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt3ub>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec4ub>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt4ub>::getType());

        //b
        _EditableTypes.push_back(&FieldTraits<Vec2b>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt2b>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec3b>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt3b>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec4b>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt4b>::getType());

        //us
        _EditableTypes.push_back(&FieldTraits<Vec2us>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt2us>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec3us>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt3us>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec4us>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt4us>::getType());

        //s
        _EditableTypes.push_back(&FieldTraits<Vec2s>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt2s>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec3s>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt3s>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec4s>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt4s>::getType());

        //f
        _EditableTypes.push_back(&FieldTraits<Vec2f>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt2f>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec3f>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt3f>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec4f>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt4f>::getType());

        //fx
        _EditableTypes.push_back(&FieldTraits<Vec2fx>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt2fx>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec3fx>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt3fx>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec4fx>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt4fx>::getType());

        //d
        _EditableTypes.push_back(&FieldTraits<Vec2d>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt2d>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec3d>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt3d>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec4d>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt4d>::getType());

        //ld
        _EditableTypes.push_back(&FieldTraits<Vec2ld>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt2ld>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec3ld>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt3ld>::getType());
        _EditableTypes.push_back(&FieldTraits<Vec4ld>::getType());
        _EditableTypes.push_back(&FieldTraits<Pnt4ld>::getType());


        
        for(UInt32 i(0) ; i<_EditableTypes.size(); ++i)
        {
            FieldEditorFactory::the()->setSingleDefaultEditor(_EditableTypes[i], &getClassType());
            FieldEditorFactory::the()->setEditorType(_EditableTypes[i], &getClassType(), "Spinner");
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool VectorSpinnerFieldEditor::internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index)
{
    Inherited::internalAttachField(fc, fieldId, index);
    const DataType& type(fc->getFieldDescription(fieldId)->getFieldType().getContentType());

    for(UInt32 i(0) ; i<_EditingSpinners.size() ; ++i)
    {
        _SpinnerStateChangedConnections[i].disconnect();
    }

    _SpinnerStateChangedConnections.clear();
    _EditingSpinnerModels.clear();
    _EditingSpinners.clear();
    _EditingLabels.clear();
    
    Int8 NumElements(0);
    //f
    if(type == FieldTraits<Vec2f>::getType() ||
       type == FieldTraits<Pnt2f>::getType())
    {
        NumElements = Vec2f::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real32SpinnerModelPtr model(new Real32SpinnerModel());
            model->setMaximum(TypeTraits<Real32>::getMax());
            model->setMinimum(TypeTraits<Real32>::getMin());
            model->setStepSize(TypeTraits<Real32>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec3f>::getType() ||
            type == FieldTraits<Pnt3f>::getType())
    {
        NumElements = Vec3f::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real32SpinnerModelPtr model(new Real32SpinnerModel());
            model->setMaximum(TypeTraits<Real32>::getMax());
            model->setMinimum(TypeTraits<Real32>::getMin());
            model->setStepSize(TypeTraits<Real32>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec4f>::getType() ||
            type == FieldTraits<Pnt4f>::getType())
    {
        NumElements = Vec4f::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real32SpinnerModelPtr model(new Real32SpinnerModel());
            model->setMaximum(TypeTraits<Real32>::getMax());
            model->setMinimum(TypeTraits<Real32>::getMin());
            model->setStepSize(TypeTraits<Real32>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }

    //ub
    else if(type == FieldTraits<Vec2ub>::getType() ||
       type == FieldTraits<Pnt2ub>::getType())
    {
        NumElements = Vec2ub::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            UInt8SpinnerModelPtr model(new UInt8SpinnerModel());
            model->setMaximum(TypeTraits<UInt8>::getMax());
            model->setMinimum(TypeTraits<UInt8>::getMin());
            model->setStepSize(TypeTraits<UInt8>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec3ub>::getType() ||
            type == FieldTraits<Pnt3ub>::getType())
    {
        NumElements = Vec3ub::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            UInt8SpinnerModelPtr model(new UInt8SpinnerModel());
            model->setMaximum(TypeTraits<UInt8>::getMax());
            model->setMinimum(TypeTraits<UInt8>::getMin());
            model->setStepSize(TypeTraits<UInt8>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec4ub>::getType() ||
            type == FieldTraits<Pnt4ub>::getType())
    {
        NumElements = Vec4ub::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            UInt8SpinnerModelPtr model(new UInt8SpinnerModel());
            model->setMaximum(TypeTraits<UInt8>::getMax());
            model->setMinimum(TypeTraits<UInt8>::getMin());
            model->setStepSize(TypeTraits<UInt8>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }

    //b
    else if(type == FieldTraits<Vec2b>::getType() ||
       type == FieldTraits<Pnt2b>::getType())
    {
        NumElements = Vec2b::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Int8SpinnerModelPtr model(new Int8SpinnerModel());
            model->setMaximum(TypeTraits<Int8>::getMax());
            model->setMinimum(TypeTraits<Int8>::getMin());
            model->setStepSize(TypeTraits<Int8>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec3b>::getType() ||
            type == FieldTraits<Pnt3b>::getType())
    {
        NumElements = Vec3b::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Int8SpinnerModelPtr model(new Int8SpinnerModel());
            model->setMaximum(TypeTraits<Int8>::getMax());
            model->setMinimum(TypeTraits<Int8>::getMin());
            model->setStepSize(TypeTraits<Int8>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec4b>::getType() ||
            type == FieldTraits<Pnt4b>::getType())
    {
        NumElements = Vec4b::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Int8SpinnerModelPtr model(new Int8SpinnerModel());
            model->setMaximum(TypeTraits<Int8>::getMax());
            model->setMinimum(TypeTraits<Int8>::getMin());
            model->setStepSize(TypeTraits<Int8>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }

    //us
    else if(type == FieldTraits<Vec2us>::getType() ||
       type == FieldTraits<Pnt2us>::getType())
    {
        NumElements = Vec2us::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            UInt16SpinnerModelPtr model(new UInt16SpinnerModel());
            model->setMaximum(TypeTraits<UInt16>::getMax());
            model->setMinimum(TypeTraits<UInt16>::getMin());
            model->setStepSize(TypeTraits<UInt16>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec3us>::getType() ||
            type == FieldTraits<Pnt3us>::getType())
    {
        NumElements = Vec3us::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            UInt16SpinnerModelPtr model(new UInt16SpinnerModel());
            model->setMaximum(TypeTraits<UInt16>::getMax());
            model->setMinimum(TypeTraits<UInt16>::getMin());
            model->setStepSize(TypeTraits<UInt16>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec4us>::getType() ||
            type == FieldTraits<Pnt4us>::getType())
    {
        NumElements = Vec4us::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            UInt16SpinnerModelPtr model(new UInt16SpinnerModel());
            model->setMaximum(TypeTraits<UInt16>::getMax());
            model->setMinimum(TypeTraits<UInt16>::getMin());
            model->setStepSize(TypeTraits<UInt16>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }

    //s
    else if(type == FieldTraits<Vec2s>::getType() ||
       type == FieldTraits<Pnt2s>::getType())
    {
        NumElements = Vec2s::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Int16SpinnerModelPtr model(new Int16SpinnerModel());
            model->setMaximum(TypeTraits<Int16>::getMax());
            model->setMinimum(TypeTraits<Int16>::getMin());
            model->setStepSize(TypeTraits<Int16>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec3s>::getType() ||
            type == FieldTraits<Pnt3s>::getType())
    {
        NumElements = Vec3s::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Int16SpinnerModelPtr model(new Int16SpinnerModel());
            model->setMaximum(TypeTraits<Int16>::getMax());
            model->setMinimum(TypeTraits<Int16>::getMin());
            model->setStepSize(TypeTraits<Int16>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec4s>::getType() ||
            type == FieldTraits<Pnt4s>::getType())
    {
        NumElements = Vec4s::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Int16SpinnerModelPtr model(new Int16SpinnerModel());
            model->setMaximum(TypeTraits<Int16>::getMax());
            model->setMinimum(TypeTraits<Int16>::getMin());
            model->setStepSize(TypeTraits<Int16>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }

    //fx
    else if(type == FieldTraits<Vec2fx>::getType() ||
       type == FieldTraits<Pnt2fx>::getType())
    {
        NumElements = Vec2fx::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Fixed32SpinnerModelPtr model(new Fixed32SpinnerModel());
            model->setMaximum(TypeTraits<Fixed32>::getMax());
            model->setMinimum(TypeTraits<Fixed32>::getMin());
            model->setStepSize(TypeTraits<Fixed32>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec3fx>::getType() ||
            type == FieldTraits<Pnt3fx>::getType())
    {
        NumElements = Vec3fx::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Fixed32SpinnerModelPtr model(new Fixed32SpinnerModel());
            model->setMaximum(TypeTraits<Fixed32>::getMax());
            model->setMinimum(TypeTraits<Fixed32>::getMin());
            model->setStepSize(TypeTraits<Fixed32>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec4fx>::getType() ||
            type == FieldTraits<Pnt4fx>::getType())
    {
        NumElements = Vec4fx::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Fixed32SpinnerModelPtr model(new Fixed32SpinnerModel());
            model->setMaximum(TypeTraits<Fixed32>::getMax());
            model->setMinimum(TypeTraits<Fixed32>::getMin());
            model->setStepSize(TypeTraits<Fixed32>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }

    //d
    else if(type == FieldTraits<Vec2d>::getType() ||
       type == FieldTraits<Pnt2d>::getType())
    {
        NumElements = Vec2d::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real64SpinnerModelPtr model(new Real64SpinnerModel());
            model->setMaximum(TypeTraits<Real64>::getMax());
            model->setMinimum(TypeTraits<Real64>::getMin());
            model->setStepSize(TypeTraits<Real64>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec3d>::getType() ||
            type == FieldTraits<Pnt3d>::getType())
    {
        NumElements = Vec3d::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real64SpinnerModelPtr model(new Real64SpinnerModel());
            model->setMaximum(TypeTraits<Real64>::getMax());
            model->setMinimum(TypeTraits<Real64>::getMin());
            model->setStepSize(TypeTraits<Real64>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec4d>::getType() ||
            type == FieldTraits<Pnt4d>::getType())
    {
        NumElements = Vec4d::_uiSize;
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real64SpinnerModelPtr model(new Real64SpinnerModel());
            model->setMaximum(TypeTraits<Real64>::getMax());
            model->setMinimum(TypeTraits<Real64>::getMin());
            model->setStepSize(TypeTraits<Real64>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }

    //ld
    else if(type == FieldTraits<Vec2ld>::getType() ||
       type == FieldTraits<Pnt2ld>::getType())
    {
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real128SpinnerModelPtr model(new Real128SpinnerModel());
            model->setMaximum(TypeTraits<Real128>::getMax());
            model->setMinimum(TypeTraits<Real128>::getMin());
            model->setStepSize(TypeTraits<Real128>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec3ld>::getType() ||
            type == FieldTraits<Pnt3ld>::getType())
    {
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real128SpinnerModelPtr model(new Real128SpinnerModel());
            model->setMaximum(TypeTraits<Real128>::getMax());
            model->setMinimum(TypeTraits<Real128>::getMin());
            model->setStepSize(TypeTraits<Real128>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }
    else if(type == FieldTraits<Vec4ld>::getType() ||
            type == FieldTraits<Pnt4ld>::getType())
    {
        for(UInt8 i(0) ; i<NumElements ; ++i)
        {
            Real128SpinnerModelPtr model(new Real128SpinnerModel());
            model->setMaximum(TypeTraits<Real128>::getMax());
            model->setMinimum(TypeTraits<Real128>::getMin());
            model->setStepSize(TypeTraits<Real128>::getOneElement());
            _EditingSpinnerModels.push_back(SpinnerModelPtr(model));

            _EditingSpinners.push_back(Spinner::create());
            _EditingSpinners.back()->setModel(_EditingSpinnerModels.back());
            _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels.back()->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
        }
    }

    else
    {
        return false;
    }
    //Labels
    for(UInt8 i(0) ; i<NumElements ; ++i)
    {
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
        case 3:
            _EditingLabels.back()->setText("W");
            break;
        }
    }

    clearChildren();
    for(UInt32 i(0) ; i<_EditingSpinners.size() ; ++i)
    {
        pushToChildren(_EditingLabels[i]);
        pushToChildren(_EditingSpinners[i]);
    }

    return true;
}

void VectorSpinnerFieldEditor::internalFieldChanged (void)
{
    const DataType& type(getEditingFC()->getFieldDescription(getEditingFieldId())->getFieldType().getContentType());
    GetFieldHandlePtr TheFieldHandle = getEditingFC()->getField(getEditingFieldId());

    for(UInt32 i(0) ; i<_EditingSpinners.size() ; ++i)
    {
        _SpinnerStateChangedConnections[i].disconnect();
    }

    _SpinnerStateChangedConnections.clear();

    //f
    if(type == FieldTraits<Vec2f>::getType())
    {
        Vec2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec3f>::getType())
    {
        Vec3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec4f>::getType())
    {
        Vec4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt2f>::getType())
    {
        Pnt2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt3f>::getType())
    {
        Pnt3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt4f>::getType())
    {
        Pnt4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }

    //ub
    else if(type == FieldTraits<Vec2ub>::getType())
    {
        Vec2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec3ub>::getType())
    {
        Vec3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec4ub>::getType())
    {
        Vec4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt2ub>::getType())
    {
        Pnt2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt3ub>::getType())
    {
        Pnt3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt4ub>::getType())
    {
        Pnt4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }

    //b
    else if(type == FieldTraits<Vec2b>::getType())
    {
        Vec2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec3b>::getType())
    {
        Vec3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec4b>::getType())
    {
        Vec4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt2b>::getType())
    {
        Pnt2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt3b>::getType())
    {
        Pnt3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt4b>::getType())
    {
        Pnt4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int8SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }

    //us
    else if(type == FieldTraits<Vec2us>::getType())
    {
        Vec2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec3us>::getType())
    {
        Vec3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec4us>::getType())
    {
        Vec4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt2us>::getType())
    {
        Pnt2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt3us>::getType())
    {
        Pnt3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt4us>::getType())
    {
        Pnt4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<UInt16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }

    //s
    else if(type == FieldTraits<Vec2s>::getType())
    {
        Vec2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec3s>::getType())
    {
        Vec3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec4s>::getType())
    {
        Vec4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt2s>::getType())
    {
        Pnt2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt3s>::getType())
    {
        Pnt3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt4s>::getType())
    {
        Pnt4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Int16SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }

    //fx
    else if(type == FieldTraits<Vec2fx>::getType())
    {
        Vec2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Fixed32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec3fx>::getType())
    {
        Vec3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Fixed32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec4fx>::getType())
    {
        Vec4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Fixed32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt2fx>::getType())
    {
        Pnt2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Fixed32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt3fx>::getType())
    {
        Pnt3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Fixed32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt4fx>::getType())
    {
        Pnt4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Fixed32SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }

    //d
    else if(type == FieldTraits<Vec2d>::getType())
    {
        Vec2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real64SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec3d>::getType())
    {
        Vec3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real64SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec4d>::getType())
    {
        Vec4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real64SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt2d>::getType())
    {
        Pnt2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real64SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt3d>::getType())
    {
        Pnt3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real64SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt4d>::getType())
    {
        Pnt4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real64SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }

    //ld
    else if(type == FieldTraits<Vec2ld>::getType())
    {
        Vec2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real128SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec3ld>::getType())
    {
        Vec3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real128SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Vec4ld>::getType())
    {
        Vec4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFVec4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFVec4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real128SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt2ld>::getType())
    {
        Pnt2f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt2f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt2f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real128SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt3ld>::getType())
    {
        Pnt3f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt3f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt3f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real128SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }
    else if(type == FieldTraits<Pnt4ld>::getType())
    {
        Pnt4f Value;
        if(TheFieldHandle->getCardinality() == FieldType::SingleField)
        {
            Value = static_cast<const SFPnt4f*>(TheFieldHandle->getField())->getValue();
        }
        else
        {
            Value = static_cast<const MFPnt4f*>(TheFieldHandle->getField())->operator[](getEditingFieldIndex());
        }
        for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
        {
            static_cast<Real128SpinnerModel*>(_EditingSpinnerModels[i].get())->setNumberValue(Value[i]);
        }
    }

    else
    {
        assert(false && "Should not reach this.");
    }
    for(UInt32 i(0) ; i<_EditingSpinners.size() ; ++i)
    {
        _SpinnerStateChangedConnections.push_back(_EditingSpinnerModels[i]->connectStateChanged(boost::bind(&VectorSpinnerFieldEditor::handleSpinnerStateChanged, this, _1)));
    }
}

void VectorSpinnerFieldEditor::internalStartEditing (void)
{
}

void VectorSpinnerFieldEditor::internalStopEditing  (void)
{
}

void VectorSpinnerFieldEditor::runCommand  (void)
{
    //Call the command to set the Field
    std::string Value("");

    for(UInt32 i(0) ; i<_EditingSpinnerModels.size() ; ++i)
    {
        Value += lexical_cast(_EditingSpinnerModels[i]->getValue()) + " ";
    }

    SetFieldValueCommandPtr SetCommand = SetFieldValueCommand::create(getEditingFC(), 
                                                                      getEditingFieldId(), 
                                                                      Value, 
                                                                      getEditingFieldIndex());

    getCommandManager()->executeCommand(SetCommand);
}

void VectorSpinnerFieldEditor::internalCancelEditing(void)
{
}

const std::vector<const DataType*>& VectorSpinnerFieldEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

void VectorSpinnerFieldEditor::updateLayout(void)
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
    /*_EditingSpinner->setPosition(TopLeft);
    _EditingSpinner->setSize(BottomRight - TopLeft);*/
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VectorSpinnerFieldEditor::VectorSpinnerFieldEditor(void) :
    Inherited()
{
}

VectorSpinnerFieldEditor::VectorSpinnerFieldEditor(const VectorSpinnerFieldEditor &source) :
    Inherited(source)
{
}

VectorSpinnerFieldEditor::~VectorSpinnerFieldEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/
void VectorSpinnerFieldEditor::onCreate(const VectorSpinnerFieldEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
    }
}

void VectorSpinnerFieldEditor::onDestroy()
{
}

void VectorSpinnerFieldEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _EditingSpinners.clear();
    _EditingLabels.clear();
    _EditingSpinnerModels.clear();

    for(UInt32 i(0) ; i<_EditingSpinners.size() ; ++i)
    {
        _SpinnerStateChangedConnections[i].disconnect();
    }
    _SpinnerStateChangedConnections.clear();
}

void VectorSpinnerFieldEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VectorSpinnerFieldEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump VectorSpinnerFieldEditor NI" << std::endl;
}

void VectorSpinnerFieldEditor::handleSpinnerStateChanged(ChangeEventDetails* const details)
{
    runCommand();
}

OSG_END_NAMESPACE
