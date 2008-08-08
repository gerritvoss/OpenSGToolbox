#include "OSGDirectShowManager.h"
#include "OSGDirectShowVideoWrapper.h"

OSG_BEGIN_NAMESPACE

DirectShowManager *DirectShowManager::_the = NULL;

VideoManager *DirectShowManager::the(void)
{
    if(_the == NULL)
        _the = new DirectShowManager;

    return _the;
}

VideoWrapperPtr DirectShowManager::createVideoWrapper(void) const
{
	return DirectShowVideoWrapper::create();
}

void DirectShowManager::init(int   argc, char *argv[])
{
    HRESULT hr;
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return;
    }
}

void DirectShowManager::exit(void)
{
    CoUninitialize();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

DirectShowManager::DirectShowManager(void)
{
}
    
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

DirectShowManager::~DirectShowManager(void)
{
}

OSG_END_NAMESPACE