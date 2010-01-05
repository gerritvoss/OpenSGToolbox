/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

template<UInt8 Rows, UInt8 Cols> inline
OSG::Matrix4f CgfxMaterial::getParamMatrixf(std::string paramName)
{
	// make sure the template parameters are the right size

	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real32 vals[Rows*Cols];

	cgGetParameterValuefc(param,Rows*Cols,vals);

	OSG::Matrix4f Result;
	for(UInt8 i(0) ; i<Rows && i < 4; ++i)
	{
		for(UInt8 j(0) ; j<Cols && j < 4; ++j)
		{
			Result[i][j] = vals[i*Cols + j];
		}
	}
	return Result;
}

template<UInt8 Rows, UInt8 Cols> inline
OSG::Matrix4d CgfxMaterial::getParamMatrixd(std::string paramName)
{
	// make sure the template parameters are the right size

	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();
	Real64 vals[Rows*Cols];

	cgGetParameterValuedc(param,Rows*Cols,vals);

	OSG::Matrix4f Result;
	for(UInt8 i(0) ; i<Rows && i < 4; ++i)
	{
		for(UInt8 j(0) ; j<Cols && j < 4; ++j)
		{
			Result[i][j] = vals[i*Cols + j];
		}
	}
	return Result;
}

template<UInt8 Rows, UInt8 Cols>
void CgfxMaterial::setParamMatrixf(std::string paramName, Matrix4f val)
{
	// make sure the template parameters are the right size


	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();

	Real32 newVals[Rows*Cols];
	
	for(UInt8 i(0) ; i<Rows && i < 4; ++i)
	{
		for(UInt8 j(0) ; j<Cols && j < 4; ++j)
		{
			newVals[i*Cols + j] = val[i][j];
		}
	}

	//Values were accessed in row major order
	cgSetMatrixParameterfr(param,newVals);
}

template<UInt8 Rows, UInt8 Cols>
void CgfxMaterial::setParamMatrixd(std::string paramName, Matrix4d val)
{
	// make sure the template parameters are the right size

	CGparameter param = cgGetNamedEffectParameter(_mCGeffect, paramName.c_str());
	if(!(param)) throw UndefinedParameterException();

	Real64 newVals[Rows*Cols];
	
	for(UInt8 i(0) ; i<Rows && i < 4; ++i)
	{
		for(UInt8 j(0) ; j<Cols && j < 4; ++j)
		{
			newVals[i*Cols + j] = vals[i][j];
		}
	}

	//Values were accessed in row major order
	cgSetMatrixParameterdr(param,newVals);
}

OSG_END_NAMESPACE
