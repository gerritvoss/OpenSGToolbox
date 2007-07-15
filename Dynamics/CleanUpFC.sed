s-#include <OpenSG/OSGConfig.h>-#include "OSGDynamicsConfig.h"-

s-OSG_DYNAMICS_CLASS_API --
s-^\(class\) \(.*[^;]\)$-\1 OSG_DYNAMICS_CLASS_API \2-

s-#include <\(.*OSG.*\)>-#include "\1"-
s-#include "\(OpenSG/.*\)"-#include <\1>-
