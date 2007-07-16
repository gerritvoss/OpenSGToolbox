#ifndef _OPENSG_MFIELD_INTERPOLATIONS_H_
#define _OPENSG_MFIELD_INTERPOLATIONS_H_

#include "OSGAnimationDef.h"

#include <vector>

#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGColor.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGField.h>

#include <OpenSG/Toolbox/OSGQuatOperations.h>
#include <OpenSG/Toolbox/OSGColorOperations.h>
#include <OpenSG/Toolbox/OSGPntOperations.h>

OSG_BEGIN_NAMESPACE

//MultiField Interpolations

//Linear
template <class FieldTypeT>
void MFieldLinearInterpFunc(const osg::Field& FromMField,
                               const osg::Field& ToMField,
                               osg::Field& ResultMField,
                               const osg::UInt32 FromIndex,
                               const osg::UInt32 ToIndex,
                               const osg::UInt32 ResultIndex,
                               const osg::Real32 t)
{
   static_cast<FieldTypeT&>(ResultMField).setValue(
      static_cast<const FieldTypeT&>(FromMField).getValue(FromIndex) + ( (static_cast<const FieldTypeT&>(ToMField).getValue(ToIndex) - static_cast<const FieldTypeT&>(FromMField).getValue(FromIndex)) * t ),
      ResultIndex);  
}

//Linear For Surface Normals
template <class FieldTypeT>
void MFieldLinearNormalInterpFunc(const osg::Field& FromMField,
                               const osg::Field& ToMField,
                               osg::Field& ResultMField,
                               const osg::UInt32 FromIndex,
                               const osg::UInt32 ToIndex,
                               const osg::UInt32 ResultIndex,
                               const osg::Real32 t)
{
   //Create the Quaternion Representing int rotation from
   //Vec From to Vec To
   QuaternionBase<typename FieldTypeT::StoredType::ValueType> Rotation(static_cast<const FieldTypeT&>(FromMField).getValue(FromIndex), static_cast<const FieldTypeT&>(ToMField).getValue(ToIndex));

   //Scale the angle to t, which is our lerp amount
   Rotation.scaleAngle(t);

   //Rotate the Resulting Vector by the Quaternion
   Rotation.multVec(static_cast<const FieldTypeT&>(FromMField).getValue(FromIndex),static_cast<FieldTypeT&>(ResultMField).getValue(ResultIndex));
}

//Step
template <class FieldTypeT>
void MFieldStepInterpFunc(const osg::Field& FromMField,
                               const osg::Field& ToMField,
                               osg::Field& ResultMField,
                               const osg::UInt32 FromIndex,
                               const osg::UInt32 ToIndex,
                               const osg::UInt32 ResultIndex,
                               const osg::Real32 t)
{
   static_cast<FieldTypeT&>(ResultMField).setValue(
      static_cast<const FieldTypeT&>(FromMField).getValue(FromIndex),
      ResultIndex);
}
OSG_END_NAMESPACE

#endif
