#include "OSGGeometryInterpolations.h"

#include "OSGInterpolations.h"
#include "OSGInterpolationFactory.h"
#include "OSGKeyframeInterpolations.h"
#include "OSGMFieldInterpolations.h"
#include "Util/OSGGeoPropertyOperations.h"

OSG_BEGIN_NAMESPACE

//Positions Lerp
bool  lerp(  const GeoPositionsPtr BaseValues,const MFGeoPositionDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoPositionsPtr Value, bool isCyclic )
{
   if(DifferenceSets.size() == 0)
   {
      SWARNING << "The Geometry Postion Animation has only one frame defined.  Must have at least two."  << std::endl;
      return false;
   }
   if(BaseValues->getSize() != Value->getSize())
   {
      SWARNING << "Cannot annimate Geometry that doesn't have corresponding sizes."  << std::endl;
      return false;
   }
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   //Get Fields
   osg::Field *ResultsField = osg::getField(Value);
   osg::Field *BaseValuesField = osg::getField(BaseValues);
   osg::Field *DifferenceSets1Field = NULL;
   osg::Field *DifferenceSets2Field = NULL;
   osg::InterpolationFactory::MFieldInterpFunc LerpFunc( osg::InterpolationFactory::the()->getMFieldFunc(LINEAR_INTERPOLATION, ResultsField->getType().getId()) );
   osg::InterpolationFactory::MFieldInterpFunc StepFunc( osg::InterpolationFactory::the()->getMFieldFunc(STEP_INTERPOLATION, ResultsField->getType().getId()) );
   
   bool isFinished = getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic);
   if( isFinished )
   {
      //The animation has reached the end of its cycles
      //Set the result to the last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getPositions()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(LastKeyframeIndex == 0)
   {
      //Interpolate between BaseValues and the first Difference Set
      UInt32 FirstDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr FirstDiffSet = DifferenceSets.getValue(0);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( FirstDiffSet->getIndices()->getValue(FirstDiffSetIndex)== i )
         {
            //Get the difference set field
            DifferenceSets1Field = osg::getField(FirstDiffSet->getPositions());

            //Apply the function
            LerpFunc(*BaseValuesField, *DifferenceSets1Field, *ResultsField, i, FirstDiffSetIndex, i, t);

            ++FirstDiffSetIndex;
         }
         else
         {
            StepFunc(*BaseValuesField, *BaseValuesField, *ResultsField, i, i, i, t);
         }
      }
   }
   else if(NextKeyframeIndex == 0)
   {
      //Interpolate between the Last Difference Set and the BaseValues
      UInt32 LastDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            //Get the difference set field
            DifferenceSets1Field = osg::getField(LastDiffSet->getPositions());

            //Apply the function
            LerpFunc(*DifferenceSets1Field, *BaseValuesField, *ResultsField, LastDiffSetIndex, i, i, t);

            ++LastDiffSetIndex;
         }
         else
         {
            StepFunc(*BaseValuesField, *BaseValuesField, *ResultsField, i, i, i, t);
         }
      }
   }
   else
   {
      //Interpolate between two Difference Sets
      UInt32 NextDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr NextDiffSet = DifferenceSets.getValue(NextKeyframeIndex-1);
      UInt32 LastDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(LastKeyframeIndex-1);
      
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //Interpolate between the Last Diff set and the next Diff set
               //Get the difference set field
               DifferenceSets1Field = osg::getField(LastDiffSet->getPositions());
               DifferenceSets2Field = osg::getField(NextDiffSet->getPositions());

               //Apply the function
               LerpFunc(*DifferenceSets1Field, *DifferenceSets2Field, *ResultsField, LastDiffSetIndex, NextDiffSetIndex, i, t);

               ++NextDiffSetIndex;
            }
            else
            {
               //Interpolate between the Last Diff set and the BaseValues
               //Get the difference set field
               DifferenceSets1Field = osg::getField(LastDiffSet->getPositions());

               //Apply the function
               LerpFunc(*DifferenceSets1Field, *BaseValuesField, *ResultsField, LastDiffSetIndex, i, i, t);
            }
            ++LastDiffSetIndex;
         }
         else
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //Interpolate between the BaseValues and the next difference Set
               //Get the difference set field
               DifferenceSets1Field = osg::getField(NextDiffSet->getPositions());

               //Apply the function
               LerpFunc(*BaseValuesField, *DifferenceSets1Field, *ResultsField, i, NextDiffSetIndex, i, t);

               ++NextDiffSetIndex;
            }
            else
            {
               StepFunc(*BaseValuesField, *BaseValuesField, *ResultsField, i, i, i, t);
            }
         }
      }
   }
   return true;
}

