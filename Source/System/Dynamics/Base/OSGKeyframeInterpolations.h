#ifndef _OPENSG_KEYFRAME_INTERPOLATIONS_H_
#define _OPENSG_KEYFRAME_INTERPOLATIONS_H_

#include "OSGTBAnimationDef.h"

#include "OSGField.h"
#include "OSGBaseFields.h"
#include "OSGSysFields.h"
#include "OSGMathFields.h"
#include "OSGBaseTypes.h"

#include "OSGInterpolations.h"
#include "OSGAnimator.h"
#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

bool OSG_TBANIMATION_DLLMAPPING getInterpolationIndexes(const MFReal32& Keys, const Real32& time, UInt32& LastKeyframeIndex, UInt32& NextKeyframeIndex, Real32& t, bool isCyclic=false);

bool OSG_TBANIMATION_DLLMAPPING getInterpolationIndex(const MFReal32& Keys, const Real32& time, UInt32& Index, Real32& t, bool isCyclic=false);

template <class ValueTypeT, UInt32 SizeI     > inline
Point<ValueTypeT, SizeI>
operator +(const Point<ValueTypeT, SizeI> &lValue,
           const Point<ValueTypeT, SizeI> &rValue )
{
    return lValue + rValue.subZero();
}

//***************************** Replacement Methods **************************/
//****************************************************************************/
template<class ValueTypeT>
bool overwriteReplacement(boost::function<bool (Real32, ValueTypeT&, bool)>& InterpFunc,
                          Real32 time,
                          Real32 prevtime,
                          bool isCyclic,
                          ValueTypeT& Result,
                          Real32 Blend)
{
    ValueTypeT Value;
    bool ReturnValue = InterpFunc(time, Value,isCyclic);
    Result = Value * Blend;

    return ReturnValue;
}

template<class ValueTypeT>
bool overwriteNoBlendReplacement(boost::function<bool (Real32, ValueTypeT&, bool)>& InterpFunc,
                                 Real32 time,
                                 Real32 prevtime,
                                 bool isCyclic,
                                 ValueTypeT& Result,
                                 Real32 Blend)
{
    ValueTypeT Value;
    bool ReturnValue = InterpFunc(time, Value,isCyclic);
    Result = Value;

    return ReturnValue;
}

template<class ValueTypeT>
bool additiveAbsoluteReplacement(boost::function<bool (Real32, ValueTypeT&, bool)>& InterpFunc,
                                 Real32 time,
                                 Real32 prevtime,
                                 bool isCyclic,
                                 ValueTypeT& Result,
                                 Real32 Blend)
{
    ValueTypeT Value;
    bool ReturnValue = InterpFunc(time, Value,isCyclic);
    Result = Result + (Value * Blend);

    return ReturnValue;
}

template<class ValueTypeT>
bool additiveSinceLastReplacement(boost::function<bool (Real32, ValueTypeT&, bool)>& InterpFunc,
                                  Real32 time,
                                  Real32 prevtime,
                                  bool isCyclic,
                                  ValueTypeT& Result,
                                  Real32 Blend)
{
    ValueTypeT Value;
    bool ReturnValue = InterpFunc(time, Value,isCyclic);

    ValueTypeT PrevValue;
    InterpFunc(prevtime, PrevValue,isCyclic);
    Result = Result + ((Value - PrevValue) * Blend);

    return ReturnValue;
}

//Matrix Replace
template<class ValueTypeT>
bool overwriteMatrixReplacement(boost::function<bool (Real32, ValueTypeT&, bool)>& InterpFunc,
                          Real32 time,
                          Real32 prevtime,
                          bool isCyclic,
                          ValueTypeT& Result,
                          Real32 Blend)
{
    ValueTypeT Value;
    bool ReturnValue = InterpFunc(time, Value,isCyclic);
    Result = Value;
    Result.scale(Blend);

    return ReturnValue;
}

template<class ValueTypeT>
bool additiveAbsoluteMatrixReplacement(boost::function<bool (Real32, ValueTypeT&, bool)>& InterpFunc,
                                 Real32 time,
                                 Real32 prevtime,
                                 bool isCyclic,
                                 ValueTypeT& Result,
                                 Real32 Blend)
{
    ValueTypeT Value(Result);
    bool ReturnValue = InterpFunc(time, Value,isCyclic);

    Value.scale(Blend);
    Result.mult(Value);

    return ReturnValue;
}

template<class ValueTypeT>
bool additiveSinceLastMatrixReplacement(boost::function<bool (Real32, ValueTypeT&, bool)>& InterpFunc,
                                        Real32 time,
                                        Real32 prevtime,
                                        bool isCyclic,
                                        ValueTypeT& Result,
                                        Real32 Blend)
{
    ValueTypeT Value(Result);
    bool ReturnValue = InterpFunc(time, Value,isCyclic);

    ValueTypeT PrevValue;
    InterpFunc(prevtime, PrevValue,isCyclic);

    ValueTypeT DeltaSinceLast(PrevValue);
    DeltaSinceLast.invert();
    DeltaSinceLast.mult(Value);
    DeltaSinceLast.scale(Blend);
    Result.mult( DeltaSinceLast );

    return ReturnValue;
}

