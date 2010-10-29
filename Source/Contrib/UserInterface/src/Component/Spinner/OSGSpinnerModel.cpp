/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
#include "OSGSpinnerModel.h"
#include "OSGNumberSpinnerModel.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

EventDescription *SpinnerModel::_eventDesc[] =
{
    new EventDescription("StateChanged", 
                          "StateChanged",
                          StateChangedEventId, 
                          FieldTraits<StateChangedEventDetailsType *>::getType(),
                          true,
                          NULL),
};

EventProducerType SpinnerModel::_producerType(
                                            "SpinnerModelProducerType",
                                            "EventProducerType",
                                            "",
                                            InitEventProducerFunctor(),
                                            _eventDesc,
                                            sizeof(_eventDesc));

const EventProducerType &SpinnerModel::getProducerType(void) const
{
    return _producerType;
}

SpinnerModelPtr createDefaultNumberSpinnerModel(const DataType& TheType)
{
    if(TheType == FieldTraits< Int8 >::getType())
    {
        return Int8SpinnerModelPtr(new Int8SpinnerModel());
    }
    else if(TheType == FieldTraits< Int16 >::getType())
    {
        return Int16SpinnerModelPtr(new Int16SpinnerModel());
    }
    else if(TheType == FieldTraits< Int32 >::getType())
    {
        return Int32SpinnerModelPtr(new Int32SpinnerModel());
    }
    else if(TheType == FieldTraits< Int64 >::getType())
    {
        return Int64SpinnerModelPtr(new Int64SpinnerModel());
    }
    else if(TheType == FieldTraits< UInt8 >::getType())
    {
        return UInt8SpinnerModelPtr(new UInt8SpinnerModel());
    }
    else if(TheType == FieldTraits< UInt16 >::getType())
    {
        return UInt16SpinnerModelPtr(new UInt16SpinnerModel());
    }
    else if(TheType == FieldTraits< UInt32 >::getType())
    {
        return UInt32SpinnerModelPtr(new UInt32SpinnerModel());
    }
    else if(TheType == FieldTraits< UInt64 >::getType())
    {
        return UInt64SpinnerModelPtr(new UInt64SpinnerModel());
    }
    /*else if(TheType == FieldTraits< Real16 >::getType())
      {
      return Real16SpinnerModelPtr(new Real16SpinnerModel());
      }*/
    else if(TheType == FieldTraits< Real32 >::getType())
    {
        return Real32SpinnerModelPtr(new Real32SpinnerModel());
    }
    else if(TheType == FieldTraits< Real64 >::getType())
    {
        return Real64SpinnerModelPtr(new Real64SpinnerModel());
    }
    /*else if(TheType == FieldTraits< Real128 >::getType())
      {
      return Real128SpinnerModelPtr(new Real128SpinnerModel());
      }*/
    return SpinnerModelPtr();
}


