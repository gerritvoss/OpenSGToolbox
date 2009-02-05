#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE
    
inline
const EventType &TreeSelectionEvent::getClassType(void)
{
    return _Type;
}

inline
const EventType &TreeSelectionEvent::getType(void) const
{
    return _Type;
}

inline
Int32 TreeSelectionEvent::getNewLeadSelectionPath(void) const
{
	return _NewLeadSelectionPath;
}

inline
Int32 TreeSelectionEvent::getOldLeadSelectionPath(void) const
{
	return _OldLeadSelectionPath;
}

inline
const std::vector<NumberRange>& TreeSelectionEvent::getElementsChanged(void) const
{
	return _ElementsChanged;
}

OSG_END_NAMESPACE
