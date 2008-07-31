#include "OSGDirectShowManager.h"
#include <iostream>
#include <vector>

OSG_BEGIN_NAMESPACE

DirectShowManager *DirectShowManager::_the = NULL;

DirectShowManager *DirectShowManager::the(void)
{
    if(_the == NULL)
        _the = new DirectShowManager;

    return _the;
}

void DirectShowManager::init(int   argc, char *argv[])
{
	pGraph = NULL;
    pControl = NULL;
    pEvent = NULL;

    // Initialize the COM library.
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return;
    }

    // Create the filter graph manager and query for interfaces.
    /*hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                        IID_IGraphBuilder, (void **)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return;
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);*/
}

void DirectShowManager::exit(void)
{
    //pControl->Release();
    //pEvent->Release();
    //pGraph->Release();
    CoUninitialize();
}

void DirectShowManager::openVideo(std::string Path)
{
		gVideoCap.RenderFile(Path.c_str());
		gVideoCap.Play();
	//int charsToProduce = mbstowcs(NULL, Path.c_str(), 0) + 1; // note error return of -1 is possible
	//if (charsToProduce == 0) { /* handle error */ }
	//if (charsToProduce > ULONG_MAX/sizeof(wchar_t)) return error;
	/*wchar_t *destString = (wchar_t *)malloc( charsToProduce * sizeof(wchar_t) );

	//wchar_t *wsym = new wchar_t[Path.size()];
	mbstowcs(destString, Path.c_str(), Path.size());


    // Build the graph. IMPORTANT: Change this string to a file on your system.
    hr = pGraph->RenderFile(L"C:\\Test.avi", NULL);
    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            // Wait for completion.
            long evCode;
            pEvent->WaitForCompletion(INFINITE, &evCode);

            // Note: Do not use INFINITE in a real application, because it
            // can block indefinitely.
        }
    }
	else
	{
		//Failed to load file
		switch(hr)
		{
		case VFW_S_AUDIO_NOT_RENDERED:
			std::cout << "VFW_S_AUDIO_NOT_RENDERED"<< std::endl;
			break;
		case VFW_S_DUPLICATE_NAME:
			std::cout << "VFW_S_DUPLICATE_NAME"<< std::endl;
			break;
		case VFW_S_PARTIAL_RENDER:
			std::cout << "VFW_S_PARTIAL_RENDER"<< std::endl;
			break;
		case VFW_S_VIDEO_NOT_RENDERED:
			std::cout << "VFW_S_VIDEO_NOT_RENDERED"<< std::endl;
			break;
		case E_ABORT:
			std::cout << "E_ABORT"<< std::endl;
			break;
		case E_FAIL:
			std::cout << "E_FAIL"<< std::endl;
			break;
		case E_INVALIDARG:
			std::cout << "E_INVALIDARG"<< std::endl;
			break;
		case E_OUTOFMEMORY:
			std::cout << "E_OUTOFMEMORY"<< std::endl;
			break;
		case E_POINTER:
			std::cout << "E_POINTER"<< std::endl;
			break;
		case VFW_E_CANNOT_CONNECT:
			std::cout << "VFW_E_CANNOT_CONNECT"<< std::endl;
			break;
		case VFW_E_CANNOT_LOAD_SOURCE_FILTER:
			std::cout << "VFW_E_CANNOT_LOAD_SOURCE_FILTER"<< std::endl;
			break;
		case VFW_E_CANNOT_RENDER:
			std::cout << "VFW_E_CANNOT_RENDER"<< std::endl;
			break;
		case VFW_E_INVALID_FILE_FORMAT:
			std::cout << "VFW_E_INVALID_FILE_FORMAT"<< std::endl;
			break;
		case VFW_E_NOT_FOUND:
			std::cout << "VFW_E_NOT_FOUND"<< std::endl;
			break;
		case VFW_E_UNKNOWN_FILE_TYPE:
			std::cout << "VFW_E_UNKNOWN_FILE_TYPE"<< std::endl;
			break;
		case VFW_E_UNSUPPORTED_STREAM:
			std::cout << "VFW_E_UNSUPPORTED_STREAM"<< std::endl;
			break;
		}
	}*/

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