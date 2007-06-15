#include "OSGMFieldInterpolations.h"
#include "Interpolation/OSGInterpolationFactory.h"

//Linear
   const bool MFLinearInterpFuncsRegistered = 
   //Points
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt2f::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt2f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt3f::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt3f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt4f::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt4f>) &&

      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt2d::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt2d>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt3d::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt3d>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt4d::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt4d>) &&

      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt2s::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt2s>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt3s::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt3s>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFPnt4s::getClassType(), osg::MFieldLinearInterpFunc<osg::MFPnt4s>) &&

   //Colors
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFColor3f::getClassType(), osg::MFieldLinearInterpFunc<osg::MFColor3f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFColor4f::getClassType(), osg::MFieldLinearInterpFunc<osg::MFColor4f>) &&

   //Vectors
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFReal32::getClassType(), osg::MFieldLinearInterpFunc<osg::MFReal32>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFReal64::getClassType(), osg::MFieldLinearInterpFunc<osg::MFReal64>) &&

      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFVec2f::getClassType(), osg::MFieldLinearInterpFunc<osg::MFVec2f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFVec3f::getClassType(), osg::MFieldLinearInterpFunc<osg::MFVec3f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFVec4f::getClassType(), osg::MFieldLinearInterpFunc<osg::MFVec4f>) &&

      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFVec2d::getClassType(), osg::MFieldLinearInterpFunc<osg::MFVec2d>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFVec3d::getClassType(), osg::MFieldLinearInterpFunc<osg::MFVec3d>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_INTERPOLATION, osg::MFVec4d::getClassType(), osg::MFieldLinearInterpFunc<osg::MFVec4d>)
      ;

//LinearNormals
   //Vectors
   const bool MFLinearNormalInterpFuncsRegistered = 
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_NORMAL_INTERPOLATION, osg::MFVec3f::getClassType(), osg::MFieldLinearNormalInterpFunc<osg::MFVec3f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::LINEAR_NORMAL_INTERPOLATION, osg::MFVec3d::getClassType(), osg::MFieldLinearNormalInterpFunc<osg::MFVec3d>)
      ;
   
//Step
   const bool MFStepInterpFuncsRegistered = 
   //Points
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt2f::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt2f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt3f::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt3f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt4f::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt4f>) &&

      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt2d::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt2d>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt3d::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt3d>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt4d::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt4d>) &&

      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt2s::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt2s>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt3s::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt3s>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFPnt4s::getClassType(), osg::MFieldStepInterpFunc<osg::MFPnt4s>) &&

   //Colors
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFColor3f::getClassType(), osg::MFieldStepInterpFunc<osg::MFColor3f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFColor4f::getClassType(), osg::MFieldStepInterpFunc<osg::MFColor4f>) &&

   //Vectors
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFReal32::getClassType(), osg::MFieldStepInterpFunc<osg::MFReal32>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFReal64::getClassType(), osg::MFieldStepInterpFunc<osg::MFReal64>) &&

      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFVec2f::getClassType(), osg::MFieldStepInterpFunc<osg::MFVec2f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFVec3f::getClassType(), osg::MFieldStepInterpFunc<osg::MFVec3f>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFVec4f::getClassType(), osg::MFieldStepInterpFunc<osg::MFVec4f>) &&

      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFVec2d::getClassType(), osg::MFieldStepInterpFunc<osg::MFVec2d>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFVec3d::getClassType(), osg::MFieldStepInterpFunc<osg::MFVec3d>) &&
      osg::InterpolationFactory::the()->registerMFieldInterpFunc(osg::STEP_INTERPOLATION, osg::MFVec4d::getClassType(), osg::MFieldStepInterpFunc<osg::MFVec4d>)
      ;