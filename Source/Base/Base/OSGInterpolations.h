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
#ifndef _OPENSG_INTERPOLATIONS_H_
#define _OPENSG_INTERPOLATIONS_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include <vector>

#include "OSGBaseFunctions.h"
#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGColor.h"
#include "OSGQuaternion.h"

OSG_BEGIN_NAMESPACE

//Generic Lerp
template <class FieldTypeT>
inline void lerp( const FieldTypeT& From, const FieldTypeT& To, const Real32& t, FieldTypeT& Result )
{
   //Return the linearly interpolated value
   Result = ( From + ( (To - From) * t ) );
}

template <class FieldTypeT>
inline FieldTypeT lerp( const FieldTypeT& From, const FieldTypeT& To, const Real32& t)
{
   //Return the linearly interpolated value
   return ( From + ( (To - From) *  t) );
}

//Generic Normal Lerp
template <class FieldTypeT>
inline void lerpNormal( const FieldTypeT& From, const FieldTypeT& To, const Real32& t, FieldTypeT& Result )
{
   //Create the Quaternion Representing int rotation from
   //Vec From to Vec To
   Quaternion Rotation(From, To);

   //Scale the angle to t, which is our lerp amount
   Rotation.scaleAngle(t);

   //Rotate the Resulting Vector by the Quaternion
   Rotation.multVec(From,Result);
}

//Generic Normal Lerp
template <class FieldTypeT>
inline FieldTypeT lerpNormal( const FieldTypeT& From, const FieldTypeT& To, const Real32& t )
{
    Quaternion::VectorType Result;
   //Create the Quaternion Representing int rotation from
   //Vec From to Vec To
   Quaternion Rotation(From, To);

   //Scale the angle to t, which is our lerp amount
   Rotation.scaleAngle(t);

   //Rotate the Resulting Vector by the Quaternion
   Rotation.multVec(From,Result);
   return FieldTypeT(Result.getValues());
}

//Matrix Lerp
template<class ValueTypeT>
inline TransformationMatrix<ValueTypeT> lerp(  const TransformationMatrix<ValueTypeT>& From, const TransformationMatrix<ValueTypeT>& To, const Real32& t)
{
    TransformationMatrix<ValueTypeT> Result;
    lerp(From,To,t,Result);
    return Result;
}

template<class ValueTypeT>
void  lerp(  const TransformationMatrix<ValueTypeT>& From, const TransformationMatrix<ValueTypeT>& To, const Real32& t, TransformationMatrix<ValueTypeT>& Result )
{
   //Return the linearly interpolated value
   //Get The Translation, Scale, and Rotation
   typename TransformationMatrix<ValueTypeT>::VectorType3f TranslationFrom;
   typename TransformationMatrix<ValueTypeT>::VectorType3f ScaleFactorFrom;
   typename TransformationMatrix<ValueTypeT>::QuaternionType RotationFrom;
   typename TransformationMatrix<ValueTypeT>::QuaternionType ScaleOrientationFrom;
   From.getTransform(TranslationFrom, RotationFrom, ScaleFactorFrom, ScaleOrientationFrom);
   
   typename TransformationMatrix<ValueTypeT>::VectorType3f TranslationTo;
   typename TransformationMatrix<ValueTypeT>::VectorType3f ScaleFactorTo;
   typename TransformationMatrix<ValueTypeT>::QuaternionType RotationTo;
   typename TransformationMatrix<ValueTypeT>::QuaternionType ScaleOrientationTo;
   To.getTransform(TranslationTo, RotationTo, ScaleFactorTo, ScaleOrientationTo);
   
   typename TransformationMatrix<ValueTypeT>::VectorType3f TranslationResult;
   typename TransformationMatrix<ValueTypeT>::VectorType3f ScaleFactorResult;
   typename TransformationMatrix<ValueTypeT>::QuaternionType RotationResult;
   typename TransformationMatrix<ValueTypeT>::QuaternionType ScaleOrientationResult;
   
   lerp(TranslationFrom, TranslationTo, t, TranslationResult);
   lerp(ScaleFactorFrom, ScaleFactorTo, t, ScaleFactorResult);
   if(RotationFrom != RotationTo)
   {
      RotationResult = TransformationMatrix<ValueTypeT>::QuaternionType::slerp(RotationFrom, RotationTo, t);
   }
   else
   {
      RotationResult = RotationTo;
   }
   if(ScaleOrientationFrom != ScaleOrientationTo)
   {
      ScaleOrientationResult = TransformationMatrix<ValueTypeT>::QuaternionType::slerp(ScaleOrientationFrom, ScaleOrientationTo, t);
   }
   else
   {
      ScaleOrientationResult = ScaleOrientationTo;
   }
   
   Result.setTransform(TranslationResult, RotationResult, ScaleFactorResult, ScaleOrientationResult);
}

