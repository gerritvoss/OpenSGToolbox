#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &VideoEvent::getClassType(void)
{
    return _Type;
}

inline
VideoWrapperPtr VideoEvent::getSourceVideo(void) const
{
	return _SourceVideo;
}


OSG_END_NAMESPACE
