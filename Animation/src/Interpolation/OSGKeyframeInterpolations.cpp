#include "OSGKeyframeInterpolations.h"

bool osg::getInterpolationIndexes(const osg::MFReal32& Keys, const osg::Real32& Time, osg::UInt32& LastKeyframeIndex, osg::UInt32& NextKeyframeIndex, osg::Real32& t, bool isCyclic)
{
   osg::Real32 AdjustedTime;
   if(isCyclic)
   {
      AdjustedTime = Time - ( Keys[Keys.size()-1] * osg::osgfloor(Time/Keys[Keys.size()-1]) );
   }
   else
   {
      AdjustedTime = Time;
   }
   
   //Get the indexes of the current keyframe in the animation
   osg::UInt32 KeysIndex(0);
   while( KeysIndex < Keys.size() )
   {
      if(AdjustedTime < Keys[KeysIndex])
      {
         break;
      }
      ++KeysIndex;
   }
   
   if( !isCyclic && KeysIndex == Keys.size() &&  AdjustedTime >= Keys[Keys.size()-1])
   {
      //Time > t
      //At the end of the animation
      return true;
   }
   
   NextKeyframeIndex = KeysIndex;
   LastKeyframeIndex = NextKeyframeIndex - 1;
   
   //Normalize t
   t = (AdjustedTime-Keys[LastKeyframeIndex])/(Keys[NextKeyframeIndex]-Keys[LastKeyframeIndex]);
   return false;
}

bool osg::getInterpolationIndex(const osg::MFReal32& Keys, const osg::Real32& Time, osg::UInt32& Index, osg::Real32& t, bool isCyclic)
{
   osg::Real32 AdjustedTime;
   if(isCyclic)
   {
      AdjustedTime = Time - ( Keys[Keys.size()-1] * osg::osgfloor(Time/Keys[Keys.size()-1]) );
   }
   else
   {
      AdjustedTime = Time;
   }
   
   //Get the indexes of the current keyframe in the animation
   osg::UInt32 KeysIndex(0);
   while( KeysIndex < Keys.size() )
   {
      if(AdjustedTime < Keys[KeysIndex])
      {
         break;
      }
      ++KeysIndex;
   }
   
   if( !isCyclic && KeysIndex == Keys.size() &&  AdjustedTime >= Keys[Keys.size()-1])
   {
      //Time > t
      //At the end of the animation
      Index = Keys.size()-1;
      return true;
   }
   
   Index = KeysIndex-1;
   
   //Normalize t
   t = (AdjustedTime-Keys[Index])/(Keys[Index+1]-Keys[Index]);
   return false;
}
