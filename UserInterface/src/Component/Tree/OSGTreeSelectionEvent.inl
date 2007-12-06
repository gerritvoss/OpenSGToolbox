#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE
    
inline
const EventType &TreeSelectionEvent::getClassType(void)
{
    return _Type;
}

OSG_END_NAMESPACE
