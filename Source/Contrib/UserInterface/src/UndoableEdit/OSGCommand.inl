#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
Command::Command(void)
{
}

inline
Command::Command(const Command& source)
{
}

inline 
void Command::operator =(const Command& source)
{
}
    
inline
const CommandType &Command::getClassType(void)
{
    return _Type;
}

OSG_END_NAMESPACE
