#ifndef _OSGTOOLBOXDEF_H_
#define _OSGTOOLBOXDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILETOOLBOXLIB
#       define OSG_TOOLBOXLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_TOOLBOXLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_TOOLBOXLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_TOOLBOXLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_TOOLBOXLIB_DLLMAPPING
#define OSG_TOOLBOXLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGTOOLBOXDEF_H_ */