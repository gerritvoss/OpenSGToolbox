#ifndef _OSGGAMEDEF_H_
#define _OSGGAMEDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEGAMELIB
#       define OSG_GAMELIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_GAMELIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_GAMELIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_GAMELIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_GAMELIB_DLLMAPPING
#define OSG_GAMELIB_DLLTMPLMAPPING
#endif

#endif /* _OSGGAMEDEF_H_ */
