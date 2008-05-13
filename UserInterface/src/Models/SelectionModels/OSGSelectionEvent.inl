#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
const EventType &SelectionEvent::getClassType(void)
{
    return _Type;
}

inline
const std::vector<Int32>& SelectionEvent::getSelectedIndicies(void) const
{
   return _Selected;
}

inline
const std::vector<Int32>& SelectionEvent::getPreviouslySelectedIndicies(void) const
{
   return _PreviouslySelected;
}

inline
bool 	SelectionEvent::getValueIsAdjusting() const
{
   return _ValueIsAdjusting;
}

inline
SelectionEvent::SelectionEvent(FieldContainerPtr Source, Time TimeStamp, std::vector<Int32>& Selected, std::vector<Int32>& PreviouslySelected, bool ValueIsAdjusting)
 : Event(Source, TimeStamp),
   _Selected(Selected),
   _PreviouslySelected(PreviouslySelected),
   _ValueIsAdjusting(ValueIsAdjusting)
{
}
    
OSG_END_NAMESPACE
