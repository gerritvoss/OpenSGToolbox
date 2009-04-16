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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

#define OSG_COMPILEKEYFRAMESEQUENCETMPLINST

#include "OSGKeyframeSequenceTmplBase.h"

OSG_USING_NAMESPACE

OSG_GEO_PROP_TYPE_TMPL_DEF(AbstractKeyframeSequenceTmpl, KeyframeSequenceDesc, PtrType)

OSG_BEGIN_NAMESPACE

OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(AbstractKeyframeSequenceTmpl, 
                                KeyframePositionsSequenceDesc, 
                                OSG_ANIMATIONLIB_DLLMAPPING);
OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(AbstractKeyframeSequenceTmpl, 
                                KeyframeVectorsSequenceDesc, 
                                OSG_ANIMATIONLIB_DLLMAPPING);
OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(AbstractKeyframeSequenceTmpl, 
                                KeyframeRotationsSequenceDesc, 
                                OSG_ANIMATIONLIB_DLLMAPPING);
OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(AbstractKeyframeSequenceTmpl, 
                                KeyframeTransformationsSequenceDesc, 
                                OSG_ANIMATIONLIB_DLLMAPPING);
OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(AbstractKeyframeSequenceTmpl, 
                                KeyframeColorsSequenceDesc, 
                                OSG_ANIMATIONLIB_DLLMAPPING);
OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(AbstractKeyframeSequenceTmpl, 
                                KeyframeNumbersSequenceDesc, 
                                OSG_ANIMATIONLIB_DLLMAPPING);
OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(AbstractKeyframeSequenceTmpl, 
                                KeyframeDiscreetSequenceDesc, 
                                OSG_ANIMATIONLIB_DLLMAPPING);
OSG_ABSTR_KEYFRAMEPROP_DLLEXPORT_DEF(AbstractKeyframeSequenceTmpl, 
                                KeyframeFCPtrsSequenceDesc, 
                                OSG_ANIMATIONLIB_DLLMAPPING);

OSG_END_NAMESPACE