SpinnerModelPtr createDefaultNumberSpinnerModel(GetFieldHandlePtr TheFieldHandle)
{
    if(TheFieldHandle->getCardinality() == FieldType::SingleField)
    {
        if(TheFieldHandle->getType().getContentType() == FieldTraits< Int8 >::getType())
        {
            Int8SpinnerModelPtr TheModel(new Int8SpinnerModel());
            TheModel->setMinimum(TypeTraits<Int8>::getMin());
            TheModel->setMaximum(TypeTraits<Int8>::getMax());
            TheModel->setStepSize(TypeTraits<Int8>::getOneElement());
            TheModel->setValue(static_cast<const SField<Int8>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< Int16 >::getType())
        {
            Int16SpinnerModelPtr TheModel(new Int16SpinnerModel());
            TheModel->setMinimum(TypeTraits<Int16>::getMin());
            TheModel->setMaximum(TypeTraits<Int16>::getMax());
            TheModel->setStepSize(TypeTraits<Int16>::getOneElement());
            TheModel->setValue(static_cast<const SField<Int16>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< Int32 >::getType())
        {
            Int32SpinnerModelPtr TheModel(new Int32SpinnerModel());
            TheModel->setMinimum(TypeTraits<Int32>::getMin());
            TheModel->setMaximum(TypeTraits<Int32>::getMax());
            TheModel->setStepSize(TypeTraits<Int32>::getOneElement());
            TheModel->setValue(static_cast<const SField<Int32>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< Int64 >::getType())
        {
            Int64SpinnerModelPtr TheModel(new Int64SpinnerModel());
            TheModel->setMinimum(TypeTraits<Int64>::getMin());
            TheModel->setMaximum(TypeTraits<Int64>::getMax());
            TheModel->setStepSize(TypeTraits<Int64>::getOneElement());
            TheModel->setValue(static_cast<const SField<Int64>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< UInt8 >::getType())
        {
            UInt8SpinnerModelPtr TheModel(new UInt8SpinnerModel());
            TheModel->setMinimum(TypeTraits<UInt8>::getMin());
            TheModel->setMaximum(TypeTraits<UInt8>::getMax());
            TheModel->setStepSize(TypeTraits<UInt8>::getOneElement());
            TheModel->setValue(static_cast<const SField<UInt8>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< UInt16 >::getType())
        {
            UInt16SpinnerModelPtr TheModel(new UInt16SpinnerModel());
            TheModel->setMinimum(TypeTraits<UInt16>::getMin());
            TheModel->setMaximum(TypeTraits<UInt16>::getMax());
            TheModel->setStepSize(TypeTraits<UInt16>::getOneElement());
            TheModel->setValue(static_cast<const SField<UInt16>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< UInt32 >::getType())
        {
            UInt32SpinnerModelPtr TheModel(new UInt32SpinnerModel());
            TheModel->setMinimum(TypeTraits<UInt32>::getMin());
            TheModel->setMaximum(TypeTraits<UInt32>::getMax());
            TheModel->setStepSize(TypeTraits<UInt32>::getOneElement());
            TheModel->setValue(static_cast<const SField<UInt32>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< UInt64 >::getType())
        {
            UInt64SpinnerModelPtr TheModel(new UInt64SpinnerModel());
            TheModel->setMinimum(TypeTraits<UInt64>::getMin());
            TheModel->setMaximum(TypeTraits<UInt64>::getMax());
            TheModel->setStepSize(TypeTraits<UInt64>::getOneElement());
            TheModel->setValue(static_cast<const SField<UInt64>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        /*else if(TheFieldHandle->getType().getContentType() == FieldTraits< Real16 >::getType())
          {
          Real16SpinnerModelPtr TheModel(new Real16SpinnerModel());
          TheModel->setMinimum(-TypeTraits<Real16>::getMax());
          TheModel->setMaximum(TypeTraits<Real16>::getMax());
          TheModel->setStepSize(TypeTraits<Real16>::getOneElement());
          TheModel->setValue(static_cast<SField< Real16 >*>(TheField)->getValue());

          return TheModel;
          }*/
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< Real32 >::getType())
        {
            Real32SpinnerModelPtr TheModel(new Real32SpinnerModel());
            TheModel->setMinimum(-TypeTraits<Real32>::getMax());
            TheModel->setMaximum(TypeTraits<Real32>::getMax());
            TheModel->setStepSize(TypeTraits<Real32>::getOneElement());
            TheModel->setValue(static_cast<const SField<Real32>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
        else if(TheFieldHandle->getType().getContentType() == FieldTraits< Real64 >::getType())
        {
            Real64SpinnerModelPtr TheModel(new Real64SpinnerModel());
            TheModel->setMinimum(-TypeTraits<Real64>::getMax());
            TheModel->setMaximum(TypeTraits<Real64>::getMax());
            TheModel->setStepSize(TypeTraits<Real64>::getOneElement());
            TheModel->setValue(static_cast<const SField<Real64>*>(TheFieldHandle->getField())->getValue());

            return TheModel;
        }
    }
    return SpinnerModelPtr();
}

std::string SpinnerModel::getValueAsString(void) const
{
    try
    {
        return lexical_cast(const_cast<SpinnerModel*>(this)->getValue());
    }
    catch(boost::bad_any_cast &ex)
    {
        SWARNING << "Bad any cast: " << ex.what();
        return std::string("");
    }
    catch(boost::bad_lexical_cast &ex)
    {
        SWARNING << "Bad lexical cast: " << ex.what();
        return std::string("");
    }
}


OSG_END_NAMESPACE

