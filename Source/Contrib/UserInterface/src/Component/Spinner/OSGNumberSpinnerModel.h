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

#ifndef _OSG_UI_NUMBER_SPINNER_MODEL_H_
#define _OSG_UI_NUMBER_SPINNER_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGAbstractSpinnerModel.h"

#include <list>
#include <exception>

OSG_BEGIN_NAMESPACE

static std::string getNumberSpinnerModelClassModelName(void);

template<class NumberTypeT>
class NumberSpinnerModel : public AbstractSpinnerModel
{
  public:
    typedef NumberTypeT NumberType;

    typedef AbstractSpinnerModel Inherited;

    NumberSpinnerModel(void);
    NumberSpinnerModel(const NumberType& value);

    //Return the object in the sequence that comes after the object returned by getValue().
    virtual boost::any getNextValue(void);

    //Return the object in the sequence that comes before the object returned by getValue().
    virtual boost::any getPreviousValue(void);

    //The current element of the sequence.
    virtual boost::any getValue(void);

    //Changes current value of the model, typically this value is displayed by the editor part of a Spinner
    virtual void setValue(const boost::any& value);

    virtual void setValue(const std::string& value);

    //Returns the last number in the sequence.
    NumberType getMaximum(void) const;

    //Returns the first number in this sequence.
    NumberType getMinimum(void) const;

    //Returns the value of the current element of the sequence.
    NumberType getNumber(void) const;

    //Returns the size of the value change computed by the getNextValue and getPreviousValue methods.
    NumberType getStepSize(void);

    //Set the value of the model
    void setNumberValue(const NumberType& value);

    //Changes the upper bound for numbers in this sequence.
    void setMaximum(const NumberType& maximum);

    //Changes the lower bound for numbers in this sequence.
    void setMinimum(const NumberType& minimum);

    //Changes the size of the value change computed by the getNextValue and getPreviousValue methods.
    void setStepSize(const NumberType& stepSize);

    virtual std::string getModelName(void) const;

    //The current element of the sequence as a string
    virtual std::string getValueAsString(void) const;


    Int16 getStringOutputPrecision(void) const;
    void setStringOutputPrecision(Int16 p);
  protected:
    boost::any _Value;
    NumberType _Maximum;
    NumberType _Minimum;
    NumberType _StepSize;
    Int16      _StringOutputPrecision;
};

typedef NumberSpinnerModel<Int8> Int8SpinnerModel;
typedef boost::shared_ptr<Int8SpinnerModel> Int8SpinnerModelPtr;

typedef NumberSpinnerModel<Int16> Int16SpinnerModel;
typedef boost::shared_ptr<Int16SpinnerModel> Int16SpinnerModelPtr;

typedef NumberSpinnerModel<Int32> Int32SpinnerModel;
typedef boost::shared_ptr<Int32SpinnerModel> Int32SpinnerModelPtr;

typedef NumberSpinnerModel<Int64> Int64SpinnerModel;
typedef boost::shared_ptr<Int64SpinnerModel> Int64SpinnerModelPtr;

typedef NumberSpinnerModel<UInt8> UInt8SpinnerModel;
typedef boost::shared_ptr<UInt8SpinnerModel> UInt8SpinnerModelPtr;

typedef NumberSpinnerModel<UInt16> UInt16SpinnerModel;
typedef boost::shared_ptr<UInt16SpinnerModel> UInt16SpinnerModelPtr;

typedef NumberSpinnerModel<UInt32> UInt32SpinnerModel;
typedef boost::shared_ptr<UInt32SpinnerModel> UInt32SpinnerModelPtr;

typedef NumberSpinnerModel<UInt64> UInt64SpinnerModel;
typedef boost::shared_ptr<UInt64SpinnerModel> UInt64SpinnerModelPtr;

typedef NumberSpinnerModel<Real16> Real16SpinnerModel;
typedef boost::shared_ptr<Real16SpinnerModel> Real16SpinnerModelPtr;

typedef NumberSpinnerModel<Real32> Real32SpinnerModel;
typedef boost::shared_ptr<Real32SpinnerModel> Real32SpinnerModelPtr;

typedef NumberSpinnerModel<Real64> Real64SpinnerModel;
typedef boost::shared_ptr<Real64SpinnerModel> Real64SpinnerModelPtr;

typedef NumberSpinnerModel<Real128> Real128SpinnerModel;
typedef boost::shared_ptr<Real128SpinnerModel> Real128SpinnerModelPtr;

typedef NumberSpinnerModel<Fixed32> Fixed32SpinnerModel;
typedef boost::shared_ptr<Fixed32SpinnerModel> Fixed32SpinnerModelPtr;

OSG_END_NAMESPACE

#include "OSGNumberSpinnerModel.inl"

#endif /* _OSG_UI_NUMBER_SPINNER_MODEL_H_ */

