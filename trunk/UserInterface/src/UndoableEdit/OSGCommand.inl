#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
Command::Command(void) : Inherited()
{
}

inline
Command::Command(const Command& source) : Inherited(source)
{
}

inline 
void Command::operator =(const Command& source)
{
	Inherited::operator=(source);
}

OSG_END_NAMESPACE
