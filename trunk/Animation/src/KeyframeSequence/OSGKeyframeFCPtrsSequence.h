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

#ifndef _OSGKEYFRAME_FCPTRS_SEQUENCE_H_
#define _OSGKEYFRAME_FCPTRS_SEQUENCE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGKeyframeSequenceTmplBase.h"
#include "OSGKeyframeSequenceTmplFields.h"

#include <OpenSG/OSGTextureChunk.h>

OSG_BEGIN_NAMESPACE

//TextureChunk Replace
template<>
bool OSG_ANIMATIONLIB_DLLMAPPING replacement<SFTextureChunkPtr>(RawInterpFuncion& InterpFunc,
                              const osg::Real32& time,
                              const osg::Real32& prevtime,
                              const osg::ValueReplacementPolicy& ReplacePolicy,
                              bool isCyclic,
                              osg::Field& Result,
                              UInt32 Index, 
                              Real32 Blend);

struct KeyframeFCPtrsSequenceTextureChunkDesc : public KeyframeFCPtrsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeFCPtrsSequenceTextureChunk";         }
    static const Char8 *getClassName(void) { return "KeyframeFCPtrsSequenceTextureChunkProperty"; }
    static const Char8 *getFieldName(void) { return "textures";              }
    static const Char8 *getGroupName(void) { return "KeyframeFCPtrsSequence";           }
    static bool isBlendable(void) { return false;           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeFCPtrsSequence               Inherited;
    typedef KeyframeFCPtrsSequence::PtrType      InheritedPtr;

    typedef KeyframeFCPtrsSequenceDesc   InheritedDesc;

    typedef MFTextureChunkPtr                    StoredFieldType;
    typedef SFTextureChunkPtr                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return NULL;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return NULL;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc> KeyframeFCPtrsSequenceTextureChunk;
#endif

#if !defined(OSG_COMPILEKEYFRAMEFCPTRSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeFCPtrsSequenceTextureChunkDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif
                      
//StateChunk Replace
template<>
bool OSG_ANIMATIONLIB_DLLMAPPING replacement<SFStateChunkPtr>(RawInterpFuncion& InterpFunc,
                              const osg::Real32& time,
                              const osg::Real32& prevtime,
                              const osg::ValueReplacementPolicy& ReplacePolicy,
                              bool isCyclic,
                              osg::Field& Result,
                              UInt32 Index, 
                              Real32 Blend);

struct KeyframeFCPtrsSequenceStateChunkDesc : public KeyframeFCPtrsSequenceDesc
{
    static FieldDescription *_desc[];

    /*---------------------------------------------------------------------*/
    static const Char8 *getTypeName (void) { return "KeyframeFCPtrsSequenceStateChunk";         }
    static const Char8 *getClassName(void) { return "KeyframeFCPtrsSequenceStateChunkProperty"; }
    static const Char8 *getFieldName(void) { return "chunks";              }
    static const Char8 *getGroupName(void) { return "KeyframeFCPtrsSequence";           }
    static bool isBlendable(void) { return false;           }
    static InitContainerF     getInitMethod(void) { return NULL; }

    static FieldDescription **getDesc      (void) { return _desc;           }


    /*---------------------------------------------------------------------*/
    typedef KeyframeFCPtrsSequence               Inherited;
    typedef KeyframeFCPtrsSequence::PtrType      InheritedPtr;

    typedef KeyframeFCPtrsSequenceDesc   InheritedDesc;

    typedef MFStateChunkPtr                    StoredFieldType;
    typedef SFStateChunkPtr                    SingleFieldType;
    typedef InheritedDesc::GenericType GenericType;
    
    typedef boost::function<bool (const StoredFieldType&, const MFReal32&, const Real32&, Field& , bool )> ConcreteInterpFunction;

    /*---------------------------------------------------------------------*/
     
    static ConcreteInterpFunction getStepConcreteInterpFuncion(void) {return stepKeyframeSequence<StoredFieldType,SingleFieldType>;}
    static ConcreteInterpFunction getLinearConcreteInterpFuncion(void) {return NULL;}
    static ConcreteInterpFunction getCubicConcreteInterpFuncion(void) {return NULL;}
    static ConcreteInterpFunction getLinearNormalConcreteInterpFuncion(void) {return NULL;}
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc> KeyframeFCPtrsSequenceStateChunk;
#endif

#if !defined(OSG_COMPILEKEYFRAMEFCPTRSEQUENCEINST) && !defined(OSG_DO_DOC)
OSG_FC_DLLEXPORT_DECL(KeyframeSequenceTmpl,
                      KeyframeFCPtrsSequenceStateChunkDesc,
                      OSG_ANIMATIONLIB_DLLMAPPING)
#endif
OSG_END_NAMESPACE

#include "OSGKeyframeFCPtrsSequence.inl"

#endif /* _OSGKEYFRAME_FCPTRS_SEQUENCE_H_ */

