#include "OSGKeyframeInterpolations.h"

bool osg::getInterpolationIndexes(const osg::MFReal32& Keys, const osg::Real32& time, osg::UInt32& LastKeyframeIndex, osg::UInt32& NextKeyframeIndex, osg::Real32& t, bool isCyclic)
{
   osg::Real32 Adjustedtime;
   if(isCyclic)
   {
      Adjustedtime = time - ( Keys[Keys.size()-1] * osg::osgfloor(time/Keys[Keys.size()-1]) );
   }
   else
   {
      Adjustedtime = time;
   }
   
   //Get the indexes of the current keyframe in the animation
   osg::UInt32 KeysIndex(0);
   while( KeysIndex < Keys.size() )
   {
      if(Adjustedtime < Keys[KeysIndex])
      {
         break;
      }
      ++KeysIndex;
   }
   
   if( !isCyclic && KeysIndex == Keys.size() &&  Adjustedtime >= Keys[Keys.size()-1])
   {
      //time > t
      //At the end of the animation
      return true;
   }
   
   NextKeyframeIndex = KeysIndex;
   if(KeysIndex == 0)
   {
        LastKeyframeIndex = Keys.size() - 1;
   }
   else
   {
        LastKeyframeIndex = NextKeyframeIndex - 1;
   }
   
   //Normalize t
   t = (Adjustedtime-Keys[LastKeyframeIndex])/(Keys[NextKeyframeIndex]-Keys[LastKeyframeIndex]);
   return false;
}

bool osg::getInterpolationIndex(const osg::MFReal32& Keys, const osg::Real32& time, osg::UInt32& Index, osg::Real32& t, bool isCyclic)
{
   osg::Real32 Adjustedtime;
   if(isCyclic)
   {
      Adjustedtime = time - ( Keys[Keys.size()-1] * osg::osgfloor(time/Keys[Keys.size()-1]) );
   }
   else
   {
      Adjustedtime = time;
   }
   
   //Get the indexes of the current keyframe in the animation
   osg::UInt32 KeysIndex(0);
   while( KeysIndex < Keys.size() )
   {
      if(Adjustedtime < Keys[KeysIndex])
      {
         break;
      }
      ++KeysIndex;
   }
   
   if( !isCyclic && KeysIndex == Keys.size() &&  Adjustedtime >= Keys[Keys.size()-1])
   {
      //time > t
      //At the end of the animation
      Index = Keys.size()-1;
      return true;
   }
   
   Index = KeysIndex-1;
   
   //Normalize t
   t = (Adjustedtime-Keys[Index])/(Keys[Index+1]-Keys[Index]);
   return false;
}
//Matrix Replace
template<>
bool osg::replacement<osg::SFMatrix>(RawInterpFuncion& InterpFunc,
                              const osg::Real32& time,
                              const osg::Real32& prevtime,
                              const osg::ValueReplacementPolicy& ReplacePolicy,
                              bool isCyclic,
                              osg::Field& Result)
{
    SFMatrix Value(static_cast<osg::SFMatrix&>(Result).getValue());
    bool ReturnValue = InterpFunc(time, Value,isCyclic);

    switch(ReplacePolicy)
    {
    case ADDITIVE_SINCE_LAST:
        {
            osg::SFMatrix PrevValue;
            InterpFunc(prevtime, PrevValue,isCyclic);
            osg::Matrix DeltaSinceLast(PrevValue.getValue());
            DeltaSinceLast.invert();
            DeltaSinceLast.mult(Value.getValue());
            static_cast<osg::SFMatrix&>(Result).getValue().mult( DeltaSinceLast );
            break;
        }
    case ADDITIVE_ABSOLUTE:
        static_cast<osg::SFMatrix&>(Result).getValue().mult( Value.getValue() );
        break;
    case OVERWRITE:
        static_cast<osg::SFMatrix&>(Result).setValue(Value.getValue());
        break;
    default:
        SWARNING << "No policy defined for Animation value replacement policy: " << ReplacePolicy << "." << std::endl;
        break;
   }
   return ReturnValue;
}

//String Replace
template<>
bool osg::replacement<osg::SFString>(RawInterpFuncion& InterpFunc,
                              const osg::Real32& time,
                              const osg::Real32& prevtime,
                              const osg::ValueReplacementPolicy& ReplacePolicy,
                              bool isCyclic,
                              osg::Field& Result)
{
    SFString Value(static_cast<osg::SFString&>(Result).getValue());
    bool ReturnValue = InterpFunc(time, Value,isCyclic);

    switch(ReplacePolicy)
    {
    case OVERWRITE:
        static_cast<osg::SFString&>(Result).setValue(Value.getValue());
        break;
    default:
        SWARNING << "No policy defined for Animation value replacement policy: " << ReplacePolicy << "." << std::endl;
        break;
   }
   return ReturnValue;
}
