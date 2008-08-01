#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void DragGestureRecognizer::addDragGestureListener(DragGestureListenerPtr Listener)
{
    _DragGestureListeners.insert(dgl);
}

OSG_END_NAMESPACE