////String Linear Interpolation
std::string OSG_TBANIMATION_DLLMAPPING lerp( const std::string& From, const std::string& To, Real32 t);
std::string OSG_TBANIMATION_DLLMAPPING lerpFromSide( const std::string& From, const std::string& To, Real32 t);
std::string OSG_TBANIMATION_DLLMAPPING lerpAll( const std::string& From, const std::string& To, Real32 t);

//Generic Step
template<class ValueTypeT>
bool  stepKeyframeSequence(const MField<ValueTypeT>& KeyValues, const MFReal32& Keys, Real32 time, ValueTypeT& Value, bool isCyclic=false )
{
    Real32 t;
    UInt32 LastKeyframeIndex, NextKeyframeIndex;
    ValueTypeT Result;

    if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
    {
        Result = KeyValues.back();
    }
    else
    {
        //Return the floor
        Result = KeyValues[LastKeyframeIndex];
    }
    if(Result == Value)
    {
        return false;
    }
    else
    {
        Value = Result;
        return true;
    }
}

template<class ValueTypeT, UInt32 MFieldNamespace>
bool  stepKeyframeSequenceSpec(const MField<ValueTypeT,MFieldNamespace>& KeyValues, const MFReal32& Keys, Real32 time, ValueTypeT& Value, bool isCyclic=false )
{
    Real32 t;
    UInt32 LastKeyframeIndex, NextKeyframeIndex;
    ValueTypeT Result;

    if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
    {
        Result = KeyValues.back();
    }
    else
    {
        //Return the floor
        Result = KeyValues[LastKeyframeIndex];
    }
    if(Result == Value)
    {
        return false;
    }
    else
    {
        Value = Result;
        return true;
    }
}

//Generic Lerp
template<class ValueTypeT>
bool  lerpKeyframeSequence(const MField<ValueTypeT>& KeyValues, const MFReal32& Keys, Real32 time, ValueTypeT& Value, bool isCyclic=false )
{
    Real32 t;
    UInt32 LastKeyframeIndex, NextKeyframeIndex;

    if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
    {
        Value = KeyValues[KeyValues.size()-1];
    }
    else
    {
        //Return the linearly interpolated value
        Value = lerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t);
    }
    return true;
}

template<class ValueTypeT, UInt32 MFieldNamespace>
bool  lerpKeyframeSequenceSpec(const MField<ValueTypeT,MFieldNamespace>& KeyValues, const MFReal32& Keys, Real32 time, ValueTypeT& Value, bool isCyclic=false )
{
    Real32 t;
    UInt32 LastKeyframeIndex, NextKeyframeIndex;

    if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
    {
        Value = KeyValues[KeyValues.size()-1];
    }
    else
    {
        //Return the linearly interpolated value
        Value = lerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t);
    }
    return true;
}

//Generic Spline
template<class ValueTypeT>
bool  splineKeyframeSequence(const MField<ValueTypeT>& KeyValues, const MFReal32& Keys, Real32 time, ValueTypeT& Value, bool isCyclic=false )
{
    Real32 t;
    UInt32 i;

    if( getInterpolationIndex(Keys, time, i, t, isCyclic) )
    {
        Value = KeyValues[KeyValues.size()-1];
        return true;
    }

    std::vector< ValueTypeT > V;
    std::vector<Real32> T;

    V.reserve(4);
    T.reserve(4);

    if(isCyclic)
    {
        if(i == 0)
        {
            V.push_back(KeyValues[KeyValues.size()-2]);
            V.push_back(KeyValues[i]);
            V.push_back(KeyValues[i+1]);
            V.push_back(KeyValues[i+2]);

            T.push_back(Keys[Keys.size()-2] - Keys[Keys.size()-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i+2]);
        }
        else if(i == KeyValues.size()-1)
        {
            V.push_back(KeyValues[i-1]);
            V.push_back(KeyValues[i]);
            V.push_back(KeyValues[1]);
            V.push_back(KeyValues[2]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[1] + Keys[KeyValues.size()-1]);
            T.push_back(Keys[2] + Keys[KeyValues.size()-1]);
        }
        else if(i == KeyValues.size()-2)
        {
            V.push_back(KeyValues[i-1]);
            V.push_back(KeyValues[i]);
            V.push_back(KeyValues[i+1]);
            V.push_back(KeyValues[1]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[1] + Keys[KeyValues.size()-1]);
        }
        else
        {
            V.push_back(KeyValues[i-1]);
            V.push_back(KeyValues[i]);
            V.push_back(KeyValues[i+1]);
            V.push_back(KeyValues[i+2]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i+2]);
        }
    }
    else
    {
        if(i == 0)
        {
            V.push_back(KeyValues[i]);
            V.push_back(KeyValues[i]);
            V.push_back(KeyValues[i+1]);
            V.push_back(KeyValues[i+2]);

            T.push_back(Keys[i+1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i+2]);
        }
        else if(i == KeyValues.size()-1)
        {
            Value = KeyValues[KeyValues.size()-1];
            return true;
        }
        else if(i == KeyValues.size()-2)
        {
            V.push_back(KeyValues[i-1]);
            V.push_back(KeyValues[i]);
            V.push_back(KeyValues[i+1]);
            V.push_back(KeyValues[i+1]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i]);
        }
        else
        {
            V.push_back(KeyValues[i-1]);
            V.push_back(KeyValues[i]);
            V.push_back(KeyValues[i+1]);
            V.push_back(KeyValues[i+2]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i+2]);
        }
    }

    Value = spline(V, T, t);
    return true;
}

