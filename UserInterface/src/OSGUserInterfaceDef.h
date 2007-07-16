#ifndef _OSGUSERINTERFACEDEF_H_
#define _OSGUSERINTERFACEDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEUSERINTERFACELIB
#       define OSG_USERINTERFACELIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_USERINTERFACELIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_USERINTERFACELIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_USERINTERFACELIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_USERINTERFACELIB_DLLMAPPING
#define OSG_USERINTERFACELIB_DLLTMPLMAPPING
#endif

#endif /* _OSGUSERINTERFACEDEF_H_ */