//Positions Step
bool  step(  const GeoPositionsPtr BaseValues,const MFGeoPositionDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoPositionsPtr Value, bool isCyclic )
{
   if(DifferenceSets.size() == 0)
   {
      SWARNING << "The Geometry Postion Animation has only one frame defined.  Must have at least two."  << std::endl;
      return false;
   }
   if(BaseValues->getSize() != Value->getSize())
   {
      SWARNING << "Cannot annimate Geometry that doesn't have corresponding sizes."  << std::endl;
      return false;
   }
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      //The animation has reached the end of its cycles
      //Set the result to the last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getPositions()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(LastKeyframeIndex == 0) 
   {
      //Interpolate between BaseValues and the first Difference Set
      //For a Step interpolatin this should be all BaseValues
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         Value->setValue(BaseValues->getValue(i), i);
      }
   }
   else if(NextKeyframeIndex == 0)
   {
      //Interpolate between the Last Difference Set and the BaseValues
      //For a Step interpolatin this should be all the Last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getPositions()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else
   {
      //Interpolate between two Difference Sets
      UInt32 NextDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr NextDiffSet = DifferenceSets.getValue(NextKeyframeIndex-1);
      UInt32 LastDiffSetIndex = 0;
      GeoPositionDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(LastKeyframeIndex-1);
      
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //For Step interpolation this should be the Last Keyframe
               Value->setValue(LastDiffSet->getPositions()->getValue(LastDiffSetIndex), i);
               ++NextDiffSetIndex;
            }
            else
            {
               //For Step interpolation this should be the Last Keyframe
               Value->setValue(LastDiffSet->getPositions()->getValue(LastDiffSetIndex), i);
            }
            ++LastDiffSetIndex;
         }
         else
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //For Step interpolation this should be the Last Keyframe
               //Which for the the last Difference set was the BaseValue for this index
               Value->setValue(BaseValues->getValue(i), i);
               ++NextDiffSetIndex;
            }
            else
            {
               Value->setValue(BaseValues->getValue(i), i);
            }
         }
      }
   }
   return true;
}

//Normals Lerp
bool  lerp(  const GeoNormalsPtr BaseValues,const MFGeoNormalDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoNormalsPtr Value, bool isCyclic )
{
   if(DifferenceSets.size() == 0)
   {
      SWARNING << "The Geometry Postion Animation has only one frame defined.  Must have at least two."  << std::endl;
      return false;
   }
   if(BaseValues->getSize() != Value->getSize())
   {
      SWARNING << "Cannot annimate Geometry that doesn't have corresponding sizes."  << std::endl;
      return false;
   }
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   bool isFinished = getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic);
   if( isFinished )
   {
      //The animation has reached the end of its cycles
      //Set the result to the last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getNormals()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(LastKeyframeIndex == 0)
   {
      //Interpolate between BaseValues and the first Difference Set
      UInt32 FirstDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr FirstDiffSet = DifferenceSets.getValue(0);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( FirstDiffSet->getIndices()->getValue(FirstDiffSetIndex)== i )
         {
            Vec3f Result;
            osg::lerpNormal(BaseValues->getValue(i), FirstDiffSet->getNormals()->getValue(FirstDiffSetIndex), t, Result);
            
            Value->setValue(Result, i);
            ++FirstDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(NextKeyframeIndex == 0)
   {
      //Interpolate between the Last Difference Set and the BaseValues
      UInt32 LastDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Vec3f Result;
            osg::lerpNormal(LastDiffSet->getNormals()->getValue(LastDiffSetIndex), BaseValues->getValue(i), t, Result);
            
            Value->setValue(Result, i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else
   {
      //Interpolate between two Difference Sets
      UInt32 NextDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr NextDiffSet = DifferenceSets.getValue(NextKeyframeIndex-1);
      UInt32 LastDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(LastKeyframeIndex-1);
      
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //Interpolate between the Last Diff set and the next Diff set
               Vec3f Result;
               osg::lerpNormal( LastDiffSet->getNormals()->getValue(LastDiffSetIndex), NextDiffSet->getNormals()->getValue(NextDiffSetIndex), t, Result);
            
               Value->setValue(Result, i);
               ++NextDiffSetIndex;
            }
            else
            {
               //Interpolate between the Last Diff set and the BaseValues
               Vec3f Result;
               osg::lerpNormal( LastDiffSet->getNormals()->getValue(LastDiffSetIndex), BaseValues->getValue(i), t, Result);
            
               Value->setValue(Result, i);
               
            }
            ++LastDiffSetIndex;
         }
         else
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //Interpolate between the BaseValues and the next difference Set
               Vec3f Result;
               osg::lerpNormal( BaseValues->getValue(i), NextDiffSet->getNormals()->getValue(NextDiffSetIndex), t, Result);
            
               Value->setValue(Result, i);
               ++NextDiffSetIndex;
            }
            else
            {
               Value->setValue(BaseValues->getValue(i), i);
            }
         }
      }
   }
   return true;
}