//Slerp -- Quaternion Lerp
template<class ValueTypeT>
bool  slerpKeyframeSequence(const MField<ValueTypeT>& KeyValues,
                            const MFReal32& Keys,
                            Real32 time,
                            ValueTypeT& Value,
                            bool isCyclic=false )
{
    Real32 t;
    UInt32 LastKeyframeIndex, NextKeyframeIndex;

    if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
    {
        Value = KeyValues[KeyValues.size()-1];
    }
    else
    {
        //Return the spherically interpolated value
        Value = ValueTypeT::slerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t);
    }
    return true;
}

//Nlerp -- Normalized Quaternion Lerp
template<class ValueTypeT>
bool  nlerpKeyframeSequence(const MField<ValueTypeT>& KeyValues,
                            const MFReal32& Keys,
                            Real32 time,
                            ValueTypeT& Value,
                            bool isCyclic=false )
{
    Real32 t;
    UInt32 LastKeyframeIndex, NextKeyframeIndex;

    if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
    {
        Value = KeyValues[KeyValues.size()-1];
    }
    else
    {
        //Return the spherically interpolated value
        Value = ValueTypeT::nlerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t);
    }
    return true;
}

//Squad -- Quaternion Spline
template<class ValueTypeT>
bool  squadKeyframeSequence(const MField<ValueTypeT>& KeyValues,
                            const MFReal32& Keys,
                            Real32 time,
                            ValueTypeT& Value,
                            bool isCyclic=false )
{
    Real32 t;
    UInt32 i;

    if( getInterpolationIndex(Keys, time, i, t, isCyclic) )
    {
        Value = KeyValues[KeyValues.size()-1];
        return true;
    }

    std::vector<ValueTypeT> Q;
    std::vector<Real32> T;

    Q.reserve(4);
    T.reserve(4);

    if(isCyclic)
    {
        if(i == 0)
        {
            Q.push_back(KeyValues[KeyValues.size()-2]);
            Q.push_back(KeyValues[i]);
            Q.push_back(KeyValues[i+1]);
            Q.push_back(KeyValues[i+2]);

            T.push_back(Keys[Keys.size()-2] - Keys[Keys.size()-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i+2]);
        }
        else if(i == KeyValues.size()-1)
        {
            Q.push_back(KeyValues[i-1]);
            Q.push_back(KeyValues[i]);
            Q.push_back(KeyValues[1]);
            Q.push_back(KeyValues[2]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[1] + Keys[KeyValues.size()-1]);
            T.push_back(Keys[2] + Keys[KeyValues.size()-1]);
        }
        else if(i == KeyValues.size()-2)
        {
            Q.push_back(KeyValues[i-1]);
            Q.push_back(KeyValues[i]);
            Q.push_back(KeyValues[i+1]);
            Q.push_back(KeyValues[1]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[1] + Keys[KeyValues.size()-1]);
        }
        else
        {
            Q.push_back(KeyValues[i-1]);
            Q.push_back(KeyValues[i]);
            Q.push_back(KeyValues[i+1]);
            Q.push_back(KeyValues[i+2]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i+2]);
        }
    }
    else
    {
        if(i == 0)
        {
            Q.push_back(KeyValues[i]);
            Q.push_back(KeyValues[i]);
            Q.push_back(KeyValues[i+1]);
            Q.push_back(KeyValues[i+2]);

            T.push_back(Keys[i+1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i+2]);
        }
        else if(i == KeyValues.size()-1)
        {
            Value = KeyValues[KeyValues.size()-1];
            return true;
        }
        else if(i == KeyValues.size()-2)
        {
            Q.push_back(KeyValues[i-1]);
            Q.push_back(KeyValues[i]);
            Q.push_back(KeyValues[i+1]);
            Q.push_back(KeyValues[i+1]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i]);
        }
        else
        {
            Q.push_back(KeyValues[i-1]);
            Q.push_back(KeyValues[i]);
            Q.push_back(KeyValues[i+1]);
            Q.push_back(KeyValues[i+2]);

            T.push_back(Keys[i-1]);
            T.push_back(Keys[i]);
            T.push_back(Keys[i+1]);
            T.push_back(Keys[i+2]);
        }
    }

    Value = ValueTypeT::squad(Q, T, t);
    return true;
}

OSG_END_NAMESPACE

#endif

