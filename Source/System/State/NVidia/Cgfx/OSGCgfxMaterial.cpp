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
#include <iostream>

#include <OSGConfig.h>

#include "OSGCgfxRenderPassChunk.h"
#include "OSGState.h"

#include "OSGCgfxMaterial.h"

OSG_BEGIN_NAMESPACE

// CGcontext to be used by all Cgfx materials
CGcontext CgfxMaterial::_mCGcontext;

// Documentation for this class is emitted in the
// OSGCgfxMaterialBase.cpp file.
// To modify it, please change the .fcd file (OSGCgfxMaterial.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/
bool CgfxMaterial::checkForCgError(const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);
	if (error != CG_NO_ERROR)
	{
		SWARNING << "CgfxMaterial Cgfx Error: " << situation << ": " << string << std::endl;
		if (error == CG_COMPILER_ERROR)
		{
			SWARNING << cgGetLastListing(_mCGcontext) << std::endl;
		}
		return true;
	}
	return false;
}
void CgfxMaterial::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


PrimeMaterial *CgfxMaterial::finalize(MaterialMapKey oKey)
{
	return this;
}

void CgfxMaterial::rebuildState(void ) 
{
}

State  *CgfxMaterial::getState(UInt32 index)
{

	return getRenderPassStates(index);
} 


UInt32  CgfxMaterial::getNPasses(void )
{
	if(_mRebuildFromString)
	{	

		_mCGcontext = cgCreateContext();
		if(!checkForCgError("Creating Cg Context"))
		{
			cgGLRegisterStates(_mCGcontext);
			cgGLSetManageTextureParameters(_mCGcontext, CG_FALSE);
			if(!checkForCgError("Registering GL States"))
			{
			
				_mCGeffect = cgCreateEffectFromFile(_mCGcontext, _mEffectFile.c_str(), _mArgHolder);
				if(!checkForCgError("Creating Cg Effect") && _mCGeffect)
				{
					initializeStates();

					_mRebuildFromString = false;
				}
			}
		}
	}
	return getMFRenderPassStates()->size();
}

bool CgfxMaterial::isTransparent(void) const
{
	return true;
}

bool CgfxMaterial::initFromFile(const char* filename, const char** args)
{
	bool DeferLoading(false);
	_mEffectFile = std::string(filename);

	// make the context
	//_mCGcontext = cgCreateContext();
	//if(!checkForCgError("Creating Cg Context"))
	//{
	//	// attempt to create the effect
	//	_mCGeffect = cgCreateEffectFromFile(_mCGcontext, filename, args); 
	//	if(!checkForCgError("Loading Cgfx Effect from file"))
	//	{
	//		initializeStates();
	//	}
	//	else
	//	{
	//		DeferLoading = true;
	//	}
	//}
	//else
	//{
		DeferLoading = true;
	//}


	if(DeferLoading) //if(!cgIsContext(_mCGcontext))
	{	// error caused by invalid context (probably because the window is not initialized yet)
		_mRebuildFromString = true;
		
	} 
	//else
	//{
	//	SWARNING << "Error reading " << filename << " : File is not valid" << std::endl;
	//}

	return !DeferLoading;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void CgfxMaterial::initializeStates(void)
{
	// initialize chunks/states if effect creation was sucessful
	CGtechnique newTechnique = cgGetFirstTechnique(_mCGeffect);
	// find valid technique
	while (newTechnique && cgValidateTechnique(newTechnique) == CG_FALSE)  
	{
		SWARNING << "Technique "<< cgGetTechniqueName(newTechnique) << " did not validate. Skipping. " << std::endl;
		newTechnique = cgGetNextTechnique(newTechnique);
	}

	if(newTechnique)
	{
		SWARNING << "Using Technique "<< cgGetTechniqueName(newTechnique) <<"." << std::endl;

		CGpass newPass = cgGetFirstPass(newTechnique);
		while(newPass)
		{	// creating new render pass chunk 
			CgfxRenderPassChunkUnrecPtr pass = OSG::CgfxRenderPassChunk::create();
			pass->setCGPass(newPass);
			pass->setPassName(std::string(cgGetPassName(newPass)));
			pass->setCGTechnique(newTechnique);
			pass->setCGEffect(&_mCGeffect);
			// giving chunk to a state
			StateUnrecPtr newState = OSG::State::create();
			newState->addChunk(pass);
			addPassState(newState);

			newPass = cgGetNextPass(newPass);
		}
	}
	else
	{
		SWARNING << "No valid technique available for " << _mEffectFile << ". Material will be set to default." << std::endl;
	}
}


/*----------------------- constructors & destructors ----------------------*/

CgfxMaterial::CgfxMaterial(void) :
    Inherited(),
		_mArgHolder(NULL)
{
}

CgfxMaterial::CgfxMaterial(const CgfxMaterial &source) :
    Inherited(source),
		_mArgHolder(source._mArgHolder)
{
}

CgfxMaterial::~CgfxMaterial(void)
{
	cgDestroyEffect(_mCGeffect);
	// not sure if context should be destroyed or not... DG
    cgDestroyContext(_mCGcontext);
}

/*----------------------------- class specific ----------------------------*/

void CgfxMaterial::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CgfxMaterial::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CgfxMaterial NI" << std::endl;
}

OSG_END_NAMESPACE
