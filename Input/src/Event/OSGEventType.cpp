#include <OpenSG/OSGConfig.h>

#include <iostream>

#include "OSGEventType.h"
#include "OSGEventFactory.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

EventType::EventType(const Char8  *szName,
                   const Char8  *szParentName,
                   const UInt32  uiNameSpace ) :
    Inherited(szName, szParentName, uiNameSpace),
    _uiEventTypeId(0),
    _uiEventTypeRootId(0)
{
    _uiEventTypeId = EventFactory::the()->registerType(this);
}

EventType::EventType(const EventType &source) :
    Inherited(source),
    _uiEventTypeId(source._uiEventTypeId),
    _uiEventTypeRootId(source._uiEventTypeRootId)
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

EventType::~EventType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

bool EventType::operator ==(const EventType &other) const
{
    return *(static_cast<const Inherited *>(this)) == other;
}

bool EventType::operator !=(const EventType &other) const
{
    return ! (*this == other);
}
