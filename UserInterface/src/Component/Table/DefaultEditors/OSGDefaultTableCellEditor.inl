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
    return _EditingTextField;
}

inline
void DefaultTableCellEditor::setClickCountToStart(const UInt32& count)
{
    _ClickCountToStart = count;
}

inline 
DefaultTableCellEditor::DefaultTableCellEditor(const UInt32& ClickCountToStart) :
            _ClickCountToStart(ClickCountToStart),
            _EditingTextField(NullFC),
            _Value("")
{
}

OSG_END_NAMESPACE
