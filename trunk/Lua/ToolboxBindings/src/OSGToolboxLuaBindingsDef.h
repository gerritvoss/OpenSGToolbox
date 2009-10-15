#ifndef _OSGTOOLBOXLUABINDINGSDEF_H_
#define _OSGTOOLBOXLUABINDINGSDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILETOOLBOXLUABINDINGSLIB
#       define OSG_TOOLBOXLUABINDINGSLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_TOOLBOXLUABINDINGSLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_TOOLBOXLUABINDINGSLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_TOOLBOXLUABINDINGSLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_TOOLBOXLUABINDINGSLIB_DLLMAPPING
#define OSG_TOOLBOXLUABINDINGSLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGTOOLBOXLUABINDINGSDEF_H_ */
