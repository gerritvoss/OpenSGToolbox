#include "OSGWindowEventProducerFactory.h"


OSG_BEGIN_NAMESPACE

WindowEventProducerFactory *WindowEventProducerFactory::_the = NULL;

WindowEventProducerFactory* WindowEventProducerFactory::the(void)
{
   if(_the == NULL)
   {
      _the = new WindowEventProducerFactory();
   }
 
   return _the;
}

const FieldContainerType* WindowEventProducerFactory::registerProducer(const FieldContainerType* WindowType, const FieldContainerType* WindowEventProducerType)
{
	if(_WindowToWindowEventProducerMap.find(WindowType->getId()) == _WindowToWindowEventProducerMap.end())
	{
		_WindowToWindowEventProducerMap[WindowType->getId()] = WindowEventProducerType->getId();
	}
	return FieldContainerFactory::the()->findType( _WindowToWindowEventProducerMap[WindowType->getId()] );
}

const FieldContainerType* WindowEventProducerFactory::unregisterProducer(const FieldContainerType* WindowType)
{
	if(_WindowToWindowEventProducerMap.find(WindowType->getId()) != _WindowToWindowEventProducerMap.end())
	{
		FieldContainerType* TheType( FieldContainerFactory::the()->findType( _WindowToWindowEventProducerMap[WindowType->getId()] ) );

		_WindowToWindowEventProducerMap.erase( _WindowToWindowEventProducerMap.find(WindowType->getId()) );

		return TheType;
	}
	else
	{
		return NULL;
	}
}

WindowEventProducerPtr WindowEventProducerFactory::createWindowEventProducer(WindowPtr TheWindow)
{
	if(_WindowToWindowEventProducerMap.find(TheWindow->getType().getId()) != _WindowToWindowEventProducerMap.end())
	{
      WindowEventProducerPtr TheProducer = WindowEventProducerPtr::dcast( FieldContainerFactory::the()->findType( _WindowToWindowEventProducerMap[TheWindow->getType().getId()] )->createFieldContainer() );
      beginEditCP(TheProducer, WindowEventProducer::WindowFieldMask);
         TheProducer->setWindow(TheWindow);
      endEditCP(TheProducer, WindowEventProducer::WindowFieldMask);
		return TheProducer;
	}
	else
	{
		return NullFC;
	}
}

OSG_END_NAMESPACE
