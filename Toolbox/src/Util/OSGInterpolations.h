#ifndef _OPENSG_INTERPOLATIONS_H_
#define _OPENSG_INTERPOLATIONS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <vector>

#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGColor.h>
#include <OpenSG/OSGQuaternion.h>

#include "OSGQuatOperations.h"
#include "OSGColorOperations.h"
#include "OSGPntOperations.h"

OSG_BEGIN_NAMESPACE

enum InterpolationType {LINEAR_INTERPOLATION=0, CUBIC_INTERPOLATION, STEP_INTERPOLATION, LINEAR_NORMAL_INTERPOLATION};
enum ValueReplacementPolicy {OVERWRITE=0, ADDITIVE_ABSOLUTE, ADDITIVE_SINCE_LAST};

//Generic Lerp
template <class FieldTypeT>
inline void lerp( const FieldTypeT& From, const FieldTypeT& To, const osg::Real32& t, FieldTypeT& Result )
{
   //Return the linearly interpolated value
   Result = ( From + ( (To - From) * t ) );
}

//Generic Normal Lerp
template <class FieldTypeT>
inline void lerpNormal( const FieldTypeT& From, const FieldTypeT& To, const osg::Real32& t, FieldTypeT& Result )
{
   //Create the Quaternion Representing int rotation from
   //Vec From to Vec To
   Quaternion Rotation(From, To);

   //Scale the angle to t, which is our lerp amount
   Rotation.scaleAngle(t);

   //Rotate the Resulting Vector by the Quaternion
   Rotation.multVec(From,Result);
}

//Matrix Lerp
template<class ValueTypeT>
void  lerp(  const osg::TransformationMatrix<ValueTypeT>& From, const osg::TransformationMatrix<ValueTypeT>& To, const osg::Real32& t, osg::TransformationMatrix<ValueTypeT>& Result )
{
   //Return the linearly interpolated value
   //Get The Translation, Scale, and Rotation
   typename osg::TransformationMatrix<ValueTypeT>::VectorType3f TranslationFrom;
   typename osg::TransformationMatrix<ValueTypeT>::VectorType3f ScaleFactorFrom;
   typename osg::TransformationMatrix<ValueTypeT>::QuaternionType RotationFrom;
   typename osg::TransformationMatrix<ValueTypeT>::QuaternionType ScaleOrientationFrom;
   From.getTransform(TranslationFrom, RotationFrom, ScaleFactorFrom, ScaleOrientationFrom);
   
   typename osg::TransformationMatrix<ValueTypeT>::VectorType3f TranslationTo;
   typename osg::TransformationMatrix<ValueTypeT>::VectorType3f ScaleFactorTo;
   typename osg::TransformationMatrix<ValueTypeT>::QuaternionType RotationTo;
   typename osg::TransformationMatrix<ValueTypeT>::QuaternionType ScaleOrientationTo;
   To.getTransform(TranslationTo, RotationTo, ScaleFactorTo, ScaleOrientationTo);
   
   typename osg::TransformationMatrix<ValueTypeT>::VectorType3f TranslationResult;
   typename osg::TransformationMatrix<ValueTypeT>::VectorType3f ScaleFactorResult;
   typename osg::TransformationMatrix<ValueTypeT>::QuaternionType RotationResult;
   typename osg::TransformationMatrix<ValueTypeT>::QuaternionType ScaleOrientationResult;
   
   osg::lerp(TranslationFrom, TranslationTo, t, TranslationResult);
   osg::lerp(ScaleFactorFrom, ScaleFactorTo, t, ScaleFactorResult);
   if(RotationFrom != RotationTo)
   {
      RotationResult = osg::TransformationMatrix<ValueTypeT>::QuaternionType::slerp(RotationFrom, RotationTo, t);
   }
   else
   {
      RotationResult = RotationTo;
   }
   if(ScaleOrientationFrom != ScaleOrientationTo)
   {
      ScaleOrientationResult = osg::TransformationMatrix<ValueTypeT>::QuaternionType::slerp(ScaleOrientationFrom, ScaleOrientationTo, t);
   }
   else
   {
      ScaleOrientationResult = ScaleOrientationTo;
   }
   
   Result.setTransform(TranslationResult, RotationResult, ScaleFactorResult, ScaleOrientationResult);
}

