#ifndef _OPENSG_VIDEO_WRAPPER_H_
#define _OPENSG_VIDEO_WRAPPER_H_

#include <OpenSG/OSGConfig.h>
#include "OSGVideoDef.h"

#include <OpenSG/Toolbox/OSGPathType.h>
#include <OpenSG/OSGImage.h>
#include <boost/shared_ptr.hpp>

OSG_BEGIN_NAMESPACE

class OSG_VIDEOLIB_DLLMAPPING VideoWrapper
{
public:
    virtual bool open(Path ThePath) = 0;

    virtual bool seek(Int64 SeekPos) = 0;
    virtual bool play(void) = 0;
    virtual bool pause(void) = 0;
    virtual bool unpause(void) = 0;
    virtual bool pauseToggle(void) = 0;
    virtual bool stop(void) = 0;
    virtual bool close(void) = 0;
	
    virtual bool isPlaying(void) const = 0;
    virtual bool isStopped(void) const = 0;
    virtual bool isPaused(void) const = 0;
    virtual bool isInitialized(void) const = 0;

	virtual Int64 getPosition(void) const = 0;
	virtual Int64 getDuration(void) const = 0;

    virtual ImagePtr getCurrentFrame(void) = 0;
    virtual bool updateImage(void) = 0;

	ImagePtr getImage(void) const
	{
		return _VideoImage;
	}

	//Events
	//Paused, Unpaused, played, stopped, reached end, seeked, opened, closed

private:
protected:
	ImagePtr _VideoImage;
};

typedef boost::shared_ptr<VideoWrapper> VideoWrapperPtr;

OSG_END_NAMESPACE

#endif
