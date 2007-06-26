//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void WindowEventProducer::addMouseListener(MouseListenerPtr Listener)
{
   _MouseListeners.insert(Listener);
}

inline
void WindowEventProducer::addMouseMotionListener(MouseMotionListenerPtr Listener)
{
   _MouseMotionListeners.insert(Listener);
}

inline
void WindowEventProducer::addMouseWheelListener(MouseWheelListenerPtr Listener)
{
   _MouseWheelListeners.insert(Listener);
}

inline
void WindowEventProducer::addKeyListener(KeyListenerPtr Listener)
{
   _KeyListeners.insert(Listener);
}

inline
void WindowEventProducer::removeMouseListener(MouseListenerPtr Listener)
{
   MouseListenerSetItor EraseIter(_MouseListeners.find(Listener));
   if(EraseIter != _MouseListeners.end())
   {
      _MouseListeners.erase(EraseIter);
   }
}

inline
void WindowEventProducer::removeMouseMotionListener(MouseMotionListenerPtr Listener)
{
   MouseMotionListenerSetItor EraseIter(_MouseMotionListeners.find(Listener));
   if(EraseIter != _MouseMotionListeners.end())
   {
      _MouseMotionListeners.erase(EraseIter);
   }
}

inline
void WindowEventProducer::removeMouseWheelListener(MouseWheelListenerPtr Listener)
{
   MouseWheelListenerSetItor EraseIter(_MouseWheelListeners.find(Listener));
   if(EraseIter != _MouseWheelListeners.end())
   {
      _MouseWheelListeners.erase(EraseIter);
   }
}

inline
void WindowEventProducer::removeKeyListener(KeyListenerPtr Listener)
{
   KeyListenerSetItor EraseIter(_KeyListeners.find(Listener));
   if(EraseIter != _KeyListeners.end())
   {
      _KeyListeners.erase(EraseIter);
   }
}

inline
WindowEventProducer::Click::Click(Time TimeStamp, Pnt2s Location) :
_TimeStamp(TimeStamp),
_Location(Location)
{
}

OSG_END_NAMESPACE
