/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGANIMATIONDEF_H_
#define _OSGANIMATIONDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEANIMATIONLIB
#       define OSG_ANIMATIONLIB_DLLMAPPING     __declspec(dllexport)
#       define OSG_ANIMATIONLIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_ANIMATIONLIB_DLLMAPPING     __declspec(dllimport)
#       define OSG_ANIMATIONLIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_ANIMATIONLIB_DLLMAPPING
#define OSG_ANIMATIONLIB_DLLTMPLMAPPING
#endif

#ifdef WIN32
#ifdef OSG_WIN32_ICL
#define  OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractKeyframeSequenceTmpl< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0);                                                         \
                                                                    \
template DLLMAPPING                                                 \
FieldContainerType &AbstractKeyframeSequenceTmpl< T1 >::getClassType(void);  \
                                                                    \
template DLLMAPPING                                                 \
UInt32 AbstractKeyframeSequenceTmpl< T1 >::getClassTypeId(void);             \
                                                                    \
template DLLMAPPING                                                 \
FieldContainerType &AbstractKeyframeSequenceTmpl< T1 >::getType(void);       \
template DLLMAPPING                                                 \
const FieldContainerType &AbstractKeyframeSequenceTmpl< T1 >::getType(void) const


#define  OSG_KEYFRAMEPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType KeyframeSequenceTmpl< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &KeyframeSequenceTmpl< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *));                              \
                                                              \
template DLLMAPPING                                           \
FieldContainerType &KeyframeSequenceTmpl< T1 >::getClassType(void);    \
                                                              \
template DLLMAPPING                                           \
UInt32 KeyframeSequenceTmpl< T1 >::getClassTypeId(void);               \
                                                              \
template DLLMAPPING                                           \
FieldContainerType &KeyframeSequenceTmpl< T1 >::getType(void);         \
template DLLMAPPING                                           \
const FieldContainerType &KeyframeSequenceTmpl< T1 >::getType(void) const
#else
#define  OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractKeyframeSequenceTmpl< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0);                                                         \
                                                                    \
template class DLLMAPPING AbstractKeyframeSequenceTmpl< T1 >

#define  OSG_KEYFRAMEPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType KeyframeSequenceTmpl< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &KeyframeSequenceTmpl< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *));                              \
                                                              \
template class DLLMAPPING KeyframeSequenceTmpl< T1 >
#endif
#else
#define  OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractKeyframeSequenceTmpl< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0)

#define  OSG_KEYFRAMEPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType KeyframeSequenceTmpl< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &KeyframeSequenceTmpl< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *))
#endif

#endif /* _OSGANIMATIONDEF_H_ */

