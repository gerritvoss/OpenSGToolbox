
#ifndef _OSGSFBASELISTTYPES_H_
#define _OSGSFBASELISTTYPES_H_

#define OSG_COMPILEFIELDINST
#ifdef __sgi
#pragma once
#endif

#include "VSEConfig.h"
#include <list>
#include "OSGBaseListTypes.h"
#include "OSGListFieldDataType.h"

OSG_BEGIN_NAMESPACE


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField< Vec3fList > SFVec3fList;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Vec3fList, VSE_CLASS_API)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField< Pnt3fList > SFPnt3fList;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Pnt3fList, VSE_CLASS_API)
#endif
      
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField< Color4fList > SFColor4fList;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Color4fList, VSE_CLASS_API)
#endif
      
#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField< Real32List > SFReal32List;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, Real32List, VSE_CLASS_API)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpBaseFieldSingle */

typedef SField< UInt64List > SFUInt64List;
#endif

#ifndef OSG_COMPILEFIELDINST
OSG_DLLEXPORT_DECL1(SField, UInt64List, VSE_CLASS_API)
#endif

OSG_END_NAMESPACE

#endif /* _OSGSFBASELISTTYPES_H_ */
