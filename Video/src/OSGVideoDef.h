#ifndef _OSGVIDEODEF_H_
#define _OSGVIDEODEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEVIDEOLIB
#       define OSG_VIDEOLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_VIDEOLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_VIDEOLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_VIDEOLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_VIDEOLIB_DLLMAPPING
#define OSG_VIDEOLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGVIDEODEF_H_ */

