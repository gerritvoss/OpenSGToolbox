#include "OSGInputConfig.h"

OSG_BEGIN_NAMESPACE

inline
MouseButton MouseEvent::getButton(void)
{
    return _Button; 
}

inline
UInt16 MouseEvent::getClickCount(void)
{
    return _ClickCount; 
}


inline
Pnt2us MouseEvent::getLocationOnScreen(void)
{
    return _Location; 
}

inline
Pnt2us MouseEvent::getLocation(void)
{
    return _Location; 
}


inline
UInt16 MouseEvent::getX(void)
{
    return _Location.x(); 
}

inline
UInt16 MouseEvent::getXOnScreen(void)
{
    return _Location.x();
}

inline
UInt16 MouseEvent::getY(void)
{
    return _Location.y();
}

inline
UInt16 MouseEvent::getYOnScreen(void)
{
    return _Location.y();
}

inline
MouseEvent::MouseEvent(FieldContainerPtr Source, Time TimeStamp, MouseButton Button, UInt16 ClickCount, Pnt2s Location) : Event(Source, TimeStamp), _Button(Button), _ClickCount(ClickCount), _Location(Location)
{}

    
OSG_END_NAMESPACE
