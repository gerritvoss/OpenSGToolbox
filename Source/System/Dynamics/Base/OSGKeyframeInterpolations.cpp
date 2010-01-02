#include "OSGKeyframeInterpolations.h"

OSG_BEGIN_NAMESPACE

bool getInterpolationIndexes(const MFReal32& Keys, const Real32& time, UInt32& LastKeyframeIndex, UInt32& NextKeyframeIndex, Real32& t, bool isCyclic)
{
   Real32 Adjustedtime;
   if(isCyclic)
   {
      Adjustedtime = time - ( Keys[Keys.size()-1] * osgFloor(time/Keys[Keys.size()-1]) );
   }
   else
   {
      Adjustedtime = time;
   }
   
   //Get the indexes of the current keyframe in the animation
   UInt32 KeysIndex(0);
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

bool getInterpolationIndex(const MFReal32& Keys, const Real32& time, UInt32& Index, Real32& t, bool isCyclic)
{
   Real32 Adjustedtime;
   if(isCyclic)
   {
      Adjustedtime = time - ( Keys[Keys.size()-1] * osgFloor(time/Keys[Keys.size()-1]) );
   }
   else
   {
      Adjustedtime = time;
   }
   
   //Get the indexes of the current keyframe in the animation
   UInt32 KeysIndex(0);
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
   
   if(KeysIndex == 0)
   {
      Index = KeysIndex;
      t = 0;
   }
   else
   {
      Index = KeysIndex-1;
      //Normalize t
      t = (Adjustedtime-Keys[Index])/(Keys[Index+1]-Keys[Index]);
   }
   
   return false;
}
//Matrix Replace
template<>
bool replacement<SFMatrix>(RawInterpFuncion& InterpFunc,
                              const Real32& time,
                              const Real32& prevtime,
                              const UInt32& ReplacePolicy,
                              bool isCyclic,
                              Field& Result,
                              UInt32 Index, 
                              Real32 Blend)
{
    SFMatrix Value(static_cast<SFMatrix&>(Result).getValue());
    bool ReturnValue = InterpFunc(time, Value,isCyclic);

    if(Result.getCardinality() == FieldType::SingleField)
    {
        switch(ReplacePolicy)
        {
        case Animator::ADDITIVE_SINCE_LAST:
            {
                SFMatrix PrevValue;
                InterpFunc(prevtime, PrevValue,isCyclic);
                Matrix DeltaSinceLast(PrevValue.getValue());
                DeltaSinceLast.invert();
                DeltaSinceLast.mult(Value.getValue());
                DeltaSinceLast.scale(Blend);
                static_cast<SFMatrix&>(Result).getValue().mult( DeltaSinceLast );
                break;
            }
        case Animator::ADDITIVE_ABSOLUTE:
            Value.getValue().scale(Blend);
            static_cast<SFMatrix&>(Result).getValue().mult( Value.getValue() );
            break;
        case Animator::OVERWRITE:
            Value.getValue().scale(Blend);
            static_cast<SFMatrix&>(Result).setValue(Value.getValue());
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
                SFMatrix PrevValue;
                InterpFunc(prevtime, PrevValue,isCyclic);
                Matrix DeltaSinceLast(PrevValue.getValue());
                DeltaSinceLast.invert();
                DeltaSinceLast.mult(Value.getValue());
                DeltaSinceLast.scale(Blend);
                static_cast<MFMatrix&>(Result)[Index].mult( DeltaSinceLast );
                break;
            }
        case Animator::ADDITIVE_ABSOLUTE:
            Value.getValue().scale(Blend);
            static_cast<MFMatrix&>(Result)[Index].mult( Value.getValue() );
            break;
        case Animator::OVERWRITE:
            Value.getValue().scale(Blend);
            static_cast<MFMatrix&>(Result)[Index] = Value.getValue();
            break;
        default:
            SWARNING << "No policy defined for Animation value replacement policy: " << ReplacePolicy << "." << std::endl;
            break;
       }
    }
   return ReturnValue;
}

std::string lerp( const std::string& From, const std::string& To, const Real32& t)
{
    return lerpFromSide(From,To,t);
}

std::string lerpFromSide( const std::string& From, const std::string& To, const Real32& t)
{
    UInt32 MaxSize(osgMax<UInt32>(From.size(),To.size()));
    Real32 TimePerChar(1.0f/static_cast<Real32>(MaxSize));
    Real32 FromChar(' '),ToChar(' ');
    
    std::string Result("");

    if(From.size() < To.size())
    {
        //Left To Right
        Int32 Index(osgFloor<Int32>(static_cast<Real32>(MaxSize)*t));
        Real32 CharT((t-Index*TimePerChar)/TimePerChar);

        Result = To.substr(0,osgMin<Int32>(To.size(),Index));
        Result.resize(Index, ' ');
        if(Index<To.size())
        {
            ToChar = To[Index];
        }
        if(Index<From.size())
        {
            FromChar = From[Index];
        }
        Result += static_cast<Char8>(FromChar +( (ToChar - FromChar) * CharT ));           //Interp Index
        Result += From.substr(osgMin<Int32>(Index+1,From.size()),std::string::npos); 
    }
    else
    {
        //Right to Left
        Int32 Index(osgMax<Int32>(0,MaxSize - osgFloor(static_cast<Real32>(MaxSize)*t) - 1));
        Real32 CharT((t-osgFloor<Int32>(static_cast<Real32>(MaxSize)*t)*TimePerChar)/TimePerChar);

        Result = From.substr(0,osgMin<Int32>(From.size(),Index));
        Result.resize(Index, ' ');
        if(Index<To.size())
        {
            ToChar = To[Index];
        }
        if(Index<From.size())
        {
            FromChar = From[Index];
        }
        Result += static_cast<Char8>(FromChar +( (ToChar - FromChar) * CharT ));           //Interp Index
        Result += To.substr(osgMin<Int32>(Index+1,To.size()),std::string::npos); 
    }

    return Result;
}

//String Linear Interpolation
//This String interpolation will create a string that is length
//Max(From.size(),To.size()), it then interpolates all of the characters at once
//using their ASCII values to interpolate on
std::string lerpAll( const std::string& From, const std::string& To, const Real32& t)
{
    std::string Result(From);
    Result.resize(osgMax(From.size(),To.size()), ' ');

    //Loop through each character
    for(UInt32 i(0) ; i<Result.size() ; ++i)
    {
        if(i<To.size())
        {
            Result[i] +=( (To[i] - Result[i]) * t );
        }
        else
        {
            Result[i] +=( (' ' - Result[i]) * t );
        }
    }
    return Result;
}

//String Replace
template<>
bool replacement<SFString>(RawInterpFuncion& InterpFunc,
                              const Real32& time,
                              const Real32& prevtime,
                              const UInt32& ReplacePolicy,
                              bool isCyclic,
                              Field& Result,
                              UInt32 Index, 
                              Real32 Blend)
{
    SFString Value(static_cast<SFString&>(Result).getValue());
    bool ReturnValue = InterpFunc(time, Value,isCyclic);

    if(Result.getCardinality() == FieldType::SingleField)
    {
        switch(ReplacePolicy)
        {
        case Animator::OVERWRITE:
            static_cast<SFString&>(Result).setValue(Value.getValue());
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
        case Animator::OVERWRITE:
            static_cast<MFString&>(Result)[Index] = Value.getValue();
            break;
        default:
            SWARNING << "No policy defined for Animation value replacement policy: " << ReplacePolicy << "." << std::endl;
            break;
        }
    }
   return ReturnValue;
}

OSG_END_NAMESPACE