//Generic Spline
template <class FieldTypeT>
void spline( const std::vector<FieldTypeT>& V, const std::vector<osg::Real32>& t, const osg::Real32& s, FieldTypeT& Result )
{
   osg::UInt8 i(1);
   //Set up the Blend Function
   osg::Vec4f S1(s*s*s, s*s, s, 1.0);
   
   //std::cout << "S: " << S1 << std::endl;
   
   osg::Vec4f H1( 2.0, -3.0, 0.0, 1.0);
   osg::Vec4f H2(-2.0,  3.0, 0.0, 0.0);
   osg::Vec4f H3( 1.0, -2.0, 1.0, 0.0);
   osg::Vec4f H4( 1.0, -1.0, 0.0, 0.0);
   
   osg::Vec4f S2;
   S2[0] = S1.dot(H1);
   S2[1] = S1.dot(H2);
   S2[2] = S1.dot(H3);
   S2[3] = S1.dot(H4);
   
   //Setup the Tangent Vectors
   FieldTypeT Ti = (V[i+1]-V[i-1]) * 0.5f;
   //std::cout << "Ti: " << Ti << std::endl;
   FieldTypeT Tiplus1 = (V[i+2]-V[i]) * 0.5f;
   //std::cout << "Ti+1: " << Tiplus1 << std::endl;
   
   //Get the Scaling values
   osg::Real32 Fnegi;
   if(t[i-1] == t[i+1])
   {
      Fnegi = 0.0;
   }
   else
   {
      Fnegi = ( 2.0 * (t[i+1] - t[i])/(t[i+1] - t[i-1]) );
   }
   //std::cout << "F-i: " << Fnegi << std::endl;
   
   osg::Real32 Fposiplus1;
   if(t[i+2] == t[i])
   {
      Fposiplus1 = 0.0;
   }
   else
   {
      Fposiplus1 = ( 2.0 * (t[i+1] - t[i])/(t[i+2] - t[i]) );
   }
   //std::cout << "F+i+1: " << Fposiplus1 << std::endl;
         
   //Return the sline
   Result = S2[0] * V[i]
         + S2[1] * V[i+1]
         + S2[2] * (Fnegi * Ti)
         + S2[3] * (Fposiplus1 * Tiplus1);
}

//Squad
template <class ValueTypeT>
inline void squad( const std::vector<osg::QuaternionBase<ValueTypeT> >& Q, const std::vector<osg::Real32>& t, const osg::Real32& s, osg::QuaternionBase<ValueTypeT>& Result )
{
   osg::UInt8 i(1);
   
   //ai
   //Get the Tangent Quats
   osg::QuaternionBase<ValueTypeT> Ti = ( osg::log( osg::inverse(Q[i])*Q[i+1] ) + osg::log( osg::inverse(Q[i-1])*Q[i] ) )/static_cast<ValueTypeT>(2.0);
   
  
   //Get the Scaling values
   ValueTypeT Fnegi;
   if(t[i-1] == t[i+1])
   {
      Fnegi = 0.0;
   }
   else
   {
      Fnegi = static_cast<ValueTypeT>(2.0) * (t[i+1] - t[i])/(t[i+1] - t[i-1]);
   }
   
   osg::QuaternionBase<ValueTypeT> TanIncoming( Fnegi * Ti );
   
   osg::QuaternionBase<ValueTypeT> ai = Q[i] * osg::exp( (TanIncoming - osg::log(osg::inverse(Q[i])*Q[i+1]))/static_cast<ValueTypeT>(2.0) );
   
   //bi+1
   osg::QuaternionBase<ValueTypeT> Tiplus1 = ( osg::log( osg::inverse(Q[i+1])*Q[i+2] ) + osg::log( osg::inverse(Q[i])*Q[i+1] ) )/static_cast<ValueTypeT>(2.0);
   
   //Get the Scaling values
   ValueTypeT Fposiplus1;
   if(t[i+2] == t[i])
   {
      Fposiplus1 = 0.0;
   }
   else
   {
      Fposiplus1 = static_cast<ValueTypeT>(2.0) * (t[i+1] - t[i])/(t[i+2] - t[i]);
   }
   
   osg::QuaternionBase<ValueTypeT> TanOutgoingplus1( Fposiplus1 * Tiplus1 );
   
   osg::QuaternionBase<ValueTypeT> biplus1 = Q[i+1] * osg::exp( (osg::log(osg::inverse(Q[i])*Q[i+1]) - TanOutgoingplus1)/static_cast<ValueTypeT>(2.0) );
   
   //slerps
   Result = osg::slerp( osg::slerp(Q[i], Q[i+1], s), osg::slerp(ai, biplus1, s), (static_cast<ValueTypeT>(2.0)*s*(static_cast<ValueTypeT>(1.0)-s)) );
}

//Matrix Spline
template <class ValueTypeT>
inline void spline( const std::vector<osg::TransformationMatrix<ValueTypeT> >& V, const std::vector<osg::Real32>& t, const osg::Real32& s, osg::TransformationMatrix<ValueTypeT>& Result )
{
   osg::UInt8 i(1);
   
   std::vector< typename osg::TransformationMatrix<ValueTypeT>::VectorType3f > TransV;
   std::vector< typename osg::TransformationMatrix<ValueTypeT>::VectorType3f > ScaleV;
   std::vector< typename osg::TransformationMatrix<ValueTypeT>::QuaternionType > RotQ;
   std::vector< typename osg::TransformationMatrix<ValueTypeT>::QuaternionType > ScaleOrientationQ;
   
   
   typename osg::TransformationMatrix<ValueTypeT>::VectorType3f Translation;
   typename osg::TransformationMatrix<ValueTypeT>::VectorType3f ScaleFactor;
   typename osg::TransformationMatrix<ValueTypeT>::QuaternionType Rotation;
   typename osg::TransformationMatrix<ValueTypeT>::QuaternionType ScaleOrientation;
   
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
   
   osg::spline(TransV, t, s, Translation);
   osg::spline(ScaleV, t, s, ScaleFactor);
   osg::squad(RotQ, t, s, Rotation);
   osg::squad(ScaleOrientationQ, t, s, ScaleOrientation);
   
   Result.setTransform(Translation, Rotation, ScaleFactor, ScaleOrientation);
}

OSG_END_NAMESPACE

#endif
