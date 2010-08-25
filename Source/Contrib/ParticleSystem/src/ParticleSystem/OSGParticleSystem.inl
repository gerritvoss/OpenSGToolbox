/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
void ParticleSystem::detachUpdateProducer(void)
{
    _UpdateEventConnection.disconnect();
}

inline 
bool ParticleSystem::GreaterThanUInt32::operator()(const UInt32 s1, const UInt32 s2) const
{
	return s1>s2;
}

inline
void ParticleSystem::setPosition(const Pnt3f& Pos, const UInt32& Index)
{
    editInternalPositions(Index) = Pos;
}

inline
UInt32 ParticleSystem::getID(const UInt32& Index) const
{
	return getInternalIDs(Index);
}

inline
const Pnt3f& ParticleSystem::getPosition(const UInt32& Index) const
{
	return getInternalPositions(Index);
}

inline
UInt32 ParticleSystem::getNumParticles(void) const
{
	return getMFInternalPositions()->size();
}

inline
UInt32 ParticleSystem::getNumSecPositions(void) const
{
	return getMFInternalSecPositions()->size();
}

inline
UInt32 ParticleSystem::getNumNormals(void) const
{
	return getMFInternalNormals()->size();
}

inline
UInt32 ParticleSystem::getNumColors(void) const
{
	return getMFInternalColors()->size();
}

inline
UInt32 ParticleSystem::getNumSizes(void) const
{
	return getMFInternalSizes()->size();
}

inline
UInt32 ParticleSystem::getNumLifespans(void) const
{
	return getMFInternalLifespans()->size();
}

inline
UInt32 ParticleSystem::getNumAges(void) const
{
	return getMFInternalAges()->size();
}

inline
UInt32 ParticleSystem::getNumVelocities(void) const
{
	return getMFInternalVelocities()->size();
}

inline
UInt32 ParticleSystem::getNumSecVelocities(void) const
{
	return getMFInternalSecVelocities()->size();
}

inline
UInt32 ParticleSystem::getNumAccelerations(void) const
{
	return getMFInternalAccelerations()->size();
}

inline
UInt32 ParticleSystem::getNumAttributes(void) const
{
	return getMFInternalAttributes()->size();
}

inline
bool ParticleSystem::isUpdating(void) const
{
    return _isUpdating;
}

OSG_END_NAMESPACE
