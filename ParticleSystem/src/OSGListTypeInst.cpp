#include "ParticleSystem/OSGParticleSystemConfig.h"

#include <OpenSG/OSGField.h>
#include <OpenSG/OSGSField.h>
#include "OSGSFBaseListTypes.h"


OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
DataType FieldDataTraits<Vec3fList >::_type("Vec3fList" , "BaseType");
DataType FieldDataTraits<Pnt3fList >::_type("Pnt3fList" , "BaseType");
DataType FieldDataTraits<Color4fList >::_type("Color4fList" , "BaseType");
DataType FieldDataTraits<Real32List >::_type("Real32List" , "BaseType");
DataType FieldDataTraits<UInt64List >::_type("UInt64List" , "BaseType");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(Vec3fList,  OSG_PARTICLE_SYSTEM_CLASS_API);
OSG_DLLEXPORT_SFIELD_DEF1(Pnt3fList,  OSG_PARTICLE_SYSTEM_CLASS_API);
OSG_DLLEXPORT_SFIELD_DEF1(Color4fList,  OSG_PARTICLE_SYSTEM_CLASS_API);
OSG_DLLEXPORT_SFIELD_DEF1(Real32List,  OSG_PARTICLE_SYSTEM_CLASS_API);
OSG_DLLEXPORT_SFIELD_DEF1(UInt64List,  OSG_PARTICLE_SYSTEM_CLASS_API);

OSG_END_NAMESPACE
