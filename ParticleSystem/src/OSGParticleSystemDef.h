#ifndef _OSGPARTICLESYSTEMDEF_H_
#define _OSGPARTICLESYSTEMDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEPARTICLESYSTEMLIB
#       define OSG_PARTICLESYSTEMLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_PARTICLESYSTEMLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_PARTICLESYSTEMLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_PARTICLESYSTEMLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_PARTICLESYSTEMLIB_DLLMAPPING
#define OSG_PARTICLESYSTEMLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGPARTICLESYSTEMDEF_H_ */

