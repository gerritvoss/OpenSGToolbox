s-#include <OpenSG/OSGConfig.h>-#include "OSGInputConfig.h"-

s-OSG_INPUT_CLASS_API --
s-^\(class\) \(.*[^;]\)$-\1 OSG_INPUT_CLASS_API \2-

s-#include <\(.*OSG.*\)>-#include "\1"-
s-#include "\(OpenSG/.*\)"-#include <\1>-
