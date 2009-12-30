#ifndef _OSGLUADEF_H_
#define _OSGLUADEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILELUALIB
#       define OSG_LUALIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_LUALIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_LUALIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_LUALIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_LUALIB_DLLMAPPING
#define OSG_LUALIB_DLLTMPLMAPPING
#endif

#endif /* _OSGLUADEF_H_ */
