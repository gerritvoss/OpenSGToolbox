#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
const EventType &ComboBoxSelectionEvent::getClassType(void)
{
    return _Type;
}

inline
Int32 ComboBoxSelectionEvent::getCurrentIndex() const
{
   return _CurrentIndex;
}

inline
Int32 ComboBoxSelectionEvent::getPreviousIndex() const
{
   return _PreviousIndex;
}

inline
ComboBoxSelectionEvent::ComboBoxSelectionEvent(FieldContainerPtr Source, Time TimeStamp, const Int32& CurrentIndex, const Int32& PreviousIndex)
 : Event(Source, TimeStamp),
   _CurrentIndex(CurrentIndex),
   _PreviousIndex(PreviousIndex)
{
}
    
OSG_END_NAMESPACE
