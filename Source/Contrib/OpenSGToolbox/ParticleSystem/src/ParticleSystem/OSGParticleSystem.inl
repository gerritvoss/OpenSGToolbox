/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   Authors: David Kabala, David Oluwatimi                                  *
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

OSG_BEGIN_NAMESPACE

inline 
bool ParticleSystem::GreaterThanUInt32::operator()(const UInt32 s1, const UInt32 s2) const
{
	return s1>s2;
}

inline
void ParticleSystem::setPosition(const Pnt3f& Pos, const UInt32& Index)
{
    getInternalPositions()[Index] = Pos;
}

inline
const Pnt3f& ParticleSystem::getPosition(const UInt32& Index) const
{
	return getInternalPositions()[Index];
}

inline
UInt32 ParticleSystem::getNumParticles(void) const
{
	return getInternalPositions().getSize();
}

inline
UInt32 ParticleSystem::getNumSecPositions(void) const
{
	return getInternalSecPositions().getSize();
}

inline
UInt32 ParticleSystem::getNumNormals(void) const
{
	return getInternalNormals().getSize();
}

inline
UInt32 ParticleSystem::getNumColors(void) const
{
	return getInternalColors().getSize();
}

inline
UInt32 ParticleSystem::getNumSizes(void) const
{
	return getInternalSizes().getSize();
}

inline
UInt32 ParticleSystem::getNumLifespans(void) const
{
	return getInternalLifespans().getSize();
}

inline
UInt32 ParticleSystem::getNumAges(void) const
{
	return getInternalAges().getSize();
}

inline
UInt32 ParticleSystem::getNumVelocities(void) const
{
	return getInternalVelocities().getSize();
}

inline
UInt32 ParticleSystem::getNumSecVelocities(void) const
{
	return getInternalSecVelocities().getSize();
}

inline
UInt32 ParticleSystem::getNumAccelerations(void) const
{
	return getInternalAccelerations().getSize();
}

inline
UInt32 ParticleSystem::getNumAttributes(void) const
{
	return getInternalAttributes().getSize();
}

inline
ParticleSystem::SystemUpdateListener::SystemUpdateListener(ParticleSystem* TheSystem) : _System(TheSystem)
{
}


inline
void ParticleSystem::attachUpdateProducer(EventProducerPtr TheProducer)
{
    if(_UpdateEventConnection.isConnected())
    {
        _UpdateEventConnection.disconnect();
    }
    _UpdateEventConnection = TheProducer->attachEventListener(this, "Update");
}

inline
void ParticleSystem::detachUpdateProducer(void)
{
    _UpdateEventConnection.disconnect();
}
OSG_END_NAMESPACE

