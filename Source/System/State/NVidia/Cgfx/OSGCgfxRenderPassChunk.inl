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


inline
const StateChunkClass *CgfxRenderPassChunk::getStaticClass(void)
{
    return &CgfxRenderPassChunk::_class;
}

inline
UInt32 CgfxRenderPassChunk::getStaticClassId(void)
{
    return getStaticClass()->getId();
}

inline
const CGtechnique CgfxRenderPassChunk::getCGTechnique()
{
	return _mTechnique;
}

inline
void CgfxRenderPassChunk::setCGTechnique(CGtechnique tech)
{
	_mTechnique = tech;
}

inline
void CgfxRenderPassChunk::setCGPass(CGpass renderPass)
{
	_mPass = renderPass;
}

inline
const CGpass CgfxRenderPassChunk::getCGPass(void)
{
	return _mPass;
}

inline
std::string CgfxRenderPassChunk::getPassName(void)
{
	return _mName;
}

inline
void CgfxRenderPassChunk::setPassName(std::string name)
{
	_mName = name;
}

inline
void CgfxRenderPassChunk::setCGEffect(CGeffect *effect)
{
	_mEffect = effect;
}

inline
void CgfxRenderPassChunk::setSemanticBitVector(OSG::BitVector bitVec)
{
	_mSemanticBV = bitVec;
}

OSG_END_NAMESPACE
