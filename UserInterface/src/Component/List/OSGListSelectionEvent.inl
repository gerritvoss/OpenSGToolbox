#include "OSGUserInterfaceConfig.h"

OSG_BEGIN_NAMESPACE

inline
UInt32 	ListSelectionEvent::getFirstIndex() const
{
   return _FirstIndex;
}

inline
UInt32 	ListSelectionEvent::getLastIndex() const
{
   return _LastIndex;
}

inline
bool 	ListSelectionEvent::getValueIsAdjusting() const
{
   return _ValueIsAdjusting;
}

inline
ListSelectionEvent::ListSelectionEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 FirstIndex, UInt32 LastIndex, bool ValueIsAdjusting)
 : Event(Source, TimeStamp),
   _FirstIndex(FirstIndex),
   _LastIndex(LastIndex),
   _ValueIsAdjusting(ValueIsAdjusting)
{
}
    
OSG_END_NAMESPACE