//Generic Spline
template <class FieldTypeT>
FieldTypeT spline( const std::vector<FieldTypeT>& V, const std::vector<Real32>& t, const Real32& s )
{
   UInt8 i(1);
   //Set up the Blend Function
   Vector<Real32, 4 > S1(s*s*s, s*s, s, (Real32)1.0);
   
   //std::cout << "S: " << S1 << std::endl;
   
   Vector<Real32, 4 > H1( (Real32)2.0, (Real32)-3.0, (Real32)0.0, (Real32)1.0);
   Vector<Real32, 4 > H2( (Real32)-2.0,(Real32)3.0,  (Real32)0.0, (Real32)0.0);
   Vector<Real32, 4 > H3( (Real32)1.0, (Real32)-2.0, (Real32)1.0, (Real32)0.0);
   Vector<Real32, 4 > H4( (Real32)1.0, (Real32)-1.0, (Real32)0.0, (Real32)0.0);
   
   Vector<Real32, 4 > S2;
   S2[0] = S1.dot(H1);
   S2[1] = S1.dot(H2);
   S2[2] = S1.dot(H3);
   S2[3] = S1.dot(H4);
   
   //Setup the Tangent Vectors
   FieldTypeT Ti = (V[i+1]-V[i-1]) * (Real32)0.5;
   FieldTypeT Tiplus1 = (V[i+2]-V[i]) * (Real32)0.5;
   
   //Get the Scaling values
   Real32 Fnegi;
   if(t[i-1] == t[i+1])
   {
      Fnegi = (Real32)0.0;
   }
   else
   {
      Fnegi = ( (Real32)2.0 * (t[i+1] - t[i])/(t[i+1] - t[i-1]) );
   }
   
   Real32 Fposiplus1;
   if(t[i+2] == t[i])
   {
      Fposiplus1 = (Real32)0.0;
   }
   else
   {
      Fposiplus1 = ( (Real32)2.0 * (t[i+1] - t[i])/(t[i+2] - t[i]) );
   }
         
   //Return the spline
   return V[i] * S2[0]
         + V[i+1] * S2[1]
         + (Ti * Fnegi) * S2[2]
         + (Tiplus1 * Fposiplus1) * S2[3];
}

template <class FieldTypeT>
inline void spline( const std::vector<FieldTypeT>& V, const std::vector<Real32>& t, const Real32& s, FieldTypeT& Result )
{
    Result = spline(V,t,s); 
}

//Matrix Spline
template<class ValueTypeT>
inline TransformationMatrix<ValueTypeT> spline( const std::vector<TransformationMatrix<ValueTypeT> >& V, const std::vector<Real32>& t, const Real32& s)
{
    TransformationMatrix<ValueTypeT> Result;
    spline(V,t,s,Result);
    return Result;
}

template <class ValueTypeT>
inline void spline( const std::vector<TransformationMatrix<ValueTypeT> >& V, const std::vector<Real32>& t, const Real32& s, TransformationMatrix<ValueTypeT>& Result )
{
   UInt8 i(1);
   
   std::vector< typename TransformationMatrix<ValueTypeT>::VectorType3f > TransV;
   std::vector< typename TransformationMatrix<ValueTypeT>::VectorType3f > ScaleV;
   std::vector< typename TransformationMatrix<ValueTypeT>::QuaternionType > RotQ;
   std::vector< typename TransformationMatrix<ValueTypeT>::QuaternionType > ScaleOrientationQ;
   
   
   typename TransformationMatrix<ValueTypeT>::VectorType3f Translation;
   typename TransformationMatrix<ValueTypeT>::VectorType3f ScaleFactor;
   typename TransformationMatrix<ValueTypeT>::QuaternionType Rotation;
   typename TransformationMatrix<ValueTypeT>::QuaternionType ScaleOrientation;
   
   V[i-1].getTransform(Translation, Rotation, ScaleFactor, ScaleOrientation);
   TransV.push_back(Translation);
   ScaleV.push_back(ScaleFactor);
   RotQ.push_back(Rotation);
   ScaleOrientationQ.push_back(ScaleOrientation);
   
   V[i].getTransform(Translation, Rotation, ScaleFactor, ScaleOrientation);
   TransV.push_back(Translation);
   ScaleV.push_back(ScaleFactor);
   RotQ.push_back(Rotation);
   ScaleOrientationQ.push_back(ScaleOrientation);
   
   V[i+1].getTransform(Translation, Rotation, ScaleFactor, ScaleOrientation);
   TransV.push_back(Translation);
   ScaleV.push_back(ScaleFactor);
   RotQ.push_back(Rotation);
   ScaleOrientationQ.push_back(ScaleOrientation);
   
   V[i+2].getTransform(Translation, Rotation, ScaleFactor, ScaleOrientation);
   TransV.push_back(Translation);
   ScaleV.push_back(ScaleFactor);
   RotQ.push_back(Rotation);
   ScaleOrientationQ.push_back(ScaleOrientation);
   
   spline(TransV, t, s, Translation);
   spline(ScaleV, t, s, ScaleFactor);
   TransformationMatrix<ValueTypeT>::QuaternionType::squad(RotQ, t, s, Rotation);
   TransformationMatrix<ValueTypeT>::QuaternionType::squad(ScaleOrientationQ, t, s, ScaleOrientation);
   
   Result.setTransform(Translation, Rotation, ScaleFactor, ScaleOrientation);
}

OSG_END_NAMESPACE

#endif


