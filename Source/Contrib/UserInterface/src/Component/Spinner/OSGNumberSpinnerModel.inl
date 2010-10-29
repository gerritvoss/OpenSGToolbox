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

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>


OSG_BEGIN_NAMESPACE

inline
std::string getNumberSpinnerModelClassModelName(void)
{
    return std::string("Number Spinner Model");
}

template<class NumberTypeT> inline
std::string NumberSpinnerModel<NumberTypeT>::getModelName(void) const
{
    return getNumberSpinnerModelClassModelName();
}

template<class NumberTypeT> inline
NumberSpinnerModel<NumberTypeT>::NumberSpinnerModel(void) :
    _Value(NumberType(0.0)),
    _Maximum(100.0),
    _Minimum(0.0),
    _StepSize(1.0),
    _StringOutputPrecision(4)
{
}

template<class NumberTypeT> inline
NumberSpinnerModel<NumberTypeT>::NumberSpinnerModel(const NumberType& value) :
    _Value(value),
    _Maximum(100.0),
    _Minimum(0.0),
    _StepSize(1.0),
    _StringOutputPrecision(4)
{
}

    template<class NumberTypeT> inline
boost::any NumberSpinnerModel<NumberTypeT>::getNextValue(void)
{
    try
    {
        //Check if we would go past the Maximum
        if(_Maximum - boost::any_cast<NumberType>(_Value) < _StepSize)
        {
            return boost::any();
        }
        NumberType NewVal(boost::any_cast<NumberType>(_Value) + _StepSize);
        return NewVal;
    }
    catch(boost::bad_any_cast &)
    {
        return boost::any();
    }
}

    template<class NumberTypeT> inline
boost::any NumberSpinnerModel<NumberTypeT>::getPreviousValue(void)
{
    try
    {
        //Check if we would go past the Minimum
        if(boost::any_cast<NumberType>(_Value) - _Minimum < _StepSize)
        {
            return boost::any();
        }
        NumberType NewVal(boost::any_cast<NumberType>(_Value) - _StepSize);
        return NewVal;
    }
    catch(boost::bad_any_cast &)
    {
        return boost::any();
    }
}

    template<class NumberTypeT> inline
boost::any NumberSpinnerModel<NumberTypeT>::getValue(void)
{
    return _Value;
}

    template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setValue(const boost::any& value)
{
    NumberType RawValue;
    try
    {
        RawValue = boost::any_cast<NumberTypeT>(value);
    }
    catch (boost::bad_any_cast &)
    {
        //Not a string
        throw IllegalArgumentException();
    }
    //If the Value is outside of the Range
    if(RawValue < _Minimum || RawValue > _Maximum)
    {
        throw IllegalArgumentException();
    }

    _Value = boost::any(RawValue);

    produceStateChanged();
}

    template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setValue(const std::string& value)
{
    NumberType NewValue(boost::lexical_cast<NumberTypeT>(value));

    //If the Value is outside of the Range
    if(NewValue < _Minimum || NewValue > _Maximum)
    {
        throw IllegalArgumentException();
    }

    _Value = boost::any(NewValue);

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
    try
    {
        return boost::any_cast<NumberTypeT>(_Value);
    }
    catch (boost::bad_any_cast &)
    {
        //Not a string
        return 0;
    }
}

    template<class NumberTypeT> inline
NumberTypeT NumberSpinnerModel<NumberTypeT>::getStepSize(void)
{
    return _StepSize;
}

template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setNumberValue(const NumberType& value)
{
    _Value = boost::any(value);
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

template<> inline
std::string NumberSpinnerModel<Real32>::getValueAsString(void) const
{
    std::ostringstream OutStream;
    OutStream << /*std::setiosflags(std::ios::floatfield) <<*/ std::setprecision(_StringOutputPrecision) << boost::any_cast<Real32>(_Value);
    return OutStream.str();
}

template<> inline
std::string NumberSpinnerModel<Real64>::getValueAsString(void) const
{
    std::ostringstream OutStream;
    OutStream << /*std::setiosflags(std::ios::floatfield) <<*/ std::setprecision(_StringOutputPrecision) << boost::any_cast<Real64>(_Value);
    return OutStream.str();
}

template<> inline
std::string NumberSpinnerModel<Fixed32>::getValueAsString(void) const
{
    std::ostringstream OutStream;
    OutStream << /*std::setiosflags(std::ios::floatfield) <<*/ std::setprecision(_StringOutputPrecision) << boost::any_cast<Fixed32>(_Value);
    return OutStream.str();
}

template<class NumberTypeT> inline
std::string NumberSpinnerModel<NumberTypeT>::getValueAsString(void) const
{
    return Inherited::getValueAsString();
}

template<class NumberTypeT> inline
Int16 NumberSpinnerModel<NumberTypeT>::getStringOutputPrecision(void) const
{
    return _StringOutputPrecision;
}

template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setStringOutputPrecision(Int16 p)
{
    _StringOutputPrecision = p;
}

OSG_END_NAMESPACE