//Normals Step
bool  step(  const GeoNormalsPtr BaseValues,const MFGeoNormalDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoNormalsPtr Value, bool isCyclic )
{
   if(DifferenceSets.size() == 0)
   {
      SWARNING << "The Geometry Postion Animation has only one frame defined.  Must have at least two."  << std::endl;
      return false;
   }
   if(BaseValues->getSize() != Value->getSize())
   {
      SWARNING << "Cannot annimate Geometry that doesn't have corresponding sizes."  << std::endl;
      return false;
   }
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      //The animation has reached the end of its cycles
      //Set the result to the last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getNormals()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(LastKeyframeIndex == 0) 
   {
      //Interpolate between BaseValues and the first Difference Set
      //For a Step interpolatin this should be all BaseValues
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         Value->setValue(BaseValues->getValue(i), i);
      }
   }
   else if(NextKeyframeIndex == 0)
   {
      //Interpolate between the Last Difference Set and the BaseValues
      //For a Step interpolatin this should be all the Last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getNormals()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else
   {
      //Interpolate between two Difference Sets
      UInt32 NextDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr NextDiffSet = DifferenceSets.getValue(NextKeyframeIndex-1);
      UInt32 LastDiffSetIndex = 0;
      GeoNormalDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(LastKeyframeIndex-1);
      
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //For Step interpolation this should be the Last Keyframe
               Value->setValue(LastDiffSet->getNormals()->getValue(LastDiffSetIndex), i);
               ++NextDiffSetIndex;
            }
            else
            {
               //For Step interpolation this should be the Last Keyframe
               Value->setValue(LastDiffSet->getNormals()->getValue(LastDiffSetIndex), i);
            }
            ++LastDiffSetIndex;
         }
         else
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //For Step interpolation this should be the Last Keyframe
               //Which for the the last Difference set was the BaseValue for this index
               Value->setValue(BaseValues->getValue(i), i);
               ++NextDiffSetIndex;
            }
            else
            {
               Value->setValue(BaseValues->getValue(i), i);
            }
         }
      }
   }
   return true;
}

//Colors Lerp
bool  lerp(  const GeoColorsPtr BaseValues,const MFGeoColorDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoColorsPtr Value, bool isCyclic )
{
   if(DifferenceSets.size() == 0)
   {
      SWARNING << "The Colors Postion Animation has only one frame defined.  Must have at least two."  << std::endl;
      return false;
   }
   if(BaseValues->getSize() != Value->getSize())
   {
      SWARNING << "Cannot annimate Geometry that doesn't have corresponding sizes."  << std::endl;
      return false;
   }
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   bool isFinished = getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic);
   if( isFinished )
   {
      //The animation has reached the end of its cycles
      //Set the result to the last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoColorDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getColors()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(LastKeyframeIndex == 0)
   {
      //Interpolate between BaseValues and the first Difference Set
      UInt32 FirstDiffSetIndex = 0;
      GeoColorDifferenceSetPtr FirstDiffSet = DifferenceSets.getValue(0);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( FirstDiffSet->getIndices()->getValue(FirstDiffSetIndex)== i )
         {
            Color3f Result;
            osg::lerp(BaseValues->getValue(i), FirstDiffSet->getColors()->getValue(FirstDiffSetIndex), t, Result);
            
            Value->setValue(Result, i);
            ++FirstDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(NextKeyframeIndex == 0)
   {
      //Interpolate between the Last Difference Set and the BaseValues
      UInt32 LastDiffSetIndex = 0;
      GeoColorDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Color3f Result;
            osg::lerp(LastDiffSet->getColors()->getValue(LastDiffSetIndex), BaseValues->getValue(i), t, Result);
            
            Value->setValue(Result, i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else
   {
      //Interpolate between two Difference Sets
      UInt32 NextDiffSetIndex = 0;
      GeoColorDifferenceSetPtr NextDiffSet = DifferenceSets.getValue(NextKeyframeIndex-1);
      UInt32 LastDiffSetIndex = 0;
      GeoColorDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(LastKeyframeIndex-1);
      
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //Interpolate between the Last Diff set and the next Diff set
               Color3f Result;
               osg::lerp( LastDiffSet->getColors()->getValue(LastDiffSetIndex), NextDiffSet->getColors()->getValue(NextDiffSetIndex), t, Result);
            
               Value->setValue(Result, i);
               ++NextDiffSetIndex;
            }
            else
            {
               //Interpolate between the Last Diff set and the BaseValues
               Color3f Result;
               osg::lerp( LastDiffSet->getColors()->getValue(LastDiffSetIndex), BaseValues->getValue(i), t, Result);
            
               Value->setValue(Result, i);
               
            }
            ++LastDiffSetIndex;
         }
         else
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //Interpolate between the BaseValues and the next difference Set
               Color3f Result;
               osg::lerp( BaseValues->getValue(i), NextDiffSet->getColors()->getValue(NextDiffSetIndex), t, Result);
            
               Value->setValue(Result, i);
               ++NextDiffSetIndex;
            }
            else
            {
               Value->setValue(BaseValues->getValue(i), i);
            }
         }
      }
   }
   return true;
}

