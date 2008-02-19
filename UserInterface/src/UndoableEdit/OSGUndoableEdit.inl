#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
UndoableEdit::UndoableEdit(void) : Inherited()
{
}

inline
UndoableEdit::UndoableEdit(const UndoableEdit& source) : Inherited(source)
{
}
    

inline
void UndoableEdit::operator=(const UndoableEdit& source)
{
	Inherited::operator=(source);
}
OSG_END_NAMESPACE
