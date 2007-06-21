#ifndef _OSG_USER_INTERFACE_CONFIG_H_
#define _OSG_USER_INTERFACE_CONFIG_H_

/*
 * ----------------------------------------------------------------------------
 * DLL-related macros.  These are based on the macros used by NSPR.  Use
 * OSG_USER_INTERFACE_EXTERN for the prototype and OSG_USER_INTERFACE_IMPLEMENT for the implementation.
 * ----------------------------------------------------------------------------
 */
#ifdef WIN32

#   if defined(__GNUC__)
#       undef _declspec
#       define _declspec(x) __declspec(x)
#   endif

#   define OSG_USER_INTERFACE_EXPORT(__type)      _declspec(dllexport) __type
#   define OSG_USER_INTERFACE_EXPORT_CLASS        _declspec(dllexport)
#   define OSG_USER_INTERFACE_EXPORT_FUNC        _declspec(dllexport)
#   define OSG_USER_INTERFACE_EXPORT_DATA(__type) _declspec(dllexport) __type
#   define OSG_USER_INTERFACE_IMPORT(__type)      _declspec(dllimport) __type
#   define OSG_USER_INTERFACE_IMPORT_DATA(__type) _declspec(dllimport) __type
#   define OSG_USER_INTERFACE_IMPORT_CLASS        _declspec(dllimport)
#   define OSG_USER_INTERFACE_IMPORT_FUNC        _declspec(dllimport)

#   define OSG_USER_INTERFACE_EXTERN(__type)         extern _declspec(dllexport) __type
#   define OSG_USER_INTERFACE_IMPLEMENT(__type)      _declspec(dllexport) __type
#   define OSG_USER_INTERFACE_EXTERN_DATA(__type)    extern _declspec(dllexport) __type
#   define OSG_USER_INTERFACE_IMPLEMENT_DATA(__type) _declspec(dllexport) __type

#   define OSG_USER_INTERFACE_CALLBACK
#   define OSG_USER_INTERFACE_CALLBACK_DECL
#   define OSG_USER_INTERFACE_STATIC_CALLBACK(__x) static __x

#else   /* UNIX (where this stuff is simple!) */

#   define OSG_USER_INTERFACE_EXPORT(__type)      __type
#   define OSG_USER_INTERFACE_EXPORT_CLASS
#   define OSG_USER_INTERFACE_EXPORT_FUNC
#   define OSG_USER_INTERFACE_EXPORT_DATA(__type) __type
#   define OSG_USER_INTERFACE_IMPORT(__type)      __type
#   define OSG_USER_INTERFACE_IMPORT_CLASS
#   define OSG_USER_INTERFACE_IMPORT_FUNC
#   define OSG_USER_INTERFACE_IMPORT_DATA(__type) __type

#   define OSG_USER_INTERFACE_EXTERN(__type)         extern __type
#   define OSG_USER_INTERFACE_IMPLEMENT(__type)      __type
#   define OSG_USER_INTERFACE_EXTERN_DATA(__type)    extern __type
#   define OSG_USER_INTERFACE_IMPLEMENT_DATA(__type) __type

#   define OSG_USER_INTERFACE_CALLBACK
#   define OSG_USER_INTERFACE_CALLBACK_DECL
#   define OSG_USER_INTERFACE_STATIC_CALLBACK(__x) static __x

#endif	/* WIN32 */

#ifdef _OSG_USER_INTERFACE_BUILD_
#   define OSG_USER_INTERFACE_API(__type)	OSG_USER_INTERFACE_EXPORT(__type)
#   define OSG_USER_INTERFACE_CLASS_API		OSG_USER_INTERFACE_EXPORT_CLASS
#   define OSG_USER_INTERFACE_FUNC_API		OSG_USER_INTERFACE_EXPORT_FUNC
#   define OSG_USER_INTERFACE_DATA_API(__type)	OSG_USER_INTERFACE_EXPORT_DATA(__type)
#else
#   define OSG_USER_INTERFACE_API(__type)	OSG_USER_INTERFACE_IMPORT(__type)
#   define OSG_USER_INTERFACE_CLASS_API		OSG_USER_INTERFACE_IMPORT_CLASS
#   define OSG_USER_INTERFACE_FUNC_API		OSG_USER_INTERFACE_IMPORT_FUNC
#   define OSG_USER_INTERFACE_DATA_API(__type)	OSG_USER_INTERFACE_IMPORT_DATA(__type)
#endif

#endif   /* _OSG_USER_INTERFACE_CONFIG_H_ */
