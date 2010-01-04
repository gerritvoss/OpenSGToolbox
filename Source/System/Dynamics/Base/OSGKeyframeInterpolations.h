#ifndef _OPENSG_KEYFRAME_INTERPOLATIONS_H_
#define _OPENSG_KEYFRAME_INTERPOLATIONS_H_

#include "OSGDynamicsDef.h"

#include "OSGField.h"
#include "OSGBaseFields.h"
#include "OSGSysFields.h"
#include "OSGMathFields.h"
#include "OSGBaseTypes.h"

#include "OSGInterpolations.h"
#include "OSGAnimator.h"
#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

typedef boost::function<bool (const Real32&, Field&, bool)> RawInterpFuncion;
typedef boost::function<bool (RawInterpFuncion&,
                              const Real32&,
                              const Real32&,
                              const UInt32&,
                              bool,
                              Field&,
                              UInt32,
                              Real32)> ReplacementFuncion;

bool OSG_DYNAMICS_DLLMAPPING getInterpolationIndexes(const MFReal32& Keys, const Real32& time, UInt32& LastKeyframeIndex, UInt32& NextKeyframeIndex, Real32& t, bool isCyclic=false);

bool OSG_DYNAMICS_DLLMAPPING getInterpolationIndex(const MFReal32& Keys, const Real32& time, UInt32& Index, Real32& t, bool isCyclic=false);

template <class ValueTypeT,
          UInt32 SizeI     > inline
Point<ValueTypeT, SizeI>
    operator +(const Point<ValueTypeT, SizeI> &lValue,
               const Point<ValueTypeT, SizeI> &rValue )
{
    return lValue + rValue.subZero();
}

//Generic Replace
template<class SFieldTypeT>
bool replacement(RawInterpFuncion& InterpFunc,
                              const Real32& time,
                              const Real32& prevtime,
                              const UInt32& ReplacePolicy,
                              bool isCyclic,
                              Field& Result,
                              UInt32 Index, 
                              Real32 Blend)
{
    SFieldTypeT Value;
    bool ReturnValue = InterpFunc(time, Value,isCyclic);

   if(Result.getCardinality() == FieldType::SingleField)
   {
        switch(ReplacePolicy)
        {
            case Animator::ADDITIVE_SINCE_LAST:
            {
                SFieldTypeT PrevValue;
                InterpFunc(prevtime, PrevValue,isCyclic);
                static_cast<SFieldTypeT&>(Result).setValue(static_cast<SFieldTypeT&>(Result).getValue() + (Value.getValue() - PrevValue.getValue()) * Blend);
                break;
            }
        case Animator::ADDITIVE_ABSOLUTE:
            {
                static_cast<SFieldTypeT&>(Result).setValue(static_cast<SFieldTypeT&>(Result).getValue() + (Value.getValue() * Blend));
                break;
            }
        case Animator::OVERWRITE:
            static_cast<SFieldTypeT&>(Result).setValue(Value.getValue() * Blend);
            break;
        default:
            SWARNING << "No policy defined for Animation value replacement policy: " << ReplacePolicy << "." << std::endl;
            break;
       }
   }
   else
   {

        switch(ReplacePolicy)
        {
        case Animator::ADDITIVE_SINCE_LAST:
            {
                SFieldTypeT PrevValue;
                InterpFunc(prevtime, PrevValue,isCyclic);
                static_cast<MField<typename SFieldTypeT::StoredType>&>(Result)[Index] = static_cast<MField<typename SFieldTypeT::StoredType>&>(Result)[Index] + (Value.getValue() - PrevValue.getValue()) * Blend, Index;
                break;
            }
        case Animator::ADDITIVE_ABSOLUTE:
            static_cast<MField<typename SFieldTypeT::StoredType>&>(Result)[Index] = static_cast<MField<typename SFieldTypeT::StoredType>&>(Result)[Index] + (Value.getValue() * Blend);
            break;
        case Animator::OVERWRITE:
            static_cast<MField<typename SFieldTypeT::StoredType>&>(Result)[Index] = Value.getValue() * Blend;
            break;
        default:
            SWARNING << "No policy defined for Animation value replacement policy: " << ReplacePolicy << "." << std::endl;
            break;
       }
   }
    return ReturnValue;
}

//Matrix Replace
template<>
bool OSG_DYNAMICS_DLLMAPPING replacement<SFMatrix>(RawInterpFuncion& InterpFunc,
                              const Real32& time,
                              const Real32& prevtime,
                              const UInt32& ReplacePolicy,
                              bool isCyclic,
                              Field& Result,
                              UInt32 Index, 
                              Real32 Blend);

//String Linear Interpolation
std::string OSG_DYNAMICS_DLLMAPPING lerp( const std::string& From, const std::string& To, const Real32& t);
std::string OSG_DYNAMICS_DLLMAPPING lerpFromSide( const std::string& From, const std::string& To, const Real32& t);
std::string OSG_DYNAMICS_DLLMAPPING lerpAll( const std::string& From, const std::string& To, const Real32& t);


