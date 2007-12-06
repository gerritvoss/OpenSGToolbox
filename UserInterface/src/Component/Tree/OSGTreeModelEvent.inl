#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE
    
inline
const EventType &TreeModelEvent::getClassType(void)
{
    return _Type;
}

OSG_END_NAMESPACE
