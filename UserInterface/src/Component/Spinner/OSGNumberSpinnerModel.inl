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
SharedFieldPtr NumberSpinnerModel<NumberTypeT>::getNextValue(void)
{
    assert(false && "getNextValue(void) not implemented");
    return NULL;
}

template<class NumberTypeT> inline
SharedFieldPtr NumberSpinnerModel<NumberTypeT>::getPreviousValue(void)
{
    assert(false && "getPreviousValue(void) not implemented");
    return NULL;
}

template<class NumberTypeT> inline
SharedFieldPtr NumberSpinnerModel<NumberTypeT>::getValue(void)
{
    return _Value;
}

template<class NumberTypeT> inline
void NumberSpinnerModel<NumberTypeT>::setValue(SharedFieldPtr value)
{
    _Value.setValue(dynamic_cast<SField<NumberTypeT>*>(value.get())->getValue());
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

