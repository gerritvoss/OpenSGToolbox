#ifndef _OSGINPUTDEF_H_
#define _OSGINPUTDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEINPUTLIB
#       define OSG_INPUTLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_INPUTLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_INPUTLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_INPUTLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_INPUTLIB_DLLMAPPING
#define OSG_INPUTLIB_DLLTMPLMAPPING
#endif

#endif /* _OSGINPUTDEF_H_ */