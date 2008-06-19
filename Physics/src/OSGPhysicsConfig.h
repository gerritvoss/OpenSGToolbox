#ifndef _OSGPHYSICSDEF_H_
#define _OSGPHYSICSDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEPHYSICSLIB
#       define OSG_PHYSICSLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_PHYSICSLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_PHYSICSLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_PHYSICSLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_PHYSICSLIB_DLLMAPPING
#define OSG_PHYSICSLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGPHYSICSDEF_H_ */
