#ifndef _OPENSG_MFINTERPOLATIONS_H_
#define _OPENSG_MFINTERPOLATIONS_H_

#include "OSGAnimationDef.h"

#include <vector>

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGMField.h>
#include <OpenSG/OSGMFSysTypes.h>
#include <OpenSG/OSGMFBaseTypes.h>
#include <OpenSG/OSGMFMathTypes.h>

#include <OpenSG/Toolbox/OSGInterpolations.h>

OSG_BEGIN_NAMESPACE

bool OSG_ANIMATIONLIB_DLLMAPPING getInterpolationIndexes(const osg::MFReal32& Keys, const osg::Real32& Time, osg::UInt32& LastKeyframeIndex, osg::UInt32& NextKeyframeIndex, osg::Real32& t, bool isCyclic=false);

bool OSG_ANIMATIONLIB_DLLMAPPING getInterpolationIndex(const osg::MFReal32& Keys, const osg::Real32& Time, osg::UInt32& Index, osg::Real32& t, bool isCyclic=false);

//Generic Lerp
template <class FieldTypeT, osg::Int32 fieldNameSpace>
void  lerp(  const osg::MField<FieldTypeT, fieldNameSpace>& KeyValues, const osg::MFReal32& Keys, const osg::Real32& Time, FieldTypeT& Value, bool isCyclic=false )
{
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      Value = KeyValues[KeyValues.size()-1];
   }
   else
   {
      //Return the linearly interpolated value
      osg::lerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t, Value);
   }
}

//Generic Spline
template <class FieldTypeT, osg::Int32 fieldNameSpace>
void  spline(  const osg::MField<FieldTypeT, fieldNameSpace>& KeyValues, const osg::MFReal32& Keys, const osg::Real32& Time, FieldTypeT& Value, bool isCyclic=false )
{
   osg::Real32 t;
   osg::UInt32 i;
   
   if( getInterpolationIndex(Keys, Time, i, t, isCyclic) )
   {
      Value = KeyValues[KeyValues.size()-1];
      return;
   }
   
   std::vector< FieldTypeT > V;
   std::vector<osg::Real32> T;
   
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
         return;
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
   
   osg::spline(V, T, t, Value);
}

//Slerp
template<class ValueTypeT>
void  slerp(  const osg::MField<osg::QuaternionBase<ValueTypeT> >& KeyValues, const osg::MFReal32& Keys, const osg::Real32& Time, osg::QuaternionBase<ValueTypeT>& Value, bool isCyclic=false )
{
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      Value = KeyValues[KeyValues.size()-1];
   }
   else
   {
      //Return the spherically interpolated value
      Value.slerp(KeyValues[LastKeyframeIndex], KeyValues[NextKeyframeIndex], t);
   }
}

//Squad
template<class ValueTypeT>
void  squad(  const osg::MField<osg::QuaternionBase<ValueTypeT> >& KeyValues, const osg::MFReal32& Keys, const osg::Real32& Time, osg::QuaternionBase<ValueTypeT>& Value, bool isCyclic=false )
{
   osg::Real32 t;
   osg::UInt32 i;
   
   if( getInterpolationIndex(Keys, Time, i, t, isCyclic) )
   {
      Value = KeyValues[KeyValues.size()-1];
      return;
   }
   
   std::vector<osg::QuaternionBase<ValueTypeT> > Q;
   std::vector<osg::Real32> T;
   
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
         return;
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
   
   osg::squad(Q, T, t, Value);
   
}

//Step
template <class FieldTypeT, osg::Int32 fieldNameSpace>
bool  step(  const osg::MField<FieldTypeT, fieldNameSpace>& KeyValues, const osg::MFReal32& Keys, const osg::Real32& Time, FieldTypeT& Value, bool isCyclic=false )
{
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   FieldTypeT Result;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      Result = KeyValues[KeyValues.size()-1];
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

//Floor
template <class FieldTypeT, osg::Int32 fieldNameSpace>
bool  floor(  const osg::MField<FieldTypeT, fieldNameSpace>& KeyValues, const osg::MFReal32& Keys, const osg::Real32& Time, FieldTypeT& Value, bool isCyclic=false )
{
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   FieldTypeT Result;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      Result = KeyValues[KeyValues.size()-1];
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

//Ceil
template <class FieldTypeT, osg::Int32 fieldNameSpace>
bool  ceil(  const osg::MField<FieldTypeT, fieldNameSpace>& KeyValues, const osg::MFReal32& Keys, const osg::Real32& Time, FieldTypeT& Value, bool isCyclic=false )
{
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   FieldTypeT Result;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      Result = KeyValues[KeyValues.size()-1];
   }
   else
   {  
      //Return the floor
      Result = KeyValues[NextKeyframeIndex];
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

//Closest
template <class FieldTypeT, osg::Int32 fieldNameSpace>
bool  closest(  const osg::MField<FieldTypeT, fieldNameSpace>& KeyValues, const osg::MFReal32& Keys, const osg::Real32& Time, FieldTypeT& Value, bool isCyclic=false )
{
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   FieldTypeT Result;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      Result = KeyValues[KeyValues.size()-1];
   }
   else
   {
      //Return the closest
      if(t <= 0.5)
      {
         Result = KeyValues[LastKeyframeIndex];
      }
      else
      {
         Result = KeyValues[NextKeyframeIndex];
      }
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

OSG_END_NAMESPACE

#endif