//Colors Step
bool  step(  const GeoColorsPtr BaseValues,const MFGeoColorDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoColorsPtr Value, bool isCyclic )
{
   if(DifferenceSets.size() == 0)
   {
      SWARNING << "The Geometry Colors Animation has only one frame defined.  Must have at least two."  << std::endl;
      return false;
   }
   if(BaseValues->getSize() != Value->getSize())
   {
      SWARNING << "Cannot annimate Geometry that doesn't have corresponding sizes."  << std::endl;
      return false;
   }
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      //The animation has reached the end of its cycles
      //Set the result to the last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoColorDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getColors()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(LastKeyframeIndex == 0) 
   {
      //Interpolate between BaseValues and the first Difference Set
      //For a Step interpolatin this should be all BaseValues
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         Value->setValue(BaseValues->getValue(i), i);
      }
   }
   else if(NextKeyframeIndex == 0)
   {
      //Interpolate between the Last Difference Set and the BaseValues
      //For a Step interpolatin this should be all the Last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoColorDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getColors()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else
   {
      //Interpolate between two Difference Sets
      UInt32 NextDiffSetIndex = 0;
      GeoColorDifferenceSetPtr NextDiffSet = DifferenceSets.getValue(NextKeyframeIndex-1);
      UInt32 LastDiffSetIndex = 0;
      GeoColorDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(LastKeyframeIndex-1);
      
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //For Step interpolation this should be the Last Keyframe
               Value->setValue(LastDiffSet->getColors()->getValue(LastDiffSetIndex), i);
               ++NextDiffSetIndex;
            }
            else
            {
               //For Step interpolation this should be the Last Keyframe
               Value->setValue(LastDiffSet->getColors()->getValue(LastDiffSetIndex), i);
            }
            ++LastDiffSetIndex;
         }
         else
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //For Step interpolation this should be the Last Keyframe
               //Which for the the last Difference set was the BaseValue for this index
               Value->setValue(BaseValues->getValue(i), i);
               ++NextDiffSetIndex;
            }
            else
            {
               Value->setValue(BaseValues->getValue(i), i);
            }
         }
      }
   }
   return true;
}

//TexCoords Lerp
bool  lerp(  const GeoTexCoordsPtr BaseValues,const MFGeoTexCoordDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoTexCoordsPtr Value, bool isCyclic )
{
   if(DifferenceSets.size() == 0)
   {
      SWARNING << "The Geometry TexCoord Animation has only one frame defined.  Must have at least two."  << std::endl;
      return false;
   }
   if(BaseValues->getSize() != Value->getSize())
   {
      SWARNING << "Cannot annimate Geometry that doesn't have corresponding sizes."  << std::endl;
      return false;
   }
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   bool isFinished = getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic);
   if( isFinished )
   {
      //The animation has reached the end of its cycles
      //Set the result to the last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getTexCoords()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(LastKeyframeIndex == 0)
   {
      //Interpolate between BaseValues and the first Difference Set
      UInt32 FirstDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr FirstDiffSet = DifferenceSets.getValue(0);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( FirstDiffSet->getIndices()->getValue(FirstDiffSetIndex)== i )
         {
            Vec2f Result;
            osg::lerp(BaseValues->getValue(i), FirstDiffSet->getTexCoords()->getValue(FirstDiffSetIndex), t, Result);
            
            Value->setValue(Result, i);
            ++FirstDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(NextKeyframeIndex == 0)
   {
      //Interpolate between the Last Difference Set and the BaseValues
      UInt32 LastDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Vec2f Result;
            osg::lerp(LastDiffSet->getTexCoords()->getValue(LastDiffSetIndex), BaseValues->getValue(i), t, Result);
            
            Value->setValue(Result, i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else
   {
      //Interpolate between two Difference Sets
      UInt32 NextDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr NextDiffSet = DifferenceSets.getValue(NextKeyframeIndex-1);
      UInt32 LastDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(LastKeyframeIndex-1);
      
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //Interpolate between the Last Diff set and the next Diff set
               Vec2f Result;
               osg::lerp( LastDiffSet->getTexCoords()->getValue(LastDiffSetIndex), NextDiffSet->getTexCoords()->getValue(NextDiffSetIndex), t, Result);
            
               Value->setValue(Result, i);
               ++NextDiffSetIndex;
            }
            else
            {
               //Interpolate between the Last Diff set and the BaseValues
               Vec2f Result;
               osg::lerp( LastDiffSet->getTexCoords()->getValue(LastDiffSetIndex), BaseValues->getValue(i), t, Result);
            
               Value->setValue(Result, i);
               
            }
            ++LastDiffSetIndex;
         }
         else
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //Interpolate between the BaseValues and the next difference Set
               Vec2f Result;
               osg::lerp( BaseValues->getValue(i), NextDiffSet->getTexCoords()->getValue(NextDiffSetIndex), t, Result);
            
               Value->setValue(Result, i);
               ++NextDiffSetIndex;
            }
            else
            {
               Value->setValue(BaseValues->getValue(i), i);
            }
         }
      }
   }
   return true;
}

