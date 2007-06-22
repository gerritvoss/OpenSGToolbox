#ifndef _OSG_TOOLBOX_CONFIG_H_
#define _OSG_TOOLBOX_CONFIG_H_

/*
 * ----------------------------------------------------------------------------
 * DLL-related macros.  These are based on the macros used by NSPR.  Use
 * OSG_TOOLBOX_EXTERN for the prototype and OSG_TOOLBOX_IMPLEMENT for the implementation.
 * ----------------------------------------------------------------------------
 */
#ifdef WIN32

#   if defined(__GNUC__)
#       undef _declspec
#       define _declspec(x) __declspec(x)
#   endif

#   define OSG_TOOLBOX_EXPORT(__type)      _declspec(dllexport) __type
#   define OSG_TOOLBOX_EXPORT_CLASS        _declspec(dllexport)
#   define OSG_TOOLBOX_EXPORT_FUNC        _declspec(dllexport)
#   define OSG_TOOLBOX_EXPORT_DATA(__type) _declspec(dllexport) __type
#   define OSG_TOOLBOX_IMPORT(__type)      _declspec(dllimport) __type
#   define OSG_TOOLBOX_IMPORT_DATA(__type) _declspec(dllimport) __type
#   define OSG_TOOLBOX_IMPORT_CLASS        _declspec(dllimport)
#   define OSG_TOOLBOX_IMPORT_FUNC        _declspec(dllimport)

#   define OSG_TOOLBOX_EXTERN(__type)         extern _declspec(dllexport) __type
#   define OSG_TOOLBOX_IMPLEMENT(__type)      _declspec(dllexport) __type
#   define OSG_TOOLBOX_EXTERN_DATA(__type)    extern _declspec(dllexport) __type
#   define OSG_TOOLBOX_IMPLEMENT_DATA(__type) _declspec(dllexport) __type

#   define OSG_TOOLBOX_CALLBACK
#   define OSG_TOOLBOX_CALLBACK_DECL
#   define OSG_TOOLBOX_STATIC_CALLBACK(__x) static __x

#else   /* UNIX (where this stuff is simple!) */

#   define OSG_TOOLBOX_EXPORT(__type)      __type
#   define OSG_TOOLBOX_EXPORT_CLASS
#   define OSG_TOOLBOX_EXPORT_FUNC
#   define OSG_TOOLBOX_EXPORT_DATA(__type) __type
#   define OSG_TOOLBOX_IMPORT(__type)      __type
#   define OSG_TOOLBOX_IMPORT_CLASS
#   define OSG_TOOLBOX_IMPORT_FUNC
#   define OSG_TOOLBOX_IMPORT_DATA(__type) __type

#   define OSG_TOOLBOX_EXTERN(__type)         extern __type
#   define OSG_TOOLBOX_IMPLEMENT(__type)      __type
#   define OSG_TOOLBOX_EXTERN_DATA(__type)    extern __type
#   define OSG_TOOLBOX_IMPLEMENT_DATA(__type) __type

#   define OSG_TOOLBOX_CALLBACK
#   define OSG_TOOLBOX_CALLBACK_DECL
#   define OSG_TOOLBOX_STATIC_CALLBACK(__x) static __x

#endif	/* WIN32 */

#ifdef _OSG_TOOLBOX_BUILD_
#   define OSG_TOOLBOX_API(__type)	OSG_TOOLBOX_EXPORT(__type)
#   define OSG_TOOLBOX_CLASS_API		OSG_TOOLBOX_EXPORT_CLASS
#   define OSG_TOOLBOX_FUNC_API		OSG_TOOLBOX_EXPORT_FUNC
#   define OSG_TOOLBOX_DATA_API(__type)	OSG_TOOLBOX_EXPORT_DATA(__type)
#else
#   define OSG_TOOLBOX_API(__type)	OSG_TOOLBOX_IMPORT(__type)
#   define OSG_TOOLBOX_CLASS_API		OSG_TOOLBOX_IMPORT_CLASS
#   define OSG_TOOLBOX_FUNC_API		OSG_TOOLBOX_IMPORT_FUNC
#   define OSG_TOOLBOX_DATA_API(__type)	OSG_TOOLBOX_IMPORT_DATA(__type)
#endif

#endif   /* _OSG_TOOLBOX_CONFIG_H_ */
