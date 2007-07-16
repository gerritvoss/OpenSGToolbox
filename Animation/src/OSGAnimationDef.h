#ifndef _OSGANIMATIONDEF_H_
#define _OSGANIMATIONDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEANIMATIONLIB
#       define OSG_ANIMATIONLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_ANIMATIONLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_ANIMATIONLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_ANIMATIONLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_ANIMATIONLIB_DLLMAPPING
#define OSG_ANIMATIONLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGANIMATIONDEF_H_ */