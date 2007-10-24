#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
UInt32 DefaultTableCellEditor::getClickCountToStart(void) const
{
    return _ClickCountToStart;
}

inline
ComponentPtr DefaultTableCellEditor::getComponent(void) const
{
    return _EditingComponent;
}

inline
void DefaultTableCellEditor::setClickCountToStart(const UInt32& count)
{
    _ClickCountToStart = count;
}

OSG_END_NAMESPACE
