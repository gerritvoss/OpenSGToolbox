#include <OpenSG/OSGConfig.h>

#include <iostream>

#include "OSGEventFactory.h"

OSG_USING_NAMESPACE

EventFactory *EventFactory::_the = NULL;

EventFactory *EventFactory::the(void)
{
    if(_the == NULL)
        _the = new EventFactory;

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

EventFactory::EventFactory(void) : Inherited()
{
}
    
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

EventFactory::~EventFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

