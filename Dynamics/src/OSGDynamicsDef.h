#ifndef _OSGDYNAMICSDEF_H_
#define _OSGDYNAMICSDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEDYNAMICSLIB
#       define OSG_DYNAMICSLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_DYNAMICSLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_DYNAMICSLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_DYNAMICSLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_DYNAMICSLIB_DLLMAPPING
#define OSG_DYNAMICSLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGDYNAMICSDEF_H_ */

