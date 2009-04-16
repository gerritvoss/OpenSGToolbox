#ifndef _OSGSOUNDDEF_H_
#define _OSGSOUNDDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILESOUNDLIB
#       define OSG_SOUNDLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_SOUNDLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_SOUNDLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_SOUNDLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_SOUNDLIB_DLLMAPPING
#define OSG_SOUNDLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGSOUNDDEF_H_ */