//TexCoords Step
bool  step(  const GeoTexCoordsPtr BaseValues,const MFGeoTexCoordDifferenceSetPtr DifferenceSets, const osg::MFReal32& Keys, const osg::Real32& Time, GeoTexCoordsPtr Value, bool isCyclic )
{
   if(DifferenceSets.size() == 0)
   {
      SWARNING << "The Geometry TexCoords Animation has only one frame defined.  Must have at least two."  << std::endl;
      return false;
   }
   if(BaseValues->getSize() != Value->getSize())
   {
      SWARNING << "Cannot annimate Geometry that doesn't have corresponding sizes."  << std::endl;
      return false;
   }
   osg::Real32 t;
   osg::UInt32 LastKeyframeIndex, NextKeyframeIndex;
   
   if( getInterpolationIndexes(Keys, Time, LastKeyframeIndex, NextKeyframeIndex, t, isCyclic) )
   {
      //The animation has reached the end of its cycles
      //Set the result to the last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getTexCoords()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else if(LastKeyframeIndex == 0) 
   {
      //Interpolate between BaseValues and the first Difference Set
      //For a Step interpolatin this should be all BaseValues
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         Value->setValue(BaseValues->getValue(i), i);
      }
   }
   else if(NextKeyframeIndex == 0)
   {
      //Interpolate between the Last Difference Set and the BaseValues
      //For a Step interpolatin this should be all the Last Difference Set
      UInt32 LastDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(DifferenceSets.getSize()-1);
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            Value->setValue(LastDiffSet->getTexCoords()->getValue(LastDiffSetIndex), i);
            ++LastDiffSetIndex;
         }
         else
         {
            Value->setValue(BaseValues->getValue(i), i);
         }
      }
   }
   else
   {
      //Interpolate between two Difference Sets
      UInt32 NextDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr NextDiffSet = DifferenceSets.getValue(NextKeyframeIndex-1);
      UInt32 LastDiffSetIndex = 0;
      GeoTexCoordDifferenceSetPtr LastDiffSet = DifferenceSets.getValue(LastKeyframeIndex-1);
      
      for(UInt32 i=0 ; i<Value->getSize() ; ++i)
      {
         if( LastDiffSet->getIndices()->getValue(LastDiffSetIndex)== i )
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //For Step interpolation this should be the Last Keyframe
               Value->setValue(LastDiffSet->getTexCoords()->getValue(LastDiffSetIndex), i);
               ++NextDiffSetIndex;
            }
            else
            {
               //For Step interpolation this should be the Last Keyframe
               Value->setValue(LastDiffSet->getTexCoords()->getValue(LastDiffSetIndex), i);
            }
            ++LastDiffSetIndex;
         }
         else
         {
            if( NextDiffSet->getIndices()->getValue(NextDiffSetIndex)== i )
            {
               //For Step interpolation this should be the Last Keyframe
               //Which for the the last Difference set was the BaseValue for this index
               Value->setValue(BaseValues->getValue(i), i);
               ++NextDiffSetIndex;
            }
            else
            {
               Value->setValue(BaseValues->getValue(i), i);
            }
         }
      }
   }
   return true;
}
OSG_END_NAMESPACE
