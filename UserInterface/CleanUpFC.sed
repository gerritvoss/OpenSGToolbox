s-#include <OpenSG/OSGConfig.h>-#include "OSGUserInterfaceConfig.h"-

s-OSG_USER_INTERFACE_CLASS_API --
s-^\(class\) \(.*[^;]\)$-\1 OSG_USER_INTERFACE_CLASS_API \2-

s-#include <\(.*OSG.*\)>-#include "\1"-
s-#include "\(OpenSG/.*\)"-#include <\1>-
