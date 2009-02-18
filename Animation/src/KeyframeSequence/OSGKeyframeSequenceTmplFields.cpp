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

#define OSG_COMPILEKEYFRAMESEQUENCETMPLFIELDINST

#include "OSGKeyframeSequenceTmplFields.h"

#include <OpenSG/OSGMFieldTypeDef.inl>
#include <OpenSG/OSGSFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

// Doxygen can't find these
#ifndef OSG_DO_DOC

DataType FieldDataTraits<KeyframePositionsSequencePtr>::_type("KeyframePositionsSequencePtr",
                                                 "KeyframePositionsSequenceInterfacePtr");

DataType FieldDataTraits<KeyframeVectorsSequencePtr>::_type("KeyframeVectorsSequencePtr",
                                                 "KeyframeVectorsSequenceInterfacePtr");

DataType FieldDataTraits<KeyframeRotationsSequencePtr>::_type("KeyframeRotationsSequencePtr",
                                                 "KeyframeRotationsSequenceInterfacePtr");

DataType FieldDataTraits<KeyframeTransformationsSequencePtr>::_type("KeyframeTransformationsSequencePtr",
                                                 "KeyframeTransformationsSequenceInterfacePtr");

DataType FieldDataTraits<KeyframeColorsSequencePtr>::_type("KeyframeColorsSequencePtr",
                                                 "KeyframeColorsSequenceInterfacePtr");

DataType FieldDataTraits<KeyframeNumbersSequencePtr>::_type("KeyframeNumbersSequencePtr",
                                                 "KeyframeNumbersSequenceInterfacePtr");

DataType FieldDataTraits<KeyframeDiscreetSequencePtr>::_type("KeyframeDiscreetSequencePtr",
                                                 "KeyframeDiscreetSequenceInterfacePtr");

DataType FieldDataTraits<KeyframeFCPtrsSequencePtr>::_type("KeyframeFCPtrsSequencePtr",
                                                 "KeyframeFCPtrsSequenceInterfacePtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(KeyframePositionsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(KeyframeVectorsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(KeyframeRotationsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(KeyframeTransformationsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(KeyframeColorsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(KeyframeNumbersSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(KeyframeDiscreetSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(KeyframeFCPtrsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);

OSG_DLLEXPORT_MFIELD_DEF1(KeyframePositionsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(KeyframeVectorsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(KeyframeRotationsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(KeyframeTransformationsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(KeyframeColorsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(KeyframeNumbersSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(KeyframeDiscreetSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(KeyframeFCPtrsSequencePtr , OSG_ANIMATIONLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE
