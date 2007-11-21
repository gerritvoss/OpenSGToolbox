/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

template<class NumberTypeT> inline
NumberSpinnerModel<NumberTypeT>::NumberSpinnerModel(void) :
  _Value(new SField<NumberType>(0))
{
}

template<class NumberTypeT> inline
NumberSpinnerModel<NumberTypeT>::NumberSpinnerModel(const NumberType& value) :
  _Value(new SField<NumberType>(value))
{
}

template<class NumberTypeT> inline
SharedFieldPtr NumberSpinnerModel<NumberTypeT>::getNextValue(void)
{
    //Check if we would go past the Maximum
    if(dynamic_cast< SField<NumberType>* >(_Value.get())->getValue() + _StepSize > _Maximum)
    {
        return SharedFieldPtr();
    }
    else
    {
        return SharedFieldPtr(new SField<NumberType>(dynamic_cast< SField<NumberType>* >(_Value.get())->getValue() + _StepSize));
    }
}

template<class NumberTypeT> inline
SharedFieldPtr NumberSpinnerModel<NumberTypeT>::getPreviousValue(void)
{
    //Check if we would go past the Minimum
    if(dynamic_cast< SField<NumberType>* >(_Value.get())->getValue() - _StepSize < _Minimum)
    {
        return SharedFieldPtr();
    }
    else
    {
        return SharedFieldPtr(new SField<NumberType>(dynamic_cast< SField<NumberType>* >(_Value.get())->getValue() - _StepSize));
    }
}

template<class NumberTypeT> inline
SharedFieldPtr NumberSpinnerModel<NumberTypeT>::getValue(void)
{
    return _Value;
}

template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setValue(SharedFieldPtr value)
{
    //If the Value is outside of the Range
    NumberType RawValue(dynamic_cast<SField<NumberTypeT>*>(value.get())->getValue());
    if(RawValue < _Minimum || RawValue > _Maximum)
    {
        throw IllegalArgumentException();
    }

    dynamic_cast<SField<NumberTypeT>*>(_Value.get())->setValue(RawValue);
    
    produceStateChanged();
}

template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setValue(const std::string& value)
{
    SharedFieldPtr NewFieldValue(new SField<NumberType>());
    NewFieldValue->pushValueByStr(value.c_str());

    //If the Value is outside of the Range
    NumberType RawValue(dynamic_cast<SField<NumberTypeT>*>(NewFieldValue.get())->getValue());
    if(RawValue < _Minimum || RawValue > _Maximum)
    {
        throw IllegalArgumentException();
    }

    _Value = NewFieldValue;
    
    produceStateChanged();
}

template<class NumberTypeT> inline
NumberTypeT NumberSpinnerModel<NumberTypeT>::getMaximum(void) const
{
    return _Maximum;
}

template<class NumberTypeT> inline
NumberTypeT NumberSpinnerModel<NumberTypeT>::getMinimum(void) const
{
    return _Minimum;
}

template<class NumberTypeT> inline
NumberTypeT NumberSpinnerModel<NumberTypeT>::getNumber(void) const
{
    return _Value.getValue();
}

template<class NumberTypeT> inline
NumberTypeT NumberSpinnerModel<NumberTypeT>::getStepSize(void)
{
    return _StepSize;
}

template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setMaximum(const NumberTypeT& maximum)
{
    _Maximum = maximum;
}

template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setMinimum(const NumberTypeT& minimum)
{
    _Minimum = minimum;
}

template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setStepSize(const NumberTypeT& stepSize)
{
    _StepSize = stepSize;
}

OSG_END_NAMESPACE

