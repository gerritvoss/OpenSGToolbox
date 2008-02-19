#include <OpenSG/OSGConfig.h>

#include <iostream>

#include "OSGCommandFactory.h"

OSG_USING_NAMESPACE

CommandFactory *CommandFactory::_the = NULL;

CommandFactory *CommandFactory::the(void)
{
    if(_the == NULL)
        _the = new CommandFactory;

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

CommandFactory::CommandFactory(void) : Inherited()
{
}
    
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

CommandFactory::~CommandFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

