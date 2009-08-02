//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

    
inline
bool WindowEventProducer::isMouseListenerAttached(MouseListenerPtr Listener) const
{
    return _MouseListeners.find(Listener) != _MouseListeners.end();
}

inline
bool WindowEventProducer::isMouseMotionListenerAttached(MouseMotionListenerPtr Listener) const
{
    return _MouseMotionListeners.find(Listener) != _MouseMotionListeners.end();
}

inline
bool WindowEventProducer::isMouseWheelListenerAttached(MouseWheelListenerPtr Listener) const
{
    return _MouseWheelListeners.find(Listener) != _MouseWheelListeners.end();
}

inline
bool WindowEventProducer::isKeyListenerAttached(KeyListenerPtr Listener) const
{
    return _KeyListeners.find(Listener) != _KeyListeners.end();
}

inline
bool WindowEventProducer::isWindowListenerAttached(WindowListenerPtr Listener) const
{
    return _WindowListeners.find(Listener) != _WindowListeners.end();
}

inline
bool WindowEventProducer::isUpdateListenerAttached(UpdateListenerPtr Listener) const
{
    return _UpdateListeners.find(Listener) != _UpdateListeners.end();
}

inline
WindowEventProducer::FileDialogFilter::FileDialogFilter(const std::string& Name, const std::string& Filter) : 
_Name(Name),
_Filter(Filter)
{
}

inline
const std::string& WindowEventProducer::FileDialogFilter::getName(void) const
{
    return _Name;
}

inline
const std::string& WindowEventProducer::FileDialogFilter::getFilter(void) const
{
    return _Filter;
}

inline
RenderAction * WindowEventProducer::getRenderAction(void)
{
	return _RenderAction;
}

inline
void WindowEventProducer::setRenderAction(RenderAction *action)
{
	_RenderAction = action;
}

inline
void WindowEventProducer::internalDraw(void)
{
	if(_DisplayCallbackFunc)
	{
		_DisplayCallbackFunc();
	}
	else
	{
		getWindow()->render(_RenderAction);
	}
}

inline
void WindowEventProducer::internalReshape(Vec2f size)
{
	if(_ReshapeCallbackFunc)
	{
		_ReshapeCallbackFunc(size);
	}
	else
	{
		getWindow()->resize(size.x(), size.y());
	}
}

inline
void WindowEventProducer::draw(void)
{
}

inline
UInt32 WindowEventProducer::getCursorType(void) const
{
	return _CursorType;
}

inline
WindowEventProducer::Click::Click(Time TimeStamp, Pnt2f Location) :
_TimeStamp(TimeStamp),
_Location(Location)
{
}

OSG_END_NAMESPACE
