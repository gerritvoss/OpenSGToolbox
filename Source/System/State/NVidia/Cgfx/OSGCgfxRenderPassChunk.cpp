/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGCgfxRenderPassChunk.h"
#include "OSGCgfxMaterial.h"
#include <OSGDrawEnv.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCgfxRenderPassChunkBase.cpp file.
// To modify it, please change the .fcd file (OSGCgfxRenderPassChunk.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

// Static StateChunk class, for implementing the getClass() method
StateChunkClass CgfxRenderPassChunk::_class("CgfxRenderPass",1);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CgfxRenderPassChunk::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *CgfxRenderPassChunk::getClass(void) const
{
    return &_class;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CgfxRenderPassChunk::CgfxRenderPassChunk(void) :
    Inherited()
{
}

CgfxRenderPassChunk::CgfxRenderPassChunk(const CgfxRenderPassChunk &source) :
    Inherited(source)
{
}

CgfxRenderPassChunk::~CgfxRenderPassChunk(void)
{
}


/*----------------------------- class specific ----------------------------*/


void CgfxRenderPassChunk::activate     (DrawEnv    *pEnv, 
										 UInt32      index)
{
	updateGLMatricies(pEnv);

	if(!_mPass)_mPass = cgGetNamedPass(_mTechnique,_mName.c_str());
	if(_mPass) cgSetPassState(_mPass);
}

void CgfxRenderPassChunk::changeFrom   (DrawEnv    *pEnv, 
									   StateChunk *pOld,
									   UInt32      index)
{
	if(pOld != this)
	{
		if(pOld->getClass() == CgfxRenderPassChunk::getClass())
		{
			CgfxRenderPassChunk* old = dynamic_cast<CgfxRenderPassChunk*>(pOld);
			cgResetPassState(old->getCGPass());
		}
		if(_mPass) cgSetPassState(_mPass);
	}
}

void CgfxRenderPassChunk::deactivate   (DrawEnv    *pEnv, 
										 UInt32      index)
{
	if(_mPass) cgResetPassState(_mPass);
}

void CgfxRenderPassChunk::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CgfxRenderPassChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CgfxRenderPassChunk NI" << std::endl;
}

void CgfxRenderPassChunk::updateGLMatricies(DrawEnv *pEnv)
{
	if( getSemanticParameters() & ((UInt32)(1 << CGFX_MODELVIEWPROJECTION_PARAMETER))) //ok
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "ModelViewProjection");
		OSG::Matrixr obj2World(pEnv->getObjectToWorld()),world2scrn(pEnv->getWorldToScreen());
		world2scrn.mult(obj2World);
		cgGLSetMatrixParameterfc(theMatrix,world2scrn.getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_MODELVIEW_PARAMETER))) //ok?
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "ModelView");
		OSG::Matrixr obj2World(pEnv->getObjectToWorld()),cameraViewing(pEnv->getCameraViewing());
		cameraViewing.mult(obj2World);
		cgGLSetMatrixParameterfc(theMatrix,cameraViewing.getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_MODELINVERSETRANSPOSE_PARAMETER))) //ok?
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "ModelInverseTranspose");
		OSG::Matrixr obj2World(pEnv->getObjectToWorld()),cameraViewing(pEnv->getCameraViewing());
		cameraViewing.mult(obj2World);
		cameraViewing.invert();
		cameraViewing.transpose();
		cgGLSetMatrixParameterfc(theMatrix,cameraViewing.getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_MODELTRANSPOSE_PARAMETER))) //ok?
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "ModelTranspose");
		OSG::Matrixr obj2World(pEnv->getObjectToWorld()),cameraViewing(pEnv->getCameraViewing());
		cameraViewing.mult(obj2World);
		cameraViewing.transpose();
		cgGLSetMatrixParameterfc(theMatrix,cameraViewing.getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_WORLDVIEWPROJECTION_PARAMETER))) // ok
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "WorldViewProjection");
		OSG::Matrixr obj2World(pEnv->getObjectToWorld()),world2scrn(pEnv->getWorldToScreen());
		world2scrn.mult(obj2World);
		cgGLSetMatrixParameterfc(theMatrix,world2scrn.getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_WORLD_PARAMETER))) //ok?
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "World");
		OSG::Matrixr obj2World(pEnv->getObjectToWorld()),cameraViewing(pEnv->getCameraViewing());
		cameraViewing.mult(obj2World);
		cgGLSetMatrixParameterfc(theMatrix,cameraViewing.getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_WORLDINVERSETRANSPOSE_PARAMETER))) //ok?
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "WorldInverseTranspose");
		OSG::Matrixr obj2World(pEnv->getObjectToWorld()),cameraViewing(pEnv->getCameraViewing());
		cameraViewing.mult(obj2World);
		cameraViewing.invert();
		cameraViewing.transpose();
		cgGLSetMatrixParameterfc(theMatrix,cameraViewing.getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_VIEWINVERSE_PARAMETER)))
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "ViewInverse");
		OSG::Matrixr cameraViewing(pEnv->getCameraViewing());
		cameraViewing.invert();
		cgGLSetMatrixParameterfc(theMatrix,cameraViewing.getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_VIEW_PARAMETER)))
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "View");
		cgGLSetMatrixParameterfc(theMatrix,pEnv->getCameraViewing().getValues());
	}

	if(getSemanticParameters() & ((UInt32)(1 << CGFX_VIEWINVERSETRANSPOSE_PARAMETER)))
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "ViewInverseTranspose");
		OSG::Matrixr cameraViewing(pEnv->getCameraViewing());
		cameraViewing.invert();
		cameraViewing.transpose();
		cgGLSetMatrixParameterfc(theMatrix,cameraViewing.getValues());
	}
    
	if(getSemanticParameters() & ((UInt32)(1 << CGFX_VIEWTRANSPOSE_PARAMETER)))
	{
		CGparameter theMatrix = cgGetEffectParameterBySemantic(*_mEffect, "ViewTranspose");
		OSG::Matrixr cameraViewing(pEnv->getCameraViewing());
		cameraViewing.transpose();
		cgGLSetMatrixParameterfc(theMatrix,cameraViewing.getValues());
	}

}

OSG_END_NAMESPACE
