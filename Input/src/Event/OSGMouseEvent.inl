#include <OpenSG/OSGConfig.h>
#include <assert.h>

OSG_BEGIN_NAMESPACE

inline
MouseEvent::MouseButton MouseEvent::getButton(void) const
{
   return _Button; 
}

inline
UInt16 MouseEvent::getClickCount(void) const
{
   return _ClickCount; 
}


inline
Pnt2s MouseEvent::getLocationOnScreen(void) const
{
   assert(false && "MouseEvent::getLocationOnScreen(void) Not Implemented");
   return _Location; 
}

inline
Pnt2s MouseEvent::getLocation(void) const
{
   return _Location; 
}


inline
Int16 MouseEvent::getX(void) const
{
   return _Location.x(); 
}

inline
Int16 MouseEvent::getXOnScreen(void) const
{
   assert(false && "MouseEvent::getXOnScreen(void) Not Implemented");
   return _Location.x();
}

inline
Int16 MouseEvent::getY(void) const
{
   return _Location.y();
}

inline
Int16 MouseEvent::getYOnScreen(void) const
{
   assert(false && "MouseEvent::getYOnScreen(void) Not Implemented");
   return _Location.y();
}

inline
MouseEvent::MouseEvent(FieldContainerPtr Source, Time TimeStamp, MouseButton Button, UInt16 ClickCount, Pnt2s Location) : Event(Source, TimeStamp), _Button(Button), _ClickCount(ClickCount), _Location(Location)
{}

    
OSG_END_NAMESPACE
