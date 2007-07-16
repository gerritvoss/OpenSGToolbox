#ifndef _OSG_PARTICLE_SYSTEM_CONFIG_H_
#define _OSG_PARTICLE_SYSTEM_CONFIG_H_

/*
 * ----------------------------------------------------------------------------
 * DLL-related macros.  These are based on the macros used by NSPR.  Use
 * OSG_PARTICLE_SYSTEM_EXTERN for the prototype and OSG_PARTICLE_SYSTEM_IMPLEMENT for the implementation.
 * ----------------------------------------------------------------------------
 */
#ifdef WIN32

#   if defined(__GNUC__)
#       undef _declspec
#       define _declspec(x) __declspec(x)
#   endif

#   define OSG_PARTICLE_SYSTEM_EXPORT(__type)      _declspec(dllexport) __type
#   define OSG_PARTICLE_SYSTEM_EXPORT_CLASS        _declspec(dllexport)
#   define OSG_PARTICLE_SYSTEM_EXPORT_DATA(__type) _declspec(dllexport) __type
#   define OSG_PARTICLE_SYSTEM_IMPORT(__type)      _declspec(dllimport) __type
#   define OSG_PARTICLE_SYSTEM_IMPORT_DATA(__type) _declspec(dllimport) __type
#   define OSG_PARTICLE_SYSTEM_IMPORT_CLASS        _declspec(dllimport)

#   define OSG_PARTICLE_SYSTEM_EXTERN(__type)         extern _declspec(dllexport) __type
#   define OSG_PARTICLE_SYSTEM_IMPLEMENT(__type)      _declspec(dllexport) __type
#   define OSG_PARTICLE_SYSTEM_EXTERN_DATA(__type)    extern _declspec(dllexport) __type
#   define OSG_PARTICLE_SYSTEM_IMPLEMENT_DATA(__type) _declspec(dllexport) __type

#   define OSG_PARTICLE_SYSTEM_CALLBACK
#   define OSG_PARTICLE_SYSTEM_CALLBACK_DECL
#   define OSG_PARTICLE_SYSTEM_STATIC_CALLBACK(__x) static __x

#else   /* UNIX (where this stuff is simple!) */

#   define OSG_PARTICLE_SYSTEM_EXPORT(__type)      __type
#   define OSG_PARTICLE_SYSTEM_EXPORT_CLASS
#   define OSG_PARTICLE_SYSTEM_EXPORT_DATA(__type) __type
#   define OSG_PARTICLE_SYSTEM_IMPORT(__type)      __type
#   define OSG_PARTICLE_SYSTEM_IMPORT_CLASS
#   define OSG_PARTICLE_SYSTEM_IMPORT_DATA(__type) __type

#   define OSG_PARTICLE_SYSTEM_EXTERN(__type)         extern __type
#   define OSG_PARTICLE_SYSTEM_IMPLEMENT(__type)      __type
#   define OSG_PARTICLE_SYSTEM_EXTERN_DATA(__type)    extern __type
#   define OSG_PARTICLE_SYSTEM_IMPLEMENT_DATA(__type) __type

#   define OSG_PARTICLE_SYSTEM_CALLBACK
#   define OSG_PARTICLE_SYSTEM_CALLBACK_DECL
#   define OSG_PARTICLE_SYSTEM_STATIC_CALLBACK(__x) static __x

#endif	/* WIN32 */

#ifdef _OSG_PARTICLE_SYSTEM_BUILD_
#   define OSG_PARTICLE_SYSTEM_API(__type)	OSG_PARTICLE_SYSTEM_EXPORT(__type)
#   define OSG_PARTICLE_SYSTEM_CLASS_API		OSG_PARTICLE_SYSTEM_EXPORT_CLASS
#   define OSG_PARTICLE_SYSTEM_DATA_API(__type)	OSG_PARTICLE_SYSTEM_EXPORT_DATA(__type)
#else
#   define OSG_PARTICLE_SYSTEM_API(__type)	OSG_PARTICLE_SYSTEM_IMPORT(__type)
#   define OSG_PARTICLE_SYSTEM_CLASS_API		OSG_PARTICLE_SYSTEM_IMPORT_CLASS
#   define OSG_PARTICLE_SYSTEM_DATA_API(__type)	OSG_PARTICLE_SYSTEM_IMPORT_DATA(__type)
#endif

#endif   /* _OSG_PARTICLE_SYSTEM_CONFIG_H_ */
