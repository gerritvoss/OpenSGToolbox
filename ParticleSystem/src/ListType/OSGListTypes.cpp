
// Source file for new Field type

// This define is only set in this source file. It switches the
// Windows-specific declarations in the header for compiling the Field, 
// not for using it.
#define OSG_COMPILEPARTICLESYSTEMINST

#include "OSGParticleSystemDef.h"

// You need this in every OpenSG file
#include <OpenSG/OSGConfig.h>

// Some basic system headers
#include <OpenSG/OSGBaseTypes.h>

// The new field type include
#include "OSGListTypes.h"

// Needed to instantiate some template functions on Windows
#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

// This is where the DataType for the new Fieldtype is defined.
// The parameters are the name of the type and the name of the parent type
DataType FieldDataTraits<Vec3fList>::_type("Vec3fList", "BaseType");
DataType FieldDataTraits<Pnt3fList>::_type("Pnt3fList", "BaseType");
DataType FieldDataTraits<Color4fList>::_type("Color4fList", "BaseType");
DataType FieldDataTraits<Real32List>::_type("Real32List", "BaseType");
DataType FieldDataTraits<UInt64List>::_type("UInt64List", "BaseType");

// These macros instantiate the necessary template methods for the fields
OSG_DLLEXPORT_SFIELD_DEF1(Vec3fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING );
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING );
OSG_DLLEXPORT_SFIELD_DEF1(Color4fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING );
OSG_DLLEXPORT_SFIELD_DEF1(Real32List, OSG_PARTICLESYSTEMLIB_DLLMAPPING );
OSG_DLLEXPORT_SFIELD_DEF1(UInt64List, OSG_PARTICLESYSTEMLIB_DLLMAPPING );

OSG_DLLEXPORT_MFIELD_DEF1(Vec3fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING );
OSG_DLLEXPORT_MFIELD_DEF1(Pnt3fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING );
OSG_DLLEXPORT_MFIELD_DEF1(Color4fList, OSG_PARTICLESYSTEMLIB_DLLMAPPING );
OSG_DLLEXPORT_MFIELD_DEF1(Real32List, OSG_PARTICLESYSTEMLIB_DLLMAPPING );
OSG_DLLEXPORT_MFIELD_DEF1(UInt64List, OSG_PARTICLESYSTEMLIB_DLLMAPPING );

OSG_END_NAMESPACE


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

OSG_USING_NAMESPACE

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGLISGTYPES_HEADER_CVSID;
}