//String Replace
template<>
bool OSG_DYNAMICS_DLLMAPPING replacement<SFString>(RawInterpFuncion& InterpFunc,
                              const Real32& time,
                              const Real32& prevtime,
                              const UInt32& ReplacePolicy,
                              bool isCyclic,
                              Field& Result,
                              UInt32 Index, 
                              Real32 Blend);

//Generic Step
template<class MFieldTypeT,class SFieldTypeT>
bool  stepKeyframeSequence(  const MFieldTypeT& KeyValues, const MFReal32& Keys, const Real32& time, Field& Value, bool isCyclic=false )
{
   Real32 t;
   UInt32 LastKeyframeIndex, NextKeyframeIndex;
   SFieldTypeT Result;
   
   if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      Result.setValue(KeyValues.back());
   }
   else
   {
      //Return the floor
      Result.setValue(KeyValues[LastKeyframeIndex]);
   }
   if(Result.getValue() == static_cast<SFieldTypeT&>(Value).getValue())
   {
      return false;
   }
   else
   {
      static_cast<SFieldTypeT&>(Value).setValue(Result.getValue());
      return true;
   }
}

//Generic Lerp
template<class MFieldTypeT,class SFieldTypeT>
bool  lerpKeyframeSequence(  const MFieldTypeT& KeyValues, const MFReal32& Keys, const Real32& time, Field& Value, bool isCyclic=false )
{
   Real32 t;
   UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      static_cast<SFieldTypeT&>(Value).setValue(KeyValues[KeyValues.size()-1]);
   }
   else
   {
      //Return the linearly interpolated value
      static_cast<SFieldTypeT&>(Value).setValue(lerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t));
   }
   return true;
}

//Generic Spline
template<typename MFieldTypeT,typename SFieldTypeT>
bool  splineKeyframeSequence(  const MFieldTypeT& KeyValues, const MFReal32& Keys, const Real32& time, Field& Value, bool isCyclic=false )
{
   Real32 t;
   UInt32 i;
   
   if( getInterpolationIndex(Keys, time, i, t, isCyclic) )
   {
      static_cast<SFieldTypeT&>(Value).setValue(KeyValues[KeyValues.size()-1]);
      return true;
   }
   
   std::vector< typename MFieldTypeT::StoredType > V;
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
         static_cast<SFieldTypeT&>(Value).setValue(KeyValues[KeyValues.size()-1]);
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
   
   static_cast<SFieldTypeT&>(Value).setValue(spline(V, T, t));
   return true;
}

//Normals Lerp
template<class MFieldTypeT,class SFieldTypeT>
bool  lerpNormalKeyframeSequence(  const MFieldTypeT& KeyValues, const MFReal32& Keys, const Real32& time, Field& Value, bool isCyclic=false )
{
   Real32 t;
   UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      static_cast<SFieldTypeT&>(Value).setValue(KeyValues[KeyValues.size()-1]);
   }
   else
   {
      //Return the linearly interpolated value
      static_cast<SFieldTypeT&>(Value).setValue(lerpNormal(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t));
   }
   return true;
}

//Slerp -- Quaternion Lerp
template<class MFieldTypeT,class SFieldTypeT>
bool  slerpKeyframeSequence(  const MFieldTypeT& KeyValues, const MFReal32& Keys, const Real32& time, Field& Value, bool isCyclic=false )
{
   Real32 t;
   UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      static_cast<SFieldTypeT&>(Value).setValue( KeyValues[KeyValues.size()-1] );
   }
   else
   {
      //Return the spherically interpolated value
      static_cast<SFieldTypeT&>(Value).setValue(SFieldTypeT::StoredType::slerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t));
   }
   return true;
}

//Nlerp -- Normalized Quaternion Lerp
template<class MFieldTypeT,class SFieldTypeT>
bool  nlerpKeyframeSequence(  const MFieldTypeT& KeyValues, const MFReal32& Keys, const Real32& time, Field& Value, bool isCyclic=false )
{
   Real32 t;
   UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      static_cast<SFieldTypeT&>(Value).setValue( KeyValues[KeyValues.size()-1] );
   }
   else
   {
      //Return the spherically interpolated value
      static_cast<SFieldTypeT&>(Value).setValue(SFieldTypeT::StoredType::nlerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t));
   }
   return true;
}
//Squad -- Quaternion Spline
template<class MFieldTypeT,class SFieldTypeT>
bool  squadKeyframeSequence(  const MFieldTypeT& KeyValues, const MFReal32& Keys, const Real32& time, Field& Value, bool isCyclic=false )
{
   Real32 t;
   UInt32 i;
   
   if( getInterpolationIndex(Keys, time, i, t, isCyclic) )
   {
      static_cast<SFieldTypeT&>(Value).setValue( KeyValues[KeyValues.size()-1] );
      return true;
   }
   
   std::vector<typename SFieldTypeT::StoredType > Q;
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
         static_cast<SFieldTypeT&>(Value).setValue(KeyValues[KeyValues.size()-1]);
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
   
   static_cast<SFieldTypeT&>(Value).setValue(SFieldTypeT::StoredType::squad(Q, T, t));
   return true;
}

OSG_END_NAMESPACE

#endif


