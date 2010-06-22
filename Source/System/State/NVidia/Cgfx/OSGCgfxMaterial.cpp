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

		// determining which matricies need to be updated when then chunks are activated
		setSemanticParameters(getEffectMatrixDependencies());

		CGpass newPass = cgGetFirstPass(newTechnique);
		int count(0);
		while(newPass)
		{	// creating new render pass chunk 
			CgfxRenderPassChunkUnrecPtr pass = OSG::CgfxRenderPassChunk::create();

			pass->setCGPass(newPass);
			
			const char* name = cgGetPassName(newPass);
			// passes aren't required to have names for the pass, so we give them one if it doesn't have one
			if(!name)
			{
				std::stringstream converter;
				converter << "Pass" << count;
				pass->setPassName(converter.str());
			}
			else
			{
				pass->setPassName(std::string(name));
			}

			pass->setCGTechnique(newTechnique);
			pass->setCGEffect(&_mCGeffect);
			pass->setSemanticParameters(this->getSemanticParameters());



			// passing chunk to a state
			StateUnrecPtr newState = OSG::State::create();
			
			newState->addChunk(pass);


			addPassState(newState);
			



			newPass = cgGetNextPass(newPass);
			count++;
		}
	}
	else
	{
		SWARNING << "No valid technique available for " << _mEffectFile << ". Material will be set to default." << std::endl;
	}
}


UInt32 CgfxMaterial::getEffectMatrixDependencies(void)
{
	UInt32 matBV = 0;

	CGparameter tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "ModelViewProjection");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_MODELVIEWPROJECTION_PARAMETER ));
	
	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "ModelView");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_MODELVIEW_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "ModelInverseTranspose");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_MODELINVERSETRANSPOSE_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "ModelTranspose");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_MODELTRANSPOSE_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "WorldViewProjection");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_WORLDVIEWPROJECTION_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "World");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_WORLD_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "WorldInverseTranspose");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_WORLDINVERSETRANSPOSE_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "ViewInverse");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_VIEWINVERSE_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "View");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_VIEW_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "ViewTranspose");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_VIEWTRANSPOSE_PARAMETER));

	tstParam = cgGetEffectParameterBySemantic(_mCGeffect, "ViewInverseTranspose");
	if(tstParam) matBV = matBV | ((UInt32)(1 << CGFX_VIEWINVERSETRANSPOSE_PARAMETER));

	return matBV;
}

void CgfxMaterial::extractTextureAndSamplerData(CGpass pass)
{
	// we need each texture and sampler associated with this pass
	
	CGprogram theProgram = cgGetPassProgram(pass,CG_VERTEX_DOMAIN);

	CGparameter param = cgGetFirstParameter(theProgram,CG_GLOBAL); // only want global parameters? 
	while(param)
	{
		if(cgGetParameterClass(param) == CG_PARAMETERCLASS_SAMPLER)
		{
			CGstateassignment curState = cgGetFirstSamplerStateAssignment(param);
			while(curState)
			{
			


				curState = cgGetNextStateAssignment(curState);
			}

		}
		else if(cgGetParameterClass(param) == CG_PARAMETERCLASS_OBJECT)
		{

		}

		param = cgGetNextParameter(param);
	}

}

/*! Get number of parameters being used for this material */
Int32 CgfxMaterial::getNumParameters()
{
	Int32 count(0);

	CGparameter param = cgGetFirstEffectParameter(_mCGeffect);

	while(param)
	{
		count++;
		param = cgGetNextParameter(param);
	}
	return count;
}

//! Gets all of the names of the parameters for an effect
std::vector<std::string> CgfxMaterial::getParameterNames()
{
	std::vector<std::string> paramNames;
	CGparameter param = cgGetFirstEffectParameter(_mCGeffect);

	while(param)
	{
		paramNames.push_back(std::string(cgGetParameterName(param)));
		param = cgGetNextParameter(param);
	}

	return paramNames;
}

/*! Functions to retrieve parameters from the material */

Int32 CgfxMaterial::getParami(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Int32 val(0);
	cgGetParameterValueir(param,1,&val);

	return val;
}

Real32 CgfxMaterial::getParamf(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real32 val(0);
	cgGetParameterValuefr(param,1,&val);

	return val;
}

Real64 CgfxMaterial::getParamd(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real64  val;
	cgGetParameterValuedr(param,1,&val);

	return val;
}


OSG::Vec2f CgfxMaterial::getParam2f(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real32 vals[2];
	vals[0] = 0;
	vals[1] = 0;

	cgGetParameterValuefr(param,2,vals);
	return OSG::Vec2f(vals[0],vals[1]);
}

OSG::Vec3f CgfxMaterial::getParam3f(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real32 vals[3];
	for(int i(0); i < 3; ++i) vals[i] = 0.0;
	cgGetParameterValuefr(param,3,vals);
	return OSG::Vec3f(vals[0],vals[1],vals[2]);
}

OSG::Vec4f CgfxMaterial::getParam4f(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real32 vals[4];
	for(int i(0); i < 4; ++i) vals[i] = 0.0;
	cgGetParameterValuefr(param,4,vals);
	return OSG::Vec4f(vals[0],vals[1],vals[2],vals[3]);
}


OSG::Vec2d CgfxMaterial::getParam2d(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real64 vals[2];
	vals[0] = 0;
	vals[1] = 0;

	cgGetParameterValuedr(param,2,vals);
	return OSG::Vec2d(vals[0],vals[1]);
}

OSG::Vec3d CgfxMaterial::getParam3d(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real64 vals[3];
	for(int i(0); i < 3; ++i) vals[i] = 0.0;

	cgGetParameterValuedr(param,3,vals);
	return OSG::Vec3d(vals[0],vals[1],vals[2]);
}

OSG::Vec4d CgfxMaterial::getParam4d(std::string paramName)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real64 vals[4];
	for(int i(0); i < 4; ++i) vals[i] = 0.0;

	cgGetParameterValuedr(param,4,vals);
	return OSG::Vec4d(vals[0],vals[1],vals[2],vals[3]);
}


/*! Functions to set parameter values */
void CgfxMaterial::setParam(std::string paramName, Int32 val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter1i(param,val);
}

void CgfxMaterial::setParam(std::string paramName, Real32 val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter1f(param,val);
}

void CgfxMaterial::setParam(std::string paramName, Real64 val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter1d(param,val);
}

void CgfxMaterial::setParam(std::string paramName, Vec2f val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter2f(param,val.x(),val.y());
}	

void CgfxMaterial::setParam(std::string paramName, Vec3f val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter3f(param,val.x(),val.y(),val.z());
}

void CgfxMaterial::setParam(std::string paramName, Vec4f val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter4f(param,val.x(),val.y(),val.z(),val.w());
}

void CgfxMaterial::setParam(std::string paramName, Vec2d val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter2d(param,val.x(),val.y());	
}

void CgfxMaterial::setParam(std::string paramName, Vec3d val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter3d(param,val.x(),val.y(),val.z());
}

void CgfxMaterial::setParam(std::string paramName, Vec4d val)
{
	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	cgSetParameter4d(param,val.x(),val.y(),val.z(),val.w());
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
